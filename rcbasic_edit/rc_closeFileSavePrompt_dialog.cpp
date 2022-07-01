#include "rc_closeFileSavePrompt_dialog.h"

rcbasic_edit_closeFileSavePrompt_dialog::rcbasic_edit_closeFileSavePrompt_dialog( wxWindow* parent, const wxString& title )
:
rc_closeFileSavePrompt_dialog( parent, wxID_ANY, title, wxDefaultPosition, wxSize( 385,149 ), wxDEFAULT_DIALOG_STYLE|wxSTAY_ON_TOP )
{
    fileCloseFlag = fileCloseFlag_CANCEL;
    //title = _("testing");
}

void rcbasic_edit_closeFileSavePrompt_dialog::onCloseFileSaveCancel( wxCommandEvent& event )
{
// TODO: Implement onCloseFileSaveCancel
    Close();
}

void rcbasic_edit_closeFileSavePrompt_dialog::onCloseFileSaveDontSave( wxCommandEvent& event )
{
// TODO: Implement onCloseFileSaveDontSave
    fileCloseFlag = fileCloseFlag_DONT_SAVE;
    Close();
}

void rcbasic_edit_closeFileSavePrompt_dialog::onCloseFileSaveOk( wxCommandEvent& event )
{
// TODO: Implement onCloseFileSaveOk
    fileCloseFlag = fileCloseFlag_SAVE;
    Close();
}

int rcbasic_edit_closeFileSavePrompt_dialog::getFileCloseFlag()
{
    return fileCloseFlag;
}
