#include "rcbasic_edit_frame.h"

#include <wx/process.h>
#include <wx/txtstrm.h>
#include <wx/utils.h>

#include "rc_debugger_dialog.h"

void rcbasic_edit_frame::onBuildProcessTerminate( wxProcessEvent& event )
{
    //wxPuts(_("BUILD HAS FINISHED"));

    isBuilding = false;
    build_process->CloseOutput();

    wxTextInputStream build_stream(*build_process->GetInputStream());

    while(build_process->IsInputAvailable())
    {
        m_messageWindow_richText->AppendText(build_stream.ReadLine() + _("\n"));
    }

    wxKill(build_pid);
    if(build_process)
        delete build_process;
    build_process = NULL;

    wxFileName main_fname = build_run_project->getMainSource();
    wxFileName dbg_fname = build_run_project->getMainSource();

    bool isCurrentFileBuild = (build_run_project == current_file_project);

    build_run_project = NULL;

    bool build_success = true;

    main_fname.SetExt(_("cbc"));
    main_fname.MakeAbsolute();

    dbg_fname.SetFullName(_("debug.cbc"));
    dbg_fname.MakeAbsolute();

    if( (!main_fname.Exists()) && ( (!wxFileExists(dbg_fname.GetFullPath())) && isDebugging ) )
    {
        wxMessageBox(_("Main Source Target failed to build.\nCheck the build log for more details."));
        //wxMessageBox(_("FILEN NOT FOUND: ") + main_fname.GetFullPath());
        isBuildingAndRunning = false;
        build_success = false;
        isDebugging = false;
    }


    for(int i = 0; i < build_files.size(); i++)
    {
        wxFileName bf_fname(build_files[i]);
        bf_fname.SetExt("cbc");

        if(!bf_fname.Exists())
        {
            wxMessageBox(_("1 or more of this projects sub-targets failed to build.\nCheck the build log for more details."));
            isBuildingAndRunning = false;
            build_success = false;
            break;
        }
    }

    if(isBuildingAndRunning && build_success)
    {
        isBuildingAndRunning = false;
        if(isCurrentFileBuild)
            runCurrentFile();
        else
        {
            //wxMessageBox(_("Run Project: ") + main_fname.GetFullPath());
            runProject();
        }
    }

    if(isDebugging && build_success)
    {
        debugProject();
    }
    else if(isDebugging)
    {
        isDebugging = false;
    }

    //wxPuts(_("PROCESS is dead"));
}

void rcbasic_edit_frame::onRunProcessTerminate( wxProcessEvent& event )
{
    //wxPuts(_("RUN HAS FINISHED"));

    //wxMessageBox(_("terminated"));

    isRunning = false;
    isBuildingAndRunning = false;

    if(wxProcess::Exists(run_pid))
        wxKill(run_pid);

    if(run_process)
        delete run_process;
    run_process = NULL;
    build_run_project = NULL;

    //wxPuts(_("PROCESS is dead"));
}


void rcbasic_edit_frame::onBuildMenuSelect( wxCommandEvent& event )
{
    buildProject();
}

