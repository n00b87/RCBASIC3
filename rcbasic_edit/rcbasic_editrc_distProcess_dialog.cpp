#include "rcbasic_editrc_distProcess_dialog.h"
#include <wx/txtstrm.h>
#include <wx/msgdlg.h>

rcbasic_editrc_distProcess_dialog::rcbasic_editrc_distProcess_dialog( wxWindow* parent, wxString dist_cmd, int num_targets )
:
rc_distProcess_dialog( parent )
{
    isRunning = false;
    dist_pid = -1;
    dist_process = NULL;

    dist_process = new wxProcess(this);
	if(!dist_process)
        Close();

    dist_process->Redirect();

	dist_process->Connect( wxEVT_END_PROCESS, wxProcessEventHandler( rcbasic_editrc_distProcess_dialog::onDistProcessTerminate ), NULL, this );

	wxString pkg_home;
	wxGetEnv(_("RC_PKG_HOME"), &pkg_home);
	wxSetWorkingDirectory(pkg_home);

	wxString p;
	wxGetEnv(_("PATH"), &p);
	//wxPuts(_("PATH: ") + p );

	dist_pid = wxExecute(dist_cmd, wxEXEC_ASYNC, dist_process, NULL);

	if(dist_pid < 0)
    {
        delete dist_process;
        return;
    }

	isRunning = true;
	target_count = num_targets;

	//wxPrintf(_("Num Targets: %d\n"), target_count);

	m_status_gauge->SetRange(target_count);
	current_count = 0;
}

void rcbasic_editrc_distProcess_dialog::onDistProcessUpdateUI( wxUpdateUIEvent& event )
{
// TODO: Implement onDistProcessUpdateUI
    if(!isRunning)
        return;

    wxTextInputStream dist_stream(*dist_process->GetInputStream());

    while(dist_process->IsInputAvailable())
    {
        wxString console_line = dist_stream.ReadLine();

        if(console_line.find(_("RCBASIC PACKAGE SUCCESS:")) != wxString::npos)
        {
            current_count++;
            m_status_gauge->SetValue(current_count);
            //wxPrintf(_("Current Value = %d out of %d\n"), m_status_gauge->GetValue(), m_status_gauge->GetRange());
        }

        m_consoleLog_textCtrl->AppendText(console_line + _("\n"));
    }

}

void rcbasic_editrc_distProcess_dialog::onCancelButtonClick( wxCommandEvent& event )
{
// TODO: Implement onCancelButtonClick
    if(!isRunning)
        Close();

    isRunning = false;
    dist_process->CloseOutput();

    wxExecute(_("taskkill /F /IM rcbasic_studio_run.exe"), wxEXEC_SYNC);

    wxKill(dist_pid);
    delete dist_process;
    dist_process = NULL;

    Close();
}

void rcbasic_editrc_distProcess_dialog::onCloseButtonClick( wxCommandEvent& event )
{
// TODO: Implement onCloseButtonClick
    Close();
}


void rcbasic_editrc_distProcess_dialog::onDistProcessTerminate( wxProcessEvent& event )
{
    isRunning = false;
    dist_process->CloseOutput();

    wxTextInputStream dist_stream(*dist_process->GetInputStream());

    while(dist_process->IsInputAvailable())
    {
        wxString console_line = dist_stream.ReadLine();
        m_consoleLog_textCtrl->AppendText(console_line + _("\n"));
    }

    if(m_status_gauge->GetValue() < m_status_gauge->GetRange())
    {
        wxMessageBox(_("ERROR: Did not successfully build app for all selected platforms."));
    }

    wxKill(dist_pid);
    delete dist_process;
    dist_process = NULL;

    m_cancel_button->Hide();
    m_close_button->Enable();
}
