#include <wx/string.h>

#include <wx/arrstr.h>
#include <wx/dir.h>
#include <wx/busyinfo.h>

#include "rcbasic_edit_frame.h"
#include "rcbasic_edit_newProject_dialog.h"
#include "rc_closeProjectSavePrompt_dialog.h"
#include "rc_find_dialog.h"
#include "rcbasic_edit_searchWrap_dialog.h"
#include "rcbasic_edit_replace_dialog.h"
#include "rcbasic_edit_gotoLine_dialog.h"
#include "rcbasic_edit_setColorScheme_dialog.h"
#include "rcbasic_edit_projectSettings_dialog.h"
#include "rcbasic_edit_projectEnvironment_dialog.h"
#include "rcbasic_edit_fileProperties_dialog.h"
#include "rcbasic_edit_preference_dialog.h"
#include "drag_files.h"
#include "eval.h"
#include "rcbasic_symbol.h"


void rcbasic_edit_frame::pfile_readContents(wxString file_path)
{
    pfile_contents.clear();

    //rcbasic_edit_frame* frame = (rcbasic_edit_frame*) parent_frame;
    notebook_mutex.Lock();

    wxFile f(file_path, wxFile::read);

    wxString file_text;
    f.ReadAll(&file_text);
    file_text += _("\n");

    f.Close();

    notebook_mutex.Unlock();

    wxString current_line = _("");
    wxString current_char;

    for(int i = 0; i < file_text.length(); i++)
    {
        current_char = file_text.substr(i,1);
        if(current_char.compare(_("\n"))==0)
        {
            pfile_contents.push_back(current_line);
            current_line = _("");
        }
        else
        {
            current_line += current_char;
        }
    }
}

void rcbasic_edit_frame::pfile_addSymbol(rcbasic_project* p, rcbasic_symbol sym)
{
    int insert_pos = 0;
    wxString sym_id = sym.id.Upper();
    for(int i = 0; i < p->project_symbols.size(); i++)
    {
        int id_sym_cmp = p->project_symbols[i].upper_id.compare(sym_id);
        if(id_sym_cmp==0 && p->project_symbols[i].token_type == sym.token_type)
        {
            //delete sym;
            return;
        }
    }
    p->project_symbols.push_back(sym);
    //sym_list->insert(sym_list->begin()+insert_pos, sym);
}



bool rcbasic_edit_frame::pfile_runParser(rcbasic_project* p)
{
    p->project_symbols.clear();
    std::vector<rcbasic_project_node*> source_files = p->getSourceFiles();

    for(int file_index = 0; file_index < source_files.size(); file_index++)
    {
        wxFileName src_file = source_files[file_index]->getPath();
        src_file.MakeAbsolute();
        pfile_readContents(src_file.GetFullPath());

        int contents_changed = 0;

        bool fn_define = false;


        for(int i = 0; i < pfile_contents.size(); i++)
        {

            rc_eval(std::string(pfile_contents[i].mb_str()), &fn_define);
            //wxPuts(_("EVAL RAN"));
            for(int t_count = 0; t_count < id_tokens.size(); t_count++)
            {
                //wxPrintf( wxString(id_tokens[t_count].name.c_str(), wxConvUTF8) + _("[%d]:%d\n"), id_tokens[t_count].dimensions, i+1 );
                rcbasic_symbol sym;// = new rcbasic_symbol();
                sym.id = id_tokens[t_count].name;
                sym.upper_id = sym.id.Upper();
                sym.line = i;
                sym.dimensions = id_tokens[t_count].dimensions;
                sym.token_type = id_tokens[t_count].token_type;
                sym.in_list = id_tokens[t_count].is_in_list;


                notebook_mutex.Lock();
                pfile_addSymbol(p, sym);
                notebook_mutex.Unlock();
            }

        }
    }

    return true;
}




rcbasic_edit_txtCtrl::rcbasic_edit_txtCtrl(wxFileName src_path, wxAuiNotebook* parent_nb)
{
    sourcePath = src_path;
    txtCtrl = new wxStyledTextCtrl(parent_nb, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, src_path.GetFullName());
    text_changed = false;
}

rcbasic_edit_txtCtrl::~rcbasic_edit_txtCtrl()
{
    if(txtCtrl)
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



BEGIN_EVENT_TABLE(rcbasic_edit_frame, wxFrame)
    EVT_COMMAND(wxID_ANY, wxEVT_MYTHREAD, rcbasic_edit_frame::OnParserThread)
END_EVENT_TABLE()

void rcbasic_edit_frame::updateSymbolTree()
{
    //symbol_tree->DeleteChildren(variable_root_node);
    //symbol_tree->DeleteChildren(function_root_node);
    int v_index = 0;
    int f_index = 0;

    //int v_count = symbol_tree->GetChildrenCount(variable_root_node);
    //int f_count = symbol_tree->GetChildrenCount(function_root_node);

    /*
    wxTreeItemIdValue v_cookie;
    wxTreeItemId v_child = symbol_tree->GetFirstChild(variable_root_node, v_cookie);

    wxTreeItemIdValue f_cookie;
    wxTreeItemId f_child = symbol_tree->GetFirstChild(function_root_node, f_cookie);
    */

    for(int i = 0; i < symbols.size(); i++)
    {
        switch(symbols[i].token_type)
        {
            case TOKEN_TYPE_VARIABLE:
                if(v_index < var_nodes.size())
                {
                    setSymbol(var_nodes[v_index], symbols[i]);
                    //v_child = symbol_tree->GetNextChild(variable_root_node, v_cookie);
                }
                else
                    addSymbol(symbols[i]);
                v_index++;
                break;
            case TOKEN_TYPE_FUNCTION:
                if(f_index < fn_nodes.size())
                {
                    setSymbol(fn_nodes[f_index], symbols[i]);
                    //f_child = symbol_tree->GetNextChild(function_root_node, f_cookie);
                }
                else
                    addSymbol(symbols[i]);
                f_index++;
                break;
        }
    }

    //wxPrintf(_("V -- %d   --  %d"), v_index, v_count);

    while(v_index < var_nodes.size())
    {
        rcbasic_treeItem_data* data = (rcbasic_treeItem_data*)symbol_tree->GetItemData(var_nodes[v_index]);
        symbol_tree->SetItemData(var_nodes[v_index], NULL);
        if(data)
            delete data;
        //if(symbol_tree-> GetChildrenCount(variable_root_node))
            symbol_tree->Delete(var_nodes[v_index]);
        var_nodes.erase(var_nodes.begin()+v_index);
        //v_child = symbol_tree->GetNextChild(variable_root_node, v_cookie);
    }

    while(f_index < fn_nodes.size())
    {
        rcbasic_treeItem_data* data = (rcbasic_treeItem_data*)symbol_tree->GetItemData(fn_nodes[f_index]);
        symbol_tree->SetItemData(fn_nodes[f_index], NULL);
        if(data)
            delete data;
        symbol_tree->Delete(fn_nodes[f_index]);
        fn_nodes.erase(fn_nodes.begin()+f_index);
        //f_child = symbol_tree->GetNextChild(function_root_node, f_cookie);
    }


    //wxPrintf(_("NODE SIZES: %d  %d\n"), var_nodes.size(), fn_nodes.size());
}

void rcbasic_edit_frame::OnParserThread(wxCommandEvent& event)
{
    notebook_mutex.Lock();
    thread_returned = true;

    std::vector<rcbasic_symbol>* sym_list = NULL;

    if(!pre_parsed_page)
    {
        sym_list = NULL;
    }
    else
    {
        sym_list = (std::vector<rcbasic_symbol>*) event.GetClientData();
    }

    if(sym_list)
    {
        /*for(int i = 0; i < symbols.size(); i++)
        {
            if(symbols[i])
            {
                delete symbols[i];
                symbols[i] = NULL;
            }
        }*/
        symbols.clear();
        user_id_list.Clear();

        user_id_list = id_list;

        if(active_project)
        {
            for(int i = 0; i < active_project->project_symbols.size(); i++)
                user_id_list.Add(active_project->project_symbols[i].id);
        }

        if(pre_parsed_page)
        {
            for(int i = 0; i < sym_list->size(); i++)
            {
                rcbasic_symbol s = sym_list[0][i];
                if(s.in_list)
                    symbols.push_back(s);

                user_id_list.Add(s.id);

                //wxPuts(_("VAR --- ") + s->id);
            }
        }

        user_id_list.Sort();

        //if(sym_list)
          //  delete sym_list;

        updateSymbolTree();
    }

    parsed_page = pre_parsed_page;
    symbolUpdateInProgress = false;

    notebook_mutex.Unlock();
}

rcbasic_edit_frame::rcbasic_edit_frame( wxWindow* parent, int argc, wxArrayString argv )
:
rc_ideFrame( parent )
{
    RCBasic_Studio_Version = _("v1.3");

    build_run_project = NULL;
    current_file_project = new rcbasic_project();

    lenCompletionCheck = 3;

    //#ifdef _WIN32
    sourceFile_auinotebook->Connect( wxEVT_DROP_FILES, wxDropFilesEventHandler( rcbasic_edit_frame::onDropFiles ), NULL, this );
    sourceFile_auinotebook->DragAcceptFiles(true);
    //#endif // _WIN32

    thread_returned = false;
    sym_sem = NULL;
    symbolUpdateInProgress = false;
    pre_parsed_page = NULL;
    parsed_page = NULL;
    sym_sem = NULL;
    token_parser = NULL;

    build_run_project = NULL;
    debug_project = NULL;
    build_process = NULL;
    run_process = NULL;

    isBuilding = false;
    isRunning = false;
    isBuildingAndRunning = false;
    isDebugging = false;
    build_pid = -1;
    run_pid = -1;

    default_font = wxFont(12,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL);
    editor_font = default_font;

    messageWindowVisible = true;
    m_showMessageWindow_menuItem->Check(messageWindowVisible);

    toolbarVisible = true;
    m_showToolbar_menuItem->Check(toolbarVisible);

    sideBarVisible = true;
    m_showSideBar_menuItem->Check(sideBarVisible);

    context_project = NULL;
    active_project = NULL;

    wxString editor_path = wxStandardPaths::Get().GetExecutablePath();

    wxIcon FrameIcon;

    wxFileName frameIcon_path(editor_path);
    frameIcon_path.SetFullName(_("rcbasic.png"));
    frameIcon_path.AppendDir(_("gfx"));

    FrameIcon.CopyFromBitmap(wxBitmap(wxImage(frameIcon_path.GetFullPath())));
    SetIcon(FrameIcon);

    wxFileName rcbasic_dir(editor_path);
#ifdef _WIN32
    rcbasic_dir.AppendDir(_("rcbasic"));
#endif
    rcbasic_dir.SetFullName(_(""));
    rcbasic_dir.MakeAbsolute();

#ifdef _WIN32
    wxFileName tools_dir = rcbasic_dir;
#else
    wxFileName tools_dir(editor_path);
#endif
    tools_dir.AppendDir(_("tools"));
    tools_dir.SetFullName(_(""));
    tools_dir.MakeAbsolute();

    wxFileName rc32_dir = rcbasic_dir;
    rc32_dir.AppendDir(_("rcbasic_32"));

    wxFileName rc64_dir = rcbasic_dir;
    rc64_dir.AppendDir(_("rcbasic_64"));

    wxFileName pkg_home_dir = tools_dir;
    pkg_home_dir.AppendDir(_("dist"));

    wxFileName keystore_dir(editor_path);
    keystore_dir.AppendDir(_("keystore"));

    wxFileName android_dir = pkg_home_dir;

    android_dir.AppendDir(_("rcbasic_android"));

    wxSetEnv(_("RCBASIC_HOME"), rcbasic_dir.GetFullPath());
    wxSetEnv(_("RCBASIC_TOOLS"), tools_dir.GetFullPath());
    wxSetEnv(_("RCBASIC_D32"), rc32_dir.GetFullPath());
    wxSetEnv(_("RCBASIC_D64"), rc64_dir.GetFullPath());
    wxSetEnv(_("RC_PKG_HOME"), pkg_home_dir.GetFullPath());
    wxSetEnv(_("RC_KEYSTORE_DIR"), keystore_dir.GetFullPath());
    wxSetEnv(_("RCBASIC_WIN"), rcbasic_dir.GetFullPath());
    wxSetEnv(_("RCBASIC_ANDROID_DIR"), android_dir.GetFullPath());

    wxFileName gfx_path(editor_path);
    gfx_path.AppendDir(_("gfx"));

    wxFileName root_image = gfx_path;
    root_image.SetFullName(_("rcbasic16.png"));

    wxFileName symbol_root_image = gfx_path;
    symbol_root_image.SetFullName(_("symbol_root.png"));

    wxFileName symbol_item_image = gfx_path;
    symbol_item_image.SetFullName(_("symbol_item.png"));

    wxFileName symbol_fn_item_image = gfx_path;
    symbol_fn_item_image.SetFullName(_("symbol_fn_item.png"));

    project_tree_imageList = new wxImageList(16,16,true);
    project_tree_rootImage = project_tree_imageList->Add(wxBitmap(wxImage(root_image.GetFullPath())));
    project_tree_folderImage  = project_tree_imageList->Add(wxArtProvider::GetBitmap( wxART_FOLDER, wxART_MENU ));
    project_tree_fileImage = project_tree_imageList->Add(wxArtProvider::GetBitmap( wxART_NORMAL_FILE, wxART_MENU ));
    project_tree->AssignImageList(project_tree_imageList);

    project_tree->AddRoot(_("Projects"), project_tree_rootImage);
    #ifdef _WIN32
    selected_project_item = project_tree->GetRootItem();
    activated_project_item_flag = false;
    activated_project_item_flag2 = false;
    remove_file_node_flag = false;
    #endif // _WIN32

    active_project = NULL;
    context_project = NULL;
    closing_project = NULL;


    symbol_tree_imageList = new wxImageList(16,16,true);
    symbol_tree_rootImage = symbol_tree_imageList->Add(wxBitmap(wxImage(symbol_root_image.GetFullPath())));
    symbol_tree_varImage  = symbol_tree_imageList->Add(wxBitmap(wxImage(symbol_item_image.GetFullPath())));
    symbol_tree_fnImage = symbol_tree_imageList->Add(wxBitmap(wxImage(symbol_fn_item_image.GetFullPath())));
    symbol_tree->AssignImageList(symbol_tree_imageList);

    symbol_tree->AddRoot(_("Symbols"), symbol_tree_rootImage);
    function_root_node = symbol_tree->AppendItem(symbol_tree->GetRootItem(), _("Function"), symbol_tree_fnImage, -1, NULL);
    variable_root_node = symbol_tree->AppendItem(symbol_tree->GetRootItem(), _("Variables"), symbol_tree_varImage, -1, NULL);

    symbol_tree->Expand(symbol_tree->GetRootItem());

    symbol_tree->SetDoubleBuffered(true);

    //Load recent files and projects
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
                    m_recentFiles_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rcbasic_edit_frame::onRecentFileSelect ), this, recent_item->GetId());
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
                    m_recentProjects_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rcbasic_edit_frame::onRecentProjectSelect ), this, recent_item->GetId());
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

    wxFileName editor_properties_path(editor_path);
    editor_properties_path.AppendDir(_("config"));
    editor_properties_path.SetFullName(_("rcbasic_edit.config"));
    loadEditorProperties(editor_properties_path);

    wxFileName view_def_path = editor_properties_path;
    view_def_path.SetFullName(_("default_view.config"));
    loadDefaultViewProperties(view_def_path);

    wxFileName scheme_path(editor_path);
    scheme_path.AppendDir(_("config"));
    scheme_path.AppendDir(_("schemes"));
    if(default_scheme.compare("")==0)
        default_scheme = _("default.scheme");
    scheme_path.SetFullName(default_scheme);
    loadScheme(scheme_path);
    applyScheme(NULL);

    wxString path;
    wxGetEnv(_("PATH"), &path);

    if(win_os_bit==64)
        wxSetEnv(_("PATH"), path + _(";") + rc64_dir.GetFullPath());
    else
        wxSetEnv(_("PATH"), path + _(";") + rc32_dir.GetFullPath());

    if(enable_parser)
    {
        token_parser = new parserThread(this, 0, this);
        token_parser->Run();
    }

    for(int i = 1; i < argc; i++)
    {
        wxFileName f(argv[i]);
        if(f.GetExt().compare(_("rcprj"))==0)
            openProject(f);
        else if(f.GetExt().compare(_("bas"))==0 || f.GetExt().compare(_("txt"))==0)
            openSourceFile(f);
    }
}

