#include "projects.h"

rcbasic_project_node::rcbasic_project_node(wxFileName node_path)
{
    path = node_path;
    rc_txtCtrl = NULL;
    notebook_page = NULL;
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

void rcbasic_project_node::setTextCtrl(wxStyledTextCtrl* txt_ctrl)
{
    if(!txt_ctrl)
        return;

    wxFile f;

    if(!f.Open(path.GetFullPath()))
        return;

    wxString f_data;

    f.ReadAll(&f_data);
    f.Close();

    txt_ctrl->ClearAll();
    txt_ctrl->AddText(f_data);
}

wxStyledTextCtrl* rcbasic_project_node::getTextCtrl()
{
    return rc_txtCtrl;
}

void rcbasic_project_node::setNotebookPage(wxWindow* page)
{
    notebook_page = page;
    notebook_page_addr = reinterpret_cast<uintptr_t>(&page);
    //data = _("Hello World");
    //wxPuts(_("data start = ") + data +_("\n"));
    //wxPrintf("Notebook page change2: %p\n", notebook_page);
}

wxWindow* rcbasic_project_node::getNotebookPage()
{
    //wxPuts(_("data = ")+data+_("\n"));
    //wxPrintf("Notebook page change return: %u\n", notebook_page_addr);
    return (wxWindow*)(notebook_page_addr);
}



rcbasic_project::rcbasic_project(wxString project_name, wxString project_location, int main_source_flag, wxString main_source_value,
                wxString project_author, wxString project_website, wxString project_description)
{
    last_saved_project = NULL;
    project_valid = false;
    wxFileName project_dir;

    switch(main_source_flag)
    {
        case RCBASIC_PROJECT_SOURCE_NEW:
        case RCBASIC_PROJECT_SOURCE_EXISTING:
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
            break;
        case RCBASIC_PROJECT_SOURCE_OPEN:
            project_dir.SetPath(project_location);
            location = project_dir.GetFullPath();
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
                project_file_location = project_file_name.GetFullPath();
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
                project_file_location = project_file_name.GetFullPath();
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
        case RCBASIC_PROJECT_SOURCE_OPEN:
            main_source = wxFileName(main_source_value);
            //wxPuts(_("Proj Loc: ") + location + _("\n"));
            //wxPuts(_("Main: ") + main_source.GetFullPath() + _("\n"));
            break;
    }

    //wxPuts(_("Testing"));
    //setLastProjectSave();

    //rcbasic_project_tree->AddRoot(name);
}

rcbasic_project::rcbasic_project()
{
    last_saved_project = NULL;
}

rcbasic_project::~rcbasic_project()
{
    if(last_saved_project)
        delete last_saved_project;

    source_files.clear();
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
            project_file.Write(_("SOURCE:")+source_files[i]->getPath().GetFullPath()+_("\n"));
        }
        project_file.Close();
        location = save_file.GetPath();
        //wxPuts(_("New location: ") + location);
    }

    //setLastProjectSave();

    return true;
}

void rcbasic_project::setLastProjectSave()
{
    if(!last_saved_project)
        last_saved_project = new rcbasic_project();

    last_saved_project->setName(name);
    last_saved_project->setMainSource(main_source.GetFullPath());
    last_saved_project->setAuthor(author);
    last_saved_project->setWebsite(website);
    last_saved_project->setDescription(description);
    last_saved_project->getSourceFiles().clear();
    for(int i = 0; i < source_files.size(); i++)
    {
        last_saved_project->addSourceFile(source_files[i]->getPath().GetFullPath());
    }
}

bool rcbasic_project::projectHasChanged()
{
    bool cmp = true;

    //wxPuts("WATS GUD");

    if(!last_saved_project)
        return true;

    cmp = cmp && name==last_saved_project->getName();
    cmp = cmp && main_source.GetFullPath()==last_saved_project->getMainSource().GetFullPath();
    cmp = cmp && author==last_saved_project->getAuthor();
    cmp = cmp && website==last_saved_project->getWebsite();
    cmp = cmp && description==last_saved_project->getDescription();
    if(source_files.size()==last_saved_project->getSourceFiles().size())
    {
        for(int i = 0; i < source_files.size(); i++)
        {
            if(source_files[i]->getPath().GetFullPath() != last_saved_project->getSourceFiles()[i]->getPath().GetFullPath())
            {
                cmp = false;
                break;
            }
        }
    }
    else
        cmp = false;

    return !cmp;
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

    for(int i = 0; i < source_files.size(); i++)
    {
        if(fname.GetFullPath()==source_files[i]->getPath().GetFullPath())
            return;
    }

    rcbasic_project_node* src_file = new rcbasic_project_node(fname);
    //fname.MakeRelativeTo(location);
    source_files.push_back(src_file);
}

int rcbasic_project::getSourceFileIndex(wxFileName file_path)
{
    int index = -1;

    for(int i = 0; i < source_files.size(); i++)
    {
        if(source_files[i]->getPath().GetFullPath()==file_path.GetFullPath())
        {
            index = i;
            break;
        }
    }
    return index;
}

bool rcbasic_project::createNewSourceFile(wxString filePath)
{
    wxFileName fname(filePath);
    wxFile f;
    if(!f.Create(filePath))
       return false;
    f.Close();
    //fname.MakeRelativeTo(location);
    rcbasic_project_node* src_file = new rcbasic_project_node(fname);
    source_files.push_back(src_file);
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

std::vector<rcbasic_project_node*> rcbasic_project::getSourceFiles()
{
    return source_files;
}

wxTreeItemId rcbasic_project::getRootNode()
{
    return root_node_id;
}

void rcbasic_project::setProjectFileLocation(wxString pfile_loc)
{
    project_file_location = pfile_loc;
}

wxString rcbasic_project::getProjectFileLocation()
{
    return project_file_location;
}
