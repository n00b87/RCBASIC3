#include "rc_debugger_dialog.h"

#include <wx/wx.h>
#include <wx/file.h>
#include <wx/filename.h>
#include <wx/filefn.h>
#include <wx/process.h>
#include <vector>

rc_debugger_dialog::rc_debugger_dialog( wxWindow* parent, wxFileName dbg_cbc, wxFileName dbg_runtime )
:
rc_debugger( parent )
{
    /*if(!wxFileExists(_("rcbasic_dbg.rt")))
    {
        wxFile f(_("rcbasic_dbg.rt"), wxFile::write);
        f.Close();
    }*/

    dbg_rt = dbg_runtime;
    dbg_rt.MakeAbsolute();

    wxFileName dbg_symbols = dbg_cbc;
    dbg_symbols.SetFullName(_("rcbasic.dbgs"));

    wxFileName dbg_src_files = dbg_cbc;
    dbg_src_files.SetFullName(_("rcbasic.dbgi"));

    msg_bkg_color[0] = wxColour(0,255,0,255);
    msg_bkg_color[1] = wxColour(255,0,0,255);

    m_var_listCtrl->AppendColumn(_("ACTION"));
    m_var_listCtrl->AppendColumn(_("VARIABLE"));
    m_var_listCtrl->AppendColumn(_("VALUE"));

    int w, h;
    m_var_listCtrl->GetSize(&w, &h);

    m_var_listCtrl->SetColumnWidth(0, w/6);
    m_var_listCtrl->SetColumnWidth(1, w/3);
    m_var_listCtrl->SetColumnWidth(2, w/3);

    //wxMessageBox(_("CBC = ") + dbg_cbc.GetFullPath() + _("\nSRC = ") + dbg_src_files.GetFullPath() + _("\nSYM = ") + dbg_symbols.GetFullPath() + _("\n"));

    loadDebugData(dbg_symbols.GetFullPath(), dbg_src_files.GetFullPath());




    rc_debug_process = new wxProcess(this);

    if(!rc_debug_process)
    {
        wxMessageBox(_("Could not start debug process"));
        Close();
    }

    rc_debug_process->Connect( wxEVT_END_PROCESS, wxProcessEventHandler( rc_debugger_dialog::onDebugProcessTerminate ), NULL, this );

    cwd = wxGetCwd();

    wxSetWorkingDirectory(dbg_cbc.GetPath());

    if(wxFileExists(_("rcbasic.dbgm")))
        wxRemoveFile(_("rcbasic.dbgm"));

    if(wxFileExists(_("rcbasic_dbg.cl")))
        wxRemoveFile(_("rcbasic_dbg.cl"));

    if(wxFileExists(_("rcbasic_dbg.sp")))
        wxRemoveFile(_("rcbasic_dbg.sp"));

    if(wxFileExists(_("rcbasic_dbg.rt")))
        wxRemoveFile(_("rcbasic_dbg.rt"));

    rc_debug_pid = wxExecute(_("\"") + dbg_runtime.GetFullPath().Trim() + _("\""), wxEXEC_ASYNC, rc_debug_process, NULL);

    //wxSetWorkingDirectory(cwd);

    if(rc_debug_pid < 0)
    {
        wxMessageBox(_("Debugger Failed to Start"));
        wxSetWorkingDirectory(cwd);
        Close();
    }
    else
        is_running = true;

}

void rc_debugger_dialog::onDebugProcessTerminate( wxProcessEvent& event )
{
    if(is_running)
    {
        wxKill(rc_debug_pid, wxSIGTERM, NULL, wxKILL_CHILDREN);
        is_running = false;
        rc_debug_pid = -1;
    }
    wxMessageBox(_("Debugger Process Terminated"));
}

#define DBG_RT_LINE_TYPE_SRC 0
#define DBG_RT_LINE_TYPE_LN 1
#define DBG_RT_LINE_TYPE_N 2
#define DBG_RT_LINE_TYPE_S 3
#define DBG_RT_LINE_TYPE_E 4

