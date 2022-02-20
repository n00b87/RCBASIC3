#include "rcbasic_edit_projectSettings_dialog.h"
#include "rcbasic_edit_fileProperties_dialog.h"

rcbasic_edit_projectSettings_dialog::rcbasic_edit_projectSettings_dialog( wxWindow* parent )
:
rc_projectSettings_dialog( parent )
{
    parent_frame = (rcbasic_edit_frame*)parent;
    current_project = parent_frame->getActiveProject();

    projectSettings_flag = PROJECT_SETTINGS_CANCEL;

    if(!current_project)
    {
        Close();
    }

    new_project = new rcbasic_project();
    new_project->copyFromProject(current_project);

    m_projectName_textCtrl->SetValue(new_project->getName());
    wxFileName ms_fname = new_project->getMainSource();

    wxFileName ms_fname_rel = ms_fname;
    ms_fname_rel.MakeRelativeTo(new_project->getLocation());

    wxFileName ms_fname_abs = ms_fname;
    ms_fname_abs.MakeAbsolute();

    //m_mainSource_textCtrl->SetValue(ms_fname.GetFullPath());
    m_author_textCtrl->SetValue(new_project->getAuthor());
    m_website_textCtrl->SetValue(new_project->getWebsite());
    m_description_textCtrl->SetValue(new_project->getDescription());

    //wxListBox * m_files_listBox;
    //wxCheckListBox m_mainSource_checkList;
    //rcbasic_project project;
    std::vector<rcbasic_project_node*> nodes = new_project->getSourceFiles();
    wxString cwd = wxGetCwd();
    wxSetWorkingDirectory(new_project->getLocation());

    int ms_index = 0;

    for(int i = 0; i < nodes.size(); i++)
    {
        if(!nodes[i])
            continue;
        wxFileName tmp = nodes[i]->getPath();

        switch(nodes[i]->getLocationStoreType())
        {
            case STORE_LOCATION_RELATIVE:
                tmp.MakeRelativeTo(new_project->getLocation());
                break;
            case STORE_LOCATION_ABSOLUTE:
                tmp.MakeAbsolute();
                break;
        }

        m_files_listBox->AppendAndEnsureVisible(tmp.GetFullPath());
        m_mainSource_listBox->AppendAndEnsureVisible(tmp.GetFullPath());
    }

    for(int i = 0; i < m_mainSource_listBox->GetCount(); i++)
    {
        if(m_mainSource_listBox->GetString(i).compare(ms_fname_rel.GetFullPath()) == 0 || m_mainSource_listBox->GetString(i).compare(ms_fname_abs.GetFullPath()) == 0)
        {
            //wxPuts(_("FOIND: ")+ m_mainSource_listBox->GetString(i));
            m_mainSource_listBox->SetSelection(i);
            m_mainSource_textCtrl->SetValue(m_mainSource_listBox->GetString(i));
            break;
        }
    }

    wxSetWorkingDirectory(cwd);
}

void rcbasic_edit_projectSettings_dialog::onCancelButtonClick( wxCommandEvent& event )
{
// TODO: Implement onCancelButtonClick
    new_project->setPointersNull();
    delete new_project;

    //wxPuts(_("THE END"));

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
    wxSetWorkingDirectory(new_project->getLocation());
    wxFileName mainSource_fname(mainSource);

    if(!mainSource_fname.Exists())
    {
        wxMessageBox(_("Main Source cannot be set. Cannot find [") + mainSource + _("]"));
        wxSetWorkingDirectory(cwd);
        return;
    }

    //wxPuts(_("--------------"));

    for(int i = 0; i < new_project->getSourceFiles().size(); i++)
    {
        rcbasic_project_node* node = new_project->getSourceFiles()[i];

         node->setAsTemp(false);
    }

    //wxPrintf(_("SOURCE SIZE: %d\n\n"), new_project->getSourceFiles().size());

    wxSetWorkingDirectory(cwd);

    new_project->setName(project_name);
    new_project->setMainSource(mainSource_fname.GetFullPath());
    new_project->setAuthor(author);
    new_project->setWebsite(website);
    new_project->setDescription(description);

    int i = parent_frame->getProjectFromRoot(new_project->getRootNode());

    if(i >= 0)
    {
        current_project->setPointersNull();
        delete current_project;
        parent_frame->setOpenProject(i, new_project);
    }

    projectSettings_flag = PROJECT_SETTINGS_OK;

    Close();
}


void rcbasic_edit_projectSettings_dialog::onFileSelection( wxCommandEvent& event )
{
// TODO: Implement onFileSelection

    //NOTE: Probably won't be doing anything with this event but I am too lazy to remove it
}

void rcbasic_edit_projectSettings_dialog::onAddFilesButtonClick( wxCommandEvent& event )
{
// TODO: Implement onAddFilesButtonClick
    if(!new_project)
        return;

    wxArrayString sourceFiles = parent_frame->openMultiFileDialog( _("Open RCBasic Source file"), _("RCBasic Source files (*.bas)|*.bas"), wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_MULTIPLE);

    for(int i = 0; i < sourceFiles.size(); i++)
    {
        wxFileName fname(sourceFiles[i]);
        if(!fname.Exists())
            continue;

        fname.MakeRelativeTo(new_project->getLocation());
        if(new_project->addSourceFile(fname.GetFullPath(), STORE_LOCATION_RELATIVE, false))
        {
            m_files_listBox->AppendAndEnsureVisible(fname.GetFullPath());
            m_mainSource_listBox->AppendAndEnsureVisible(fname.GetFullPath());
        }
    }
}

