#include <wx/string.h>

#include "rcbasic_edit_frame.h"
#include "rcbasic_edit_newProject_dialog.h"
#include "rc_closeProjectSavePrompt_dialog.h"
#include "rc_find_dialog.h"

rcbasic_edit_txtCtrl::rcbasic_edit_txtCtrl(wxFileName src_path, wxAuiNotebook* parent_nb)
{
    sourcePath = src_path;
    txtCtrl = new wxStyledTextCtrl(parent_nb, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, src_path.GetFullName());
    text_changed = false;
}

rcbasic_edit_txtCtrl::~rcbasic_edit_txtCtrl()
{
    delete txtCtrl;
}

wxStyledTextCtrl* rcbasic_edit_txtCtrl::getTextCtrl()
{
    return txtCtrl;
}

wxFileName rcbasic_edit_txtCtrl::getSourcePath()
{
    return sourcePath;
}

void rcbasic_edit_txtCtrl::setFileName(wxFileName fname)
{
    sourcePath = fname;
}

void rcbasic_edit_txtCtrl::setTextCtrl(wxStyledTextCtrl* t_ctrl)
{
    txtCtrl = t_ctrl;
}

void rcbasic_edit_txtCtrl::setTextChangedFlag(bool flag)
{
    //wxPrintf(_("TEXT CHANGED: %d\n"), flag);
    text_changed = flag;
}

bool rcbasic_edit_txtCtrl::getTextChangedFlag()
{
    return text_changed;
}

void rcbasic_edit_txtCtrl::setTempText(wxString tmp)
{
    temp_text = tmp;
}

wxString rcbasic_edit_txtCtrl::getTempText()
{
    return temp_text;
}





rcbasic_edit_frame::rcbasic_edit_frame( wxWindow* parent )
:
rc_ideFrame( parent )
{
    messageWindowVisible = true;
    m_showMessageWindow_menuItem->Check(messageWindowVisible);

    toolbarVisible = true;
    m_showToolbar_menuItem->Check(toolbarVisible);

    sideBarVisible = true;
    m_showSideBar_menuItem->Check(sideBarVisible);

    context_project = NULL;
    active_project = NULL;

    project_tree_imageList = new wxImageList(16,16,true);
    project_tree_rootImage = project_tree_imageList->Add(wxBitmap(wxImage("gfx/rcbasic16.png")));
    project_tree_folderImage  = project_tree_imageList->Add(wxArtProvider::GetBitmap( wxART_FOLDER, wxART_MENU ));
    project_tree_fileImage = project_tree_imageList->Add(wxArtProvider::GetBitmap( wxART_NORMAL_FILE, wxART_MENU ));
    project_tree->AssignImageList(project_tree_imageList);

    project_tree->AddRoot(_("Projects"), project_tree_rootImage);

    //Load recent files and projects
    wxString editor_path = wxStandardPaths::Get().GetExecutablePath();
    wxFileName data_path(editor_path);
    data_path.AppendDir(_("data"));

    wxFileName recent_file_path = data_path;
    recent_file_path.SetName(_("recent_files"));
    recent_file_path.SetExt(_("data"));

    if(recent_file_path.Exists())
    {
        wxFile f;
        if(f.Open(recent_file_path.GetFullPath()))
        {
            wxString contents;
            f.ReadAll(&contents);
            f.Close();

            wxString c_line;
            c_line.clear();
            int rec_count = 0;

            int RECENT_ID = RECENT_FILE_OFFSET_ID;

            wxMenuItem* recent_item;

            for(int i = 0; i < contents.Length(); i++)
            {
                if(contents.substr(i, 1).compare(_("\n"))==0)
                {
                    recent_files[rec_count] = c_line;
                    recent_files_items[rec_count] = c_line;
                    rec_count++;
                    if(rec_count >= 9)
                        break;
                    if(c_line.compare(_(""))==0)
                        continue;
                    recent_item = m_recentFiles_menu->Append(RECENT_ID, c_line);
                    m_recentFiles_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( onRecentFileSelect ), this, recent_item->GetId());
                    RECENT_ID++;
                    c_line.clear();
                }
                else
                {
                    c_line += contents.substr(i, 1);
                }
            }

            f.Close();
        }
    }


    wxFileName recent_project_path = data_path;
    recent_project_path.SetName(_("recent_projects"));
    recent_project_path.SetExt(_("data"));

    if(recent_project_path.Exists())
    {
        wxFile f;
        if(f.Open(recent_project_path.GetFullPath()))
        {
            wxString contents;
            f.ReadAll(&contents);
            f.Close();

            wxString c_line;
            c_line.clear();
            int rec_count = 0;

            int RECENT_ID = RECENT_PROJECT_OFFSET_ID;

            wxMenuItem* recent_item;

            for(int i = 0; i < contents.Length(); i++)
            {
                if(contents.substr(i, 1).compare(_("\n"))==0)
                {
                    recent_projects[rec_count] = c_line;
                    recent_projects_items[rec_count] = c_line;
                    rec_count++;
                    if(rec_count >= 9)
                        break;
                    if(c_line.compare(_(""))==0)
                        continue;
                    recent_item = m_recentProjects_menu->Append(RECENT_ID, c_line);
                    m_recentProjects_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( onRecentProjectSelect ), this, recent_item->GetId());
                    RECENT_ID++;
                    c_line.clear();
                }
                else
                {
                    c_line += contents.substr(i, 1);
                }
            }

            f.Close();
        }
    }
}

void rcbasic_edit_frame::onRecentProjectSelect( wxCommandEvent& event )
{
    int id = event.GetId();

    int item = id - RECENT_PROJECT_OFFSET_ID;

    if(item >= 0 && item < 10)
    {
        openProject(wxFileName(recent_projects_items[item]));
    }
}

