#ifndef PROJECTS_H_INCLUDED
#define PROJECTS_H_INCLUDED

#include <wx/wx.h>
#include <wx/treectrl.h>
#include <wx/file.h>
#include <wx/imaglist.h>
#include <wx/image.h>
#include <wx/filename.h>
#include <wx/filefn.h>
#include <wx/stc/stc.h>
#include <wx/treebase.h>
#include <vector>
#include <stdint.h>

#define RCBASIC_PROJECT_SOURCE_NEW      0
#define RCBASIC_PROJECT_SOURCE_EXISTING 1
#define RCBASIC_PROJECT_SOURCE_OPEN 2

#define STORE_LOCATION_RELATIVE 0
#define STORE_LOCATION_ABSOLUTE 1

class rcbasic_project_node
{
    private:
        wxFileName path;
        wxTreeItemId tree_node;
        wxStyledTextCtrl* rc_txtCtrl;
        wxWindow* notebook_page;
        uintptr_t notebook_page_addr;
        bool text_changed;
        wxString txt_backup;
        int store_location_type;
    public:
        rcbasic_project_node(wxFileName node_path);
        void setNode(wxTreeItemId node);
        wxTreeItemId getNode();
        wxFileName getPath();
        void setTextCtrl(wxStyledTextCtrl* txt_ctrl);
        wxStyledTextCtrl* getTextCtrl();
        void setNotebookPage(wxWindow* page);
        wxWindow* getNotebookPage();
        void setTextChangedFlag(bool flag);
        bool getTextChangedFlag();
};

class rcbasic_project
{
    private:
        wxString name;
        wxFileName main_source;
        wxString author;
        wxString website;
        wxString description;
        std::vector<rcbasic_project_node*> source_files;
        wxTreeItemId root_node_id;

        wxString location;
        wxString project_file_location;

        bool project_valid;

        rcbasic_project* last_saved_project;

    public:
        rcbasic_project();
        rcbasic_project(wxString project_name, wxString project_location, int main_source_flag, wxString main_source_value,
                        wxString project_author, wxString project_website, wxString project_description);
        ~rcbasic_project();

        void setName(wxString new_project_name);
        void setMainSource(wxString new_main_source);
        void setAuthor(wxString new_author);
        void setWebsite(wxString new_website);
        void setDescription(wxString new_description);
        void addSourceFile(wxString filePath);
        bool createNewSourceFile(wxString filePath);
        void setRootNode(wxTreeItemId project_root);

        void setLocation(wxString new_location);
        wxString getLocation();

        wxString getName();
        wxFileName getMainSource();
        wxString getAuthor();
        wxString getWebsite();
        wxString getDescription();
        std::vector<rcbasic_project_node*> getSourceFiles();
        void removeSourceFile(wxString fname)
        {
            for(int i = 0; i < source_files.size(); i++)
            {
                wxFileName tmp = source_files[i]->getPath();
                tmp.MakeRelativeTo(location);
                if(tmp.GetFullPath().compare(fname)==0)
                {
                    //wxPuts(_("match: ")+tmp.GetFullPath());
                    delete source_files[i];
                    source_files.erase(source_files.begin() + i);
                    i--;
                    break;
                }
            }
        }
        int getSourceFileIndex(wxFileName file_path);

        wxTreeItemId getRootNode();

        bool projectExists();

        bool saveProject(wxFileName save_file);
        bool projectHasChanged();
        void setProjectFileLocation(wxString pfile_loc);
        wxString getProjectFileLocation();

        void setLastProjectSave();
};

class rcbasic_treeItem_data : public wxTreeItemData
{
    public:
        wxFileName node_file_path;
        rcbasic_project* parent_project;
        rcbasic_treeItem_data(wxFileName fname, rcbasic_project* project)
        {
            node_file_path = fname;
            parent_project = project;
        }
};

//std::vector<rcbasic_project> open_projects;

//rcbasic_project loadProject(wxString project_filePath);
//rcbasic_project getProjectFromNode(wxTreeItemId);

#endif // PROJECTS_H_INCLUDED
