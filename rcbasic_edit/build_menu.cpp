#include "rcbasic_edit_frame.h"

#include <wx/process.h>
#include <wx/txtstrm.h>

class MyProcess : public wxProcess
{
public:
    MyProcess(rcbasic_edit_frame* parent)
        : wxProcess(parent)//, m_cmd(cmd)
    {
        m_parent = parent;
        Redirect();
    }

    // instead of overriding this virtual function we might as well process the
    // event from it in the frame class - this might be more convenient in some
    // cases
    virtual void OnTerminate(int pid, int status)
    {
        //wxString editor_path = wxStandardPaths::Get().GetExecutablePath();
        //wxFileName editor_cwd(editor_cwd);

        //NOTE TO MYSELF: THIS IS A TEMP DIRECTORY FOR TESTING PURPOSES


        //wxPuts(_("Set Path to: ") + editor_path);
        //wxSetWorkingDirectory(editor_path);
    }

protected:
    rcbasic_edit_frame* m_parent;
    //wxString m_cmd;
};


void rcbasic_edit_frame::onBuildProcessTerminate( wxProcessEvent& event )
{
    wxPuts(_("BUILD HAS FINISHED"));

    isBuilding = false;
    wxKill(build_pid);
    delete build_process;
    build_process = NULL;
}


void rcbasic_edit_frame::onBuildMenuSelect( wxCommandEvent& event )
{
    /*wxSetWorkingDirectory(rc_fnames[AuiNotebook1->GetPageIndex(t)].substr(0, rc_fnames[AuiNotebook1->GetPageIndex(t)].find_last_of("/")));
    wxString fs = rc_path + _("rcbasic_build ") + _("\"") + rc_fnames[AuiNotebook1->GetPageIndex(t)] + _("\"");

    int rt = -1;
    rt = wxExecute(fs, wxEXEC_SYNC);*/

    if(isBuilding || isRunning || isBuildingAndRunning)
        return;

    build_process = new wxProcess(this);

    if(!build_process)
        return;

    build_process->Connect( wxEVT_END_PROCESS, wxProcessEventHandler( rcbasic_edit_frame::onBuildProcessTerminate ), NULL, this );

    m_messageWindow_richText->Clear();

    isBuilding = true;
    build_process->Redirect();

    build_pid = wxExecute(wxT("tasklist"),wxEXEC_ASYNC, build_process);

    //wxTextInputStream build_stream(*build_process->GetInputStream());

    build_process->CloseOutput();

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
    if(isBuilding || isRunning || isBuildingAndRunning)
        return;
}