bool rcbasic_edit_frame::loadDefaultViewProperties(wxFileName fname)
{
    wxFile properties_file;

    if(!fname.Exists())
    {
        return false;
    }

    if(!properties_file.Open(fname.GetFullPath()))
        return false;

    wxString properties;
    properties_file.ReadAll(&properties);
    properties_file.Close();

    properties.Append(_(" \n"));

    wxString property;
    wxString value;

    for(int i = 0; i < properties.length(); i++)
    {
        int vpos = properties.find_first_of(_("="));
        if(vpos == wxString::npos)
            break;
        property = properties.substr(0, vpos).Trim();
        property = property.substr(property.find_first_not_of(_(" ")));

        value = properties.substr(vpos+1);
        value = value.substr(0, value.find_first_of(_("\n")));

        if(property.compare(_("DEFAULT_SCHEME"))==0)
        {
            wxFileName scheme_fname;
            scheme_fname.SetFullName(value);
            scheme_fname.SetExt(_("scheme"));
            default_scheme = scheme_fname.GetFullName();
        }


        properties = properties.substr(properties.find_first_of(_("\n"))+1);
    }

    return true;
}

bool rcbasic_edit_frame::loadEditorProperties(wxFileName fname)
{
    wxFile properties_file;
    enable_parser = false;
    conv_rel = false;

    if(!fname.Exists())
    {
        wxMessageBox(_("Cannot load properties from ")+fname.GetFullPath());
        return false;
    }

    if(!properties_file.Open(fname.GetFullPath()))
        return false;

    wxString properties;
    properties_file.ReadAll(&properties);
    properties_file.Close();

    properties.Append(_(" \n"));

    wxString property;
    wxString value;

    for(int i = 0; i < properties.length(); i++)
    {
        int vpos = properties.find_first_of(_("="));
        if(vpos == wxString::npos)
            break;
        property = properties.substr(0, vpos).Trim();
        property = property.substr(property.find_first_not_of(_(" ")));

        value = properties.substr(vpos+1);
        value = value.substr(0, value.find_first_of(_("\n")));

        if(property.compare(_("keywords"))==0)
        {
            rcbasic_edit_keywords = value;
        }
        else if(property.compare(_("keywords2"))==0)
        {
            rcbasic_edit_keywords2 = value;
        }
        else if(property.compare(_("CODE_COMP_LENGTH"))==0)
        {
            long cc_len = 0;
            value.ToLong(&cc_len);
            lenCompletionCheck = cc_len;
        }
        else if(property.compare(_("RCBASIC_PATH"))==0)
        {
            wxFileName rcbasic_path_fname(value);
            rcbasic_path_fname.MakeAbsolute();
            rcbasic_path = rcbasic_path_fname.GetFullPath();
            #ifndef _WIN32
            wxString path_var;
            wxGetEnv(_("PATH"), &path_var);
            wxSetEnv(_("PATH"), rcbasic_path + _(":") + path_var);
            #endif
        }
        else if(property.compare(_("RCBASIC_BUILD"))==0)
        {
            rcbasic_build_path = wxFileName(value);
            rcbasic_build_path.MakeAbsolute();
            wxSetEnv(_("RCBASIC_BUILD_PATH"), rcbasic_build_path.GetFullPath());
        }
        else if(property.compare(_("RCBASIC_RUN"))==0)
        {
            rcbasic_run_path = wxFileName(value);
            rcbasic_run_path.MakeAbsolute();
            wxSetEnv(_("RCBASIC_RUN_PATH"), rcbasic_run_path.GetFullPath());
        }
        else if(property.compare(_("RCBASIC_WIN_BIT"))==0)
        {
            //wxPuts(_("WIN_BIT = ") + value);
            value.ToLong(&win_os_bit);
        }
        else if(property.compare(_("DOC_URL"))==0)
        {
            RCBasic_Documentation_Link = value;
        }
        else if(property.compare(_("STUDIO_DOC_URL"))==0)
        {
            Studio_Documentation_Link = value;
        }
        else if(property.compare(_("ENABLE_PARSER"))==0)
        {
            enable_parser = value.compare(_("TRUE")) == 0 ? true : false;
        }
        else if(property.compare(_("ENABLE_CODE_COMPLETE"))==0)
        {
            enable_codeCompletion = value.compare(_("TRUE")) == 0 ? true : false;
        }
        else if(property.compare(_("ENABLE_PRESETS"))==0)
        {
            enable_presets = value.compare(_("TRUE")) == 0 ? true : false;
        }
        else if(property.compare(_("CONVERT_REL"))==0)
        {
            conv_rel = value.compare(_("TRUE")) == 0 ? true : false;
        }
        else if(property.compare(_("DEFAULT_SCHEME"))==0)
        {
            default_scheme = value;
        }
        else if(property.compare(_("RCBASIC_HOME"))==0)
        {
            wxFileName rcbasic_home_fname(value);
            rcbasic_home_fname.MakeAbsolute();
            wxSetEnv(_("RCBASIC_HOME_CONFIG"), rcbasic_home_fname.GetFullPath());
            wxSetEnv(_("RCBASIC_HOME"), rcbasic_home_fname.GetFullPath());
        }
        else if(property.compare(_("RCBASIC_TOOLS"))==0)
        {
            wxFileName rcbasic_tools_fname(value);
            rcbasic_tools_fname.MakeAbsolute();
            wxSetEnv(_("RCBASIC_TOOLS_CONFIG"), rcbasic_tools_fname.GetFullPath());
            wxSetEnv(_("RCBASIC_TOOLS"), rcbasic_tools_fname.GetFullPath());
        }
        else if(property.compare(_("RC_PKG_HOME"))==0)
        {
            wxFileName rcbasic_pkg_fname(value);
            rcbasic_pkg_fname.MakeAbsolute();
            wxSetEnv(_("RC_PKG_HOME_CONFIG"), rcbasic_pkg_fname.GetFullPath());
            wxSetEnv(_("RC_PKG_HOME"), rcbasic_pkg_fname.GetFullPath());
        }
        else if(property.compare(_("RCBASIC_ANDROID_DIR"))==0)
        {
            wxFileName rcbasic_android_fname(value);
            rcbasic_android_fname.MakeAbsolute();
            wxSetEnv(_("RCBASIC_ANDROID_DIR_CONFIG"), rcbasic_android_fname.GetFullPath());
            wxSetEnv(_("RCBASIC_ANDROID_DIR"), rcbasic_android_fname.GetFullPath());
        }
        else if(property.compare(_("RCBASIC_LIB_PATH"))==0)
        {
            wxFileName rcbasic_lib_fname(value);
            rcbasic_lib_fname.MakeAbsolute();
            wxString current_lib_path;
            wxGetEnv(_("LD_LIBRARY_PATH"), &current_lib_path);
            wxSetEnv(_("LD_LIBRARY_PATH_CONFIG"), rcbasic_lib_fname.GetFullPath());
            wxSetEnv(_("LD_LIBRARY_PATH"), current_lib_path + _(":") + rcbasic_lib_fname.GetFullPath());
        }
        else if(property.compare(_("ANDROID_HOME"))==0)
        {
            wxFileName rcbasic_droidHome_fname(value);
            rcbasic_droidHome_fname.MakeAbsolute();
            wxSetEnv(_("ANDROID_HOME_CONFIG"), rcbasic_droidHome_fname.GetFullPath());
            wxSetEnv(_("ANDROID_HOME"), rcbasic_droidHome_fname.GetFullPath());
            wxSetEnv(_("ANDROID_SDK_ROOT"), rcbasic_droidHome_fname.GetFullPath());
        }


        properties = properties.substr(properties.find_first_of(_("\n"))+1);

        //wxPuts(_("PROPERTY: ") + property);
        //wxPuts(_("VALUE: ") + value);
        //wxPuts(_(""));
    }

    wxString kw = _("");
    wxString curr_char = _("");

    wxString kw_list = rcbasic_edit_keywords + _(" ");

    id_list.Clear();

    for(int i = 0; i < kw_list.length(); i++)
    {
        curr_char = kw_list.substr(i, 1);
        if(curr_char.compare(_(" "))==0)
        {
            if(kw.Trim().compare(_(""))!=0)
                id_list.Add(kw);

            kw = _("");
        }
        else
        {
            kw.Append(curr_char);
        }
    }

    kw = _("");
    curr_char = _("");
    kw_list = rcbasic_edit_keywords2 + _(" ");

    for(int i = 0; i < kw_list.length(); i++)
    {
        curr_char = kw_list.substr(i, 1);
        if(curr_char.compare(_(" "))==0)
        {
            if(kw.Trim().compare(_(""))!=0)
                id_list.Add(kw.MakeUpper());

            kw = _("");
        }
        else
        {
            kw.Append(curr_char);
        }
    }

    id_list.Sort();
    kw_count = id_list.GetCount();

    return true;
}

bool rcbasic_edit_frame::saveEditorProperties(wxFileName fname)
{
    wxFile properties_file;

    if(fname.Exists())
    {
        if(!properties_file.Open(fname.GetFullPath(), wxFile::write))
            return false;
    }
    else if(!properties_file.Create(fname.GetFullPath()))
    {
        return false;
    }

    wxString editor_path = wxStandardPaths::Get().GetExecutablePath();
    wxFileName base_dir(editor_path);

    wxFileName rel_build_path = rcbasic_build_path;
    wxFileName rel_run_path = rcbasic_run_path;
    wxFileName rel_base_path = rcbasic_path;
    rel_build_path.MakeRelativeTo(base_dir.GetPath());
    rel_run_path.MakeRelativeTo(base_dir.GetPath());
    rel_base_path.MakeRelativeTo(base_dir.GetPath());

    properties_file.Write(_("CONVERT_REL=") + (conv_rel ? _("TRUE") : _("FALSE")) + _("\n"));
    properties_file.Write(_("DEFAULT_SCHEME=") + default_scheme + _("\n"));
    #ifdef _WIN32
    properties_file.Write(_("RCBASIC_WIN_BIT=") + wxString::Format(wxT("%i"),win_os_bit) + _("\n"));
    #endif // _WIN32
    properties_file.Write(_("RCBASIC_BUILD=") + rel_build_path.GetFullPath() + _("\n"));
    properties_file.Write(_("RCBASIC_RUN=") + rel_run_path.GetFullPath() + _("\n"));
    properties_file.Write(_("RCBASIC_PATH=") + rel_base_path.GetFullPath() + _("\n"));
    properties_file.Write(_("ENABLE_PARSER=") + (enable_parser ? _("TRUE") : _("FALSE")) + _("\n"));
    properties_file.Write(_("ENABLE_CODE_COMPLETE=") + (enable_parser ? _("TRUE") : _("FALSE")) + _("\n"));
    properties_file.Write(_("ENABLE_PRESETS=") + (enable_presets ? _("TRUE") : _("FALSE")) + _("\n"));
    properties_file.Write(_("RCBASIC_DOC_PATH=doc") + _("\n")); //This is just a place holder for compatability
    properties_file.Write(_("STUDIO_DOC_URL=") + Studio_Documentation_Link + _("\n"));
    properties_file.Write(_("DOC_URL=") + RCBasic_Documentation_Link + _("\n"));
    properties_file.Write(_("keywords=") + rcbasic_edit_keywords + _("\n"));
    properties_file.Write(_("keywords2=") + rcbasic_edit_keywords2 + _("\n"));

    wxString tmp_str;

    wxGetEnv(_("RCBASIC_HOME_CONFIG"), &tmp_str);
    if(tmp_str.Trim().compare(_(""))!=0)
    {
        properties_file.Write(_("RCBASIC_HOME=") + tmp_str + _("\n"));
        tmp_str = _("");
    }

    wxGetEnv(_("RCBASIC_TOOLS_CONFIG"), &tmp_str);
    if(tmp_str.Trim().compare(_(""))!=0)
    {
        properties_file.Write(_("RCBASIC_TOOLS=") + tmp_str + _("\n"));
        tmp_str = _("");
    }

    wxGetEnv(_("RC_PKG_HOME_CONFIG"), &tmp_str);
    if(tmp_str.Trim().compare(_(""))!=0)
    {
        properties_file.Write(_("RC_PKG_HOME=") + tmp_str + _("\n"));
        tmp_str = _("");
    }

    wxGetEnv(_("RCBASIC_ANDROID_DIR_CONFIG"), &tmp_str);
    if(tmp_str.Trim().compare(_(""))!=0)
    {
        properties_file.Write(_("RCBASIC_ANDROID_DIR=") + tmp_str + _("\n"));
        tmp_str = _("");
    }

    wxGetEnv(_("LD_LIBRARY_PATH_CONFIG"), &tmp_str);
    if(tmp_str.Trim().compare(_(""))!=0)
    {
        properties_file.Write(_("LD_LIBRARY_PATH=") + tmp_str + _("\n"));
        tmp_str = _("");
    }

    wxGetEnv(_("ANDROID_HOME_CONFIG"), &tmp_str);
    if(tmp_str.Trim().compare(_(""))!=0)
    {
        properties_file.Write(_("ANDROID_HOME=") + tmp_str + _("\n"));
        tmp_str = _("");
    }

    properties_file.Close();

    return true;
}

