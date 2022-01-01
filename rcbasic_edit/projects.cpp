#include "projects.h"

rcbasic_project_node::rcbasic_project_node(wxFileName node_path)
{
    path = node_path;
}

void rcbasic_project_node::setNode(wxTreeItemId node)
{
    tree_node = node;
}

wxTreeItemId rcbasic_project_node::getNode()
{
    return tree_node;
}

wxFileName rcbasic_project_node::getPath()
{
    return path;
}






rcbasic_project::rcbasic_project(wxString project_name, wxString project_location, int main_source_flag, wxString main_source_value,
                wxString project_author, wxString project_website, wxString project_description)
{

    wxFileName project_dir;

    project_dir.SetPath(project_location);
    project_dir.AppendDir(project_name);
    location = project_dir.GetFullPath();
    if(!wxMkdir(location))
    {
        wxMessageBox(_("Could not access project location"));
        return;
    }


    name = project_name;
    author = project_author;
    website = project_website;
    description = project_description;

    wxFile project_file;
    wxFileName fname;
    fname.SetPath(location);
    fname.SetName(main_source_value);

    //wxFileName x = fname;
    //x.MakeRelativeTo(location);
    //wxPuts(_("Fname: ")+x.GetFullPath());

    switch(main_source_flag)
    {
        case RCBASIC_PROJECT_SOURCE_NEW:
            if(!project_file.Create(fname.GetFullPath()))
            {
                if(!project_file.Open(fname.GetFullPath()))
                {
                    wxMessageBox(_("Could not access main source file"));
                    return;
                }
                else
                {
                    main_source = fname;
                    //main_source.MakeRelativeTo(location);
                }
            }
            else
            {
                main_source = fname;
                //main_source.MakeRelativeTo(location);
                project_file.Write("This is a test\n");
                project_file.Write("The end");
                project_file.Close();
            }
            break;
        case RCBASIC_PROJECT_SOURCE_EXISTING:
            break;
    }

    //rcbasic_project_tree->AddRoot(name);
}

void rcbasic_project::setName(wxString new_project_name)
{

}

void rcbasic_project::setMainSource(wxString new_main_source)
{

}

void rcbasic_project::setAuthor(wxString new_author)
{

}

void rcbasic_project::setWebsite(wxString new_website)
{

}

void rcbasic_project::setDescription(wxString new_description)
{

}

void rcbasic_project::addSourceFile(wxString filePath)
{
    wxFileName fname(filePath);
    fname.MakeRelativeTo(location);
    source_files.push_back(fname);
}

bool rcbasic_project::createNewSourceFile(wxString filePath)
{
    wxFileName fname(filePath);
    wxFile f;
    if(!f.Create(filePath))
       return false;
    f.Close();
    fname.MakeRelativeTo(location);
    source_files.push_back(fname);
    return true;
}

void rcbasic_project::setRootNode(wxTreeItemId project_root)
{
    root_node_id = project_root;
}


wxString rcbasic_project::getName()
{

}

wxFileName rcbasic_project::getMainSource()
{
    return main_source;
}

wxString rcbasic_project::getAuthor()
{

}

wxString rcbasic_project::getWebsite()
{

}

wxString rcbasic_project::getDescription()
{

}

std::vector<rcbasic_project_node> rcbasic_project::getSourceFiles()
{
    return source_files;
}

wxTreeItemId rcbasic_project::getRootNode()
{
    return root_node_id;
}


