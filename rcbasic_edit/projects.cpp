#include "projects.h"

rcbasic_project_node::rcbasic_project_node(wxFileName node_path)
{
    path = node_path;
    rc_txtCtrl = NULL;
    notebook_page = NULL;
    text_changed = false;
    temp_flag = false;
    add_remove_state = 1;
}

void rcbasic_project_node::setLocationStoreType(int store_loc_type)
{
    store_location_type = store_loc_type;

}

int rcbasic_project_node::getLocationStoreType()
{
    return store_location_type;
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

void rcbasic_project_node::setTextChangedFlag(bool flag)
{
    text_changed = flag;
    /*if(text_changed)
    {
        if(rc_txtCtrl)
            txt_backup = rc_txtCtrl->GetText();
    }*/
}

bool rcbasic_project_node::getTextChangedFlag()
{
    return text_changed;
}

void rcbasic_project_node::setTextCtrl(wxStyledTextCtrl* txt_ctrl)
{

    if( (!txt_ctrl) || txt_ctrl==rc_txtCtrl)
    {
        rc_txtCtrl = txt_ctrl;
        return;
    }

    rc_txtCtrl = txt_ctrl;

    wxFile f;

    /*if(text_changed)
    {
        txt_ctrl->ClearAll();
        txt_ctrl->AddText(txt_backup);
        txt_backup.clear();
        text_changed = false;
        return;
    }*/

    if(!f.Open(path.GetFullPath()))
    {
        wxMessageBox(_("Could not read file."));
        return;
    }

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
                source_file.Write("Print \"Hello World\"\n");
                source_file.Close();
            }

            main_source.MakeRelativeTo(project_dir.GetFullPath());

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
                project_file.Write(_("SOURCE_REL:")+main_source.GetFullPath()+_("\n"));
                project_file.Close();
            }
            break;
        case RCBASIC_PROJECT_SOURCE_EXISTING:
            fname = wxFileName(main_source_value);
            fname.SetPath(location);
            //wxPuts(_("FileName = ") + fname.GetFullPath());
            //wxPuts(_("NAME ONLY = ") + fname.GetFullName());
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

            //wxPuts(_("MAIN source = ") + main_source.GetFullPath());

            main_source.MakeRelativeTo(project_dir.GetFullPath());

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
                project_file.Write(_("SOURCE_REL:")+main_source.GetFullPath()+_("\n"));
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

void rcbasic_project::copyFromProject(rcbasic_project* p)
{
    name = p->getName();
    main_source = p->getMainSource();
    author = p->getAuthor();
    website = p->getWebsite();
    description = p->getDescription();

    source_files.clear();

    for(int i = 0; i < p->getSourceFiles().size(); i++)
    {
        rcbasic_project_node* p_node = p->getSourceFiles()[i];
        rcbasic_project_node* node = new rcbasic_project_node(p_node->getPath());
        node->setNode(p_node->getNode());
        node->setLocationStoreType(p_node->getLocationStoreType());
        node->setNotebookPage(p_node->getNotebookPage());
        node->setTextChangedFlag(p_node->getTextChangedFlag());
        node->setTextCtrl(p_node->getTextCtrl());
        source_files.push_back(node);
    }

    root_node_id = p->getRootNode();

    location = p->getLocation();
    project_file_location = p->getProjectFileLocation();

    project_valid = p->projectExists();
    last_saved_project = p->getLastProjectSave();
}

void rcbasic_project::setPointersNull()
{
    last_saved_project = NULL;
    for(int i = 0; i < source_files.size(); i++)
    {
        source_files[i] = NULL;
    }
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
            if(source_files[i]->getLocationStoreType()==STORE_LOCATION_RELATIVE)
            {
                wxFileName fname = source_files[i]->getPath();
                fname.MakeRelativeTo(location);
                project_file.Write(_("SOURCE_REL:")+fname.GetFullPath()+_("\n"));
            }
            else
            {
                wxFileName fname = source_files[i]->getPath();
                fname.MakeAbsolute();
                project_file.Write(_("SOURCE_ABS:")+fname.GetFullPath()+_("\n"));
            }
        }
        for(int i = 0; i < env_vars.size(); i++)
        {
            project_file.Write(_("ENV:")+env_vars[i].var_name+_("=")+env_vars[i].var_value+_("\n"));
        }
        project_file.Close();
        location = save_file.GetPath();
        project_file_location = save_file.GetFullPath();
        setLastProjectSave();
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
        last_saved_project->addSourceFile(source_files[i]->getPath().GetFullPath(), source_files[i]->getLocationStoreType());
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
            if(source_files[i]->getPath().GetFullPath() != last_saved_project->getSourceFiles()[i]->getPath().GetFullPath() ||
               source_files[i]->getLocationStoreType() != last_saved_project->getSourceFiles()[i]->getLocationStoreType())
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