bool rcbasic_edit_frame::loadScheme(wxFileName fname)
{
    wxFile scheme_file;

    if(!fname.Exists())
    {
        wxMessageBox(_("Cannot open ")+fname.GetFullPath());
        return false;
    }

    editor_scheme.scheme_name = fname.GetName();

    if(scheme_file.Open(fname.GetFullPath()))
    {
        wxString scheme_data;
        scheme_file.ReadAll(&scheme_data);
        scheme_file.Close();


        //wxPuts(_("---DATA---\n")+scheme_data);
        scheme_data.Append(_(" \n"));

        wxString property;
        wxString values;
        long r = 0;
        long g = 0;
        long b = 0;

        wxString n_value;

        editor_scheme.caret_bkg_color_set = false;
        editor_scheme.caret_fg_color_set = false;
        editor_scheme.comment_fg_color_set = false;
        editor_scheme.current_line_bkg_color_set = false;
        editor_scheme.current_line_fg_color_set = false;
        editor_scheme.identifier_fg_color_set = false;
        editor_scheme.keyword2_fg_color_set = false;
        editor_scheme.keyword_fg_color_set = false;
        editor_scheme.number_fg_color_set = false;
        editor_scheme.operator_fg_color_set = false;
        editor_scheme.selection_bkg_color_set = false;
        editor_scheme.selection_fg_color_set = false;
        editor_scheme.string_fg_color_set = false;
        editor_scheme.style_bkg_color_set = false;
        editor_scheme.line_number_bkg_color_set = false;
        editor_scheme.line_number_fg_color_set = false;

        for(int i = 0; i < scheme_data.length(); i++)
        {
            int vpos = scheme_data.find_first_of(_("="));
            if(vpos == wxString::npos)
                break;
            property = scheme_data.substr(0, vpos).Trim();
            property = property.substr(property.find_first_not_of(_(" ")));

            values = scheme_data.substr(vpos+1);
            values = values.substr(0, values.find_first_of(_("\n")));

            n_value = values.substr(0, values.find_first_of(_(",")));
            n_value.ToLong(&r);
            values = values.substr(values.find_first_of(_(","))+1);

            n_value = values.substr(0, values.find_first_of(_(",")));
            n_value.ToLong(&g);
            values = values.substr(values.find_first_of(_(","))+1);

            n_value = values.substr(0, values.find_first_of(_("\n")));
            n_value.ToLong(&b);

            if(property.compare(_("style_bkg_color"))==0)
            {
                //uint8_t r8b = (uint8_t)r;
                //uint8_t g8b = (uint8_t)g;
                //uint8_t b8b = (uint8_t)b;
                //wxPrintf(_("Style Background: %d, %d, %d"), r8b, g8b, b8b);
                editor_scheme.style_bkg_color = wxColour(r, g, b);
                editor_scheme.style_bkg_color_set = true;
            }
            else if(property.compare(_("keyword_fg_color"))==0)
            {
                editor_scheme.keyword_fg_color = wxColour(r, g, b);
                editor_scheme.keyword_fg_color_set = true;
            }
            else if(property.compare(_("keyword2_fg_color"))==0)
            {
                editor_scheme.keyword2_fg_color = wxColour(r, g, b);
                editor_scheme.keyword2_fg_color_set = true;
            }
            else if(property.compare(_("number_fg_color"))==0)
            {
                editor_scheme.number_fg_color = wxColour(r, g, b);
                editor_scheme.number_fg_color_set = true;
            }
            else if(property.compare(_("string_fg_color"))==0)
            {
                editor_scheme.string_fg_color = wxColour(r, g, b);
                editor_scheme.string_fg_color_set = true;
            }
            else if(property.compare(_("comment_fg_color"))==0)
            {
                editor_scheme.comment_fg_color = wxColour(r, g, b);
                editor_scheme.comment_fg_color_set = true;
            }
            else if(property.compare(_("identifier_fg_color"))==0)
            {
                editor_scheme.identifier_fg_color = wxColour(r, g, b);
                editor_scheme.identifier_fg_color_set = true;
            }
            else if(property.compare(_("operator_fg_color"))==0)
            {
                editor_scheme.operator_fg_color = wxColour(r, g, b);
                editor_scheme.operator_fg_color_set = true;
            }
            else if(property.compare(_("caret_fg_color"))==0)
            {
                //wxPrintf(_("Caret: %d, %d, %d"), r, g, b);
                editor_scheme.caret_fg_color = wxColour(r, g, b);
                editor_scheme.caret_fg_color_set = true;
            }
            else if(property.compare(_("selection_fg_color"))==0)
            {
                editor_scheme.selection_fg_color = wxColour(r, g, b);
                editor_scheme.selection_fg_color_set = true;
            }
            else if(property.compare(_("selection_bkg_color"))==0)
            {
                editor_scheme.selection_bkg_color = wxColour(r, g, b);
                editor_scheme.selection_bkg_color_set = true;
            }
            else if(property.compare(_("current_line_bkg_color"))==0)
            {
                editor_scheme.current_line_bkg_color = wxColour(r, g, b);
                editor_scheme.current_line_bkg_color_set = true;
            }
            else if(property.compare(_("current_line_fg_color"))==0)
            {
                editor_scheme.current_line_fg_color = wxColour(r, g, b);
                editor_scheme.current_line_fg_color_set = true;
            }
            else if(property.compare(_("line_number_fg_color"))==0)
            {
                editor_scheme.line_number_fg_color = wxColour(r, g, b);
                editor_scheme.line_number_fg_color_set = true;
            }
            else if(property.compare(_("line_number_bkg_color"))==0)
            {
                editor_scheme.line_number_bkg_color = wxColour(r, g, b);
                editor_scheme.line_number_bkg_color_set = true;
            }


            scheme_data = scheme_data.substr(scheme_data.find_first_of(_("\n"))+1);

            //wxPuts(_("PROPERTY: ") + property);
            //wxPrintf(_("RGB: %d %d %d\n"), r, g, b);

        }

        return true;
    }

    return false;
}

void rcbasic_edit_frame::applyScheme(wxStyledTextCtrl* rc_txtCtrl)
{
    //wxPuts(_("Debug 1"));
    project_tree->SetBackgroundColour(editor_scheme.style_bkg_color);
    symbol_tree->SetBackgroundColour(editor_scheme.style_bkg_color);
    m_messageWindow_richText->SetBackgroundColour(editor_scheme.style_bkg_color);
    m_searchResults_listBox->SetBackgroundColour(editor_scheme.style_bkg_color);

    //wxPuts(_("Debug 2"));

    if(rc_txtCtrl)
    {
        rc_txtCtrl->StyleSetBackground(wxSTC_STYLE_DEFAULT, editor_scheme.style_bkg_color);
        rc_txtCtrl->StyleClearAll();

        updateFont(rc_txtCtrl);
    }

    //wxPuts(_("Debug 3"));

    //project_tree->SetItemDropHighlight(project_tree->GetRootItem(), false);

    //project_tree->SelectItem(project_tree->GetRootItem(), true);

    if(editor_scheme.keyword_fg_color_set)
    {
        if(rc_txtCtrl)
            rc_txtCtrl->StyleSetForeground(wxSTC_B_KEYWORD, editor_scheme.keyword_fg_color);
    }

    //wxPuts(_("Debug 4"));

    if(editor_scheme.keyword2_fg_color_set)
    {
        if(rc_txtCtrl)
            rc_txtCtrl->StyleSetForeground(wxSTC_B_KEYWORD2, editor_scheme.keyword2_fg_color);
    }

    //wxPuts(_("Debug 5"));

    if(editor_scheme.number_fg_color_set)
    {
        if(rc_txtCtrl)
            rc_txtCtrl->StyleSetForeground(wxSTC_B_NUMBER, editor_scheme.number_fg_color);
    }

    //wxPuts(_("Debug 6"));

    if(editor_scheme.string_fg_color_set)
    {
        if(rc_txtCtrl)
            rc_txtCtrl->StyleSetForeground(wxSTC_B_STRING, editor_scheme.string_fg_color);
    }

    //wxPuts(_("Debug 7"));

    if(editor_scheme.comment_fg_color_set)
    {
        if(rc_txtCtrl)
            rc_txtCtrl->StyleSetForeground(wxSTC_B_COMMENT, editor_scheme.comment_fg_color);
    }

    //wxPuts(_("Debug 8"));

    if(editor_scheme.identifier_fg_color_set)
    {
        if(rc_txtCtrl)
            rc_txtCtrl->StyleSetForeground(wxSTC_B_IDENTIFIER, editor_scheme.identifier_fg_color);
        project_tree->SetForegroundColour(editor_scheme.identifier_fg_color);
        symbol_tree->SetForegroundColour(editor_scheme.identifier_fg_color);
        m_messageWindow_richText->SetDefaultStyle(wxTextAttr( editor_scheme.identifier_fg_color, m_messageWindow_richText->GetBackgroundColour()) );
        wxString current_value = m_messageWindow_richText->GetValue();
        m_messageWindow_richText->Clear();
        m_messageWindow_richText->SetValue(current_value);
        m_messageWindow_richText->Refresh();
        m_searchResults_listBox->SetForegroundColour(editor_scheme.identifier_fg_color);
        m_searchResults_listBox->Refresh();
    }

    //wxPuts(_("Debug 9"));

    if(editor_scheme.operator_fg_color_set)
    {
        if(rc_txtCtrl)
            rc_txtCtrl->StyleSetForeground(wxSTC_B_OPERATOR, editor_scheme.operator_fg_color);
    }

    if(editor_scheme.caret_fg_color_set)
    {
        if(rc_txtCtrl)
            rc_txtCtrl->SetCaretForeground(editor_scheme.caret_fg_color);
    }

    if(editor_scheme.selection_fg_color_set)
    {
        if(rc_txtCtrl)
            rc_txtCtrl->SetSelForeground(true, editor_scheme.selection_fg_color);
    }

    if(editor_scheme.selection_bkg_color_set)
    {
        if(rc_txtCtrl)
            rc_txtCtrl->SetSelBackground(true, editor_scheme.selection_bkg_color);
    }

    if(rc_txtCtrl)
    {
        rc_txtCtrl->StyleSetForeground(wxSTC_B_ERROR, editor_scheme.string_fg_color);
        rc_txtCtrl->StyleSetBold(wxSTC_B_ERROR, true);

        rc_txtCtrl->StyleSetBold(wxSTC_B_KEYWORD2, true);
    }

    if(editor_scheme.line_number_bkg_color_set)
    {
        if(rc_txtCtrl)
            rc_txtCtrl->StyleSetBackground(wxSTC_STYLE_LINENUMBER, editor_scheme.line_number_bkg_color);
    }

    if(editor_scheme.line_number_fg_color_set)
    {
        if(rc_txtCtrl)
            rc_txtCtrl->StyleSetForeground(wxSTC_STYLE_LINENUMBER, editor_scheme.line_number_fg_color);
    }

    //updateFont(rc_txtCtrl);
#ifdef _WIN32

    project_tree->UnselectAll();
    symbol_tree->UnselectAll();


    wxColour item_bkg = project_tree->GetBackgroundColour();
    wxColour item_fg = project_tree->GetForegroundColour();

    if(project_tree->GetRootItem().IsOk())
    {
        project_tree->SetItemBackgroundColour(project_tree->GetRootItem(), item_bkg);
        project_tree->SetItemTextColour(project_tree->GetRootItem(), item_fg);

    }

    for(int i = 0; i < open_projects.size(); i++)
    {
        if(open_projects[i]->getRootNode().IsOk())
        {
            project_tree->SetItemBackgroundColour(open_projects[i]->getRootNode(), item_bkg);
            project_tree->SetItemTextColour(open_projects[i]->getRootNode(), item_fg);
        }
        std::vector<rcbasic_project_node*> sourceFiles = open_projects[i]->getSourceFiles();
        for(int pnode = 0; pnode < sourceFiles.size(); pnode++)
        {
            wxTreeItemId p_item = sourceFiles[pnode]->getNode();
            if(p_item.IsOk())
            {
                project_tree->SetItemBackgroundColour(p_item, item_bkg);
                project_tree->SetItemTextColour(p_item, item_fg);
            }
        }
    }


    if(selected_project_item.IsOk())
    {
        //project_tree->SelectItem(selected_project_item);
        project_tree->SetItemBackgroundColour(selected_project_item, wxColour(0, 120, 215));
        project_tree->SetItemTextColour(selected_project_item, wxColour(240, 240, 240));
    }


    //////////////

    if(symbol_tree->GetRootItem().IsOk())
    {
        symbol_tree->SetItemBackgroundColour(symbol_tree->GetRootItem(), item_bkg);
        symbol_tree->SetItemTextColour(symbol_tree->GetRootItem(), item_fg);
    }

    if(variable_root_node.IsOk())
    {
        symbol_tree->SetItemBackgroundColour(variable_root_node, item_bkg);
        symbol_tree->SetItemTextColour(variable_root_node, item_fg);
    }

    if(function_root_node.IsOk())
    {
        symbol_tree->SetItemBackgroundColour(function_root_node, item_bkg);
        symbol_tree->SetItemTextColour(function_root_node, item_fg);
    }

    for(int i = 0; i < var_nodes.size(); i++)
    {
        if(var_nodes[i].IsOk())
        {
            symbol_tree->SetItemBackgroundColour(var_nodes[i], item_bkg);
            symbol_tree->SetItemTextColour(var_nodes[i], item_fg);
        }
    }

    for(int i = 0; i < fn_nodes.size(); i++)
    {
        if(fn_nodes[i].IsOk())
        {
            symbol_tree->SetItemBackgroundColour(fn_nodes[i], item_bkg);
            symbol_tree->SetItemTextColour(fn_nodes[i], item_fg);
        }
    }


    if(selected_symbol_item.IsOk())
    {
        //symbol_tree->SelectItem(selected_symbol_item);
        symbol_tree->SetItemBackgroundColour(selected_symbol_item, wxColour(0, 120, 215));
        symbol_tree->SetItemTextColour(selected_symbol_item, wxColour(240, 240, 240));
    }
#endif
}

void rcbasic_edit_frame::onRecentProjectSelect( wxCommandEvent& event )
{
    int id = event.GetId();

    int item = id - RECENT_PROJECT_OFFSET_ID;

    if(item >= 0 && item < 10)
    {
        notebook_mutex.Lock();
        wxFileName project_fname(recent_projects_items[item]);
        if(project_fname.Exists())
            openProject(project_fname);
        else
            wxMessageBox(_("Could not locate project:\n") + project_fname.GetFullPath());
        notebook_mutex.Unlock();
    }
}

