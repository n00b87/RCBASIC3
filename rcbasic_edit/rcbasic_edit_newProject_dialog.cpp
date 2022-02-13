#include "rcbasic_edit_newProject_dialog.h"
#include "projects.h"

rcbasic_edit_newProject_dialog::rcbasic_edit_newProject_dialog( wxWindow* parent )
:
rc_newProject_dialog( parent )
{
    newProjectValue = false;
}

void rcbasic_edit_newProject_dialog::cancelNewProject( wxCommandEvent& event )
{
// TODO: Implement cancelNewProject
    Close();
}

void rcbasic_edit_newProject_dialog::createNewProject( wxCommandEvent& event )
{
    newProjectValue = true;
    Close();
// TODO: Implement createNewProject
    /*wxString project_name = projectName_field->GetValue();
    wxString project_location = projectLocation_picker->GetPath();
    int main_source_flag = projectCreateMain_radio->GetValue() ? 0 : 1;
    wxString main_source_value = main_source_flag==0 ? projectNewMain_field->GetValue() : projectExistingFile_picker->GetTextCtrlValue();
    wxString project_author = projectAuthor_field->GetValue();
    wxString project_website = projectWebsite_field->GetValue();
    wxString project_description = projectDescription_field->GetValue();
    */

    //rcbasic_project new_project(project_name, project_location, main_source_flag, main_source_value, project_author, project_website, project_description);

    //wxString str, str2;
    //str.Printf(wxT("Sash Position: %d"), sashPOS);
    //str2.Printf(wxT("Sash Size: %d\n"), sashSize);

    //wxPuts(_("Project_Location: ") + project_location);
    //wxPuts(_("Main Source: ") + main_source_value);

    //open_projects.push_back(new_project);
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

bool rcbasic_edit_newProject_dialog::getNewProjectValue()
{
    return newProjectValue;
}
