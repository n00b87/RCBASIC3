#include "rcbasic_edit_projectSettings_dialog.h"

rcbasic_edit_projectSettings_dialog::rcbasic_edit_projectSettings_dialog( wxWindow* parent )
:
rc_projectSettings_dialog( parent )
{
    rcbasic_edit_frame* frame = (rcbasic_edit_frame*)parent;
    project = frame->getActiveProject();

    if(!project)
        return;

    m_projectName_textCtrl->SetValue(project->getName());
    m_mainSource_textCtrl->SetValue(project->getMainSource().GetFullPath());
    m_author_textCtrl->SetValue(project->getAuthor());
    m_website_textCtrl->SetValue(project->getWebsite());
    m_description_textCtrl->SetValue(project->getDescription());

    //wxListBox * m_files_listBox;
    //rcbasic_project project;
    std::vector<rcbasic_project_node*> nodes = project->getSourceFiles();
    wxString cwd = wxGetCwd();
    wxSetWorkingDirectory(project->getLocation());
    for(int i = 0; i < nodes.size(); i++)
    {
        wxFileName tmp = nodes[i]->getPath();
        tmp.MakeRelativeTo(project->getLocation());
        m_files_listBox->AppendAndEnsureVisible(tmp.GetFullPath());
    }

    m_files_listBox->SetSelection(0);
    wxSetWorkingDirectory(cwd);
}

void rcbasic_edit_projectSettings_dialog::onCancelButtonClick( wxCommandEvent& event )
{
// TODO: Implement onCancelButtonClick
    Close();
}

void rcbasic_edit_projectSettings_dialog::onOKButtonClick( wxCommandEvent& event )
{
// TODO: Implement onOKButtonClick
    wxString project_name = m_projectName_textCtrl->GetValue();
    wxString mainSource = m_mainSource_textCtrl->GetValue();
    wxString author = m_author_textCtrl->GetValue();
    wxString website = m_website_textCtrl->GetValue();
    wxString description = m_description_textCtrl->GetValue();

    wxString cwd = wxGetCwd();
    wxSetWorkingDirectory(project->getLocation());
    wxFileName mainSource_fname(mainSource);

    if(!mainSource_fname.Exists())
    {
        wxMessageBox(_("Main Source cannot be set. Cannot find [") + mainSource + _("]"));
        wxSetWorkingDirectory(cwd);
        return;
    }


    for(int i = 0; i < removed_files.size(); i++)
    {
        project->removeSourceFile(removed_files[i]);
    }

    wxSetWorkingDirectory(cwd);

    project->setName(project_name);
    project->setMainSource(mainSource_fname.GetFullPath());
    project->setAuthor(author);
    project->setWebsite(website);
    project->setDescription(description);


    Close();
}


void rcbasic_edit_projectSettings_dialog::onFileSelection( wxCommandEvent& event )
{
// TODO: Implement onFileSelection
}

void rcbasic_edit_projectSettings_dialog::onAddFilesButtonClick( wxCommandEvent& event )
{
// TODO: Implement onAddFilesButtonClick
}

void rcbasic_edit_projectSettings_dialog::onRemoveSelectedButtonClick( wxCommandEvent& event )
{
// TODO: Implement onRemoveSelectedButtonClick
    //wxListBox m_files_listBox;
    int i = m_files_listBox->GetSelection();
    //wxPrintf(_("i = %d\n"), i);
    if(i < 0)
        return;

    //wxListBox m_files_listbox;
    removed_files.push_back(m_files_listBox->GetString(i));
    m_files_listBox->Delete(i);
}

void rcbasic_edit_projectSettings_dialog::onFilePropertiesButtonClick( wxCommandEvent& event )
{
// TODO: Implement onFilePropertiesButtonClick
}
