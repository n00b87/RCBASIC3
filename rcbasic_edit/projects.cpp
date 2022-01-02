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
    project_valid = false;
    wxFileName project_dir;

    project_dir.SetPath(project_location);
    project_dir.AppendDir(project_name);
    location = project_dir.GetFullPath();

    if(wxDirExists(location))
    {
        wxMessageBox(_("A folder with the project name already exists at this location."));
        return;
    }

    if(!wxMkdir(location))
    {
        wxMessageBox(_("Could not access project location"));
        return;
    }


    name = project_name;
    author = project_author;
    website = project_website;
    description = project_description;

    wxFile project_file, source_file;

    wxFileName fname, dest_name, project_file_name;

    project_file_name.SetPath(location);
    project_file_name.SetName(name + _(".rcprj"));

    //wxFileName x = fname;
    //x.MakeRelativeTo(location);
    //wxPuts(_("Fname: ")+x.GetFullPath());

    switch(main_source_flag)
    {
        case RCBASIC_PROJECT_SOURCE_NEW:
            fname.SetPath(location);
            fname.SetName(main_source_value);

            if(!source_file.Create(fname.GetFullPath()))
            {
                if(!source_file.Open(fname.GetFullPath()))
                {
                    wxMessageBox(_("Could not access main source file"));
                    return;
                }
                else
                {
                    main_source = fname;
                    project_valid = true;
                    //main_source.MakeRelativeTo(location);
                }
            }
            else
            {
                main_source = fname;
                project_valid = true;
                //main_source.MakeRelativeTo(location);
                source_file.Write("This is a test\n");
                source_file.Write("The end");
                source_file.Close();
            }


            if(!project_file.Create(project_file_name.GetFullPath()))
            {
                wxMessageBox(_("Could not create project file"));
                return;
            }
            else
            {
                project_valid = true;
                //main_source.MakeRelativeTo(location);
                project_file.Write(_("RCBASIC_STUDIO:1.0\n"));
                project_file.Write(_("PROJECT_NAME:")+name+_("\n"));
                project_file.Write(_("PROJECT_MAIN:")+main_source.GetFullPath()+_("\n"));
                project_file.Write(_("AUTHOR:")+author+_("\n"));
                project_file.Write(_("WEBSITE:")+website+_("\n"));
                description.Replace("\r","");
                description.Replace("\n","");
                project_file.Write(_("DESCRIPTION:")+description+_("\n"));
                project_file.Write(_("SOURCE:")+main_source.GetFullPath()+_("\n"));
                project_file.Close();
            }
            break;
        case RCBASIC_PROJECT_SOURCE_EXISTING:
            fname = wxFileName(main_source_value);
            fname.SetPath(location);
            if(!wxCopyFile(main_source_value, fname.GetFullPath() ))
            {
                wxMessageBox(_("Could not copy main source file into project"));
                return;
            }
            else
            {
                main_source = fname;
                project_valid = true;
            }

            if(!project_file.Create(project_file_name.GetFullPath()))
            {
                wxMessageBox(_("Could not create project file"));
                return;
            }
            else
            {
                project_valid = true;
                //main_source.MakeRelativeTo(location);
                project_file.Write(_("RCBASIC_STUDIO:1.0\n"));
                project_file.Write(_("PROJECT_NAME:")+name+_("\n"));
                project_file.Write(_("PROJECT_MAIN:")+main_source.GetFullPath()+_("\n"));
                project_file.Write(_("AUTHOR:")+author+_("\n"));
                project_file.Write(_("WEBSITE:")+website+_("\n"));
                description.Replace("\r","");
                description.Replace("\n","");
                project_file.Write(_("DESCRIPTION:")+description+_("\n"));
                project_file.Write(_("SOURCE:")+main_source.GetFullPath()+_("\n"));
                project_file.Close();
            }
            break;
    }

    //rcbasic_project_tree->AddRoot(name);
}

bool rcbasic_project::saveProject(wxFileName save_file)
{
    //wxPuts(_("Save PATH: ") + save_file.GetPath());
    //wxPuts(_("Full PATH: ") + save_file.GetFullPath());
    //return false;

    if(!wxDirExists(save_file.GetPath()))
    {
        if(!wxMkdir(save_file.GetPath()))
        {
            wxMessageBox(_("Could not save project to this directory"));
            return false;
        }
    }

    wxFile project_file;

    if(!project_file.Open(save_file.GetFullPath(), wxFile::write))
    {
        if(!project_file.Create(save_file.GetFullPath(), true))
        {
            wxMessageBox(_("Could not open project file"));
            return false;
        }
    }
    else
    {
        //wxPuts("Saving Project");
        project_file.Write(_("RCBASIC_STUDIO:1.0\n"));
        project_file.Write(_("PROJECT_NAME:")+name+_("\n"));
        project_file.Write(_("PROJECT_MAIN:")+main_source.GetFullPath()+_("\n"));
        project_file.Write(_("AUTHOR:")+author+_("\n"));
        project_file.Write(_("WEBSITE:")+website+_("\n"));
        description.Replace("\r","");
        description.Replace("\n","");
        project_file.Write(_("DESCRIPTION:")+description+_("\n"));
        for(int i = 0; i < source_files.size(); i++)
        {
            project_file.Write(_("SOURCE:")+source_files[i].getPath().GetFullPath()+_("\n"));
        }
        project_file.Close();
        location = save_file.GetPath();
        //wxPuts(_("New location: ") + location);
    }
    return true;
}

void rcbasic_project::setLocation(wxString new_location)
{
    location = new_location;
}

wxString rcbasic_project::getLocation()
{
    return location;
}

bool rcbasic_project::projectExists()
{
    return project_valid;
}

void rcbasic_project::setName(wxString new_project_name)
{
    name = new_project_name;
}

void rcbasic_project::setMainSource(wxString new_main_source)
{
    main_source = wxFileName(new_main_source);
}

void rcbasic_project::setAuthor(wxString new_author)
{
    author = new_author;
}

void rcbasic_project::setWebsite(wxString new_website)
{
    website = new_website;
}

void rcbasic_project::setDescription(wxString new_description)
{
    description = new_description;
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
    return name;
}

wxFileName rcbasic_project::getMainSource()
{
    return main_source;
}

wxString rcbasic_project::getAuthor()
{
    return author;
}

wxString rcbasic_project::getWebsite()
{
    return website;
}

wxString rcbasic_project::getDescription()
{
    return description;
}

std::vector<rcbasic_project_node> rcbasic_project::getSourceFiles()
{
    return source_files;
}

wxTreeItemId rcbasic_project::getRootNode()
{
    return root_node_id;
}