void rcbasic_edit_frame::onRecentFileSelect( wxCommandEvent& event )
{
    int id = event.GetId();

    int item = id - RECENT_FILE_OFFSET_ID;

    if(item >= 0 && item < 10)
    {
        notebook_mutex.Lock();
        wxFileName fname(recent_files_items[item]);
        if(fname.Exists())
            openSourceFile(fname);
        else
            wxMessageBox(_("Could not locate file:\n") + fname.GetFullPath());
        notebook_mutex.Unlock();
    }
}

void rcbasic_edit_frame::onEditorClose( wxCloseEvent& event )
{
    notebook_mutex.Unlock();

    for(int i = 0; i < open_files.size(); i++)
    {
        rcbasic_edit_txtCtrl* o_file = open_files[i];
        if(o_file->getTextChangedFlag())
        {
            wxString title = _("Closing ") + o_file->getSourcePath().GetFullName();
            rcbasic_edit_closeFileSavePrompt_dialog saveFile_dialog(this, title);
            saveFile_dialog.ShowModal();

            if(saveFile_dialog.getFileCloseFlag()==fileCloseFlag_SAVE)
            {
                saveFile(i, 0);
            }
            else if(saveFile_dialog.getFileCloseFlag()==fileCloseFlag_CANCEL)
            {
                return;
            }
        }
    }

    if(enable_parser && token_parser)
    {
        if(token_parser->IsAlive())
        {
            sym_sem = new wxSemaphore();
            token_parser->Delete();
            sym_sem->Wait();
            delete sym_sem;
            //wxPuts(_("thread successfully ended"));
        }
    }



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

        wxString p_name_tmp = project_name;
        p_name_tmp.Replace(_(" "), _(""));
        if(p_name_tmp.size() <= 0)
            return;

        wxString project_location = newProject_win->projectLocation_picker->GetPath();
        int main_source_flag = newProject_win->projectCreateMain_radio->GetValue() ? 0 : 1;
        #ifdef _WIN32
        wxString main_source_value = main_source_flag==0 ? newProject_win->projectNewMain_field->GetValue() : newProject_win->projectExistingFile_picker->GetTextCtrlValue();
        #else
        wxString main_source_value = main_source_flag==0 ? newProject_win->projectNewMain_field->GetValue() : newProject_win->projectExistingFile_picker->GetFileName().GetFullPath();
        #endif
        wxString project_author = newProject_win->projectAuthor_field->GetValue();
        wxString project_website = newProject_win->projectWebsite_field->GetValue();
        wxString project_description = newProject_win->projectDescription_field->GetValue();

        rcbasic_project* new_project = new rcbasic_project(project_name, project_location, main_source_flag, main_source_value, project_author, project_website, project_description);
        if(!new_project)
        {
            wxMessageBox(_("Error: Could not create New Project"));
            return;
        }
        else if(!new_project->projectExists())
        {
            wxMessageBox(_("Error: Could not create New Project"));
            delete new_project;
            new_project = NULL;
            return;
        }

        //wxPuts(_("DEBUG 3"));

        new_project->setRootNode(project_tree->AppendItem(project_tree->GetRootItem(), project_name, project_tree_folderImage));
        new_project->addSourceFile(new_project->getMainSource().GetFullPath(), STORE_LOCATION_RELATIVE, false);

        //wxPuts(_("DEBUG 4"));

        new_project->setLastProjectSave();

        //wxPuts(_("DEBUG 5"));

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
        notebook_mutex.Lock();
        wxString cwd = wxGetCwd();
        wxSetWorkingDirectory(new_project->getLocation());
        wxFileName main_fname = new_project->getMainSource();
        main_fname.MakeAbsolute();
        rcbasic_edit_txtCtrl* txtCtrl_obj = openFileTab(new_project, new_project->getMainSource());
        wxSetWorkingDirectory(cwd);
        txtCtrl_obj->setTextChangedFlag(false);
        notebook_mutex.Unlock();
    }

    //wxPuts(_("Project_Location: ") + project_location);
    //wxPuts(_("Main Source: ") + main_source_value);

    newProject_win->Destroy();
}

