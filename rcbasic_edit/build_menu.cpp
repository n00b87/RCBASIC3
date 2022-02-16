#include "rcbasic_edit_frame.h"

#include <wx/process.h>
#include <wx/txtstrm.h>
#include <wx/utils.h>


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
    delete build_process;
    build_process = NULL;
    build_run_project = NULL;

    if(isBuildingAndRunning)
    {
        isBuildingAndRunning = false;
        runProject();
    }

    //wxPuts(_("PROCESS is dead"));
}

void rcbasic_edit_frame::onRunProcessTerminate( wxProcessEvent& event )
{
    //wxPuts(_("RUN HAS FINISHED"));

    isRunning = false;
    isBuildingAndRunning = false;

    wxKill(run_pid);
    delete run_process;
    run_process = NULL;
    build_run_project = NULL;

    //wxPuts(_("PROCESS is dead"));
}


void rcbasic_edit_frame::onBuildMenuSelect( wxCommandEvent& event )
{
    buildProject();
}

void rcbasic_edit_frame::buildProject()
{
    /*wxSetWorkingDirectory(rc_fnames[AuiNotebook1->GetPageIndex(t)].substr(0, rc_fnames[AuiNotebook1->GetPageIndex(t)].find_last_of("/")));
    wxString fs = rc_path + _("rcbasic_build ") + _("\"") + rc_fnames[AuiNotebook1->GetPageIndex(t)] + _("\"");

    int rt = -1;
    rt = wxExecute(fs, wxEXEC_SYNC);*/

    if(isBuilding || isRunning)
        return;


    if(build_process || run_process)
        return;

    if(!build_run_project)
    {
        if(!active_project)
            return;
        else
        {
            build_run_project = active_project;
        }
    }
    else
        return;

    m_results_notebook->SetSelection(RESULTS_LISTBOX_BUILDMSG);


    //SAVE FILES IN PROJECT
    notebook_mutex.Lock();
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
    notebook_mutex.Unlock();

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

    build_pid = wxExecute(_("\"") + rcbasic_build_path.GetFullPath() + _("\" \"") + build_run_project->getMainSource().GetFullPath() + _("\""), wxEXEC_ASYNC, build_process, &env);

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
    if(isBuilding || isRunning)
        return;

    if(build_process || run_process)
        return;

    if(!build_run_project)
    {
        if(!active_project)
            return;
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

    wxString run_cmd = _("\"") + rcbasic_run_path.GetFullPath() + _("\" \"") + main_source.GetFullPath() + _("\" \r\n");

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
    if(isBuilding || isRunning || isBuildingAndRunning)
        return;

    m_results_notebook->SetSelection(RESULTS_LISTBOX_BUILDMSG);

    isBuildingAndRunning = true;
    buildProject();
}


void rcbasic_edit_frame::onStopExecuteMenuSelect( wxCommandEvent& event )
{
    if(isRunning)
    {
        #ifndef _WIN32
        wxString editor_path = wxStandardPaths::Get().GetExecutablePath();
        wxFileName editor_path_dir(editor_path);
        editor_path_dir.SetFullName(_(""));
        wxProcess* term_process = new wxProcess(this);
        term_process->Redirect();
        wxString term_cmd = _("get_run_pid.sh [editor_path]");
        term_cmd.Replace(_("[editor_path]"), editor_path_dir.GetFullPath());
        wxExecute(term_cmd, wxEXEC_SYNC, term_process, NULL);

        wxTextInputStream term_stream(*term_process->GetInputStream());

        while(term_process->IsInputAvailable())
        {
            wxString term_out = term_stream.ReadLine();
            term_out = term_out.substr(term_out.find_first_not_of(_(" ")));
            term_out = term_out.substr(0, term_out.find_first_of(_(" ")));
            wxPuts(_("TERMINATE PID = ") + term_out);
        }
        return;
        #else
        //wxPuts(_("STOPPING NOW: ") + _("taskkill /f /im ") + rcbasic_run_path.GetFullName());
        wxSystem(_("taskkill /f /im ") + rcbasic_run_path.GetFullName());
        isRunning = false;
        isBuildingAndRunning = false;
        wxKill(run_pid);
        delete run_process;
        run_process = NULL;
        build_run_project = NULL;
        #endif
    }

    isBuilding = false;
}