void rcbasic_edit_frame::buildProject(wxString build_flags)
{
    /*wxSetWorkingDirectory(rc_fnames[AuiNotebook1->GetPageIndex(t)].substr(0, rc_fnames[AuiNotebook1->GetPageIndex(t)].find_last_of("/")));
    wxString fs = rc_path + _("rcbasic_build ") + _("\"") + rc_fnames[AuiNotebook1->GetPageIndex(t)] + _("\"");

    int rt = -1;
    rt = wxExecute(fs, wxEXEC_SYNC);*/

    if(isBuilding || isRunning || isDebugging)
        return;


    if(build_process || run_process)
        return;

    if(!build_run_project)
    {
        if(!active_project)
        {
            wxMessageBox(_("No project has been selected"));
            return;
        }
        else
        {
            build_run_project = active_project;
            debug_project = build_run_project;
        }
    }
    else
        return;

    m_results_notebook->SetSelection(RESULTS_LISTBOX_BUILDMSG);


    notebook_mutex.Lock();


    //-----------
    wxFileName project_fname = wxFileName(build_run_project->getProjectFileLocation());

    if(!wxDirExists(build_run_project->getLocation()))
    {
        project_fname = openFileDialog(_("Save Project As"), _("RCBasic Project (*.rcprj)|*.rcprj"), wxFD_SAVE);
        if(project_fname.GetFullPath().compare(_(""))==0)
        {
            notebook_mutex.Unlock();
            return;
        }
    }

    //SAVE FILES IN PROJECT
    std::vector<rcbasic_project_node*> pf_nodes = build_run_project->getSourceFiles();
    for(int i = 0; i < open_files.size(); i++)
    {
        wxFileName o_fname = open_files[i]->getSourcePath();
        o_fname.MakeAbsolute();

        for(int p_file = 0; p_file < pf_nodes.size(); p_file++)
        {
            wxFileName p_fname = pf_nodes[p_file]->getPath();
            p_fname.MakeAbsolute();
            if(o_fname.GetFullPath().compare(p_fname.GetFullPath())==0)
            {
                //wxPuts(_("SAVING: ") + o_fname.GetFullPath());
                saveFile(i, 0);
            }
        }
    }

    build_files.clear();
    for(int p_file = 0; p_file < pf_nodes.size(); p_file++)
    {
        wxFileName p_fname = pf_nodes[p_file]->getPath();
        p_fname.MakeAbsolute();

        //wxPrintf(_("Target: ") + p_fname.GetFullName() + _(":--> %d\n"), pf_nodes[p_file]->getTargetFlag());

        if(pf_nodes[p_file]->getTargetFlag())
        {
            build_files.push_back(p_fname.GetFullPath());
        }
    }



    build_run_project->saveProject(project_fname);
    //------------------

    notebook_mutex.Unlock();


    wxFile build_script;

    wxFileName build_script_fname(rcbasic_build_path);

    wxString additional_flags = _("");

    if(!enable_presets)
    {
        additional_flags += _(" --no-presets ");
    }

    #ifdef _WIN32
    build_script_fname.SetFullName(_("build_project.bat"));
    if(!build_script.Create(build_script_fname.GetFullPath(), true))
        return;

    build_script.Write(_("\"") + rcbasic_build_path.GetFullPath() + _("\" ") + build_flags + additional_flags + (" \"") + build_run_project->getMainSource().GetFullPath() + _("\" \r\n"));

    for(int i = 0; i < build_files.size(); i ++)
    {
        build_script.Write(_("\"") + rcbasic_build_path.GetFullPath() + _("\" ") + additional_flags + (" \"") + build_files[i] + _("\" \r\n"));
    }

    build_script.Close();

    #else
    build_script_fname.SetFullName(_("build_project.sh"));
    if(!build_script.Create(build_script_fname.GetFullPath(), true))
        return;

    build_script.Write(_("\"") + rcbasic_build_path.GetFullPath() + _("\" ") + build_flags + (" \"") + build_run_project->getMainSource().GetFullPath() + _("\" \n"));

    for(int i = 0; i < build_files.size(); i ++)
    {
        build_script.Write(_("\"") + rcbasic_build_path.GetFullPath() + _("\" ") + additional_flags + (" \"") + build_files[i] + _("\" \n"));
    }

    build_script.Close();

    wxSystem(_("chmod +x ") + build_script_fname.GetFullPath());

    #endif // _WIN32

    //wxPuts(_("BUILD START"));

    build_run_project = active_project;

    build_process = new wxProcess(this);

    if(!build_process)
        return;

    build_process->Connect( wxEVT_END_PROCESS, wxProcessEventHandler( rcbasic_edit_frame::onBuildProcessTerminate ), NULL, this );

    m_messageWindow_richText->Clear();

    build_process->Redirect();

    wxEnvVariableHashMap build_env_vars;

    /*if(build_run_project)
    {
        std::vector<rcbasic_edit_env_var> vars = build_run_project->getVars();

        for(int i = 0; i < vars.size(); i++)
        {
            build_env_vars[vars[i].var_name] = vars[i].var_value;
        }
    }*/

    wxExecuteEnv env;
    env.cwd = build_run_project->getLocation();
    env.env = build_env_vars;

    //NEED TO SAVE FILES IN PROJECT
    //ALSO NEED TO SWITCH TO BUILD TAB

    //wxString c =  _("+++\"") + rcbasic_build_path.GetFullPath() + _("\" \"") + build_run_project->getMainSource().GetFullPath() + _("\"---");
    //wxPuts(_("CMD: ") + c);

    //build_pid = wxExecute(_("\"") + rcbasic_build_path.GetFullPath() + _("\" \"") + build_run_project->getMainSource().GetFullPath() + _("\""), wxEXEC_ASYNC, build_process, &env);

    build_pid = wxExecute(_("\"") + build_script_fname.GetFullPath() + _("\""), wxEXEC_ASYNC, build_process, NULL);

    if(build_pid >= 0)
    {
        isBuilding = true;
    }

    //wxTextInputStream build_stream(*build_process->GetInputStream());

    //build_process->CloseOutput();

    wxString tst;

    m_messageWindow_richText->Clear();

    /*while(build_process->IsInputAvailable())
    {
        tst = build_stream.ReadLine();
        m_messageWindow_richText->AppendText(tst + _("\n"));
    }*/


    //wxPrintf(_("IsInputAvailable: %d\n"), build_process->IsInputAvailable() ? 1 : 0 );

    //wxPuts(_("-------THE END---------"));

    //os<<wxT("get net.ckt\n");
    //os<<wxT("print tran v(nodes)\n");
    //os<<wxT("tran 0 500u 50u\n");

    //wxKill(build_pid);
    //delete build_process;
    //build_process = NULL;

}


