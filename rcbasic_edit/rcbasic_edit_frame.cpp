#include <wx/string.h>

#include "rcbasic_edit_frame.h"
#include "rcbasic_edit_newProject_dialog.h"
#include "rc_closeProjectSavePrompt_dialog.h"

rcbasic_edit_txtCtrl::rcbasic_edit_txtCtrl(wxFileName src_path, wxAuiNotebook* parent_nb)
{
    sourcePath = src_path;
    txtCtrl = new wxStyledTextCtrl(parent_nb, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, src_path.GetFullName());
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

}

void rcbasic_edit_frame::createNewProject( wxCommandEvent& event)
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
        int new_project_index = getProjectFromRoot(new_project->getRootNode());
        if(new_project_index >= 0)
            updateProjectTree(new_project_index);

        //----
        openFileTab(new_project, new_project->getMainSource());
    }

    //wxPuts(_("Project_Location: ") + project_location);
    //wxPuts(_("Main Source: ") + main_source_value);

    newProject_win->Destroy();
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
    std::vector<rcbasic_project_node> source_files = open_projects[project_index]->getSourceFiles();

    wxFileName node_label;
    rcbasic_treeItem_data* data;

    for(int i = 0; i < source_files.size(); i++)
    {
        node_label = wxFileName(source_files[i].getPath().GetFullPath());
        data = new rcbasic_treeItem_data(node_label, open_projects[project_index]);
        node_label.MakeRelativeTo(open_projects[project_index]->getLocation());
        source_files[i].setNode( project_tree->AppendItem( project_node, node_label.GetFullPath(), project_tree_fileImage, -1, data) );
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

void rcbasic_edit_frame::closeProject(rcbasic_project* project)
{

    if(!project)
        return;

    if(project->projectHasChanged())
    {
        //wxPuts(_("Project has changed"));
        rcbasic_edit_closeProjectSavePrompt_dialog cs_prompt(this);
        cs_prompt.ShowModal();
        switch(cs_prompt.getProjectCloseFlag())
        {
            case projectCloseFlag_SAVE:
                //wxPuts(_("SAVE and CLOSE"));
                saveProject(project);
                break;
            case projectCloseFlag_CANCEL:
                return;
            default:
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
                    active_project = open_projects[i];
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
        //No need to check for project value here because index will be -1 if project is NULL
        if(index >= 0)
            project->getSourceFiles()[index].setTextCtrl(txtCtrl);
    }
    else
    {
        wxPrintf("Index = %d\n", index);
        txtCtrl_obj = new rcbasic_edit_txtCtrl(newFile, sourceFile_auinotebook);

        //apply settings here

        int page_index = sourceFile_auinotebook->GetPageCount();

        sourceFile_auinotebook->AddPage(txtCtrl_obj->getTextCtrl(), newFile.GetFullName());
        open_files.push_back(txtCtrl_obj);

        project->getSourceFiles()[index].setTextCtrl(txtCtrl_obj->getTextCtrl());
        wxPrintf("Notebook page: %p\n", sourceFile_auinotebook->GetPage(page_index));
        project->getSourceFiles()[index].setNotebookPage(sourceFile_auinotebook->GetPage(page_index));
        //wxString s;
        //s.Printf("S--Notebook page: %p\n", sourceFile_auinotebook->GetPage(page_index));
        //wxPuts(s);
        wxPrintf("Notebook page[V]: %p\n\n", project->getSourceFiles()[index].getNotebookPage());
    }

    return txtCtrl_obj;
}

void rcbasic_edit_frame::createNewFile(rcbasic_project* project, wxFileName newFile)
{
    rcbasic_edit_newFile_dialog newFile_dialog(this);
    newFile_dialog.ShowModal();

    if(newFile_dialog.getNewFileFlag()==newFileFlag_CANCEL)
        return;

    wxFile f;

    if(!f.Create(newFile.GetFullPath()))
    {
        wxMessageBox(_("Could not create new file"));
        return;
    }
    //Might want to add header info
    f.Close();

    project->addSourceFile(newFile.GetFullPath());

    openFileTab(project, newFile);

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
        case NEW_FILE:
            wxPuts(_("New File"));
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
    menu.Append(NEW_FILE, wxT("&New File"));
    menu.Append(ADD_FILES, wxT("&Add Files"));
    menu.Append(REMOVE_FILES, wxT("&Remove Files"));
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
    wxPrintf("Node Activated: %d\n\n", 0);
    wxTreeItemId selected_node = event.GetItem();
    rcbasic_treeItem_data* data = (rcbasic_treeItem_data*)project_tree->GetItemData(selected_node);

    if(data)
    {
        wxPuts(_("Node Data: ")+data->node_file_path.GetFullPath()+_(", ")+data->parent_project->getName());
    }

    for(int i = 0; i < open_projects.size(); i++)
    {
        if(open_projects[i]->getRootNode()==selected_node)
        {
            if(active_project != NULL)
            {
                project_tree->SetItemBold(active_project->getRootNode(), false);
            }
            active_project = open_projects[i];
            project_tree->SetItemBold(active_project->getRootNode(), true);
            return;
        }
        else
        {
            continue;
            rcbasic_project_node file_node(wxFileName(_("")));
            wxPuts(_("Looking through project files"));
            for(int file_node_index = 0; file_node_index < open_projects[i]->getSourceFiles().size(); file_node_index++)
            {
                file_node = open_projects[i]->getSourceFiles()[file_node_index];
                wxPuts(file_node.getPath().GetFullPath());
                if(file_node.getNode()==selected_node)
                {
                    wxPuts(_("Request open"));
                    if(sourceFile_auinotebook->GetPageIndex(file_node.getTextCtrl())<0)
                    {
                        wxPuts(_("Open a tab"));
                        file_node.setTextCtrl(openFileTab(open_projects[i], file_node.getPath())->getTextCtrl());
                        return;
                    }
                }
                else
                {
                    wxPuts(_("\n\nCould not open ")+file_node.getPath().GetFullName());
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

    for(int i = 0; i < open_projects.size(); i++)
    {
        for(int file_node_index = 0; file_node_index < open_projects[i]->getSourceFiles().size(); file_node_index++)
        {
            if(sourceFile_auinotebook->GetPageIndex(open_projects[i]->getSourceFiles()[file_node_index].getTextCtrl()) == selected_page)
            {
                wxPuts(_("Tab belongs to project -> ") + open_projects[i]->getName());
            }
            else
            {
                wxPrintf("addr 1: %d\n", sourceFile_auinotebook->GetPageIndex(open_projects[i]->getSourceFiles()[file_node_index].getTextCtrl()));
                wxPrintf("addr 2: %d\n\n", selected_page);
            }
        }

    }
}