void rc_debugger_dialog::updateDebugData()
{
    std::vector<wxString> msg_args;
    wxFile msg_file;
    wxString msg_data;

    used_vars.clear();

    if(wxFileExists(_("rcbasic.dbgm")))
    {
        msg_file.Open(_("rcbasic.dbgm"), wxFile::read);
        msg_file.ReadAll(&msg_data);
        msg_data.Append(_(" \n "));
        msg_file.Close();
    }
    else
        return;

    //wxMessageBox(_("file read"));

    wxString f_line;
    dbg_var tmp;

    wxString arg;
    int arg_num = 0;
    int line_type = 0;

    for(int msg_c = 0; msg_c < msg_data.length(); msg_c++)
    {
        f_line = msg_data.substr(0, msg_data.find_first_of(_("\n"))).Trim() + _(" ");
        msg_data = msg_data.substr(msg_data.find_first_of(_("\n"))+1);

        int vpos = msg_data.find_first_of(_("\n"));
        if(vpos == wxString::npos)
            break;

        arg_num = 0;
        line_type = -1;

        tmp.dimensions = 0;
        tmp.index = 0;
        tmp.scope = _("");
        tmp.name = _("");
        long dbg_index = 0;
        long tmp_long = 0;

        for(int i = 0; f_line.length() > 0; i++)
        {

            vpos = f_line.find_first_of(_(" "));
            if(vpos == wxString::npos)
                break;

            arg = f_line.substr(0, vpos);

            if(arg_num == 0)
            {
                if(arg.Trim().compare(_("SRC"))==0)
                {
                    line_type = DBG_RT_LINE_TYPE_SRC;
                    current_src_file = f_line.substr(vpos).Trim();
                    //wxMessageBox(_("SRC = ") + f_line);
                    break;
                }
                else if(arg.Trim().compare(_("LN"))==0)
                {
                    line_type = DBG_RT_LINE_TYPE_LN;
                    long ln = 0;
                    f_line.substr(vpos).Trim().ToLong(&ln);
                    current_line = (uint64_t) ln;
                    break;
                }
                else if(arg.Trim().compare(_("N"))==0)
                    line_type = DBG_RT_LINE_TYPE_N;
                else if(arg.Trim().compare(_("S"))==0)
                    line_type = DBG_RT_LINE_TYPE_S;
                else if(arg.Trim().compare(_("E"))==0)
                {
                    line_type = DBG_RT_LINE_TYPE_E;
                    ends_on_error = true;
                    error_msg = f_line.substr(vpos).Trim();
                }
                else
                    break;

                f_line = f_line.substr(vpos+1);
                arg_num++;
                continue;
            }

            switch(line_type)
            {
                case DBG_RT_LINE_TYPE_N:
                case DBG_RT_LINE_TYPE_S:
                    if(arg_num == 1)
                    {
                        //wxMessageBox(_("D_INDEX = ") + arg);
                        arg.Trim().ToLong(&dbg_index);
                        if(dbg_index >= 0 && dbg_index < dbg_vars.size())
                        {
                            tmp = dbg_vars[dbg_index];
                        }
                    }
                    else if(arg_num == 2)
                    {
                        arg.Trim().ToLong(&tmp_long);
                        tmp.access_type = tmp_long;
                    }
                    else if(arg_num == 3)
                    {
                        tmp.status = (arg.Trim().compare(_("G"))==0) ? RC_DBG_STATUS_GOOD : RC_DBG_STATUS_ERROR;
                    }
                    else if(arg_num == 4)
                    {
                        //wxMessageBox(_("dimensions = ") + arg);
                        arg.Trim().ToLong(&tmp_long);
                        tmp.dimensions = tmp_long;
                    }
                    else if(arg_num == 5)
                    {
                        arg.Trim().ToLong(&tmp_long);
                        tmp.dim[0] = tmp_long;
                    }
                    else if(arg_num == 6)
                    {
                        arg.Trim().ToLong(&tmp_long);
                        tmp.dim[1] = tmp_long;
                    }
                    else if(arg_num == 7)
                    {
                        arg.Trim().ToLong(&tmp_long);
                        tmp.dim[2] = tmp_long;
                    }
                    else if(arg_num == 8)
                    {
                        if(f_line.find_first_of(_("=")) != wxString::npos)
                            tmp.var_value = f_line.substr(f_line.find_first_of(_("="))+1).Trim();
                        //wxMessageBox(_("VAL=") + f_line);
                    }

                    break;

            }

            arg_num++;
            f_line = f_line.substr(vpos+1);
        }

        if(line_type == DBG_RT_LINE_TYPE_N || line_type == DBG_RT_LINE_TYPE_S)
            used_vars.push_back(tmp);
    }
}