void rcbasic_edit_frame::onRunMenuSelect( wxCommandEvent& event )
{
    runProject();
}

void rcbasic_edit_frame::runProject()
{
    if(isBuilding || isRunning || isDebugging)
        return;

    if(build_process || run_process)
        return;

    if(!build_run_project)
    {
        if(!active_project)
        {
            wxMessageBox(_("No project has been selected"));
            return;
        }
        else
        {
            build_run_project = active_project;
        }
    }
    else
        return;

    //wxPuts(_("RUN START"));

    run_process = new wxProcess(this);

    if(!run_process)
        return;

    run_process->Connect( wxEVT_END_PROCESS, wxProcessEventHandler( rcbasic_edit_frame::onRunProcessTerminate ), NULL, this );

    //wxPuts(_("ENV: ")+env.cwd+_("\n"));

    wxString editor_path = wxStandardPaths::Get().GetExecutablePath();

    wxFile run_file;
    wxFileName run_file_fname(rcbasic_path);
    run_file_fname.SetFullName(_("run_rc.bat"));

    #ifdef _WIN32
    if(run_file_fname.Exists())
    {
        wxRemove(run_file_fname.GetFullPath());
    }

    if(!run_file.Create(run_file_fname.GetFullPath(), true))
    {
        isRunning = false;

        wxKill(run_pid);
        if(run_process)
            delete run_process;
        run_process = NULL;
        build_run_project = NULL;

        return;
    }

    run_file.Write(_("@echo OFF \r\n"));
    run_file.Write(_("cd ") + build_run_project->getLocation() + _("\r\n"));
    #endif

    wxEnvVariableHashMap run_env_vars;

    if(build_run_project)
    {
        //wxPuts(_("ISSUE START"));
        std::vector<rcbasic_edit_env_var> vars = build_run_project->getVars();

        for(int i = 0; i < vars.size(); i++)
        {
            #ifdef _WIN32
            run_file.Write(_("set ") + vars[i].var_name + _("=") + vars[i].var_value + _("\r\n"));
            #endif
            run_env_vars[vars[i].var_name] = vars[i].var_value;
        }

        //wxPuts(_("ISSUE END"));
    }

    wxExecuteEnv env;
    env.cwd = build_run_project->getLocation();
    env.env = run_env_vars;

    wxFileName main_source = build_run_project->getMainSource();
    main_source.SetExt(_("cbc"));

    #ifdef _WIN32
    run_file.Write(_("\"") + rcbasic_run_path.GetFullPath() + _("\" \"") + main_source.GetFullPath() + _("\" \r\n"));
    run_file.Write(_("PAUSE\r\n"));
    run_file.Close();

    run_pid = wxExecute(_("\"") + run_file_fname.GetFullPath() + _("\"") , wxEXEC_SHOW_CONSOLE | wxEXEC_ASYNC, run_process, NULL);
    #else

    wxString run_cmd = _("\"") + rcbasic_run_path.GetFullPath() + _("\" \"") + main_source.GetFullPath() + _("\"");

    //run_pid = wxExecute(_("\"") + run_file_fname.GetFullPath() + _("\"") , wxEXEC_SHOW_CONSOLE | wxEXEC_ASYNC, run_process, NULL);
    run_pid = wxExecute( run_cmd , wxEXEC_SHOW_CONSOLE | wxEXEC_ASYNC, run_process, &env);
    #endif

    if(run_pid >= 0)
    {
        isRunning = true;
    }
    //run_pid = wxExecute(_("\"") + rcbasic_run_path.GetFullPath() + _("\" \"") + main_source.GetFullPath() + _("\"") , wxEXEC_SHOW_CONSOLE | wxEXEC_ASYNC, run_process, NULL);

}