bool rcbasic_project::addSourceFile(wxString filePath, int store_loc_type)
{
    //wxString cwd = wxGetCwd();
    //wxPuts(_("DEBUG 1"));
    //wxSetWorkingDirectory(location);
    //wxPuts(_("DEBUG 2"));
    wxFileName fname(filePath);

    wxFileName fname_rel(filePath);
    fname.MakeRelativeTo(location);

    wxFileName fname_abs(filePath);
    fname_abs.MakeAbsolute();

    //wxSetWorkingDirectory(cwd);

    for(int i = 0; i < source_files.size(); i++)
    {
        if(fname.GetFullPath().compare(source_files[i]->getPath().GetFullPath())==0 ||
           fname_abs.GetFullPath().compare(source_files[i]->getPath().GetFullPath())==0 ||
           fname_rel.GetFullPath().compare(source_files[i]->getPath().GetFullPath())==0)
            return false;
    }

    rcbasic_project_node* src_file;

    if(store_loc_type==STORE_LOCATION_RELATIVE)
        src_file = new rcbasic_project_node(fname_rel);
    else
        src_file = new rcbasic_project_node(fname_abs);

    src_file->setLocationStoreType(store_loc_type);
    //fname.MakeRelativeTo(location);
    source_files.push_back(src_file);
    return true;
}

bool rcbasic_project::addTempSourceFile(wxString filePath, int store_loc_type)
{
    wxFileName fname(filePath);
    wxFileName fname_rel(filePath);

    wxFileName fname_abs(filePath);
    fname_abs.MakeAbsolute();

    int p_index = -1;
    bool should_add = true;

    for(int i = 0; i < source_files.size(); i++)
    {
        if(fname.GetFullPath().compare(source_files[i]->getPath().GetFullPath())==0 ||
           fname_abs.GetFullPath().compare(source_files[i]->getPath().GetFullPath())==0 ||
           fname_rel.GetFullPath().compare(source_files[i]->getPath().GetFullPath())==0)
        {
            p_index = i;

            //if(source_files[i]->getAddRemoveFlag()==1)
              //  wxPuts(_("file in project already: ")+fname.GetFullPath());

            if(source_files[i]->getAddRemoveFlag()==1)
                should_add = false;
        }
    }

    if(!should_add)
        return false;

    rcbasic_project_node* src_file;

    if(p_index < 0)
        src_file = new rcbasic_project_node(fname);
    else
    {
        src_file = source_files[p_index];
        src_file->setAsAddFile(true);
        src_file->setLocationStoreType(store_loc_type);
        //src_file->setAsTemp(true);
        return true;
    }

    src_file->setLocationStoreType(store_loc_type);
    src_file->setAsTemp(true);
    src_file->setAsAddFile(true);
    //fname.MakeRelativeTo(location);
    source_files.push_back(src_file);
    return true;
}

int rcbasic_project::getSourceFileIndex(wxFileName file_path)
{
    int index = -1;

    wxFileName fname_abs = file_path;
    file_path.MakeAbsolute();

    wxFileName fname_rel = file_path;
    fname_rel.MakeRelativeTo(location);

    for(int i = 0; i < source_files.size(); i++)
    {
        //wxPuts(_("File path compare[1] : ") + file_path.GetFullPath());
        //wxPuts(_("File path compare[1.1] : ") + fname_abs.GetFullPath());
        //wxPuts(_("File path compare[1.2] : ") + fname_rel.GetFullPath());
        //wxPuts(_("File path compare[2] : ") + source_files[i]->getPath().GetFullPath());
        if(source_files[i]->getPath().GetFullPath().compare(fname_abs.GetFullPath())==0 ||
           source_files[i]->getPath().GetFullPath().compare(fname_rel.GetFullPath())==0 ||
           source_files[i]->getPath().GetFullPath().compare(file_path.GetFullPath())==0)
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
    src_file->setLocationStoreType(STORE_LOCATION_RELATIVE);
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

void rcbasic_project::addEnvVar(wxString var_name, wxString var_value)
{
    rcbasic_edit_env_var new_var;
    new_var.var_name = var_name;
    new_var.var_value = var_value;
    env_vars.push_back(new_var);
}

void rcbasic_project::clearEnvVars()
{
    env_vars.clear();
}

std::vector<rcbasic_edit_env_var> rcbasic_project::getVars()
{
    return env_vars;
}

void rcbasic_project::setVars(std::vector<rcbasic_edit_env_var> v)
{
    env_vars = v;
}
