#ifndef PROJECTS_H_INCLUDED
#define PROJECTS_H_INCLUDED

#include <wx/wx.h>
#include <wx/treectrl.h>
#include <vector>

class rcbasic_project
{
    private:
        wxString name;
        wxString main_source;
        wxString author;
        wxString website;
        wxString description;
        std::vector<wxString> source_files;
        wxTreeItemId root_node_id;

    public:
        rcbasic_project(wxString project_name, wxString project_location, int main_source_flag, wxString main_source_value,
                        wxString author, wxString website, wxString description);

        void setName(wxString new_project_name);
        void setMainSource(wxString new_main_source);
        void setAuthor(wxString new_author);
        void setWebsite(wxString new_website);
        void setDescription(wxString new_description);
        void addSourceFile(wxString filePath);
        void createNewSourceFile(wxString filePath);

        wxString getName();
        wxString getMainSource();
        wxString getAuthor();
        wxString getWebsite();
        wxString getDescription();
        wxString getSourceFiles();

        wxTreeItemId getRootNode();
};

std::vector<rcbasic_project> open_projects;

rcbasic_project loadProject(wxString project_filePath);

#endif // PROJECTS_H_INCLUDED