void rcbasic_edit_frame::onBuildRunMenuSelect( wxCommandEvent& event )
{
    if(isBuilding || isRunning || isBuildingAndRunning || isDebugging)
        return;

    if(!active_project)
    {
        wxMessageBox(_("No project has been selected"));
        return;
    }

    m_results_notebook->SetSelection(RESULTS_LISTBOX_BUILDMSG);

    isBuildingAndRunning = true;
    buildProject();
}


void rcbasic_edit_frame::onStopExecuteMenuSelect( wxCommandEvent& event )
{
    if(isRunning)
    {
        #ifndef _WIN32
        isRunning = false;
        isBuildingAndRunning = false;
        wxString editor_path = wxStandardPaths::Get().GetExecutablePath();
        wxFileName editor_path_dir(editor_path);
        editor_path_dir.SetFullName(_(""));

        wxFileName pid_filename = editor_path_dir;
        pid_filename.SetFullName(_("run_pid.txt"));

        if(pid_filename.Exists())
        {
            wxRemove(pid_filename.GetFullPath());
        }

        wxString term_cmd = _("cd [editor_path] && echo $( ps ax | grep rcbasic_studio_run | grep [editor_path] ) > run_pid.txt");
        term_cmd.Replace(_("[editor_path]"), editor_path_dir.GetFullPath());
        //wxPuts(_("-------------DEBUG-----------------"));
        //wxPuts(_("get pid: ") + term_cmd);
        wxSystem(term_cmd);

        wxFile pid_file;

        if(pid_file.Open(pid_filename.GetFullPath()))
        {
            wxString rpid;
            pid_file.ReadAll(&rpid);
            pid_file.Close();
            rpid = rpid.substr(rpid.find_first_not_of(_(" ")));
            rpid = rpid.substr(0, rpid.find_first_of(_(" ")));
            if(rpid.Length() > 0)
            {
                //wxPuts(_("Stop Prog: kill ") + rpid);
                wxSystem(_("kill ") + rpid);
            }
        }

        #else
        //wxPuts(_("STOPPING NOW: ") + _("taskkill /f /im ") + rcbasic_run_path.GetFullName());

        wxSystem(_("taskkill /f /im ") + rcbasic_run_path.GetFullName());
        isRunning = false;
        isBuildingAndRunning = false;

        //if(wxProcess::Exists(run_pid))
        //    wxKill(run_pid, wxSIGTERM, NULL, wxKILL_CHILDREN);

        //if(run_process)
        //    delete run_process;
        //run_process = NULL;
        //build_run_project = NULL;
        #endif
    }

    isRunning = false;
    isBuildingAndRunning = false;
    isBuilding = false;
    isDebugging = false;
}


void rcbasic_edit_frame::onBuildFileMenuSelect( wxCommandEvent& event )
{
    buildCurrentFile();
}