void rcbasic_edit_frame::onRecentFileSelect( wxCommandEvent& event )
{
    int id = event.GetId();

    int item = id - RECENT_FILE_OFFSET_ID;

    if(item >= 0 && item < 10)
    {
        openSourceFile(wxFileName(recent_files_items[item]));
    }
}

void rcbasic_edit_frame::onEditorClose( wxCloseEvent& event )
{
    wxString editor_path = wxStandardPaths::Get().GetExecutablePath();
    wxFileName data_path(editor_path);
    data_path.AppendDir(_("data"));

    //wxPuts(_("Making data path at ") + data_path.GetPath());

    if(!wxDirExists(data_path.GetPath()))
    {
        if(!wxMkdir(data_path.GetPath()))
            return;
    }

    wxFileName recent_file_path = data_path;
    recent_file_path.SetName(_("recent_files"));
    recent_file_path.SetExt(_("data"));

    wxFileName recent_project_path = data_path;
    recent_project_path.SetName(_("recent_projects"));
    recent_project_path.SetExt(_("data"));

    wxFile f;

    //Save Recent Files
    if(!f.Open(recent_file_path.GetFullPath(), wxFile::write))
    {
        f.Create(recent_file_path.GetFullPath(), true);
    }

    //wxPuts(_("writing files"));

    if(f.IsOpened())
    {

        for(int i = 0; i < 10; i++)
        {
            f.Write(recent_files[i]+_("\n"));
        }
        f.Close();
    }

    //Save Recent Projects
    if(!f.Open(recent_project_path.GetFullPath(), wxFile::write))
    {
        f.Create(recent_project_path.GetFullPath(), true);
    }

    //wxPuts(_("writing projects"));

    if(f.IsOpened())
    {
        for(int i = 0; i < 10; i++)
        {
            //wxPuts(_("PF: ") + recent_projects[i]);
            f.Write(recent_projects[i]+_("\n"));
        }
        //wxPuts(_("***end project write***"));
        f.Close();
    }
    this->Destroy();
}

void rcbasic_edit_frame::newProjectMenuSelect( wxCommandEvent& event)
{
    rcbasic_edit_newProject_dialog* newProject_win = new rcbasic_edit_newProject_dialog(this);
    newProject_win->ShowModal();

    if(newProject_win->getNewProjectValue())
    {
        wxString project_name = newProject_win->projectName_field->GetValue();
        wxString project_location = newProject_win->projectLocation_picker->GetPath();
        int main_source_flag = newProject_win->projectCreateMain_radio->GetValue() ? 0 : 1;
        wxString main_source_value = main_source_flag==0 ? newProject_win->projectNewMain_field->GetValue() : newProject_win->projectExistingFile_picker->GetTextCtrlValue();
        wxString project_author = newProject_win->projectAuthor_field->GetValue();
        wxString project_website = newProject_win->projectWebsite_field->GetValue();
        wxString project_description = newProject_win->projectDescription_field->GetValue();

        rcbasic_project* new_project = new rcbasic_project(project_name, project_location, main_source_flag, main_source_value, project_author, project_website, project_description);
        if(!new_project->projectExists())
        {
            delete new_project;
            return;
        }
        new_project->setRootNode(project_tree->AppendItem(project_tree->GetRootItem(), project_name, project_tree_folderImage));
        new_project->addSourceFile(new_project->getMainSource().GetFullPath());

        new_project->setLastProjectSave();

        //project_tree->AppendItem(new_project->getRootNode(), new_project->getMainSource().GetFullPath());

        open_projects.push_back(new_project);
        addRecentProject(new_project);

        if(!active_project)
        {
            active_project = new_project;
            if(active_project)
            {
                wxSetWorkingDirectory(active_project->getLocation());
            }

            project_tree->SetItemBold(active_project->getRootNode(), true);
        }

        int new_project_index = getProjectFromRoot(new_project->getRootNode());
        if(new_project_index >= 0)
            updateProjectTree(new_project_index);

        //----
        rcbasic_edit_txtCtrl* txtCtrl_obj = openFileTab(new_project, new_project->getMainSource());
        txtCtrl_obj->setTextChangedFlag(false);
    }

    //wxPuts(_("Project_Location: ") + project_location);
    //wxPuts(_("Main Source: ") + main_source_value);

    newProject_win->Destroy();
}

void rcbasic_edit_frame::newFileMenuSelect( wxCommandEvent& event)
{
    //wxPuts(_("New file Dialog"));
    createNewFile(active_project);
}