void rcbasic_edit_projectSettings_dialog::onRemoveSelectedButtonClick( wxCommandEvent& event )
{
// TODO: Implement onRemoveSelectedButtonClick
    //wxListBox m_files_listBox;
    int selected_item = m_files_listBox->GetSelection();
    //wxPrintf(_("i = %d\n"), i);
    if(selected_item < 0)
        return;

    //wxFileName main_source = project->getMainSource();
    //main_source.MakeRelativeTo(project->getLocation());

    if(m_files_listBox->GetString(selected_item).compare(m_mainSource_textCtrl->GetValue())==0)
    {
        wxMessageBox(_("Cannot remove \"") + m_mainSource_textCtrl->GetValue() + _("\" while it is set as main source."));
        return;
    }

    //wxListBox m_files_listbox;

    std::vector<rcbasic_project_node*> nodes = new_project->getSourceFiles();

    for(int i = 0; i < new_project->getSourceFiles().size(); i++)
    {
        rcbasic_project_node* node = nodes[i];
        wxFileName fname_rel = node->getPath();
        wxFileName fname_abs = node->getPath();
        fname_rel.MakeRelativeTo(new_project->getLocation());
        fname_abs.MakeAbsolute();

        if(fname_rel.GetFullPath().compare(m_files_listBox->GetString(selected_item))==0 ||
           fname_abs.GetFullPath().compare(m_files_listBox->GetString(selected_item))==0)
        {
            new_project->removeSourceFile(node->getPath().GetFullPath());
            //node->setAsAddFile(false);
            //wxPrintf(_("SET NODE to remove: [%d] ")+ m_files_listBox->GetString(selected_item) +_("\n"), node->getAddRemoveFlag());
            //removed_files.push_back(node);
            //break;
        }
    }

    //removed_files.push_back(m_files_listBox->GetString(selected_item));
    m_files_listBox->Delete(selected_item);
    m_mainSource_listBox->Delete(selected_item);
}

void rcbasic_edit_projectSettings_dialog::onFilePropertiesButtonClick( wxCommandEvent& event )
{
    openProperties();
}

void rcbasic_edit_projectSettings_dialog::openProperties()
{
// TODO: Implement onFilePropertiesButtonClick
    if(m_files_listBox->GetSelection()<0)
        return;

    int selected_item = m_files_listBox->GetSelection();

    rcbasic_project_node* f_node;
    for(int i = 0; i < new_project->getSourceFiles().size(); i++)
    {
        f_node = new_project->getSourceFiles()[i];
        wxFileName fname(f_node->getPath().GetFullPath());
        if(f_node->getLocationStoreType()==STORE_LOCATION_RELATIVE)
            fname.MakeRelativeTo(new_project->getLocation());
        else
            fname.MakeAbsolute();

        //wxPuts(_("Compare1: ") + fname.GetFullPath() );
        //wxPuts(_("Compare2: ") + m_files_listBox->GetString(selected_item));

        if(fname.GetFullPath().compare(m_files_listBox->GetString(selected_item))==0)
            break;
        f_node = NULL;
    }

    if(!f_node)
    {
        //wxPuts(_("Could not find file node"));
        return;
    }

    rcbasic_edit_fileProperties_dialog fp_dialog(this, f_node);
    fp_dialog.ShowModal();

    wxFileName node_fname = f_node->getPath();
    if(f_node->getLocationStoreType()==STORE_LOCATION_RELATIVE)
        node_fname.MakeRelativeTo(new_project->getLocation());
    else
        node_fname.MakeAbsolute();

    m_files_listBox->SetString(selected_item, node_fname.GetFullPath());
    m_mainSource_listBox->SetString(selected_item, node_fname.GetFullPath());

    wxFileName node_fname_rel = node_fname;
    node_fname_rel.MakeRelativeTo(new_project->getLocation());

    wxFileName node_fname_abs = node_fname;
    node_fname_abs.MakeAbsolute();

    if(node_fname.GetFullPath().compare(m_mainSource_textCtrl->GetValue())==0 ||
       node_fname_rel.GetFullPath().compare(m_mainSource_textCtrl->GetValue())==0 ||
       node_fname_abs.GetFullPath().compare(m_mainSource_textCtrl->GetValue())==0)
    {
        m_mainSource_textCtrl->SetValue(node_fname.GetFullPath());
    }
}

void rcbasic_edit_projectSettings_dialog::onMainSourceListBoxSelection( wxCommandEvent& event )
{
// TODO: Implement onMainSourceListBoxSelection
    //wxListBox m_mainSource_listBox;

    int selected_item = event.GetSelection();

    if(selected_item < 0)
        return;

    m_mainSource_textCtrl->SetValue(m_mainSource_listBox->GetString(selected_item));

}

void rcbasic_edit_projectSettings_dialog::onFileDoubleClick( wxCommandEvent& event )
{
// TODO: Implement onFileDoubleClick
    openProperties();
}