void rc_debugger_dialog::updateDebugUI()
{
    m_file_textCtrl->SetValue(current_src_file);
    wxString tmp_str = _("");
    tmp_str << current_line;
    m_line_textCtrl->SetValue(tmp_str);

    int index = 0;

    m_var_listCtrl->ClearAll();

    m_var_listCtrl->AppendColumn(_("ACTION"));
    m_var_listCtrl->AppendColumn(_("VARIABLE"));
    m_var_listCtrl->AppendColumn(_("VALUE"));

    int w, h;
    m_var_listCtrl->GetSize(&w, &h);

    m_var_listCtrl->SetColumnWidth(0, w/6);
    m_var_listCtrl->SetColumnWidth(1, w/3);
    m_var_listCtrl->SetColumnWidth(2, w/3);

    for(int i = 0; i < used_vars.size(); i++)
    {
        wxString access_type = (used_vars[i].access_type == RC_DBG_ACCESS_GET) ? _("GET") : _("SET");
        index = m_var_listCtrl->InsertItem(m_var_listCtrl->GetItemCount(), access_type);
        wxString var_name = used_vars[i].name;
        if(used_vars[i].dimensions > 0)
        {
            var_name += _("[");
            tmp_str = _("");
            //tmp_str << used_vars[i].dimensions;
            //wxMessageBox(_("Num Dimensions = ") + tmp_str);
            switch(used_vars[i].dimensions)
            {
                case 1:
                    tmp_str << used_vars[i].dim[0];
                    var_name += tmp_str;
                    break;
                case 2:
                    tmp_str << used_vars[i].dim[0] << _(", ") << used_vars[i].dim[1];
                    var_name += tmp_str;
                    break;
                case 3:
                    tmp_str << used_vars[i].dim[0] << _(", ") << used_vars[i].dim[1] << _(", ") << used_vars[i].dim[2];
                    var_name += tmp_str;
                    break;
            }
            var_name += _("]");
        }

        m_var_listCtrl->SetItem(index, 1, var_name);
        m_var_listCtrl->SetItem(index, 2, used_vars[i].var_value);

        if(used_vars[i].status == RC_DBG_STATUS_ERROR)
            m_var_listCtrl->SetItemBackgroundColour(index, msg_bkg_color[1]);
    }

    m_msg_textCtrl->SetBackgroundColour(msg_bkg_color[ends_on_error ? 1 : 0]);
    m_msg_textCtrl->SetValue(error_msg);
}

void rc_debugger_dialog::onDebugUpdate( wxUpdateUIEvent& event )
{
    if(auto_run)
    {
        if(wxFileExists(_("rcbasic_dbg.cl")))
        {
            updateDebugData();
            wxRemoveFile(_("rcbasic_dbg.cl"));
            wxFile f(_("rcbasic_dbg.rt"), wxFile::write);
            while(!f.IsOpened())
                f.Open(_("rcbasic_dbg.rt"), wxFile::write);
            f.Close();
            updateDebugUI();
        }
    }
    else if(super_run)
    {
        if(wxFileExists(_("rcbasic_dbg.cl")))
        {
            if(wxFileExists(_("rcbasic.dbgm")))
            {
                updateDebugData();
                updateDebugUI();
            }

            wxRemoveFile(_("rcbasic_dbg.cl"));

            wxFile f(_("rcbasic_dbg.rt"), wxFile::write);
            while(!f.IsOpened())
                f.Open(_("rcbasic_dbg.rt"), wxFile::write);
            f.Close();

            /*if(wxFileExists(_("rcbasic.dbgm")))
            {
                wxRemoveFile(_("rcbasic.dbgm"));
                updateDebugUI();
            }*/
        }
    }
    else if(step)
    {
        if(wxFileExists(_("rcbasic_dbg.cl")))
        {
            updateDebugData();
            wxRemoveFile(_("rcbasic_dbg.cl"));
            wxFile f(_("rcbasic_dbg.rt"), wxFile::write);
            while(!f.IsOpened())
                f.Open(_("rcbasic_dbg.rt"), wxFile::write);
            f.Close();
        }
        step = false;
        updateDebugUI();
    }
}

void rc_debugger_dialog::onPause( wxCommandEvent& event )
{
    if(wxFileExists(_("rcbasic_dbg.sp")))
    {
        wxRemoveFile(_("rcbasic_dbg.sp"));
    }
    auto_run = false;
    step = false;
    super_run = false;
}

void rc_debugger_dialog::onStep( wxCommandEvent& event )
{
    if(wxFileExists(_("rcbasic_dbg.sp")))
    {
        wxRemoveFile(_("rcbasic_dbg.sp"));
    }
    step = true;
    super_run = false;
    auto_run = false;
}

void rc_debugger_dialog::onRun( wxCommandEvent& event )
{
    if(wxFileExists(_("rcbasic_dbg.sp")))
    {
        wxRemoveFile(_("rcbasic_dbg.sp"));
    }
    auto_run = true;
    step = false;
    super_run = false;
}

void rc_debugger_dialog::onSuper( wxCommandEvent& event )
{
    if(!wxFileExists(_("rcbasic_dbg.sp")))
    {
        wxFile f(_("rcbasic_dbg.sp"), wxFile::write);
        f.Close();
    }
    super_run = true;
    auto_run = false;
    step = false;
}