void rcbasic_edit_frame::buildCurrentFile()
{

    if(isBuilding || isRunning || isDebugging)
        return;


    if(build_process || run_process)
        return;

    build_run_project = NULL;

    m_results_notebook->SetSelection(RESULTS_LISTBOX_BUILDMSG);


    notebook_mutex.Lock();

    //-----------
    wxFileName project_fname = getCurrentFile()->getSourcePath();
    saveFile(getOpenFileFromSelection(), 0);

    //------------------

    notebook_mutex.Unlock();

    build_files.clear();

    wxFile build_script;

    wxFileName build_script_fname(rcbasic_build_path);

    wxString additional_flags = _("");

    if(!enable_presets)
        additional_flags += _(" --no-presets ");

    #ifdef _WIN32
    build_script_fname.SetFullName(_("build_project.bat"));
    if(!build_script.Create(build_script_fname.GetFullPath(), true))
        return;

    build_script.Write(_("pushd ") + project_fname.GetPath() + _(" \r\n"));
    build_script.Write(_("\"") + rcbasic_build_path.GetFullPath() + _("\" ") + additional_flags + (" \"") + project_fname.GetFullPath() + _("\" \r\n"));
    build_script.Write(_("popd \r\n"));
    build_script.Close();

    #else
    build_script_fname.SetFullName(_("build_project.sh"));
    if(!build_script.Create(build_script_fname.GetFullPath(), true))
        return;

    build_script.Write(_("export tmp_cwd=$PWD && cd ") + project_fname.GetPath() + _("\n"));
    build_script.Write(_("\"") + rcbasic_build_path.GetFullPath() + _("\" ") + additional_flags + (" \"") + project_fname.GetFullPath() + _("\" \n"));
    build_script.Write(_("cd $tmp_cwd\n"));
    build_script.Close();

    wxSystem(_("chmod +x ") + build_script_fname.GetFullPath());

    #endif // _WIN32

    //wxPuts(_("BUILD START"));

    current_file_project->setMainSource(project_fname.GetFullPath());
    current_file_project->setLocation(project_fname.GetPath());

    build_run_project = current_file_project;

    build_process = new wxProcess(this);

    if(!build_process)
        return;

    build_process->Connect( wxEVT_END_PROCESS, wxProcessEventHandler( rcbasic_edit_frame::onBuildProcessTerminate ), NULL, this );

    m_messageWindow_richText->Clear();

    build_process->Redirect();

    build_pid = wxExecute(_("\"") + build_script_fname.GetFullPath() + _("\""), wxEXEC_ASYNC, build_process, NULL);

    if(build_pid >= 0)
    {
        isBuilding = true;
    }

}

void rcbasic_edit_frame::onRunFileMenuSelect( wxCommandEvent& event )
{
    runCurrentFile();
}

void rcbasic_edit_frame::runCurrentFile()
{
    if(isBuilding || isRunning || isDebugging)
        return;

    if(build_process || run_process)
        return;

    build_run_project = NULL;

    wxFileName project_fname = getCurrentFile()->getSourcePath();

    run_process = new wxProcess(this);

    if(!run_process)
        return;

    run_process->Connect( wxEVT_END_PROCESS, wxProcessEventHandler( rcbasic_edit_frame::onRunProcessTerminate ), NULL, this );

    wxString editor_path = wxStandardPaths::Get().GetExecutablePath();

    current_file_project->setMainSource(project_fname.GetFullPath());
    current_file_project->setLocation(project_fname.GetPath());

    build_run_project = current_file_project;

    wxFile run_file;
    wxFileName run_file_fname(rcbasic_path);
    run_file_fname.SetFullName(_("run_rc.bat"));

    #ifdef _WIN32
    if(run_file_fname.Exists())
    {
        wxRemove(run_file_fname.GetFullPath());
    }

    if(!run_file.Create(run_file_fname.GetFullPath(), true))
    {
        isRunning = false;

        wxKill(run_pid);
        if(run_process)
            delete run_process;
        run_process = NULL;
        build_run_project = NULL;

        return;
    }

    run_file.Write(_("@echo OFF \r\n"));
    run_file.Write(_("cd ") + build_run_project->getLocation() + _("\r\n"));
    #endif


    wxFileName main_source = build_run_project->getMainSource();
    main_source.SetExt(_("cbc"));

    #ifdef _WIN32
    run_file.Write(_("\"") + rcbasic_run_path.GetFullPath() + _("\" \"") + main_source.GetFullPath() + _("\" \r\n"));
    run_file.Write(_("PAUSE\r\n"));
    run_file.Close();

    run_pid = wxExecute(_("\"") + run_file_fname.GetFullPath() + _("\"") , wxEXEC_SHOW_CONSOLE | wxEXEC_ASYNC, run_process, NULL);
    #else

    wxString run_cmd = _("\"") + rcbasic_run_path.GetFullPath() + _("\" \"") + main_source.GetFullPath() + _("\"");

    run_pid = wxExecute( run_cmd , wxEXEC_SHOW_CONSOLE | wxEXEC_ASYNC, run_process, NULL);
    #endif

    if(run_pid >= 0)
    {
        isRunning = true;
    }
    //run_pid = wxExecute(_("\"") + rcbasic_run_path.GetFullPath() + _("\" \"") + main_source.GetFullPath() + _("\"") , wxEXEC_SHOW_CONSOLE | wxEXEC_ASYNC, run_process, NULL);

}

