#include "rc_closeProjectSavePrompt_dialog.h"

rcbasic_edit_closeProjectSavePrompt_dialog::rcbasic_edit_closeProjectSavePrompt_dialog( wxWindow* parent )
:
rc_closeProjectSavePrompt_dialog( parent )
{
    projectCloseFlag = 0;
}

void rcbasic_edit_closeProjectSavePrompt_dialog::onCloseProjectSaveCancel( wxCommandEvent& event )
{
// TODO: Implement onCloseProjectSaveCancel
    projectCloseFlag = projectCloseFlag_CANCEL;
    Close();
}

void rcbasic_edit_closeProjectSavePrompt_dialog::onCloseProjectSaveDontSave( wxCommandEvent& event )
{
// TODO: Implement onCloseProjectSaveDontSave
    projectCloseFlag = projectCloseFlag_DONT_SAVE;
    Close();
}

void rcbasic_edit_closeProjectSavePrompt_dialog::onCloseProjectSaveOk( wxCommandEvent& event )
{
// TODO: Implement onCloseProjectSaveOk
    projectCloseFlag = projectCloseFlag_SAVE;
    Close();
}

int rcbasic_edit_closeProjectSavePrompt_dialog::getProjectCloseFlag()
{
    return projectCloseFlag;
}