void rcbasic_edit_frame::openProjectMenuSelect( wxCommandEvent& event )
{
    wxFileName project_fname = openFileDialog(_("Open Project"), _("RCBasic Project (*.rcprj)|*.rcprj"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    openProject(project_fname);
}

void rcbasic_edit_frame::openFileMenuSelect( wxCommandEvent& event )
{
    wxFileName fname = openFileDialog( _("Open RCBasic Source file"), _("RCBasic Source files (*.bas)|*.bas"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    openSourceFile(fname);
}

void rcbasic_edit_frame::openProject(wxFileName project_path)
{
    for(int i = 0; i < open_projects.size(); i++)
    {
        if(open_projects[i]->getProjectFileLocation().compare(project_path.GetFullPath())==0)
            return;
    }

    if(project_path.GetFullPath().compare(_(""))==0)
        return;
    wxFile project_file;
    if(!project_file.Open(project_path.GetFullPath()))
    {
        wxMessageBox(_("Could not open project file"));
        return;
    }
    else
    {

        wxString contents;
        project_file.ReadAll(&contents);
        project_file.Close();

        contents += _("\n");

        wxString project_property;
        wxString project_name;
        wxString project_main;
        wxString project_author;
        wxString project_website;
        wxString project_description;
        std::vector<wxString> project_source;

        wxString property_name;
        wxString property_value;
        for(int i = 0; i < contents.Length(); i++)
        {
            if(contents.substr(i, 1).compare(_("\n"))==0)
            {
                //wxPuts( _("PROPERTY [") + project_property.substr(0,project_property.find_first_of(_(":"))) + _("]={") + project_property.substr(project_property.find_first_of(_(":"))+1) + _("}\n") );
                property_name = project_property.substr(0,project_property.find_first_of(_(":")));
                property_value = project_property.substr(project_property.find_first_of(_(":"))+1);

                if(property_name.compare(_("PROJECT_NAME"))==0)
                {
                    project_name = property_value;
                }
                else if(property_name.compare(_("PROJECT_MAIN"))==0)
                {
                    project_main = property_value;
                }
                else if(property_name.compare(_("AUTHOR"))==0)
                {
                    project_author = property_value;
                }
                else if(property_name.compare(_("WEBSITE"))==0)
                {
                    project_website = property_value;
                }
                else if(property_name.compare(_("DESCRIPTION"))==0)
                {
                    project_description = property_value;
                }
                else if(property_name.compare(_("SOURCE"))==0)
                {
                    project_source.push_back(property_value);
                }
                project_property = _("");
            }
            else
            {
                project_property += contents.substr(i, 1);
            }
        }

        rcbasic_project* project = new rcbasic_project(project_name, project_path.GetPath(true), RCBASIC_PROJECT_SOURCE_OPEN, project_main, project_author, project_website, project_description);
        for(int i = 0; i < project_source.size(); i++)
        {
            project->addSourceFile(project_source[i]);
        }

        project->setRootNode(project_tree->AppendItem(project_tree->GetRootItem(), project_name, project_tree_folderImage));
        project->setLastProjectSave();
        open_projects.push_back(project);

        project->setProjectFileLocation(project_path.GetFullPath());
        addRecentProject(project);

        if(!active_project)
        {
            active_project = project;
            if(active_project)
            {
                wxSetWorkingDirectory(active_project->getLocation());
            }

            project_tree->SetItemBold(active_project->getRootNode(), true);
        }

        int project_index = getProjectFromRoot(project->getRootNode());
        if(project_index >= 0)
            updateProjectTree(project_index);

        rcbasic_edit_txtCtrl* txtCtrl_obj;
        txtCtrl_obj = openFileTab(project, project->getMainSource());
        txtCtrl_obj->setTextChangedFlag(false);
    }
}

void rcbasic_edit_frame::openSourceFile(wxFileName source_path)
{
    if(source_path.GetFullPath().compare(_(""))==0)
        return;
    wxFile s_file;
    if(!s_file.Open(source_path.GetFullPath()))
    {
        wxMessageBox(_("Could not open file"));
        return;
    }
    else
    {
        wxString contents;
        s_file.ReadAll(&contents);
        s_file.Close();

        addRecentFile(source_path);

        rcbasic_edit_txtCtrl* txtCtrl_obj = openFileTab(NULL, source_path);
        txtCtrl_obj->getTextCtrl()->ClearAll();
        txtCtrl_obj->getTextCtrl()->SetText(contents);
        txtCtrl_obj->getTextCtrl()->EmptyUndoBuffer();
        txtCtrl_obj->setTextChangedFlag(false);
    }
}

int rcbasic_edit_frame::getOpenFileFromSelection()
{
    int selected_page = sourceFile_auinotebook->GetSelection();
    for(int i = 0; i < open_files.size(); i++)
    {
        if(open_files[i]->getTextCtrl()==sourceFile_auinotebook->GetPage(selected_page))
        {
            //wxPuts(_("File = ") + open_files[i]->getSourcePath().GetFullPath());
            return i;
        }
    }

    return -1;
}

void rcbasic_edit_frame::saveFile(int openFile_index, int flag=0)
{
    last_fileSave_flag = false;

    if(openFile_index < 0)
        return;

    int selected_page = sourceFile_auinotebook->GetSelection();

    wxFileName fname = open_files[openFile_index]->getSourcePath();

    if(flag==FILE_SAVEAS_FLAG)
    {
        fname = openFileDialog(_("Save RCBasic Source File As"), _("RCBasic Source files (*.bas)|*.bas"),wxFD_SAVE);
        if(fname.GetFullPath().compare(_(""))==0)
            return;
    }

    wxFile f;

    if(!f.Open(fname.GetFullPath(), wxFile::write))
    {
        if(!f.Create(fname.GetFullPath(), true))
        {
            wxMessageBox(_("Could not open file"));
            return;
        }
    }

    f.Write( open_files[openFile_index]->getTextCtrl()->GetText() );
    f.Close();

    if(flag==FILE_SAVEAS_FLAG)
    {
        for(int p_index = 0; p_index < open_projects.size(); p_index++)
        {
            std::vector<rcbasic_project_node*> source_files = open_projects[p_index]->getSourceFiles();
            for(int f_index = 0; f_index < source_files.size(); f_index++)
            {
                if(source_files[f_index]->getPath().GetFullPath().compare(fname.GetFullPath()))
                {
                    source_files[f_index]->setTextCtrl(NULL);
                    source_files[f_index]->setTextChangedFlag(false);
                }
            }
        }

        //wxPuts(_("Change filename to ") + fname.GetFullPath());

        sourceFile_auinotebook->SetPageText(selected_page, fname.GetFullName());
        open_files[openFile_index]->setFileName(fname);
    }

    open_files[openFile_index]->setTextChangedFlag(false);

    last_fileSave_flag = true;
}

void rcbasic_edit_frame::onSaveFileMenuSelect( wxCommandEvent& event )
{
    saveFile(getOpenFileFromSelection());
}

void rcbasic_edit_frame::onSaveFileAsMenuSelect( wxCommandEvent& event )
{
    saveFile(getOpenFileFromSelection(), FILE_SAVEAS_FLAG);
}

void rcbasic_edit_frame::onSaveProjectMenuSelect( wxCommandEvent& event )
{
    if(!active_project)
    {
        wxMessageBox(_("There is no active project selected"));
        return;
    }

    wxFileName project_fname = wxFileName(active_project->getProjectFileLocation());

    if(!wxDirExists(active_project->getLocation()))
    {
        project_fname = openFileDialog(_("Save Project As"), _("RCBasic Project (*.rcprj)|*.rcprj"), wxFD_SAVE);
        if(project_fname.GetFullPath().compare(_(""))==0)
            return;
    }

    for(int i = 0; i < open_files.size(); i++)
    {
        for(int pf = 0; pf < active_project->getSourceFiles().size(); pf++)
        {
            if(open_files[i]->getSourcePath().GetFullPath().compare(active_project->getSourceFiles()[pf]->getPath().GetFullPath()) == 0)
            {
                saveFile(i);
            }
        }
    }

    active_project->saveProject(project_fname);
}

void rcbasic_edit_frame::onSaveProjectAsMenuSelect( wxCommandEvent& event )
{
    if(!active_project)
    {
        wxMessageBox(_("There is no active project selected"));
        return;
    }

    wxFileName project_fname = wxFileName(active_project->getProjectFileLocation());

    project_fname = openFileDialog(_("Save Project As"), _("RCBasic Project (*.rcprj)|*.rcprj"), wxFD_SAVE);
    if(project_fname.GetFullPath().compare(_(""))==0)
        return;

    for(int i = 0; i < open_files.size(); i++)
    {
        for(int pf = 0; pf < active_project->getSourceFiles().size(); pf++)
        {
            if(open_files[i]->getSourcePath().GetFullPath().compare(active_project->getSourceFiles()[pf]->getPath().GetFullPath()) == 0)
            {
                saveFile(i);
            }
        }
    }

    active_project->saveProject(project_fname);
}

void rcbasic_edit_frame::onSaveAllMenuSelect( wxCommandEvent& event )
{
    for(int i = 0; i < open_files.size(); i++)
    {
        if(open_files[i]->getTextChangedFlag())
        {
            saveFile(i);
        }
    }

    for(int i = 0; i < open_projects.size(); i++)
    {
        open_projects[i]->saveProject(wxFileName(open_projects[i]->getProjectFileLocation()));
    }
}

int rcbasic_edit_frame::closeFile(int notebook_page)
{
    if(notebook_page < 0)
        return -1;

    int rtn_val = -1;

    for(int i = 0; i < open_files.size(); i++)
    {
        if(open_files[i]->getTextCtrl()==sourceFile_auinotebook->GetPage(notebook_page))
        {
            if(open_files[i]->getTextChangedFlag())
            {
                wxString title = _("Closing ") + open_files[i]->getSourcePath().GetFullName();
                rcbasic_edit_closeFileSavePrompt_dialog saveFile_dialog(this, title);
                saveFile_dialog.ShowModal();

                switch(saveFile_dialog.getFileCloseFlag())
                {
                    case fileCloseFlag_SAVE:
                        saveFile(i);
                        if(!last_fileSave_flag)
                            return fileCloseFlag_SAVE;
                        break;
                    case fileCloseFlag_DONT_SAVE:
                        rtn_val = fileCloseFlag_DONT_SAVE;
                        break;
                    case fileCloseFlag_CANCEL:
                        return fileCloseFlag_CANCEL;
                }
            }
            open_files.erase(open_files.begin()+i);
            sourceFile_auinotebook->DeletePage(notebook_page);
            break;
        }
    }
    return rtn_val;
}

void rcbasic_edit_frame::onCloseFileMenuSelect( wxCommandEvent& event )
{
    int current_file = sourceFile_auinotebook->GetSelection();

    if(current_file < 0)
        return;

    closeFile(current_file);
}

void rcbasic_edit_frame::onCloseProjectMenuSelect( wxCommandEvent& event )
{
    if(!active_project)
        return;

    closeProject(active_project);
}

int rcbasic_edit_frame::getProjectFromRoot(wxTreeItemId node)
{
    for(int i = 0; i < open_projects.size(); i++)
    {
        if(open_projects[i]->getRootNode()==node)
            return i;
    }
    return -1;
}

void rcbasic_edit_frame::updateProjectTree(int project_index)
{
    wxTreeItemId project_node = open_projects[project_index]->getRootNode();
    project_tree->DeleteChildren(project_node);
    std::vector<rcbasic_project_node*> source_files = open_projects[project_index]->getSourceFiles();

    wxFileName node_label;
    rcbasic_treeItem_data* data;

    for(int i = 0; i < source_files.size(); i++)
    {
        node_label = wxFileName(source_files[i]->getPath().GetFullPath());
        data = new rcbasic_treeItem_data(node_label, open_projects[project_index]);
        node_label.MakeRelativeTo(open_projects[project_index]->getLocation());
        source_files[i]->setNode( project_tree->AppendItem( project_node, node_label.GetFullPath(), project_tree_fileImage, -1, data) );
    }
}

wxFileName rcbasic_edit_frame::openFileDialog(wxString title, wxString default_wildcard, int flag)
{
    wxFileDialog openFileDialog(this, title, "", "", default_wildcard, flag);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return wxFileName();     // the user changed idea...

    wxFileName fname(openFileDialog.GetPath());
    return fname;
}

wxArrayString rcbasic_edit_frame::openMultiFileDialog(wxString title, wxString default_wildcard, int flag)
{
    wxFileDialog openFileDialog(this, title, "", "", default_wildcard, flag);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return wxArrayString();     // the user changed idea...

    wxArrayString fnames;
    openFileDialog.GetPaths(fnames);
    return fnames;
}

void rcbasic_edit_frame::addFileToProject(wxFileName sourceFile)
{
    if(!sourceFile.Exists())
        return;

    if(context_project==NULL)
        return;

    context_project->addSourceFile(sourceFile.GetFullPath());
    updateProjectTree(getProjectFromRoot(context_project->getRootNode()));
}

void rcbasic_edit_frame::saveProject(rcbasic_project* project)
{
    if(!project)
        return;

    wxFileName project_file;

    //wxPuts(_("Location: ")+project->getLocation());
    //wxPuts(_("Name: ")+project->getName());
    //return;

    project_file.SetPath(project->getLocation());
    project_file.SetName(project->getName());
    project_file.SetExt(_("rcprj"));

    project->saveProject(project_file);
}

int rcbasic_edit_frame::closeProject(rcbasic_project* project)
{

    if(!project)
        return -1;

    int rtn_val = -1;

    if(project->projectHasChanged())
    {
        //wxPuts(_("Project has changed"));
        rcbasic_edit_closeProjectSavePrompt_dialog cs_prompt(this, _("Project: ") + project->getName());
        cs_prompt.ShowModal();
        switch(cs_prompt.getProjectCloseFlag())
        {
            case projectCloseFlag_SAVE:
                //wxPuts(_("SAVE and CLOSE"));
                saveProject(project);
                rtn_val = projectCloseFlag_SAVE;
                break;
            case projectCloseFlag_CANCEL:
                return projectCloseFlag_CANCEL;
            default:
                rtn_val = projectCloseFlag_DONT_SAVE;
                break;
        }
    }

    //int project_index = getProjectFromRoot(project->getRootNode());

    if(context_project==project)
        context_project = NULL;

    if(active_project==project)
    {
        active_project = NULL;
        if(open_projects.size()>1)
        {
            for(int i = 0; i < open_projects.size(); i++)
            {
                if(open_projects[i]->getRootNode()!=project->getRootNode())
                {
                    active_project = open_projects[i];

                    if(active_project)
                    {
                        wxSetWorkingDirectory(active_project->getLocation());
                    }

                    project_tree->SetItemBold(active_project->getRootNode(), true);

                    break;
                }
            }
        }
    }

    wxFileName project_file;

    //wxPuts(_("-Location: ")+project->getLocation());
    //wxPuts(_("-Name: ")+project->getName());
    //return;

    project_file.SetPath(project->getLocation());
    project_file.SetName(project->getName());
    project_file.SetExt(_("rcprj"));

    if(project->projectHasChanged())
    {
        project->saveProject(project_file);
    }

    project_tree->Delete(project->getRootNode());

    open_projects.erase(open_projects.begin()+getProjectFromRoot(project->getRootNode()));
    delete project;

    return rtn_val;
}

void rcbasic_edit_frame::onCloseAllMenuSelect( wxCommandEvent& event )
{
    int i = 0;
    while(open_files.size() > i)
    {
        int close_val = closeFile(sourceFile_auinotebook->GetPageIndex(open_files[i]->getTextCtrl()));

        if(close_val==fileCloseFlag_CANCEL)
            i++;
    }

    i = 0;
    while(open_projects.size() > i)
    {
        int close_val = closeProject(open_projects[i]);

        if(close_val==projectCloseFlag_CANCEL)
            i++;
    }
}

void rcbasic_edit_frame::onExitMenuSelect( wxCommandEvent& event )
{
    Close();
}

void rcbasic_edit_frame::onSaveProject(wxCommandEvent& event)
{
    saveProject(active_project);
}

void rcbasic_edit_frame::onSaveProjectAs(wxCommandEvent& event)
{
    if(active_project)
    {
        active_project->saveProject(openFileDialog(_("Save Project As"), _("RCBasic Project (*.rcprj)|*.rcprj"),wxFD_SAVE));
    }
}

void rcbasic_edit_frame::onUndoMenuSelect( wxCommandEvent& event )
{
    int selected_page = sourceFile_auinotebook->GetSelection();

    if(selected_page < 0)
        return;

    wxStyledTextCtrl* t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(selected_page);
    t->Undo();
}

void rcbasic_edit_frame::onRedoMenuSelect( wxCommandEvent& event )
{
    int selected_page = sourceFile_auinotebook->GetSelection();

    if(selected_page < 0)
        return;

    wxStyledTextCtrl* t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(selected_page);
    t->Redo();
}

void rcbasic_edit_frame::onCutMenuSelect( wxCommandEvent& event )
{
    int selected_page = sourceFile_auinotebook->GetSelection();

    if(selected_page < 0)
        return;

    wxStyledTextCtrl* t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(selected_page);
    t->Cut();
}

void rcbasic_edit_frame::onCopyMenuSelect( wxCommandEvent& event )
{
    int selected_page = sourceFile_auinotebook->GetSelection();

    if(selected_page < 0)
        return;

    wxStyledTextCtrl* t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(selected_page);
    t->Copy();
}

void rcbasic_edit_frame::onPasteMenuSelect( wxCommandEvent& event )
{
    int selected_page = sourceFile_auinotebook->GetSelection();

    if(selected_page < 0)
        return;

    wxStyledTextCtrl* t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(selected_page);
    t->Paste();
}

void rcbasic_edit_frame::onDeleteMenuSelect( wxCommandEvent& event )
{
    int selected_page = sourceFile_auinotebook->GetSelection();

    if(selected_page < 0)
        return;

    wxStyledTextCtrl* t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(selected_page);
    //wxPrintf(_("Line: %d to %d"), t->LineFromPosition(t->GetSelectionStart()), t->LineFromPosition(t->GetSelectionEnd()));
    t->Clear();
}

void rcbasic_edit_frame::onCommentMenuSelect( wxCommandEvent& event )
{
    int selected_page = sourceFile_auinotebook->GetSelection();

    if(selected_page < 0)
        return;

    wxStyledTextCtrl* t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(selected_page);
    //wxPrintf(_("Line: %d to %d"), t->LineFromPosition(t->GetSelectionStart()), t->LineFromPosition(t->GetSelectionEnd()));
    int start_line = t->LineFromPosition(t->GetSelectionStart());
    int end_line = t->LineFromPosition(t->GetSelectionEnd());

    wxString new_line;

    for(int i = start_line; i <= end_line; i++)
    {
        new_line = t->GetLine(i);
        new_line.Replace(_("\n"), _(""));
        t->Replace(t->PositionFromLine(i), t->GetLineEndPosition(i), _("\'") + new_line);
    }
}

void rcbasic_edit_frame::onBlockCommentMenuSelect( wxCommandEvent& event )
{
    int selected_page = sourceFile_auinotebook->GetSelection();

    if(selected_page < 0)
        return;

    wxStyledTextCtrl* t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(selected_page);
    //wxPrintf(_("Line: %d to %d"), t->LineFromPosition(t->GetSelectionStart()), t->LineFromPosition(t->GetSelectionEnd()));
    int start_line = t->LineFromPosition(t->GetSelectionStart());
    int end_line = t->LineFromPosition(t->GetSelectionEnd());

    wxString new_line;

    new_line = t->GetLine(start_line);
    new_line.Replace(_("\n"), _(""));
    t->Replace(t->PositionFromLine(start_line), t->GetLineEndPosition(start_line), _("/\'") + new_line);

    new_line = t->GetLine(end_line);
    new_line.Replace(_("\n"), _(""));
    t->Replace(t->PositionFromLine(end_line), t->GetLineEndPosition(end_line), new_line + _("\'/"));
}

void rcbasic_edit_frame::onFindMenuSelect( wxCommandEvent& event )
{
    rcbasic_edit_find_dialog find_dialog(this);
    find_dialog.ShowModal();
}

void rcbasic_edit_frame::toggleMessageWindow( wxCommandEvent& event )
{
// TODO: Implement toggleMessageWindow

    //note: set sash position to 2 to hide
    int w, h;
    this->GetSize(&w, &h);
    int current_pos = m_mainView_message_splitter->GetSashPosition();
    m_mainView_message_splitter->SetSashPosition( messageWindowVisible ? -2 : h-220 );
    m_mainView_message_splitter->SetSashInvisible(messageWindowVisible);
    m_mainView_message_splitter->UpdateSize();
    messageWindowVisible = !messageWindowVisible;
    m_showMessageWindow_menuItem->Check(messageWindowVisible);

    //m_messageWindow_panel->Hide();
    //wxSplitterWindow* split = (wxSplitterWindow*)m_messageWindow_panel->GetParent();
    //wxBoxSizer* bsizer = (wxBoxSizer*)split->GetParent();
    //bsizer->Layout();

    //int sashPOS = m_mainView_message_splitter->GetSashPosition();
    //int sashSize = 0;
    //int w, h;
    //this->GetSize(&w, &h);
    //sashSize = h;

    //wxString str, str2;
    //str.Printf(wxT("Sash Position: %d"), sashPOS);
    //str2.Printf(wxT("Sash Size: %d\n"), sashSize);

    //wxPuts(str);
    //wxPuts(str2);
}

void rcbasic_edit_frame::toggleToolbar( wxCommandEvent& event )
{
    // TODO: Implement toggleToolbar
    switch(toolbarVisible)
    {
        case true:
            mainWindowSizer->Hide(m_toolBar);
            mainWindowSizer->Layout();
            break;
        default:
            mainWindowSizer->Show(m_toolBar);
            mainWindowSizer->Layout();
            break;
    }
    toolbarVisible = !toolbarVisible;
    m_showToolbar_menuItem->Check(toolbarVisible);
}

void rcbasic_edit_frame::toggleSideBar( wxCommandEvent& event )
{
    // TODO: Implement toggleSideBar
    int w, h;
    this->GetSize(&w, &h);
    int current_pos = m_project_file_splitter->GetSashPosition();
    m_project_file_splitter->SetSashPosition( sideBarVisible ? 2 : 220 );
    m_project_file_splitter->SetSashInvisible(sideBarVisible);
    m_project_file_splitter->UpdateSize();
    sideBarVisible = !sideBarVisible;
    m_showSideBar_menuItem->Check(sideBarVisible);
}

#define SAVE_PROJECT 1001
#define CLOSE_PROJECT 1002
#define NEW_FILE 1003
#define ADD_FILES 1004
#define REMOVE_FILES 1005
#define BUILD_PROJECT 1006
#define RUN_PROJECT 1007
#define DEBUG_PROJECT 1008
#define PROJECT_PROPERTIES 1009

void rcbasic_edit_frame::addMultipleFilesToProject()
{
    if(context_project==NULL)
        return;

    wxArrayString sourceFiles = openMultiFileDialog( _("Open RCBasic Source file"), _("RCBasic Source files (*.bas)|*.bas"), wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_MULTIPLE);

    for(int i = 0; i < sourceFiles.size(); i++)
    {
        wxFileName fname(sourceFiles[i]);
        if(!fname.Exists())
            continue;

        context_project->addSourceFile(fname.GetFullPath());
    }

    updateProjectTree(getProjectFromRoot(context_project->getRootNode()));
}

rcbasic_edit_txtCtrl* rcbasic_edit_frame::openFileTab(rcbasic_project* project, wxFileName newFile)
{
    wxStyledTextCtrl* txtCtrl = NULL;
    rcbasic_edit_txtCtrl* txtCtrl_obj;

    for(int i = 0; i < open_files.size(); i++)
    {
        if(open_files[i]->getSourcePath().GetFullPath()==newFile.GetFullPath())
        {
            txtCtrl = open_files[i]->getTextCtrl();
            break;
        }
    }

    int index = -1;

    if(project)
        index = project->getSourceFileIndex(newFile);

    if(txtCtrl)
    {
        wxPuts(_("\nT CTRL\n"));
        for(int i = 0; i < open_files.size(); i++)
        {
            if(open_files[i]->getTextCtrl()==txtCtrl)
                txtCtrl_obj = open_files[i];
        }
        //No need to check for project value here because index will be -1 if project is NULL
        if(index >= 0)
        {
            wxPrintf(_("Set txtCtrl to %p\n"), txtCtrl);
            project->getSourceFiles()[index]->setTextCtrl(txtCtrl);
        }
    }
    else
    {
        wxPrintf("\nIndex = %d\n", index);
        txtCtrl_obj = new rcbasic_edit_txtCtrl(newFile, sourceFile_auinotebook);

        //apply settings here

        int page_index = sourceFile_auinotebook->GetPageCount();

        sourceFile_auinotebook->AddPage(txtCtrl_obj->getTextCtrl(), newFile.GetFullName());
        open_files.push_back(txtCtrl_obj);

        if(project)
        {
            project->getSourceFiles()[index]->setTextCtrl(txtCtrl_obj->getTextCtrl());
            project->getSourceFiles()[index]->setNotebookPage(sourceFile_auinotebook->GetPage(page_index));
            updateProjectTree(getProjectFromRoot(project->getRootNode()));
        }
    }

    if(txtCtrl_obj->getTextCtrl())
    {
        wxStyledTextCtrl* rc_txtCtrl = txtCtrl_obj->getTextCtrl();
        //wxPuts(_("Set event"));
        rc_txtCtrl->Connect( wxEVT_STC_CHANGE, wxStyledTextEventHandler( rcbasic_edit_frame::onTextCtrlUpdated ), NULL, this );

        rc_txtCtrl->SetMarginType(0, wxSTC_MARGIN_NUMBER);
        rc_txtCtrl->SetMarginWidth(0, 40);
        rc_txtCtrl->SetUndoCollection(true);
        rc_txtCtrl->EmptyUndoBuffer();
        rc_txtCtrl->SetLexer(wxSTC_LEX_FREEBASIC);
    }

    txtCtrl_obj->setTextChangedFlag(false);

    return txtCtrl_obj;
}

void rcbasic_edit_frame::createNewFile(rcbasic_project* project)
{
    rcbasic_edit_newFile_dialog newFile_dialog(this);
    newFile_dialog.ShowModal();

    if(newFile_dialog.getNewFileFlag()==newFileFlag_CANCEL)
        return;

    wxFileName newFile = newFile_dialog.getFileName();

    wxFile f;

    if(!f.Create(newFile.GetFullPath()))
    {
        wxMessageBox(_("Could not create new file"));
        return;
    }
    //wxPuts(_("\nCreated New File: ")+newFile.GetFullPath());
    //Might want to add header info
    f.Close();

    addRecentFile(newFile);

    rcbasic_edit_txtCtrl* txtCtrl_obj;

    if(newFile_dialog.getAddToProjectFlag())
    {
        //wxPuts("Adding to project");
        if(project)
        {
            project->addSourceFile(newFile.GetFullPath());
        }
        else
        {
            wxMessageBox(_("There is no active project to add new file to."));
        }
        txtCtrl_obj = openFileTab(project, newFile);
    }
    else
    {
        txtCtrl_obj = openFileTab(NULL, newFile);
    }

    txtCtrl_obj->setTextChangedFlag(false);

}

void rcbasic_edit_frame::onTreeContextClick(wxCommandEvent &evt)
{
    switch(evt.GetId())
    {
        case SAVE_PROJECT:
            //wxPuts(_("Saving the project"));
            saveProject(context_project);
            break;
        case CLOSE_PROJECT:
            wxPuts(_("###Closing the project"));
            closeProject(context_project);
            break;
        case ADD_FILES:
            //wxPuts(_("Add Files"));
            addMultipleFilesToProject();
            break;
        case REMOVE_FILES:
            wxPuts(_("Remove Files"));
            break;
        case BUILD_PROJECT:
            wxPuts(_("Build Project"));
            break;
        case RUN_PROJECT:
            wxPuts(_("Run Project"));
            break;
        case DEBUG_PROJECT:
            wxPuts(_("Debug Project"));
            break;
        case PROJECT_PROPERTIES:
            wxPuts(_("Properties"));
            break;
    }
}

void rcbasic_edit_frame::projectTreeContextMenu()
{
    wxMenu menu;
    menu.Append(SAVE_PROJECT, wxT("&Save Project"));
    menu.Append(CLOSE_PROJECT, wxT("&Close Project"));
    menu.AppendSeparator();
    menu.Append(ADD_FILES, wxT("&Add Files"));
    menu.Append(REMOVE_FILES, wxT("&Remove Files"));
    menu.AppendSeparator();
    menu.Append(BUILD_PROJECT, wxT("&Build"));
    menu.Append(RUN_PROJECT, wxT("&Run"));
    menu.Append(DEBUG_PROJECT, wxT("&Debug"));
    menu.Append(PROJECT_PROPERTIES, wxT("&Properties"));
    menu.Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(rcbasic_edit_frame::onTreeContextClick), NULL, this);
    PopupMenu(&menu);
}

void rcbasic_edit_frame::onProjectTreeContextMenu( wxTreeEvent& event )
{
    wxTreeItemId selected_node = event.GetItem();
    for(int i = 0; i < open_projects.size(); i++)
    {
        if(open_projects[i]->getRootNode()==selected_node)
        {
            context_project = open_projects[i];
            projectTreeContextMenu();
        }
    }
}

void rcbasic_edit_frame::onProjectTreeNodeActivated( wxTreeEvent& event )
{
    //wxPrintf("Node Activated: %d\n\n", 0);
    wxTreeItemId selected_node = event.GetItem();
    rcbasic_treeItem_data* data = (rcbasic_treeItem_data*)project_tree->GetItemData(selected_node);

    /*if(data)
    {
        wxPuts(_("Node Data: ")+data->node_file_path.GetFullPath()+_(", ")+data->parent_project->getName());
    }*/

    for(int i = 0; i < open_projects.size(); i++)
    {
        if(open_projects[i]->getRootNode()==selected_node)
        {
            if(active_project != NULL)
            {
                project_tree->SetItemBold(active_project->getRootNode(), false);
            }
            active_project = open_projects[i];

            if(active_project)
            {
                wxSetWorkingDirectory(active_project->getLocation());
            }

            project_tree->SetItemBold(active_project->getRootNode(), true);
            return;
        }
        else
        {
            rcbasic_project_node* file_node;
            //wxPuts(_("Looking through project files"));
            for(int file_node_index = 0; file_node_index < open_projects[i]->getSourceFiles().size(); file_node_index++)
            {
                file_node = open_projects[i]->getSourceFiles()[file_node_index];
                wxPrintf(_("CMP: %p\n"), file_node->getTextCtrl());
                if(file_node->getNode()==selected_node)
                {
                    wxPuts(_("Request open"));
                    if(sourceFile_auinotebook->GetPageIndex(file_node->getTextCtrl())<0)
                    {
                        wxPrintf(_("Open a tab: %d\n"), sourceFile_auinotebook->GetPageIndex(file_node->getTextCtrl()));
                        if(file_node->getTextCtrl())
                            file_node->setTextCtrl(NULL);
                        file_node->setTextCtrl(openFileTab(open_projects[i], file_node->getPath())->getTextCtrl());
                        wxPrintf(_("file_node t_Ctrl = %p\n"), file_node->getTextCtrl());
                        return;
                    }
                    else
                    {
                        //if tab is already open then switch to it
                        sourceFile_auinotebook->SetSelection(sourceFile_auinotebook->GetPageIndex(file_node->getTextCtrl()));
                    }
                }
                else
                {
                    //wxPuts(_("\n\nCould not open ")+file_node->getPath().GetFullName());
                }
            }
        }
    }
}

void rcbasic_edit_frame::onSourceFileTabClose( wxAuiNotebookEvent& event )
{
    int selected_page = event.GetSelection();

    //wxPuts( _("page to close: ") + sourceFile_auinotebook->GetPageText(selected_page) );
    //return;

    wxString temp_text;
    bool text_changed = false;

    for(int i = 0; i < open_files.size(); i++)
    {
        if(sourceFile_auinotebook->GetPageIndex(open_files[i]->getTextCtrl()) == selected_page)
        {
            if(open_files[i]->getTextChangedFlag())
            {
                wxString title = _("Closing ") + open_files[i]->getSourcePath().GetFullName();
                rcbasic_edit_closeFileSavePrompt_dialog saveFile_dialog(this, title);
                saveFile_dialog.ShowModal();

                switch(saveFile_dialog.getFileCloseFlag())
                {
                    case fileCloseFlag_SAVE:
                        saveFile(i);
                        if(!last_fileSave_flag)
                            event.Veto();
                        break;
                    case fileCloseFlag_DONT_SAVE:
                        break;
                    case fileCloseFlag_CANCEL:
                        event.Veto();
                        return;
                }
            }

            open_files.erase(open_files.begin()+i);
            break;
        }
    }

    for(int i = 0; i < open_projects.size(); i++)
    {
        for(int file_node_index = 0; file_node_index < open_projects[i]->getSourceFiles().size(); file_node_index++)
        {
            if(sourceFile_auinotebook->GetPageIndex(open_projects[i]->getSourceFiles()[file_node_index]->getTextCtrl()) == selected_page)
            {
                //wxPuts(_("Tab belongs to project -> ") + open_projects[i]->getName());
                //wxPuts(_("Full PATH = ") + open_projects[i]->getSourceFiles()[file_node_index]->getPath().GetFullPath());
                /*if(text_changed)
                {
                    open_projects[i]->getSourceFiles()[file_node_index]->setTextChangedFlag(true);
                }*/
                open_projects[i]->getSourceFiles()[file_node_index]->setTextCtrl(NULL);
            }
        }

    }
}

void rcbasic_edit_frame::addRecentProject(rcbasic_project* project)
{
    if(!project)
        return;
    //wxPuts(_("Adding project: ") + project->getProjectFileLocation());
    wxString tmp[10];
    for(int i = 0; i < 10; i++)
    {
        //wxPrintf(_("%d = [")+recent_projects[i]+_("]"),i);
        if(recent_projects[i].compare(project->getProjectFileLocation())==0)
            return;

        tmp[i]=recent_projects[i];
    }

    for(int i = 1; i < 10; i++)
    {
        recent_projects[i] = tmp[i-1];
    }
    recent_projects[0] = project->getProjectFileLocation();
}

void rcbasic_edit_frame::addRecentFile(wxFileName file)
{
    //wxPuts(_("Adding file: ") + file.GetFullPath());
    //return;
    wxString tmp[10];
    for(int i = 0; i < 10; i++)
    {
        //wxPrintf(_("%d = [")+recent_projects[i]+_("]"),i);
        if(recent_files[i].compare(file.GetFullPath())==0)
            return;

        tmp[i]=recent_files[i];
    }

    for(int i = 1; i < 10; i++)
    {
        recent_files[i] = tmp[i-1];
    }
    recent_files[0] = file.GetFullPath();
}


void rcbasic_edit_frame::onTextCtrlUpdated( wxStyledTextEvent& event )
{
    //wxPuts(_("TEXT CHANGED"));
    wxStyledTextCtrl* rc_txtCtrl = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(sourceFile_auinotebook->GetSelection());
    for(int i = 0; i < open_files.size(); i++)
    {
        if(open_files[i]->getTextCtrl()==rc_txtCtrl)
        {
            //wxPuts(_("File Changed: ") + open_files[i]->getSourcePath().GetFullPath());
            open_files[i]->setTextChangedFlag(true);
        }
    }
}
