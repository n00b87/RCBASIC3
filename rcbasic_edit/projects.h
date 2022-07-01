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
        bool temp_flag;
        int add_remove_state;
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
        void setLocationStoreType(int store_loc_type);
        int getLocationStoreType();
        void setAsTemp(bool flag) { temp_flag = flag; }
        bool isTemp() { return temp_flag; }
        void setAsAddFile(bool flag) { add_remove_state = flag ? 1 : 0; }
        int getAddRemoveFlag() { return add_remove_state; }
};

struct rcbasic_edit_env_var
{
    wxString var_name;
    wxString var_value;
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

        std::vector<rcbasic_edit_env_var> env_vars;

    public:
        rcbasic_project();
        rcbasic_project(wxString project_name, wxString project_location, int main_source_flag, wxString main_source_value,
                        wxString project_author, wxString project_website, wxString project_description);
        ~rcbasic_project();

        void copyFromProject(rcbasic_project* p);
        void setPointersNull();

        void setName(wxString new_project_name);
        void setMainSource(wxString new_main_source);
        void setAuthor(wxString new_author);
        void setWebsite(wxString new_website);
        void setDescription(wxString new_description);
        bool addSourceFile(wxString filePath, int store_loc_type);
        bool addTempSourceFile(wxString filePath, int store_loc_type);
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
            if(fname.length() <= 0)
                return;
            wxString cwd = wxGetCwd();
            wxSetWorkingDirectory(location);

            for(int i = 0; i < source_files.size(); i++)
            {
                wxFileName tmp_rel = source_files[i]->getPath();
                tmp_rel.MakeRelativeTo(location);

                wxFileName tmp_abs = source_files[i]->getPath();
                tmp_abs.MakeAbsolute();

                if(tmp_rel.GetFullPath().compare(fname)==0 || tmp_abs.GetFullPath().compare(fname)==0)
                {
                    //wxPuts(_("match: ")+tmp.GetFullPath());
                    delete source_files[i];
                    source_files.erase(source_files.begin() + i);
                    i--;
                    break;
                }
            }
            wxSetWorkingDirectory(cwd);
        }
        int getSourceFileIndex(wxFileName file_path);

        wxTreeItemId getRootNode();

        bool projectExists();

        bool saveProject(wxFileName save_file);
        bool projectHasChanged();
        void setProjectFileLocation(wxString pfile_loc);
        wxString getProjectFileLocation();

        void setLastProjectSave();
        rcbasic_project* getLastProjectSave() { return last_saved_project; }

        void addEnvVar(wxString var_name, wxString var_value);
        void setVars(std::vector<rcbasic_edit_env_var> v);
        void clearEnvVars();
        std::vector<rcbasic_edit_env_var> getVars();
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
