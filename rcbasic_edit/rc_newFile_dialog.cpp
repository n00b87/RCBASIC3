#include "rc_newFile_dialog.h"

rcbasic_edit_newFile_dialog::rcbasic_edit_newFile_dialog( wxWindow* parent )
:
rc_newFile_dialog( parent )
{
    newFileFlag = 0;
}

void rcbasic_edit_newFile_dialog::onCreateNewSourceCancel( wxCommandEvent& event )
{
// TODO: Implement onCreateNewSourceCancel
    newFileFlag = newFileFlag_CANCEL;
    Close();
}

void rcbasic_edit_newFile_dialog::onCreateNewSourceOk( wxCommandEvent& event )
{
// TODO: Implement onCreateNewSourceOk
    newFileFlag = newFileFlag_OK;
}

int rcbasic_edit_newFile_dialog::getNewFileFlag()
{
    return newFileFlag;
}