void rcbasic_edit_frame::onBuildRunFileMenuSelect( wxCommandEvent& event )
{
    if(isBuilding || isRunning || isBuildingAndRunning || isDebugging)
        return;

    m_results_notebook->SetSelection(RESULTS_LISTBOX_BUILDMSG);

    isBuildingAndRunning = true;
    buildCurrentFile();
}

void rcbasic_edit_frame::debugProject()
{
    //wxMessageBox(_("Step 2"));
    if(!debug_project)
    {
        isDebugging = false;
        debug_project = NULL;
        return;
    }

    wxFileName cbc_fname = debug_project->getProjectFileLocation();
    cbc_fname.SetFullName(_("debug.cbc"));

    /*if(!cbc_fname.Exists())
    {
        wxMessageBox(_("Failed to compile"));
        return;
    }*/

    //wxMessageBox(_("cbc = ") + cbc_fname.GetFullPath());

    wxFileName dbg_rt_fname = rcbasic_run_path;
    #ifdef WIN32
        dbg_rt_fname.SetFullName(_("rcbasic_debug.exe"));
    #else
        dbg_rt_fname.SetFullName(_("rcbasic_debug"));
    #endif
    //wxFileName cbc_fname(_("C:\\Users\\omega\\Desktop\\Projects\\RCBASIC3\\rcbasic_build\\bin\\Release64\\debug.cbc"));
    //wxFileName dbg_rt_fname(_("C:\\Users\\omega\\Desktop\\Projects\\RCBASIC3\\rcbasic_runtime\\bin\\Release64\\rcbasic_runtime.exe"));


    isBuilding = false;
    isRunning = false;
    isDebugging = false;
    isBuildingAndRunning = false;

    rc_debugger_dialog dbg_dialog(this, cbc_fname, dbg_rt_fname);

    dbg_dialog.ShowWindowModal();

    //wxMessageBox(_("end of debug"));

    isDebugging = false;
    debug_project = NULL;

    if(wxFileExists(_("rcbasic.dbgm")))
        wxRemoveFile(_("rcbasic.dbgm"));

    if(wxFileExists(_("rcbasic_dbg.cl")))
        wxRemoveFile(_("rcbasic_dbg.cl"));

    if(wxFileExists(_("rcbasic_dbg.sp")))
        wxRemoveFile(_("rcbasic_dbg.sp"));

    if(wxFileExists(_("rcbasic_dbg.rt")))
        wxRemoveFile(_("rcbasic_dbg.rt"));

    if(wxFileExists(_("rcbasic.dbgi")))
        wxRemoveFile(_("rcbasic.dbgi"));

    if(wxFileExists(_("rcbasic.dbgs")))
        wxRemoveFile(_("rcbasic.dbgs"));
}

void rcbasic_edit_frame::onDebugMenuSelect( wxCommandEvent& event )
{
    buildProject(_("--debug"));

    if(build_run_project)
        isDebugging = true;
}