void rc_debugger_dialog::term_process()
{
    if(rc_debug_pid < 0)
        return;

    wxFileName editor_path_dir = dbg_rt;;
    editor_path_dir.SetFullName(_(""));

    wxFileName pid_filename = editor_path_dir;
    pid_filename.SetFullName(_("dbg_pid.txt"));

    if(pid_filename.Exists())
    {
        wxRemove(pid_filename.GetFullPath());
    }

    wxString term_cmd = _("cd [editor_path] && echo $( pidof rcbasic_debug ) > dbg_pid.txt");
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
            wxSystem(_("kill -9 ") + rpid);
            rc_debug_pid = -1;
            is_running = false;
        }
    }

}

void rc_debugger_dialog::onEnd( wxCommandEvent& event )
{
    if(is_running)
    {
        #ifdef WIN32
        wxKill(rc_debug_pid, wxSIGKILL, NULL, wxKILL_CHILDREN);
        is_running = false;
        rc_debug_pid = -1;
        #else
        //return; // Disable abort on linux until we figure this nonsense
        term_process();
        wxMessageBox(_("process terminated"));
        #endif
    }
}

void rc_debugger_dialog::onClose( wxCommandEvent& event )
{
    if(is_running)
    {
        #ifdef WIN32
        wxKill(rc_debug_pid, wxSIGKILL, NULL, wxKILL_CHILDREN);
        is_running = false;
        rc_debug_pid = -1;
        #else
        term_process();
        wxMessageBox(_("process terminated"));
        //is_running = false;
        //rc_debug_pid = -1;
        #endif
    }

    wxSetWorkingDirectory(cwd);

    Close();
}



void rc_debugger_dialog::loadDebugData(wxString sym_file, wxString inc_file)
{
    wxFile f(sym_file, wxFile::read);
    wxString file_data;
    f.ReadAll(&file_data);
    file_data.Append(_(" \n "));
    f.Close();

    wxString f_line;

    wxString type_str = _("");

    dbg_var tmp;

    wxString f_log = _("");

    //wxMessageBox(_("SYM = ") + file_data);

    for(int i = 0; i < file_data.length(); i++)
    {
        f_line = file_data.substr(0, file_data.find_first_of(_("\n"))) + _(" ");
        file_data = file_data.substr(file_data.find_first_of(_("\n"))+1);

        int vpos = f_line.find_first_of(_(" "));
        if(vpos == wxString::npos)
            break;

        if(f_line.substr(0, vpos).Trim().compare(_("N"))==0 ||
           f_line.substr(0, vpos).Trim().compare(_("AN"))==0 ||
           f_line.substr(0, vpos).Trim().compare(_("BN"))==0)
        {
            tmp.data_type = RC_DBG_VAR_TYPE_NUM;
        }
        else if(f_line.substr(0, vpos).Trim().compare(_("S"))==0 ||
                f_line.substr(0, vpos).Trim().compare(_("AS"))==0 ||
                f_line.substr(0, vpos).Trim().compare(_("BS"))==0)
        {
            tmp.data_type = RC_DBG_VAR_TYPE_STR;
        }
        else
        {
            //wxMessageBox(_("Invalid symbol: ") + f_line.substr(0, vpos).Trim());
            continue;
        }

        f_line = f_line.substr(vpos+1);
        vpos = f_line.find_first_of(_(" "));
        if(vpos == wxString::npos)
            break;

        tmp.scope = f_line.substr(0, vpos);

        f_line = f_line.substr(vpos+1);
        vpos = f_line.find_first_of(_(" "));
        if(vpos == wxString::npos)
            break;

        tmp.name = f_line.substr(0, vpos);

        f_line = f_line.substr(vpos+1);
        vpos = f_line.find_first_of(_(" "));
        if(vpos == wxString::npos)
            break;

        long t_index = 0;
        f_line.substr(0, vpos).ToLong(&t_index);
        tmp.index = t_index;

        wxString fmt_index;
        fmt_index << tmp.index;

        //f_log.Append( _("SYM  Type=") + ((tmp.data_type == RC_DBG_VAR_TYPE_NUM) ? _("NUM "): _("STR ")) +
        //             _("SCOPE=") + tmp.scope + _(" NAME=") + tmp.name + _(" INDEX=") + fmt_index + _("\n"));

        dbg_vars.push_back(tmp);

    }



    f.Open(inc_file, wxFile::read);
    f.ReadAll(&file_data);
    file_data.Append(_(" \n "));
    f.Close();

    for(int i = 0; i < file_data.length(); i++)
    {
        f_line = file_data.substr(0, file_data.find_first_of(_("\n")));
        file_data = file_data.substr(file_data.find_first_of(_("\n"))+1);

        src_files.push_back(f_line);
        //f_log.Append(_("SRC = ") + f_line + _("\n"));

        int vpos = file_data.find_first_of(_("\n"));
        if(vpos == wxString::npos)
            break;
    }

    //wxMessageBox(f_log);
}