void rcbasic_edit_frame::newFileMenuSelect( wxCommandEvent& event)
{
    //wxPuts(_("New file Dialog"));
    notebook_mutex.Lock();
    createNewFile(active_project);
    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::openProjectMenuSelect( wxCommandEvent& event )
{
    notebook_mutex.Lock();
    wxFileName project_fname = openFileDialog(_("Open Project"), _("RCBasic Project (*.rcprj)|*.rcprj"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    //wxPuts(_("project_fname: ") + project_fname.GetLongPath());
    if(project_fname.GetFullPath().compare(_(""))!=0)
        openProject(project_fname);
    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::openFileMenuSelect( wxCommandEvent& event )
{
    notebook_mutex.Lock();
    wxFileName fname = openFileDialog( _("Open RCBasic Source file"), _("RCBasic Source files (*.bas)|*.bas"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    openSourceFile(fname);
    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::openProject(wxFileName project_path)
{
    //wxPuts(_("Openning Project [[[ ") + project_path.GetPath());
    wxSetWorkingDirectory(project_path.GetPath());

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
        wxString cwd = wxGetCwd();
        wxSetWorkingDirectory(project_path.GetPath());

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
        std::vector<int> project_source_store_type;
        std::vector<bool> project_source_target_flag;

        std::vector<rcbasic_edit_env_var> project_vars;

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
                    if(conv_rel)
                    {
                        #ifdef _WIN32
                        property_value.Replace(_("/"), _("\\"));
                        #else
                        property_value.Replace(_("\\"), _("/"));
                        #endif // _WIN32
                    }
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
                else if(property_name.compare(_("SOURCE_ABS"))==0)
                {
                    bool isTarget = property_value.find(_("${RCBASIC_STUDIO_TARGET}")) != wxString::npos ? true : false;
                    //wxPrintf(_("File (") + property_value + _("): %d\n"), isTarget);

                    property_value.Replace(_("${RCBASIC_STUDIO_TARGET}"), _(""));

                    project_source.push_back(property_value);
                    project_source_store_type.push_back(STORE_LOCATION_ABSOLUTE);
                    project_source_target_flag.push_back(isTarget);
                }
                else if(property_name.compare(_("SOURCE_REL"))==0)
                {
                    bool isTarget = property_value.find(_("${RCBASIC_STUDIO_TARGET}")) != wxString::npos ? true : false;
                    //wxPrintf(_("File (") + property_value + _("): %d\n"), isTarget);

                    property_value.Replace(_("${RCBASIC_STUDIO_TARGET}"), _(""));

                    if(conv_rel)
                    {
                        #ifdef _WIN32
                        property_value.Replace(_("/"), _("\\"));
                        #else
                        property_value.Replace(_("\\"), _("/"));
                        #endif // _WIN32
                    }
                    wxFileName fname(property_value);
                    fname.SetCwd(project_path.GetPath());
                    fname.MakeAbsolute();
                    property_value = fname.GetFullPath();

                    project_source.push_back(property_value);
                    project_source_store_type.push_back(STORE_LOCATION_RELATIVE);
                    project_source_target_flag.push_back(isTarget);
                }
                else if(property_name.compare(_("ENV"))==0)
                {
                    rcbasic_edit_env_var p_var;
                    p_var.var_name = property_value.substr(0, property_value.find_first_of(_("=")));
                    p_var.var_value = property_value.substr(property_value.find_first_of(_("="))+1);
                    project_vars.push_back(p_var);
                    //wxPuts(_("VAR:")+p_var.var_name);
                    //wxPuts(_("VAL:")+p_var.var_value);
                    //wxPuts(_(""));
                }
                project_property = _("");
            }
            else
            {
                project_property += contents.substr(i, 1);
            }
        }


        wxFileName project_location = project_path;
        project_location.SetFullName(_(""));

        wxFileName p_main_fname;
        p_main_fname.SetPath(project_location.GetLongPath());
        p_main_fname.SetFullName(project_main);
        p_main_fname.MakeAbsolute();
        project_main = p_main_fname.GetFullPath();

        //wxSetWorkingDirectory(cwd);

        rcbasic_project* project = new rcbasic_project(project_name, project_location.GetLongPath(), RCBASIC_PROJECT_SOURCE_OPEN, project_main, project_author, project_website, project_description);
        for(int i = 0; i < project_source.size(); i++)
        {
            //wxPuts(_("Adding Source: ") + project_source[i]);
            project->addSourceFile(project_source[i], project_source_store_type[i], project_source_target_flag[i]);
        }

        //add to project parser list
        pfile_runParser(project);

        project->setVars(project_vars);
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

        rcbasic_edit_txtCtrl* txtCtrl_obj = NULL;
        //wxPuts(_("DEBUG P_INFO\nLocation: ") + project->getLocation() + _("\nMain: ") + project->getMainSource().GetFullPath() + _("\n"));
        txtCtrl_obj = openFileTab(project, project->getMainSource());
        if(txtCtrl_obj)
        {
            //wxMessageBox(_("DEBUG"));
            txtCtrl_obj->setTextChangedFlag(false);
        }

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
        if(!txtCtrl_obj)
        {
            return;
        }
        txtCtrl_obj->getTextCtrl()->ClearAll();
        txtCtrl_obj->getTextCtrl()->SetText(contents);
        txtCtrl_obj->getTextCtrl()->EmptyUndoBuffer();
        txtCtrl_obj->setTextChangedFlag(false);
    }
}

int rcbasic_edit_frame::getOpenFileFromSelection()
{
    int selected_page = sourceFile_auinotebook->GetSelection();

    if(selected_page < 0)
        return -1;

    for(int i = 0; i < open_files.size(); i++)
    {
        if(!open_files[i])
            continue;

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

    if(!open_files[openFile_index])
        return;

    //int selected_page = sourceFile_auinotebook->GetSelection();
    int selected_page = -1;

    if(open_files[openFile_index]->getTextCtrl())
        selected_page = sourceFile_auinotebook->GetPageIndex(open_files[openFile_index]->getTextCtrl());

    if(selected_page < 0)
        return;

    open_files[openFile_index]->getTextCtrl()->ConvertEOLs(wxSTC_EOL_LF);

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
            if(!open_projects[p_index])
                continue;

            std::vector<rcbasic_project_node*> source_files = open_projects[p_index]->getSourceFiles();
            for(int f_index = 0; f_index < source_files.size(); f_index++)
            {
                if(!source_files[f_index])
                    continue;

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
    else
    {
        sourceFile_auinotebook->SetPageText(selected_page, fname.GetFullName());
    }

    open_files[openFile_index]->setTextChangedFlag(false);

    last_fileSave_flag = true;
}

void rcbasic_edit_frame::onSaveFileMenuSelect( wxCommandEvent& event )
{
    notebook_mutex.Lock();
    saveFile(getOpenFileFromSelection());
    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::onSaveFileAsMenuSelect( wxCommandEvent& event )
{
    notebook_mutex.Lock();
    saveFile(getOpenFileFromSelection(), FILE_SAVEAS_FLAG);
    notebook_mutex.Unlock();
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

    notebook_mutex.Lock();
    //SAVE FILES IN PROJECT
    std::vector<rcbasic_project_node*> pf_nodes = active_project->getSourceFiles();
    for(int i = 0; i < open_files.size(); i++)
    {
        if(!open_files[i])
            continue;
        wxFileName o_fname = open_files[i]->getSourcePath();
        o_fname.MakeAbsolute();
        for(int p_file = 0; p_file < pf_nodes.size(); p_file++)
        {
            if(!pf_nodes[p_file])
                continue;
            wxFileName p_fname = pf_nodes[p_file]->getPath();
            p_fname.MakeAbsolute();
            if(o_fname.GetFullPath().compare(p_fname.GetFullPath())==0)
            {
                //wxPuts(_("SAVING: ") + o_fname.GetFullPath());
                saveFile(i, 0);
            }
        }
    }

    active_project->saveProject(project_fname);
    pfile_runParser(active_project);

    notebook_mutex.Unlock();
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

    notebook_mutex.Lock();
    for(int i = 0; i < open_files.size(); i++)
    {
        if(!open_files[i])
            continue;

        for(int pf = 0; pf < active_project->getSourceFiles().size(); pf++)
        {
            if(!active_project->getSourceFiles()[pf])
                continue;

            if(open_files[i]->getSourcePath().GetFullPath().compare(active_project->getSourceFiles()[pf]->getPath().GetFullPath()) == 0)
            {
                saveFile(i);
            }
        }
    }

    active_project->saveProject(project_fname);
    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::onSaveAllMenuSelect( wxCommandEvent& event )
{
    notebook_mutex.Lock();
    for(int i = 0; i < open_files.size(); i++)
    {
        if(!open_files[i])
            continue;

        if(open_files[i]->getTextChangedFlag())
        {
            saveFile(i);
        }
    }

    for(int i = 0; i < open_projects.size(); i++)
    {
        if(!open_projects[i])
            continue;

        open_projects[i]->saveProject(wxFileName(open_projects[i]->getProjectFileLocation()));
    }
    notebook_mutex.Unlock();
}

int rcbasic_edit_frame::closeFile(int notebook_page)
{
    if(notebook_page < 0)
        return -1;

    int rtn_val = -1;

    for(int i = 0; i < open_files.size(); i++)
    {
        if(!open_files[i])
            continue;

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
    notebook_mutex.Lock();
    int current_file = sourceFile_auinotebook->GetSelection();

    if(current_file < 0)
    {
        notebook_mutex.Unlock();
        return;
    }

    closeFile(current_file);
    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::onCloseProjectMenuSelect( wxCommandEvent& event )
{
    if(!active_project)
        return;

    notebook_mutex.Lock();
    closeProject(active_project);
    notebook_mutex.Unlock();
}

int rcbasic_edit_frame::getProjectFromRoot(wxTreeItemId node)
{
    for(int i = 0; i < open_projects.size(); i++)
    {
        if(!open_projects[i])
            continue;

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
        if(!source_files[i])
            continue;

        node_label = wxFileName(source_files[i]->getPath().GetFullPath());
        data = new rcbasic_treeItem_data(node_label, open_projects[project_index]);
        if(source_files[i]->getLocationStoreType()==STORE_LOCATION_RELATIVE)
            node_label.MakeRelativeTo(open_projects[project_index]->getLocation());
        else
            node_label.MakeAbsolute();
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

    context_project->addSourceFile(sourceFile.GetFullPath(), STORE_LOCATION_RELATIVE, false);
    updateProjectTree(getProjectFromRoot(context_project->getRootNode()));
}

void rcbasic_edit_frame::saveProject(rcbasic_project* project)
{
    if(!project)
        return;

    std::vector<rcbasic_project_node*> pf_nodes = project->getSourceFiles();
    for(int i = 0; i < open_files.size(); i++)
    {
        if(!open_files[i])
            continue;
        wxFileName o_fname = open_files[i]->getSourcePath();
        o_fname.MakeAbsolute();
        for(int p_file = 0; p_file < pf_nodes.size(); p_file++)
        {
            if(!pf_nodes[p_file])
                continue;
            wxFileName p_fname = pf_nodes[p_file]->getPath();
            p_fname.MakeAbsolute();
            if(o_fname.GetFullPath().compare(p_fname.GetFullPath())==0)
            {
                //wxPuts(_("SAVING: ") + o_fname.GetFullPath());
                saveFile(i, 0);
            }
        }
    }

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

    int rtn_val = projectCloseFlag_SAVE;

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

    if(rtn_val == projectCloseFlag_SAVE)
    {
        project->saveProject(project_file);
    }

    project_tree->Delete(project->getRootNode());

    open_projects.erase(open_projects.begin()+getProjectFromRoot(project->getRootNode()));
    if(project)
    {
        delete project;
        project = NULL;
    }

    return rtn_val;
}

void rcbasic_edit_frame::onCloseAllMenuSelect( wxCommandEvent& event )
{
    int i = 0;
    notebook_mutex.Lock();
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
    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::onExitMenuSelect( wxCommandEvent& event )
{
    Close();
}

void rcbasic_edit_frame::onSaveProject(wxCommandEvent& event)
{
    notebook_mutex.Lock();
    saveProject(active_project);
    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::onSaveProjectAs(wxCommandEvent& event)
{
    if(active_project)
    {
        notebook_mutex.Lock();
        active_project->saveProject(openFileDialog(_("Save Project As"), _("RCBasic Project (*.rcprj)|*.rcprj"),wxFD_SAVE));
        notebook_mutex.Unlock();
    }
}

void rcbasic_edit_frame::onUndoMenuSelect( wxCommandEvent& event )
{
    notebook_mutex.Lock();
    int selected_page = sourceFile_auinotebook->GetSelection();

    if(selected_page < 0)
    {
        notebook_mutex.Unlock();
        return;
    }

    wxStyledTextCtrl* t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(selected_page);
    t->Undo();
    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::onRedoMenuSelect( wxCommandEvent& event )
{
    notebook_mutex.Lock();
    int selected_page = sourceFile_auinotebook->GetSelection();

    if(selected_page < 0)
    {
        notebook_mutex.Unlock();
        return;
    }

    wxStyledTextCtrl* t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(selected_page);
    t->Redo();
    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::onCutMenuSelect( wxCommandEvent& event )
{
    notebook_mutex.Lock();
    int selected_page = sourceFile_auinotebook->GetSelection();

    if(selected_page < 0)
    {
        notebook_mutex.Unlock();
        return;
    }

    wxStyledTextCtrl* t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(selected_page);
    t->Cut();

    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::onCopyMenuSelect( wxCommandEvent& event )
{
    notebook_mutex.Lock();
    int selected_page = sourceFile_auinotebook->GetSelection();

    if(selected_page < 0)
    {
        notebook_mutex.Unlock();
        return;
    }

    wxStyledTextCtrl* t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(selected_page);
    t->Copy();
    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::onPasteMenuSelect( wxCommandEvent& event )
{
    notebook_mutex.Lock();

    int selected_page = sourceFile_auinotebook->GetSelection();

    if(selected_page < 0)
    {
        notebook_mutex.Unlock();
        return;
    }

    wxStyledTextCtrl* t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(selected_page);
    t->Paste();
    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::onDeleteMenuSelect( wxCommandEvent& event )
{
    notebook_mutex.Lock();
    int selected_page = sourceFile_auinotebook->GetSelection();

    if(selected_page < 0)
    {
        notebook_mutex.Unlock();
        return;
    }

    wxStyledTextCtrl* t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(selected_page);
    //wxPrintf(_("Line: %d to %d"), t->LineFromPosition(t->GetSelectionStart()), t->LineFromPosition(t->GetSelectionEnd()));
    t->Clear();

    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::onSelectAllMenuSelect( wxCommandEvent& event )
{
    notebook_mutex.Lock();
    int selected_page = sourceFile_auinotebook->GetSelection();

    if(selected_page < 0)
    {
        notebook_mutex.Unlock();
        return;
    }

    wxStyledTextCtrl* t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(selected_page);
    //wxPrintf(_("Line: %d to %d"), t->LineFromPosition(t->GetSelectionStart()), t->LineFromPosition(t->GetSelectionEnd()));
    t->SelectAll();

    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::onCommentMenuSelect( wxCommandEvent& event )
{
    notebook_mutex.Lock();

    int selected_page = sourceFile_auinotebook->GetSelection();

    if(selected_page < 0)
    {
        notebook_mutex.Unlock();
        return;
    }

    wxStyledTextCtrl* t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(selected_page);

    if(!t)
    {
        notebook_mutex.Unlock();
        return;
    }

    t->BeginUndoAction();

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

    t->EndUndoAction();

    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::onBlockCommentMenuSelect( wxCommandEvent& event )
{
    notebook_mutex.Lock();

    int selected_page = sourceFile_auinotebook->GetSelection();

    if(selected_page < 0)
    {
        notebook_mutex.Unlock();
        return;
    }

    wxStyledTextCtrl* t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(selected_page);

    if(!t)
    {
        notebook_mutex.Unlock();
        return;
    }

    t->BeginUndoAction();

    //wxPrintf(_("Line: %d to %d"), t->LineFromPosition(t->GetSelectionStart()), t->LineFromPosition(t->GetSelectionEnd()));
    int start_line = t->LineFromPosition(t->GetSelectionStart());
    int end_line = t->LineFromPosition(t->GetSelectionEnd());

    wxString new_line;

    for(int line_num = start_line; line_num < end_line; line_num++)
    {
        new_line = t->GetLine(line_num);
        new_line.Replace(_("\n"), _(""));
        t->Replace(t->PositionFromLine(line_num), t->GetLineEndPosition(line_num), _("/\'") + new_line);
    }

    t->EndUndoAction();

    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::onUnCommentMenuSelect( wxCommandEvent& event )
{
    notebook_mutex.Lock();

    int selected_page = sourceFile_auinotebook->GetSelection();

    if(selected_page < 0)
    {
        notebook_mutex.Unlock();
        return;
    }

    wxStyledTextCtrl* t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(selected_page);

    if(!t)
    {
        notebook_mutex.Unlock();
        return;
    }

    t->BeginUndoAction();

    //wxPrintf(_("Line: %d to %d"), t->LineFromPosition(t->GetSelectionStart()), t->LineFromPosition(t->GetSelectionEnd()));
    int start_line = t->LineFromPosition(t->GetSelectionStart());
    int end_line = t->LineFromPosition(t->GetSelectionEnd());

    wxString new_line;

    for(int line_num = start_line; line_num <= end_line; line_num++)
    {
        new_line = t->GetLine(line_num);
        new_line.Replace(_("\n"), _(""));

        if(new_line.substr(0,1).compare(_("\'"))==0)
            new_line = new_line.substr(1);

        t->Replace(t->PositionFromLine(line_num), t->GetLineEndPosition(line_num), new_line);
    }

    t->EndUndoAction();

    notebook_mutex.Unlock();
}

wxString rcbasic_edit_frame::getRCBasicBasePath()
{
    return rcbasic_path;
}

wxFileName rcbasic_edit_frame::getRCBasicBuildPath()
{
    return rcbasic_build_path;
}

wxFileName rcbasic_edit_frame::getRCBasicRunPath()
{
    return rcbasic_run_path;
}

bool rcbasic_edit_frame::getParserFlag()
{
    return enable_parser;
}

bool rcbasic_edit_frame::getAutoCompleteFlag()
{
    return enable_codeCompletion;
}

bool rcbasic_edit_frame::getPresetFlag()
{
    return enable_presets;
}

wxString rcbasic_edit_frame::getRCBasicDocLink()
{
    return RCBasic_Documentation_Link;
}

wxString rcbasic_edit_frame::getStudioDocLink()
{
    return Studio_Documentation_Link;
}

void rcbasic_edit_frame::onPreferenceMenuSelect( wxCommandEvent& event )
{
    notebook_mutex.Lock();

    rcbasic_edit_preference_dialog* pref_dialog = new rcbasic_edit_preference_dialog(this);
    pref_dialog->ShowModal();

    if(pref_dialog->getPreferenceDialogValue() == preference_value_OK)
    {
        rcbasic_path = pref_dialog->getRCBasicBasePath();
        rcbasic_build_path = pref_dialog->getRCBasicBuildPath();
        rcbasic_run_path = pref_dialog->getRCBasicRunPath();
        RCBasic_Documentation_Link = pref_dialog->getRCBasicDocLink();
        Studio_Documentation_Link = pref_dialog->getStudioDocLink();
        enable_parser = pref_dialog->getParserFlag();
        enable_codeCompletion = pref_dialog->getAutoCompleteFlag();
        enable_presets = pref_dialog->getPresetFlag();

        wxString editor_path = wxStandardPaths::Get().GetExecutablePath();
        wxFileName edit_config(editor_path);
        edit_config.AppendDir(_("config"));
        edit_config.SetFullName(_("rcbasic_edit.config"));
        saveEditorProperties(edit_config);
    }

    notebook_mutex.Unlock();
}

int rcbasic_edit_frame::getOpenFileFromPath(wxFileName f_path)
{
    wxFileName f_path_abs = f_path;
    f_path_abs.MakeAbsolute();

    wxFileName o_fname_abs;

    for(int i = 0; i < open_files.size(); i++)
    {
        o_fname_abs = open_files[i]->getSourcePath();
        o_fname_abs.MakeAbsolute();

        if(o_fname_abs.GetFullPath().compare(f_path_abs.GetFullPath())==0)
            return i;
    }
    return -1;
}

void rcbasic_edit_frame::onSearchResultSelection(wxCommandEvent& event)
{
    int selection = event.GetSelection();
    //wxPrintf(_("Search Selection: %d\n"), selection);

    if(search_results.size() <= selection)
        return;

    notebook_mutex.Lock();
    int open_files_index = getOpenFileFromPath(search_results[selection].result_file);

    if(open_files_index < 0)
    {
        openSourceFile(search_results[selection].result_file);
        open_files_index = getOpenFileFromPath(search_results[selection].result_file);
        if(open_files_index < 0)
        {
            notebook_mutex.Unlock();
            return;
        }
    }

    if(open_files_index >= open_files.size())
    {
        notebook_mutex.Unlock();
        return;
    }

    if(!open_files[open_files_index]->getTextCtrl())
    {
        notebook_mutex.Unlock();
        return;
    }

    wxStyledTextCtrl* t = open_files[open_files_index]->getTextCtrl();

    int page_index = sourceFile_auinotebook->GetPageIndex(t);

    if(page_index < 0)
    {
        notebook_mutex.Unlock();
        return;
    }

    sourceFile_auinotebook->SetSelection(page_index);
    //t->SetCurrentPos( t->PositionFromLine(search_results[selection].line));
    //t->GotoLine(search_results[selection].line);
    t->GotoPos( search_results[selection].pos );
    t->SetSelection(t->GetCurrentPos(), t->GetCurrentPos() + search_term.length());

    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::setSearchResultsInFile(int findDialog_flag, wxString txt)
{
    clearSearchResults();

    if(sourceFile_auinotebook->GetPageCount() <= 0)
        return;

    search_term = txt;

    int current_page_index = sourceFile_auinotebook->GetSelection();
    wxStyledTextCtrl* t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(current_page_index);

    int flag = findDialog_flag;

    wxString selText= txt;
    int selLen = selText.Len();
    int selStart= 0;

    int totalLen = t->GetTextLength();
    int searchStart=0;
    int foundLoc = 0;

    t->SetSearchFlags(flag);

    rcbasic_search_result r;

    wxFileName fname;

    for(int i = 0; i < open_files.size(); i++)
    {
        if(open_files[i]->getTextCtrl()==t)
        {
            fname = open_files[i]->getSourcePath();
            r.result_file = fname;
            break;
        }
    }

    while(foundLoc!=-1)
    {
        t->SetTargetStart(searchStart);
        t->SetTargetEnd(totalLen);

        foundLoc= t->SearchInTarget(selText);
        searchStart= foundLoc+selLen;

        if(foundLoc!=-1)
        {
            r.pos = foundLoc;
            r.line = t->LineFromPosition(foundLoc);
            wxString line_str;
            line_str.Printf(_(":%d:    "), r.line+1);
            m_searchResults_listBox->AppendAndEnsureVisible( fname.GetFullName() + line_str + t->GetLineText(r.line) );
            search_results.push_back(r);
        }
    }

    if(m_searchResults_listBox->GetCount() > 0)
        m_searchResults_listBox->SetSelection(0);

    m_results_notebook->SetSelection(RESULTS_LISTBOX_SEARCHMSG);
}

void rcbasic_edit_frame::setSearchResultsInProject(int findDialog_flag, wxString txt)
{
    clearSearchResults();

    if(!active_project)
        return;

    //wxPuts(_("Search for \"") + txt + _("\" In ") + active_project->getName() );
    search_term = txt;

    rcbasic_project_node* p_node;
    wxStyledTextCtrl* t;

    int flag = findDialog_flag;

    wxString selText= txt;
    int selLen = selText.Len();

    notebook_mutex.Lock();
    for(int p_file=0; p_file < active_project->getSourceFiles().size(); p_file++)
    {
        p_node = active_project->getSourceFiles()[p_file];
        if(!p_node->getTextCtrl())
        {
            t = new wxStyledTextCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, _("temp"));
            //t->ClearAll();
            wxFile f;
            if(!f.Open(p_node->getPath().GetFullPath()))
            {
                if(t)
                    delete t;
                t = NULL;
                continue;
            }
            else
            {
                wxString f_txt;
                f.ReadAll(&f_txt);
                f.Close();
                t->SetText(f_txt);
            }
        }
        else
        {
            t = p_node->getTextCtrl();
        }

        int selStart= 0;

        int totalLen = t->GetTextLength();
        int searchStart=0;
        int foundLoc = 0;

        t->SetSearchFlags(flag);

        rcbasic_search_result r;

        //
        wxFileName fname = p_node->getPath();
        r.result_file = fname;


        while(foundLoc!=-1)
        {
            t->SetTargetStart(searchStart);
            t->SetTargetEnd(totalLen);

            foundLoc= t->SearchInTarget(selText);
            searchStart= foundLoc+selLen;

            if(foundLoc!=-1)
            {
                r.pos = foundLoc;
                r.line = t->LineFromPosition(foundLoc);
                wxString line_str;
                line_str.Printf(_(":%d:    "), r.line+1);
                m_searchResults_listBox->AppendAndEnsureVisible( fname.GetFullName() + line_str + t->GetLineText(r.line) );
                search_results.push_back(r);
            }
        }

        if(t != p_node->getTextCtrl())
        {
            if(t)
                delete t;
            t= NULL;
        }

    }


    if(m_searchResults_listBox->GetCount() > 0)
        m_searchResults_listBox->SetSelection(0);

    m_results_notebook->SetSelection(RESULTS_LISTBOX_SEARCHMSG);

}

void rcbasic_edit_frame::clearSearchResults()
{
    m_searchResults_listBox->DeselectAll();
    m_searchResults_listBox->Clear();
    search_results.clear();
}

void rcbasic_edit_frame::onFindMenuSelect( wxCommandEvent& event )
{
    if(sourceFile_auinotebook->GetPageCount() <= 0)
        return;

    rcbasic_edit_find_dialog find_dialog(this);
    find_dialog.ShowModal();

    switch(find_dialog.getValue())
    {
        case find_dialog_value_INFILE:
            notebook_mutex.Lock();
            setSearchResultsInFile(find_dialog.getFlags(), find_dialog.getSearchText());
            notebook_mutex.Unlock();
            break;
        case find_dialog_value_INPROJECT:
            notebook_mutex.Lock();
            setSearchResultsInProject(find_dialog.getFlags(), find_dialog.getSearchText());
            notebook_mutex.Unlock();
            break;
    }

    search_term = find_dialog.getSearchText();
}

int rcbasic_edit_frame::searchNextPrev(wxStyledTextCtrl* t, int search_type)
{
    if(!t)
        return -1;

    //int previous_pos = t->FindText(t->GetCurrentPos()+1, t->GetLastPosition(), m_search_textCtrl->GetLineText(0));
    int flag = search_flags;
    if(t->GetSelectedText().Length() > 0)
        search_term = t->GetSelectedText().substr(0, 100);
    //wxPrintf(_("CPOS = %d\n"), t->GetCurrentPos());
    t->GotoPos( t->GetCurrentPos() + (search_type==search_type_NEXT ? 1 : -1) );
    //wxPrintf(_("NEW CPOS = %d\n"), t->GetCurrentPos());
    t->SearchAnchor();
    int find_pos = search_type==search_type_NEXT ? t->SearchNext(flag, search_term) : t->SearchPrev(flag, search_term);
    //wxPrintf(_("Prev POS = %d\n"), previous_pos);
    if(find_pos >= 0)
    {
        //wxPuts(_("found: ") + search_term);
        //wxPrintf(_("F-CPOS = %d\n"), t->GetCurrentPos());
        t->GotoPos(find_pos);
        t->SetSelection(t->GetCurrentPos(), t->GetCurrentPos() + search_term.length());
    }

    return find_pos;
}

void rcbasic_edit_frame::onFindNextMenuSelect(wxCommandEvent& event)
{
    notebook_mutex.Lock();
    if(sourceFile_auinotebook->GetSelection() < 0)
    {
        notebook_mutex.Unlock();
        return;
    }

    wxStyledTextCtrl* t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(sourceFile_auinotebook->GetSelection());

    if(!t)
    {
        notebook_mutex.Unlock();
        //wxPuts(_("No TXT_CTRL\n"));
        return;
    }


    if(searchNextPrev(t, search_type_NEXT) < 0)
    {
        rcbasic_edit_searchWrap_dialog sw_dialog(this, search_term);
        sw_dialog.ShowModal();

        if(sw_dialog.getValue()==searchWrap_value_OK)
        {
            int current_pos = t->GetCurrentPos();
            t->GotoPos(0);
            if(searchNextPrev(t, search_type_NEXT) < 0)
            {
                t->GotoPos(current_pos);
                wxMessageBox(_("Could not find \"") + search_term + _("\"."));
            }
        }
    }
    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::onFindPreviousMenuSelect(wxCommandEvent& event)
{
    notebook_mutex.Lock();

    if(sourceFile_auinotebook->GetSelection() < 0)
    {
        notebook_mutex.Unlock();
        return;
    }

    wxStyledTextCtrl* t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(sourceFile_auinotebook->GetSelection());

    if(!t)
    {
        notebook_mutex.Unlock();
        //wxPuts(_("No TXT_CTRL\n"));
        return;
    }

    if(searchNextPrev(t, search_type_PREV) < 0)
    {
        rcbasic_edit_searchWrap_dialog sw_dialog(this, search_term);
        sw_dialog.ShowModal();

        if(sw_dialog.getValue()==searchWrap_value_OK)
        {
            int current_pos = t->GetCurrentPos();
            t->GotoPos( t->GetLastPosition());
            if(searchNextPrev(t, search_type_PREV) < 0)
            {
                t->GotoPos(current_pos);
                wxMessageBox(_("Could not find \"") + search_term + _("\"."));
            }
        }
    }
    notebook_mutex.Unlock();
}




void rcbasic_edit_frame::replaceInFile(int findDialog_flag, wxString txt, wxString replace_txt)
{

    if(sourceFile_auinotebook->GetPageCount() <= 0)
        return;

    search_term = txt;

    int current_page_index = sourceFile_auinotebook->GetSelection();
    wxStyledTextCtrl* t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(current_page_index);

    if(!t)
        return;

    int flag = findDialog_flag;

    wxString selText= txt;
    int selLen = selText.Len();
    int selStart= 0;

    int totalLen = t->GetTextLength();
    int searchStart=0;
    int foundLoc = 0;

    t->SetSearchFlags(flag);

    rcbasic_search_result r;

    wxFileName fname;

    for(int i = 0; i < open_files.size(); i++)
    {
        if(open_files[i]->getTextCtrl()==t)
        {
            fname = open_files[i]->getSourcePath();
            r.result_file = fname;
            break;
        }
    }

    while(foundLoc!=-1)
    {
        t->SetTargetStart(searchStart);
        t->SetTargetEnd(totalLen);

        foundLoc= t->SearchInTarget(selText);
        searchStart= foundLoc+selLen;

        if(foundLoc!=-1)
        {
            t->Replace(foundLoc, foundLoc + selText.length(), replace_txt);
            //r.pos = foundLoc;
            //r.line = t->LineFromPosition(foundLoc);
            //wxString line_str;
            //line_str.Printf(_(":%d:    "), r.line+1);
            //m_searchResults_listBox->AppendAndEnsureVisible( fname.GetFullName() + line_str + t->GetLineText(r.line) );
            //search_results.push_back(r);
        }
    }

    //if(m_searchResults_listBox->GetCount() > 0)
    //    m_searchResults_listBox->SetSelection(0);

}

void rcbasic_edit_frame::replaceInProject(int findDialog_flag, wxString txt, wxString replace_txt)
{
    clearSearchResults();

    if(!active_project)
        return;

    //wxPuts(_("Search for \"") + txt + _("\" In ") + active_project->getName() );
    search_term = txt;

    rcbasic_project_node* p_node;
    wxStyledTextCtrl* t;

    int flag = findDialog_flag;

    wxString selText= txt;
    int selLen = selText.Len();

    for(int p_file=0; p_file < active_project->getSourceFiles().size(); p_file++)
    {
        p_node = active_project->getSourceFiles()[p_file];
        if(!p_node->getTextCtrl())
        {
            t = new wxStyledTextCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, _("temp"));
            //t->ClearAll();
            wxFile f;
            if(!f.Open(p_node->getPath().GetFullPath()))
            {
                if(t)
                    delete t;
                t = NULL;
                continue;
            }
            else
            {
                wxString f_txt;
                f.ReadAll(&f_txt);
                f.Close();
                t->SetText(f_txt);
            }
        }
        else
        {
            t = p_node->getTextCtrl();
        }

        int selStart= 0;

        int totalLen = t->GetTextLength();
        int searchStart=0;
        int foundLoc = 0;

        t->SetSearchFlags(flag);

        rcbasic_search_result r;

        //
        wxFileName fname = p_node->getPath();
        r.result_file = fname;


        while(foundLoc!=-1)
        {
            t->SetTargetStart(searchStart);
            t->SetTargetEnd(totalLen);

            foundLoc= t->SearchInTarget(selText);
            searchStart= foundLoc+selLen;

            if(foundLoc!=-1)
            {
                r.pos = foundLoc;
                r.line = t->LineFromPosition(foundLoc);
                wxString line_str;
                line_str.Printf(_(":%d:    "), r.line+1);
                m_searchResults_listBox->AppendAndEnsureVisible( fname.GetFullName() + line_str + t->GetLineText(r.line) );
                search_results.push_back(r);
            }
        }

        if(t != p_node->getTextCtrl())
        {
            if(t)
                delete t;
            t = NULL;
        }

    }

    if(m_searchResults_listBox->GetCount() > 0)
        m_searchResults_listBox->SetSelection(0);

    m_results_notebook->SetSelection(RESULTS_LISTBOX_SEARCHMSG);

}

void rcbasic_edit_frame::onReplaceMenuSelect(wxCommandEvent& event)
{
    if(sourceFile_auinotebook->GetPageCount() <= 0)
        return;

    rcbasic_edit_replace_dialog r_dialog(this);
    r_dialog.ShowModal();

    switch(r_dialog.getValue())
    {
        case replace_dialog_INFILE:
            notebook_mutex.Lock();
            replaceInFile(r_dialog.getFlags(), r_dialog.getSearchText(), r_dialog.getReplaceText());
            notebook_mutex.Unlock();
            break;
    }
}


void rcbasic_edit_frame::onGotoMenuSelect( wxCommandEvent& event )
{
    rcbasic_edit_gotoLine_dialog goto_dialog(this);
    goto_dialog.ShowModal();
}

void rcbasic_edit_frame::updateFont(wxStyledTextCtrl* t)
{
    t->StyleSetFont(wxSTC_B_COMMENT, editor_font);
    t->StyleSetFont(wxSTC_B_CONSTANT, editor_font);
    t->StyleSetFont(wxSTC_B_DATE, editor_font);
    t->StyleSetFont(wxSTC_B_DEFAULT, editor_font);
    t->StyleSetFont(wxSTC_B_ERROR, editor_font);
    t->StyleSetFont(wxSTC_B_HEXNUMBER, editor_font);
    t->StyleSetFont(wxSTC_B_IDENTIFIER, editor_font);
    t->StyleSetFont(wxSTC_B_KEYWORD, editor_font);
    t->StyleSetFont(wxSTC_B_KEYWORD2, editor_font);
    t->StyleSetFont(wxSTC_B_KEYWORD3, editor_font);
    t->StyleSetFont(wxSTC_B_KEYWORD4, editor_font);
    t->StyleSetFont(wxSTC_B_LABEL, editor_font);
    t->StyleSetFont(wxSTC_B_NUMBER, editor_font);
    t->StyleSetFont(wxSTC_B_OPERATOR, editor_font);
    t->StyleSetFont(wxSTC_B_PREPROCESSOR, editor_font);
    t->StyleSetFont(wxSTC_B_STRING, editor_font);
    t->StyleSetFont(wxSTC_B_STRINGEOL, editor_font);
}

void rcbasic_edit_frame::onChangeFontMenuSelect( wxCommandEvent& event )
{
    wxFontData font_data;
    font_data.SetInitialFont(default_font);
    wxFontDialog font_picker(this, font_data);
    if(font_picker.ShowModal()==wxID_CANCEL)
        return;

    font_data = font_picker.GetFontData();
    editor_font = font_data.GetChosenFont();

    for(int i = 0; i < open_files.size(); i++)
    {
        notebook_mutex.Lock();
        applyScheme(open_files[i]->getTextCtrl());
        notebook_mutex.Unlock();
    }
}

void rcbasic_edit_frame::onChangeSchemeMenuSelect( wxCommandEvent& event )
{
    notebook_mutex.Lock();

    rcbasic_edit_setColorScheme_dialog scheme_dialog(this);
    scheme_dialog.ShowModal();

    notebook_mutex.Unlock();
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


void rcbasic_edit_frame::onZoomInMenuSelect( wxCommandEvent& event )
{
    notebook_mutex.Lock();
    int selected_page = sourceFile_auinotebook->GetSelection();

    if(selected_page < 0)
    {
        notebook_mutex.Unlock();
        return;
    }

    wxStyledTextCtrl* t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(selected_page);

    if(!t)
    {
        notebook_mutex.Unlock();
        return;
    }

    t->ZoomIn();

    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::onZoomOutMenuSelect( wxCommandEvent& event )
{
    notebook_mutex.Lock();
    int selected_page = sourceFile_auinotebook->GetSelection();

    if(selected_page < 0)
    {
        notebook_mutex.Unlock();
        return;
    }

    wxStyledTextCtrl* t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(selected_page);

    if(!t)
    {
        notebook_mutex.Unlock();
        return;
    }

    t->ZoomOut();

    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::onNormalSizeMenuSelect( wxCommandEvent& event )
{
    notebook_mutex.Lock();
    int selected_page = sourceFile_auinotebook->GetSelection();

    if(selected_page < 0)
    {
        notebook_mutex.Unlock();
        return;
    }

    wxStyledTextCtrl* t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(selected_page);

    if(!t)
    {
        notebook_mutex.Unlock();
        return;
    }

    t->SetZoom(0);

    notebook_mutex.Unlock();
}


void rcbasic_edit_frame::onProjectSettingsMenuSelect( wxCommandEvent& event )
{
    if((!active_project) || open_projects.size()<=0)
        return;

    rcbasic_edit_projectSettings_dialog ps_dialog(this);
    ps_dialog.ShowModal();

    if(ps_dialog.getFlag()==PROJECT_SETTINGS_CANCEL)
        return;

    notebook_mutex.Lock();
    active_project = ps_dialog.getNewProject();

    int project_index = getProjectFromRoot(active_project->getRootNode());
    updateProjectTree(project_index);
    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::onProjectEnvironmentMenuSelect( wxCommandEvent& event )
{
    if(!active_project || open_projects.size()<=0)
        return;

    rcbasic_edit_projectEnvironment_dialog p_dialog(this, active_project->getVars());
    p_dialog.ShowModal();

    if(p_dialog.getFlag()==PROJECT_ENVIRONMENT_DLG_CANCEL)
        return;

    active_project->clearEnvVars();
    active_project->setVars(p_dialog.getVars());
}


#define SAVE_PROJECT 1001
#define CLOSE_PROJECT 1002
#define NEW_FILE 1003
#define ADD_FILES 1004
#define NEW_FILE 1005
#define BUILD_PROJECT 1006
#define RUN_PROJECT 1007
#define PROJECT_PROPERTIES 1008

#define PT_OPEN_FILE 2001
#define PT_REMOVE_FILE 2002
#define PT_FILE_PROPERTIES 2003

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

        context_project->addSourceFile(fname.GetFullPath(), STORE_LOCATION_RELATIVE, false);
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
            //wxPuts(_("TEST 1"));
            txtCtrl = open_files[i]->getTextCtrl();
            if(txtCtrl)
                txtCtrl->SetEOLMode(wxSTC_EOL_LF);
            break;
        }
    }

    int index = -1;

    if(project)
    {
        newFile.MakeAbsolute();
        //wxPuts(_("Search for: ") + newFile.GetFullPath());
        index = project->getSourceFileIndex(newFile);
        //wxPrintf(_("\nDEBUG [index] = %d\n\n"), index);
    }

    if(txtCtrl)
    {
        //wxPuts(_("\nT CTRL\n"));
        for(int i = 0; i < open_files.size(); i++)
        {
            if(open_files[i]->getTextCtrl()==txtCtrl)
                txtCtrl_obj = open_files[i];
        }
        //No need to check for project value here because index will be -1 if project is NULL
        if(index >= 0)
        {
            //wxPrintf(_("Set txtCtrl to %p\n"), txtCtrl);
            project->getSourceFiles()[index]->setTextCtrl(txtCtrl);
        }
    }
    else
    {
        //wxPrintf("\nIndex = %d\n", index);
        if(project && index < 0)
            return NULL;

        txtCtrl_obj = new rcbasic_edit_txtCtrl(newFile, sourceFile_auinotebook);

        //wxPuts(_("OT DEBUG 2"));

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
        rc_txtCtrl->SetDropTarget(new rc_dragFileTarget(rc_txtCtrl));
        rc_txtCtrl->Connect(wxEVT_DROP_FILES, wxDropFilesEventHandler(rcbasic_edit_frame::onDropFiles), NULL, this);
        rc_txtCtrl->Connect( wxEVT_STC_CHANGE, wxStyledTextEventHandler( rcbasic_edit_frame::onTextCtrlUpdated ), NULL, this );
        rc_txtCtrl->Connect( wxEVT_STC_CHARADDED, wxStyledTextEventHandler( rcbasic_edit_frame::onTextCtrlModified ), NULL, this );

        rc_txtCtrl->SetMarginType(0, wxSTC_MARGIN_NUMBER);
        rc_txtCtrl->SetMarginWidth(0, 55);
        rc_txtCtrl->SetUndoCollection(true);
        rc_txtCtrl->EmptyUndoBuffer();
        rc_txtCtrl->SetLexer(wxSTC_LEX_FREEBASIC);

        rc_txtCtrl->SetKeyWords(0, rcbasic_edit_keywords.MakeLower());
        rc_txtCtrl->SetKeyWords(1, rcbasic_edit_keywords2);
        rc_txtCtrl->AutoCompSetIgnoreCase(true);
        //rc_txtCtrl->AutoCompSetMaxWidth(60);
        //rc_txtCtrl->StyleSetFont(wxSTC_STYLE_DEFAULT, editor_font);
        //rc_txtCtrl->SetTabWidth(4);

        rc_txtCtrl->SetEOLMode(wxSTC_EOL_LF);

        //wxPuts(_("Applying scheme"));
        applyScheme(rc_txtCtrl);
        //wxPrintf(_("TAB WIDTH = %d\n"), rc_txtCtrl->GetTabWidth());
        //wxPuts(_("Scheme has been applied"));
    }

    txtCtrl_obj->setTextChangedFlag(false);


    return txtCtrl_obj;
}

void rcbasic_edit_frame::createNewFile(rcbasic_project* project)
{
    wxString cwd = wxGetCwd();
    if(project)
    {
        wxSetWorkingDirectory(project->getLocation());
        //wxPuts(_("New Dir = ") + wxGetCwd());
    }
    rcbasic_edit_newFile_dialog newFile_dialog(this);
    newFile_dialog.ShowModal();

    if(newFile_dialog.getNewFileFlag()==newFileFlag_CANCEL)
        return;

    wxFileName newFile = newFile_dialog.getFileName();
    newFile.SetExt(_("bas"));

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

    rcbasic_edit_txtCtrl* txtCtrl_obj = NULL;

    if(newFile_dialog.getAddToProjectFlag())
    {
        //wxPuts("Adding to project");
        if(project)
        {
            project->addSourceFile(newFile.GetFullPath(), STORE_LOCATION_RELATIVE, false);
        }
        else
        {
            wxMessageBox(_("There is no active project to add new file to."));
        }
        notebook_mutex.Lock();
        txtCtrl_obj = openFileTab(project, newFile);
        notebook_mutex.Unlock();
    }
    else
    {
        notebook_mutex.Lock();
        txtCtrl_obj = openFileTab(NULL, newFile);
        notebook_mutex.Unlock();
    }

    notebook_mutex.Lock();
    if(txtCtrl_obj)
        txtCtrl_obj->setTextChangedFlag(false);

    if(project)
        updateProjectTree(getProjectFromRoot(project->getRootNode()));
    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::onTreeContextClick(wxCommandEvent &evt)
{
    //---ACTIVATE CONTEXT PROJECT
    if((!context_project) || open_projects.size()<=0)
            return;

    notebook_mutex.Lock();

    if(active_project != NULL)
    {
        project_tree->SetItemBold(active_project->getRootNode(), false);
    }
    active_project = context_project;

    if(active_project)
    {
        wxSetWorkingDirectory(active_project->getLocation());
    }

    project_tree->SetItemBold(active_project->getRootNode(), true);

    //---------

    switch(evt.GetId())
    {
        case SAVE_PROJECT:
            //wxPuts(_("Saving the project"));
            saveProject(context_project);
            break;
        case CLOSE_PROJECT:
            //wxPuts(_("###Closing the project"));
            closeProject(context_project);
            break;
        case ADD_FILES:
            //wxPuts(_("Add Files"));
            addMultipleFilesToProject();
            break;
        case NEW_FILE:
            //wxPuts(_("Remove Files"));
            createNewFile(context_project);
            break;
        case BUILD_PROJECT:
            //wxPuts(_("Build Project"));
            buildProject();
            break;
        case RUN_PROJECT:
            //wxPuts(_("Run Project"));
            runProject();
            break;
        case PROJECT_PROPERTIES:
            //wxPuts(_("Properties"));

            rcbasic_edit_projectSettings_dialog ps_dialog(this);
            ps_dialog.ShowModal();

            if(ps_dialog.getFlag()==PROJECT_SETTINGS_CANCEL)
            {
                notebook_mutex.Unlock();
                return;
            }

            active_project = ps_dialog.getNewProject();
            context_project = active_project;

            int project_index = getProjectFromRoot(active_project->getRootNode());
            updateProjectTree(project_index);

            break;
    }

    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::openFileProperties(rcbasic_project* f_project, rcbasic_project_node* f_node)
{
    wxString cwd = wxGetCwd();
    wxSetWorkingDirectory(f_project->getLocation());
    rcbasic_edit_fileProperties_dialog fp_dialog(this, f_node);
    fp_dialog.ShowModal();

    wxFileName node_fname = f_node->getPath();
    if(f_node->getLocationStoreType()==STORE_LOCATION_RELATIVE)
        node_fname.MakeRelativeTo(f_project->getLocation());
    else
        node_fname.MakeAbsolute();

    f_node->setPath(node_fname);


    wxFileName node_fname_abs = node_fname;
    node_fname_abs.MakeAbsolute();

    wxFileName f_node_path = f_project->getMainSource();
    f_node_path.MakeAbsolute();

    if( node_fname.GetFullPath().compare(f_node_path.GetFullPath())==0 )
    {
        f_project->setMainSource(f_node->getPath().GetFullPath());
    }

    wxSetWorkingDirectory(cwd);
}

void rcbasic_edit_frame::onTreeFileContextClick(wxCommandEvent &evt)
{
    remove_file_node_flag = 0;

    if(! (context_project || context_file) )
        return;

    wxString cwd = wxGetCwd();
    wxSetWorkingDirectory(context_project->getLocation());

    notebook_mutex.Lock();

    if(evt.GetId() == PT_OPEN_FILE)
    {
        remove_file_node_flag = PT_OPEN_FILE;
        wxFileName node_fname = context_file->getPath();
        node_fname.MakeAbsolute();
        openSourceFile(node_fname);
    }
    else if(evt.GetId() == PT_REMOVE_FILE)
    {
        remove_file_node_flag = PT_REMOVE_FILE;
        project_tree->Delete(context_file->getNode());
        context_project->removeSourceFile(context_file->getPath().GetFullPath());
        updateProjectTree(getProjectFromRoot(context_project->getRootNode()));
    }
    else if(evt.GetId() == PT_FILE_PROPERTIES)
    {
        remove_file_node_flag = PT_FILE_PROPERTIES;
        openFileProperties(context_project, context_file);
        updateProjectTree(getProjectFromRoot(context_project->getRootNode()));
    }

    notebook_mutex.Unlock();

    wxSetWorkingDirectory(cwd);
}


void rcbasic_edit_frame::projectTreeContextMenu()
{
    wxMenu menu;
    menu.Append(SAVE_PROJECT, wxT("&Save Project"));
    menu.Append(CLOSE_PROJECT, wxT("&Close Project"));
    menu.AppendSeparator();
    menu.Append(ADD_FILES, wxT("&Add Files"));
    menu.Append(NEW_FILE, wxT("&New File"));
    menu.AppendSeparator();
    menu.Append(BUILD_PROJECT, wxT("&Build"));
    menu.Append(RUN_PROJECT, wxT("&Run"));
    menu.Append(PROJECT_PROPERTIES, wxT("&Properties"));
    menu.Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(rcbasic_edit_frame::onTreeContextClick), NULL, this);
    PopupMenu(&menu);
}

void rcbasic_edit_frame::projectTreeFileContextMenu()
{
    wxMenu menu;
    menu.Append(PT_OPEN_FILE, wxT("&Open File"));
    menu.Append(PT_REMOVE_FILE, wxT("&Remove from Project"));
    menu.Append(PT_FILE_PROPERTIES, wxT("&Properties"));
    menu.Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(rcbasic_edit_frame::onTreeFileContextClick), NULL, this);
    PopupMenu(&menu);
}

void rcbasic_edit_frame::onProjectTreeContextMenu( wxTreeEvent& event )
{
    wxTreeItemId selected_node = event.GetItem();
    remove_file_node_flag = 0;
    for(int i = 0; i < open_projects.size(); i++)
    {
        if(open_projects[i]->getRootNode()==selected_node)
        {
            context_project = open_projects[i];
            projectTreeContextMenu();
            break;
        }

        std::vector<rcbasic_project_node*> p_files = open_projects[i]->getSourceFiles();
        bool should_break = false;
        for(int f = 0; f < p_files.size(); f++)
        {
            if(p_files[f]->getNode()==selected_node)
            {
                context_project = open_projects[i];
                context_file = p_files[f];
                projectTreeFileContextMenu();
                should_break = true;
                break;
            }
        }
        if(should_break)
            break;
    }

    if(!context_project)
        return;

    if(remove_file_node_flag == PT_REMOVE_FILE)
    {
        project_tree->SelectItem(context_project->getRootNode(), true);
    }
    else if(selected_node.IsOk() && remove_file_node_flag == 0)
    {
        project_tree->SelectItem(selected_node, true);
    }
}

void rcbasic_edit_frame::onProjectTreeNodeActivated( wxTreeEvent& event )
{
    //wxPrintf("Node Activated: %d\n\n", 0);
    wxTreeItemId selected_node = event.GetItem();
#ifdef _WIN32
    rcbasic_treeItem_data* data = (rcbasic_treeItem_data*)project_tree->GetItemData(selected_node);
#else
    if(!selected_node.IsOk())
        return;

    //rcbasic_treeItem_data* data = (rcbasic_treeItem_data*)project_tree->GetItemData(selected_node);
#endif

    /*if(data)
    {
        wxPuts(_("Node Data: ")+data->node_file_path.GetFullPath()+_(", ")+data->parent_project->getName());
    }*/

    notebook_mutex.Lock();
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
            //project_tree->SelectItem(active_project->getRootNode(), true);
            notebook_mutex.Unlock();
            return;
        }
        else
        {
            rcbasic_project_node* file_node;
            //wxPuts(_("Looking through project files"));
            for(int file_node_index = 0; file_node_index < open_projects[i]->getSourceFiles().size(); file_node_index++)
            {
                file_node = open_projects[i]->getSourceFiles()[file_node_index];
                //wxPrintf(_("CMP: %p\n"), file_node->getTextCtrl());
                if(file_node->getNode()==selected_node)
                {
                    #ifdef _WIN32
                    activated_project_item = selected_node;
                    activated_project_item_flag = true;
                    #endif
                    //wxPuts(_("Request open: ")+file_node->getPath().GetFullPath());
                    if(sourceFile_auinotebook->GetPageIndex(file_node->getTextCtrl())<0)
                    {
                        //wxPrintf(_("Open a tab: %d\n"), sourceFile_auinotebook->GetPageIndex(file_node->getTextCtrl()));
                        if(file_node->getTextCtrl())
                            file_node->setTextCtrl(NULL);
                        //wxPuts(_("OPENING FILE: ") + file_node->getPath().GetFullPath());
                        file_node->setTextCtrl(openFileTab(open_projects[i], file_node->getPath())->getTextCtrl());
                        //wxPuts(_("File Opened"));
                        //wxPrintf(_("file_node t_Ctrl = %p\n"), file_node->getTextCtrl());
                        notebook_mutex.Unlock();
                        int new_page_index = sourceFile_auinotebook->GetPageCount()-1;
                        //wxPrintf(_("new_page_index=%d\n"), new_page_index);
                        sourceFile_auinotebook->SetSelection(new_page_index);
                        //wxPuts(_("page has been switched"));
                        //project_tree->SelectItem(selected_node);
                        //wxPuts(_("TREE NODE SELECTED: ")+ project_tree->GetItemText(selected_node) );
                        #ifdef _WIN32
                        activated_project_item_flag2 = true;
                        selected_project_node = file_node;
                        #endif
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
    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::onProjectTreeSelectionChanged( wxTreeEvent& event )
{
    //wxPuts(_("Changed"));
    #ifdef _WIN32
    if(activated_project_item_flag2)
    {
        if(selected_project_node)
            selected_project_item = selected_project_node->getNode();
        activated_project_item_flag2 = false;
        //wxPuts(_("NODE OK 2: ") + project_tree->GetItemText(selected_project_item) );
        project_tree->SetItemBackgroundColour(selected_project_item, wxColour(0, 120, 215));
        project_tree->SetItemTextColour(selected_project_item, wxColour(240, 240, 240));
        project_tree->UnselectAll();
    }
    //project_tree->UnselectAll();
    event.Veto();
    #endif
}

void rcbasic_edit_frame::onProjectTreeSelectionChanging( wxTreeEvent& event )
{
    //wxPuts(_("Changing"));
    #ifdef _WIN32
    project_tree->UnselectAll();

    wxColour item_bkg = project_tree->GetBackgroundColour();
    wxColour item_fg = project_tree->GetForegroundColour();

    //wxTreeItemId old_item = event.GetOldItem();
    //if(old_item.IsOk())
    //    project_tree->SetItemBackgroundColour(old_item, item_bkg);

    if(selected_project_item.IsOk())
    {
        project_tree->SetItemBackgroundColour(selected_project_item, item_bkg);
        project_tree->SetItemTextColour(selected_project_item, item_fg);
    }

    selected_project_item  = event.GetItem();
    if(activated_project_item_flag)
    {
        activated_project_item_flag = false;
        selected_project_item = activated_project_item;
        //project_tree->SetItemBackgroundColour(selected_project_item, wxColour(0, 120, 215));
        //project_tree->SetItemTextColour(selected_project_item, wxColour(240, 240, 240));
    }

    if(activated_project_item_flag2)
    {
        return;
    }

    if(selected_project_item.IsOk())
    {
        //wxPuts(_("NODE OK: ") + project_tree->GetItemText(selected_project_item) );
        project_tree->SetItemBackgroundColour(selected_project_item, wxColour(0, 120, 215));
        project_tree->SetItemTextColour(selected_project_item, wxColour(240, 240, 240));
    }

    event.Veto();
    #endif
}

void rcbasic_edit_frame::onSourceFileTabClose( wxAuiNotebookEvent& event )
{
    notebook_mutex.Lock();

    int selected_page = event.GetSelection();

    if(selected_page < 0)
        return;

    wxString temp_text;
    bool text_changed = false;

    for(int i = 0; i < open_files.size(); i++)
    {
        if(!open_files[i])
            continue;

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
                        notebook_mutex.Unlock();
                        return;
                }
            }

            open_files.erase(open_files.begin()+i);
            break;
        }
    }

    for(int i = 0; i < open_projects.size(); i++)
    {
        if(!open_projects[i])
            continue;

        for(int file_node_index = 0; file_node_index < open_projects[i]->getSourceFiles().size(); file_node_index++)
        {
            if(!open_projects[i]->getSourceFiles()[file_node_index])
                continue;

            if(sourceFile_auinotebook->GetPageIndex(open_projects[i]->getSourceFiles()[file_node_index]->getTextCtrl()) == selected_page)
            {
                open_projects[i]->getSourceFiles()[file_node_index]->setTextCtrl(NULL);
            }
        }

    }

    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::addRecentProject(rcbasic_project* project)
{
    if(!project)
        return;

    wxString tmp[10];
    for(int i = 0; i < 10; i++)
    {
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
    wxString tmp[10];
    file.MakeAbsolute();

    for(int i = 0; i < 10; i++)
    {
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
    //event here
    notebook_mutex.Lock();
    int selected_tab = sourceFile_auinotebook->GetSelection();
    wxString selection_string = sourceFile_auinotebook->GetPageText(selected_tab);
    wxStyledTextCtrl* rc_txtCtrl = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(selected_tab);



    for(int i = 0; i < open_files.size(); i++)
    {
        if(!open_files[i])
            continue;

        if(open_files[i]->getTextCtrl()==rc_txtCtrl)
        {
            open_files[i]->setTextChangedFlag(true);
            sourceFile_auinotebook->SetPageText(selected_tab, _("[*]") + selection_string.substr(selection_string.find_first_not_of(_("[*]"))) );
        }
    }
    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::onTextCtrlModified( wxStyledTextEvent& event )
{
    notebook_mutex.Lock();
    if(sourceFile_auinotebook->GetSelection() < 0)
    {
        notebook_mutex.Unlock();
        return;
    }

    wxStyledTextCtrl * t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(sourceFile_auinotebook->GetSelection());

    if(!t)
    {
        notebook_mutex.Unlock();
        return;
    }

    //int selected_tab = sourceFile_auinotebook->GetSelection();
    //wxString selection_string = sourceFile_auinotebook->GetPageText(selected_tab);

    //sourceFile_auinotebook->SetPageText(selected_tab, _("[*]") + selection_string.substr(selection_string.find_first_not_of(_("[*]"))) );
    //t->SetLabel(_("[*]") + t->GetLabel().substr(t->GetLabel().find_first_not_of(_("]"))));

    char chr = event.GetKey();
    int currentLine = t->GetCurrentLine();
    int indent = 0;

    if(chr == '\n')
    {
        //wxMessageBox(_("Current Line = ") + wxString::Format("%i",currentLine));
        if(currentLine > 0)
        {
            indent = t->GetLineIndentation(currentLine-1);
        }
        if(indent == 0)
        {
            notebook_mutex.Unlock();
            return;
        }
        //wxMessageBox(_("Position from line = ") + wxString::Format("%i",t->PositionFromLine(currentLine)));
        t->SetLineIndentation(currentLine, indent);
        t->GotoPos(t->GetLineIndentPosition(currentLine));
    }
    else if(enable_codeCompletion)
    {
        wxStyledTextCtrl* rc_txtCtrl = t;
        // Find the word start
        int currentPos = rc_txtCtrl->GetCurrentPos();
        int wordStartPos = rc_txtCtrl->WordStartPosition( currentPos, true );

        // Display the autocompletion list
        int lenEntered = currentPos - wordStartPos;
        if (lenEntered >= lenCompletionCheck)
        {
            wxString cc_list = _("");
            wxString current_word = rc_txtCtrl->GetTextRange(wordStartPos, currentPos).MakeLower();
            int cc_index = 0;

            bool item_added = false;

            for(int i = cc_index; i < user_id_list.GetCount(); i++)
            {
                //wxPuts(_("compare [") + id_list[i].substr(0, lenEntered) + _("] to [") + current_word + _("]"));
                if(user_id_list[i].substr(0, lenEntered).MakeLower().compare(current_word)==0)
                {
                    cc_list += user_id_list[i] + _(" ");
                    item_added = true;
                }
                //else if(item_added)
                //    break;
            }

            cc_list += "_____________________________________ ";

            rc_txtCtrl->AutoCompShow(lenEntered, cc_list);
        }
    }

    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::addSymbol(rcbasic_symbol sym)
{
    wxString node_label = sym.id;

    if(sym.dimensions > 0)
        node_label.Printf(node_label + _(" [ %dd ]"), sym.dimensions);

    node_label.Printf(node_label + _(" : %d"), sym.line+1);

    //wxPrintf(_("token_type = %d"), sym->token_type);

    switch(sym.token_type)
    {
        case TOKEN_TYPE_VARIABLE:
            var_nodes.push_back(symbol_tree->AppendItem( variable_root_node, node_label, symbol_tree_varImage, -1, new rc_symbol_treeItem_data(sym)));
            break;
        case TOKEN_TYPE_FUNCTION:
            //wxPuts(_("ADD FUNCTION NODE")+sym->id);
            fn_nodes.push_back(symbol_tree->AppendItem( function_root_node, node_label, symbol_tree_fnImage, -1, new rc_symbol_treeItem_data(sym)));
            break;
    }
}

void rcbasic_edit_frame::setSymbol(wxTreeItemId s_node, rcbasic_symbol sym)
{
    wxString node_label = sym.id;

    if(s_node == variable_root_node || s_node == function_root_node)
        return;

    if(sym.dimensions > 0)
        node_label.Printf(node_label + _(" [ %dd ]"), sym.dimensions);

    node_label.Printf(node_label + _(" : %d"), sym.line+1);

    rc_symbol_treeItem_data* old_data = (rc_symbol_treeItem_data*)symbol_tree->GetItemData(s_node);
    symbol_tree->SetItemData(s_node, NULL);
    if(old_data)
        delete old_data;

    symbol_tree->SetItemText(s_node, node_label);
    symbol_tree->SetItemData(s_node, new rc_symbol_treeItem_data(sym));
    symbol_tree->SetItemImage(s_node, sym.token_type==TOKEN_TYPE_VARIABLE ? symbol_tree_varImage : symbol_tree_fnImage);

}

void rcbasic_edit_frame::onSymbolSelectionChanged( wxTreeEvent& event )
{
    #ifdef _WIN32
    wxTreeItemId selected_symbol = selected_symbol_item;
    #else
    wxTreeItemId selected_symbol = event.GetItem();
    #endif

    notebook_mutex.Lock();
    if(sourceFile_auinotebook->GetSelection()<0)
    {
        notebook_mutex.Unlock();
        return;
    }

    if(sourceFile_auinotebook->GetPage(sourceFile_auinotebook->GetSelection())!=parsed_page)
    {
        notebook_mutex.Unlock();
        #ifdef _WIN32
        symbol_tree->UnselectAll();
        #endif
        return;
    }

    if(selected_symbol==symbol_tree->GetRootItem() || selected_symbol==variable_root_node || selected_symbol==function_root_node)
    {
        notebook_mutex.Unlock();
        #ifdef _WIN32
        symbol_tree->UnselectAll();
        #endif
        return;
    }

    wxString symbol_txt = symbol_tree->GetItemText(selected_symbol);
    rc_symbol_treeItem_data* sym_data = (rc_symbol_treeItem_data*)symbol_tree->GetItemData(selected_symbol);
    rcbasic_symbol sym = sym_data->symbol;

    //wxPrintf(_("Symbol: ") + sym.id + _(" -- line=%d"), sym.line );


    wxStyledTextCtrl* t = (wxStyledTextCtrl*) sourceFile_auinotebook->GetPage(sourceFile_auinotebook->GetSelection());

    if(!t)
    {
        notebook_mutex.Unlock();
        #ifdef _WIN32
        symbol_tree->UnselectAll();
        #endif
        return;
    }

    if(sym.line >= 0)
    {
        t->GotoLine(sym.line);
        t->SetSelection(t->GetCurrentPos(), t->GetCurrentPos() + t->GetLineText(sym.line).length());
    }

    #ifdef _WIN32
    symbol_tree->UnselectAll();
    #endif

    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::onSymbolSelectionChanging( wxTreeEvent& event )
{
    notebook_mutex.Lock();
    #ifdef _WIN32
    symbol_tree->UnselectAll();

    wxColour item_bkg = symbol_tree->GetBackgroundColour();
    wxColour item_fg = symbol_tree->GetForegroundColour();

    if(selected_symbol_item.IsOk())
    {
        symbol_tree->SetItemBackgroundColour(selected_symbol_item, item_bkg);
        symbol_tree->SetItemTextColour(selected_symbol_item, item_fg);
    }

    selected_symbol_item  = event.GetItem();
    if(selected_symbol_item.IsOk())
    {
        symbol_tree->SetItemBackgroundColour(selected_symbol_item, wxColour(0, 120, 215));
        symbol_tree->SetItemTextColour(selected_symbol_item, wxColour(240, 240, 240));
    }
    #endif
    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::onNotebookPageChanged( wxAuiNotebookEvent& event )
{
    notebook_mutex.Lock();
    for(int i = 0; i < var_nodes.size(); i++)
    {
        rcbasic_treeItem_data * data = NULL;
        data = (rcbasic_treeItem_data*)symbol_tree->GetItemData(var_nodes[i]);
        symbol_tree->SetItemData(var_nodes[i], NULL);
        if(data)
            delete data;
    }

    for(int i = 0; i < fn_nodes.size(); i++)
    {
        rcbasic_treeItem_data * data = NULL;
        data = (rcbasic_treeItem_data*)symbol_tree->GetItemData(fn_nodes[i]);
        symbol_tree->SetItemData(fn_nodes[i], NULL);
        if(data)
            delete data;
    }

    symbol_tree->DeleteChildren(variable_root_node);
    symbol_tree->DeleteChildren(function_root_node);
    symbols.clear();
    var_nodes.clear();
    fn_nodes.clear();
    notebook_mutex.Unlock();
}


void rcbasic_edit_frame::onDropFiles( wxDropFilesEvent& event )
{
    if (event.GetNumberOfFiles() > 0)
    {

        wxString* dropped = event.GetFiles();
        wxASSERT(dropped);

        wxBusyCursor busyCursor;
        wxWindowDisabler disabler;
        wxBusyInfo busyInfo(_("Adding files, wait please..."));

        wxString name;
        wxArrayString files;

        for (int i = 0; i < event.GetNumberOfFiles(); i++)
        {
            name = dropped[i];
            if (wxFileExists(name))
                files.push_back(name);
            else if (wxDirExists(name))
                wxDir::GetAllFiles(name, &files);
        }


        notebook_mutex.Lock();
        for (size_t i = 0; i < files.size(); i++)
        {
            //wxMessageBox( files[i] + _("\n"));
            wxFileName fname(files[i]);
            if(fname.GetExt().MakeLower().compare(_("bas"))==0 || fname.GetExt().MakeLower().compare(_("txt"))==0)
                openSourceFile(wxFileName(files[i]));
            else if(fname.GetExt().MakeLower().compare(_("rcprj"))==0)
                openProject(fname);

        }
        notebook_mutex.Unlock();
    }
}


void rcbasic_edit_frame::onEditorUpdateUI( wxUpdateUIEvent& event )
{
    notebook_mutex.Lock();
    int selected_page = sourceFile_auinotebook->GetSelection();
    int selected_file_index = -1;

    int line_num = 0;
    int total_lines = 0;
    int col_num = 0;
    int total_col = 0;

    if(selected_page >= 0)
    {
        wxStyledTextCtrl* t = (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(selected_page);

        if(t)
        {
            line_num = t->GetCurrentLine();
            total_lines = t->GetLineCount();
            col_num = t->GetColumn(t->GetCurrentPos());
            total_col = t->GetColumn(t->GetLineEndPosition(line_num));
        }

        for(int i = 0; i < open_files.size(); i++)
        {
            if(!open_files[i])
                continue;

            if(sourceFile_auinotebook->GetPageIndex(open_files[i]->getTextCtrl()) == selected_page)
            {
                selected_file_index = i;
                break;
            }
        }
    }

    notebook_mutex.Unlock();

    wxString line_status;
    wxString column_status;

    line_status.Printf(_("Line: %d / %d"), line_num+1, total_lines);
    column_status.Printf(_("Column: %d / %d"), col_num, total_col);

    //m_statusBar->SetStatusText(line_status + _("   ") + column_status, 0);

    if(selected_file_index >= 0)
        m_statusBar->SetStatusText( line_status + _("   ") + column_status + _("\t\tFile: ") + open_files[selected_file_index]->getSourcePath().GetFullPath(), 0);
    else
        m_statusBar->SetStatusText(line_status + _("   ") + column_status, 0);

    if(isBuilding && (build_process != NULL))
    {
        wxTextInputStream build_stream(*build_process->GetInputStream());

        while(build_process->IsInputAvailable())
        {
            m_messageWindow_richText->AppendText(build_stream.ReadLine() + _("\n"));
        }
    }
}
