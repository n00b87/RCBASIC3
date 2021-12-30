#include "rcbasic_edit_newProject_dialog.h"

rcbasic_edit_newProject_dialog::rcbasic_edit_newProject_dialog( wxWindow* parent )
:
rc_newProject_dialog( parent )
{

}

void rcbasic_edit_newProject_dialog::cancelNewProject( wxCommandEvent& event )
{
// TODO: Implement cancelNewProject
    Close();
}

void rcbasic_edit_newProject_dialog::createNewProject( wxCommandEvent& event )
{
// TODO: Implement createNewProject
}

void rcbasic_edit_newProject_dialog::createMainSourceRadioSelected( wxCommandEvent& event )
{
    projectNewMain_field->Enable( true );
    projectExistingFile_picker->Enable( false );
}

void rcbasic_edit_newProject_dialog::copyExistingSourceRadioSelected( wxCommandEvent& event )
{
    projectNewMain_field->Enable( false );
    projectExistingFile_picker->Enable( true );
}
