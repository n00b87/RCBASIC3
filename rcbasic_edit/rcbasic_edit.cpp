///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "rcbasic_edit.h"

///////////////////////////////////////////////////////////////////////////

rc_ideFrame::rc_ideFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	m_menubar1 = new wxMenuBar( 0 );
	m_file_menu = new wxMenu();
	m_new_menu = new wxMenu();
	wxMenuItem* m_new_menuItem = new wxMenuItem( m_file_menu, wxID_ANY, wxT("New"), wxEmptyString, wxITEM_NORMAL, m_new_menu );
	#if (defined( __WXMSW__ ) || defined( __WXGTK__ ) || defined( __WXOSX__ ))
	m_new_menuItem->SetBitmap( wxNullBitmap );
	#endif

	m_newProject_menuItem = new wxMenuItem( m_new_menu, wxID_ANY, wxString( wxT("New Project") ) , wxEmptyString, wxITEM_NORMAL );
	m_new_menu->Append( m_newProject_menuItem );

	m_newFile_menuItem = new wxMenuItem( m_new_menu, wxID_ANY, wxString( wxT("New Source File") ) , wxEmptyString, wxITEM_NORMAL );
	m_new_menu->Append( m_newFile_menuItem );

	m_file_menu->Append( m_new_menuItem );

	m_file_menu->AppendSeparator();

	m_open_menuItem = new wxMenuItem( m_file_menu, wxID_ANY, wxString( wxT("Open") ) , wxEmptyString, wxITEM_NORMAL );
	m_file_menu->Append( m_open_menuItem );

	m_recentProjects_menu = new wxMenu();
	wxMenuItem* m_recentProjects_menuItem = new wxMenuItem( m_file_menu, wxID_ANY, wxT("Recent Projects"), wxEmptyString, wxITEM_NORMAL, m_recentProjects_menu );
	m_file_menu->Append( m_recentProjects_menuItem );

	m_recentFiles_menu = new wxMenu();
	wxMenuItem* m_recentFiles_menuItem = new wxMenuItem( m_file_menu, wxID_ANY, wxT("Recent Files"), wxEmptyString, wxITEM_NORMAL, m_recentFiles_menu );
	m_file_menu->Append( m_recentFiles_menuItem );

	m_file_menu->AppendSeparator();

	m_saveFile_menuItem = new wxMenuItem( m_file_menu, wxID_ANY, wxString( wxT("Save File") ) , wxEmptyString, wxITEM_NORMAL );
	m_file_menu->Append( m_saveFile_menuItem );

	m_saveFileAs_menuItem = new wxMenuItem( m_file_menu, wxID_ANY, wxString( wxT("Save File As") ) , wxEmptyString, wxITEM_NORMAL );
	m_file_menu->Append( m_saveFileAs_menuItem );

	m_file_menu->AppendSeparator();

	m_saveProject_menuItem = new wxMenuItem( m_file_menu, wxID_ANY, wxString( wxT("Save Project") ) , wxEmptyString, wxITEM_NORMAL );
	m_file_menu->Append( m_saveProject_menuItem );

	m_saveProjectAs_menuItem = new wxMenuItem( m_file_menu, wxID_ANY, wxString( wxT("Save Project As") ) , wxEmptyString, wxITEM_NORMAL );
	m_file_menu->Append( m_saveProjectAs_menuItem );

	m_file_menu->AppendSeparator();

	m_saveAll_menuItem = new wxMenuItem( m_file_menu, wxID_ANY, wxString( wxT("Save All") ) , wxEmptyString, wxITEM_NORMAL );
	m_file_menu->Append( m_saveAll_menuItem );

	m_file_menu->AppendSeparator();

	m_closeFile_menuItem = new wxMenuItem( m_file_menu, wxID_ANY, wxString( wxT("Close File") ) , wxEmptyString, wxITEM_NORMAL );
	m_file_menu->Append( m_closeFile_menuItem );

	m_closeProject_menuItem = new wxMenuItem( m_file_menu, wxID_ANY, wxString( wxT("Close Project") ) , wxEmptyString, wxITEM_NORMAL );
	m_file_menu->Append( m_closeProject_menuItem );

	m_closeAll_menuItem = new wxMenuItem( m_file_menu, wxID_ANY, wxString( wxT("Close All") ) , wxEmptyString, wxITEM_NORMAL );
	m_file_menu->Append( m_closeAll_menuItem );

	m_file_menu->AppendSeparator();

	m_exit_menuItem = new wxMenuItem( m_file_menu, wxID_ANY, wxString( wxT("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	m_file_menu->Append( m_exit_menuItem );

	m_menubar1->Append( m_file_menu, wxT("File") );

	m_edit_menu = new wxMenu();
	m_undo_menuItem = new wxMenuItem( m_edit_menu, wxID_ANY, wxString( wxT("Undo") ) , wxEmptyString, wxITEM_NORMAL );
	m_edit_menu->Append( m_undo_menuItem );

	m_redo_menuItem = new wxMenuItem( m_edit_menu, wxID_ANY, wxString( wxT("Redo") ) , wxEmptyString, wxITEM_NORMAL );
	m_edit_menu->Append( m_redo_menuItem );

	m_edit_menu->AppendSeparator();

	m_cut_menuItem = new wxMenuItem( m_edit_menu, wxID_ANY, wxString( wxT("Cut") ) , wxEmptyString, wxITEM_NORMAL );
	m_edit_menu->Append( m_cut_menuItem );

	m_copy_menuItem = new wxMenuItem( m_edit_menu, wxID_ANY, wxString( wxT("Copy") ) , wxEmptyString, wxITEM_NORMAL );
	m_edit_menu->Append( m_copy_menuItem );

	m_paste_menuItem = new wxMenuItem( m_edit_menu, wxID_ANY, wxString( wxT("Paste") ) , wxEmptyString, wxITEM_NORMAL );
	m_edit_menu->Append( m_paste_menuItem );

	m_delete_menuItem = new wxMenuItem( m_edit_menu, wxID_ANY, wxString( wxT("Delete") ) , wxEmptyString, wxITEM_NORMAL );
	m_edit_menu->Append( m_delete_menuItem );

	m_edit_menu->AppendSeparator();

	m_comment_menuItem = new wxMenuItem( m_edit_menu, wxID_ANY, wxString( wxT("Comment Selected") ) , wxEmptyString, wxITEM_NORMAL );
	m_edit_menu->Append( m_comment_menuItem );

	m_blockComment_menuItem = new wxMenuItem( m_edit_menu, wxID_ANY, wxString( wxT("Block Comment Selected") ) , wxEmptyString, wxITEM_NORMAL );
	m_edit_menu->Append( m_blockComment_menuItem );

	m_menubar1->Append( m_edit_menu, wxT("Edit") );

	m_search_menu = new wxMenu();
	m_find_menuItem = new wxMenuItem( m_search_menu, wxID_ANY, wxString( wxT("Find") ) , wxEmptyString, wxITEM_NORMAL );
	m_search_menu->Append( m_find_menuItem );

	m_findNext_menuItem = new wxMenuItem( m_search_menu, wxID_ANY, wxString( wxT("Find Next") ) , wxEmptyString, wxITEM_NORMAL );
	m_search_menu->Append( m_findNext_menuItem );

	m_findPrevious_menuItem = new wxMenuItem( m_search_menu, wxID_ANY, wxString( wxT("Find Previous") ) , wxEmptyString, wxITEM_NORMAL );
	m_search_menu->Append( m_findPrevious_menuItem );

	m_search_menu->AppendSeparator();

	m_findInFiles_menuItem = new wxMenuItem( m_search_menu, wxID_ANY, wxString( wxT("Find in Files") ) , wxEmptyString, wxITEM_NORMAL );
	m_search_menu->Append( m_findInFiles_menuItem );

	m_replace_menuItem = new wxMenuItem( m_search_menu, wxID_ANY, wxString( wxT("Replace") ) , wxEmptyString, wxITEM_NORMAL );
	m_search_menu->Append( m_replace_menuItem );

	m_search_menu->AppendSeparator();

	m_goto_menuItem = new wxMenuItem( m_search_menu, wxID_ANY, wxString( wxT("Go To Line") ) , wxEmptyString, wxITEM_NORMAL );
	m_search_menu->Append( m_goto_menuItem );

	m_menubar1->Append( m_search_menu, wxT("Search") );

	m_view_menu = new wxMenu();
	m_changeFont_menuItem = new wxMenuItem( m_view_menu, wxID_ANY, wxString( wxT("Change Font") ) , wxEmptyString, wxITEM_NORMAL );
	m_view_menu->Append( m_changeFont_menuItem );

	m_changeColors_menuItem = new wxMenuItem( m_view_menu, wxID_ANY, wxString( wxT("Change Color Scheme") ) , wxEmptyString, wxITEM_NORMAL );
	m_view_menu->Append( m_changeColors_menuItem );

	m_view_menu->AppendSeparator();

	m_showToolbar_menuItem = new wxMenuItem( m_view_menu, wxID_ANY, wxString( wxT("Show Toolbar") ) , wxEmptyString, wxITEM_CHECK );
	m_view_menu->Append( m_showToolbar_menuItem );

	m_showSideBar_menuItem = new wxMenuItem( m_view_menu, wxID_ANY, wxString( wxT("Show Sidebar") ) , wxEmptyString, wxITEM_CHECK );
	m_view_menu->Append( m_showSideBar_menuItem );

	m_showMessageWindow_menuItem = new wxMenuItem( m_view_menu, wxID_ANY, wxString( wxT("Show Message Window") ) , wxEmptyString, wxITEM_CHECK );
	m_view_menu->Append( m_showMessageWindow_menuItem );

	m_view_menu->AppendSeparator();

	m_zoomIn_menuItem = new wxMenuItem( m_view_menu, wxID_ANY, wxString( wxT("Zoom In") ) , wxEmptyString, wxITEM_NORMAL );
	m_view_menu->Append( m_zoomIn_menuItem );

	m_zoomOut_menuItem = new wxMenuItem( m_view_menu, wxID_ANY, wxString( wxT("Zoom Out") ) , wxEmptyString, wxITEM_NORMAL );
	m_view_menu->Append( m_zoomOut_menuItem );

	m_normalSize_menuItem = new wxMenuItem( m_view_menu, wxID_ANY, wxString( wxT("Normal Size") ) , wxEmptyString, wxITEM_NORMAL );
	m_view_menu->Append( m_normalSize_menuItem );

	m_menubar1->Append( m_view_menu, wxT("View") );

	m_build_menu = new wxMenu();
	m_build_menuItem = new wxMenuItem( m_build_menu, wxID_ANY, wxString( wxT("Build") ) , wxEmptyString, wxITEM_NORMAL );
	m_build_menu->Append( m_build_menuItem );

	m_run_menuItem = new wxMenuItem( m_build_menu, wxID_ANY, wxString( wxT("Run") ) , wxEmptyString, wxITEM_NORMAL );
	m_build_menu->Append( m_run_menuItem );

	m_buildRun_menuItem = new wxMenuItem( m_build_menu, wxID_ANY, wxString( wxT("Build and Run") ) , wxEmptyString, wxITEM_NORMAL );
	m_build_menu->Append( m_buildRun_menuItem );

	m_debugRun_menuItem = new wxMenuItem( m_build_menu, wxID_ANY, wxString( wxT("Debug") ) , wxEmptyString, wxITEM_NORMAL );
	m_build_menu->Append( m_debugRun_menuItem );

	m_menubar1->Append( m_build_menu, wxT("Build") );

	m_tools_menu = new wxMenu();
	m_genKeystore_menuItem = new wxMenuItem( m_tools_menu, wxID_ANY, wxString( wxT("Generate Keystore") ) , wxEmptyString, wxITEM_NORMAL );
	m_tools_menu->Append( m_genKeystore_menuItem );

	m_distribute_menuItem = new wxMenuItem( m_tools_menu, wxID_ANY, wxString( wxT("Distribute") ) , wxEmptyString, wxITEM_NORMAL );
	m_tools_menu->Append( m_distribute_menuItem );

	m_menubar1->Append( m_tools_menu, wxT("Tools") );

	m_help_menu = new wxMenu();
	m_doc_menuItem = new wxMenuItem( m_help_menu, wxID_ANY, wxString( wxT("RCBasic Documentation") ) , wxEmptyString, wxITEM_NORMAL );
	m_help_menu->Append( m_doc_menuItem );

	m_editorManual_menuItem = new wxMenuItem( m_help_menu, wxID_ANY, wxString( wxT("Editor Documentation") ) , wxEmptyString, wxITEM_NORMAL );
	m_help_menu->Append( m_editorManual_menuItem );

	m_about_menuItem = new wxMenuItem( m_help_menu, wxID_ANY, wxString( wxT("About") ) , wxEmptyString, wxITEM_NORMAL );
	m_help_menu->Append( m_about_menuItem );

	m_menubar1->Append( m_help_menu, wxT("Help") );

	this->SetMenuBar( m_menubar1 );

	mainWindowSizer = new wxBoxSizer( wxVERTICAL );

	m_toolBar = new wxToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL );
	m_new_tool = m_toolBar->AddTool( wxID_ANY, wxT("New File"), wxArtProvider::GetBitmap( wxART_NEW, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_open_tool = m_toolBar->AddTool( wxID_ANY, wxT("Open"), wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_save_tool = m_toolBar->AddTool( wxID_ANY, wxT("Save"), wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_saveas_tool = m_toolBar->AddTool( wxID_ANY, wxT("Save As"), wxArtProvider::GetBitmap( wxART_FILE_SAVE_AS, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_toolBar->AddSeparator();

	m_run_tool = m_toolBar->AddTool( wxID_ANY, wxT("Build and Run"), wxBitmap( wxT("gfx/play.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_abort_tool = m_toolBar->AddTool( wxID_ANY, wxT("Abort"), wxBitmap( wxT("gfx/stop.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_toolBar->Realize();

	mainWindowSizer->Add( m_toolBar, 0, wxEXPAND, 5 );

	projectViewSizer = new wxBoxSizer( wxVERTICAL );

	m_mainView_message_splitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_mainView_message_splitter->SetSashGravity( 1 );
	m_mainView_message_splitter->Connect( wxEVT_IDLE, wxIdleEventHandler( rc_ideFrame::m_mainView_message_splitterOnIdle ), NULL, this );

	m_panel61 = new wxPanel( m_mainView_message_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	projectFileSizer = new wxBoxSizer( wxVERTICAL );

	m_project_file_splitter = new wxSplitterWindow( m_panel61, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_project_file_splitter->Connect( wxEVT_IDLE, wxIdleEventHandler( rc_ideFrame::m_project_file_splitterOnIdle ), NULL, this );

	m_sideBar_panel = new wxPanel( m_project_file_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	m_notebook4 = new wxNotebook( m_sideBar_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_project_panel = new wxPanel( m_notebook4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );

	m_treeCtrl6 = new wxTreeCtrl( m_project_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxBORDER_NONE );
	bSizer8->Add( m_treeCtrl6, 1, wxALL|wxEXPAND, 5 );


	m_project_panel->SetSizer( bSizer8 );
	m_project_panel->Layout();
	bSizer8->Fit( m_project_panel );
	m_notebook4->AddPage( m_project_panel, wxT("Projects"), true );
	m_ = new wxPanel( m_notebook4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );

	m_treeCtrl5 = new wxTreeCtrl( m_, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxBORDER_NONE );
	bSizer7->Add( m_treeCtrl5, 1, wxALL|wxEXPAND, 5 );


	m_->SetSizer( bSizer7 );
	m_->Layout();
	bSizer7->Fit( m_ );
	m_notebook4->AddPage( m_, wxT("Symbols"), false );

	bSizer5->Add( m_notebook4, 1, wxEXPAND | wxALL, 5 );


	m_sideBar_panel->SetSizer( bSizer5 );
	m_sideBar_panel->Layout();
	bSizer5->Fit( m_sideBar_panel );
	m_panel6 = new wxPanel( m_project_file_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	m_auinotebook1 = new wxAuiNotebook( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE );

	bSizer6->Add( m_auinotebook1, 1, wxEXPAND | wxALL, 5 );


	m_panel6->SetSizer( bSizer6 );
	m_panel6->Layout();
	bSizer6->Fit( m_panel6 );
	m_project_file_splitter->SplitVertically( m_sideBar_panel, m_panel6, 221 );
	projectFileSizer->Add( m_project_file_splitter, 1, wxEXPAND, 1 );


	m_panel61->SetSizer( projectFileSizer );
	m_panel61->Layout();
	projectFileSizer->Fit( m_panel61 );
	m_panel7 = new wxPanel( m_mainView_message_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxVERTICAL );

	m_messageWindow_richText = new wxRichTextCtrl( m_panel7, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
	bSizer17->Add( m_messageWindow_richText, 1, wxEXPAND | wxALL, 5 );


	m_panel7->SetSizer( bSizer17 );
	m_panel7->Layout();
	bSizer17->Fit( m_panel7 );
	m_mainView_message_splitter->SplitHorizontally( m_panel61, m_panel7, 500 );
	projectViewSizer->Add( m_mainView_message_splitter, 1, wxEXPAND, 5 );


	mainWindowSizer->Add( projectViewSizer, 1, wxEXPAND, 5 );


	this->SetSizer( mainWindowSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_new_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::createNewProject ), this, m_newProject_menuItem->GetId());
	m_view_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::toggleToolbar ), this, m_showToolbar_menuItem->GetId());
	m_view_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::toggleSideBar ), this, m_showSideBar_menuItem->GetId());
	m_view_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::toggleMessageWindow ), this, m_showMessageWindow_menuItem->GetId());
}

rc_ideFrame::~rc_ideFrame()
{
	// Disconnect Events

}

rc_newProject_dialog::rc_newProject_dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );


	bSizer16->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxHORIZONTAL );


	bSizer17->Add( 0, 0, 1, wxEXPAND, 5 );

	projectName_label = new wxStaticText( this, wxID_ANY, wxT("Project Name    "), wxDefaultPosition, wxDefaultSize, 0 );
	projectName_label->Wrap( -1 );
	bSizer17->Add( projectName_label, 1, wxALL, 5 );

	projectName_field = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer17->Add( projectName_field, 8, wxALL, 5 );


	bSizer17->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer16->Add( bSizer17, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxHORIZONTAL );


	bSizer18->Add( 0, 0, 1, wxEXPAND, 5 );

	projectLocation_label = new wxStaticText( this, wxID_ANY, wxT("Project Location"), wxDefaultPosition, wxDefaultSize, 0 );
	projectLocation_label->Wrap( -1 );
	bSizer18->Add( projectLocation_label, 1, wxALL, 5 );

	projectLocation_picker = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE );
	bSizer18->Add( projectLocation_picker, 8, wxALL, 5 );


	bSizer18->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer16->Add( bSizer18, 1, wxEXPAND, 5 );


	bSizer16->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );


	bSizer19->Add( 0, 0, 1, wxALIGN_LEFT|wxEXPAND, 5 );

	projectCreateMain_radio = new wxRadioButton( this, wxID_ANY, wxT("Create Main Source File"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	projectCreateMain_radio->SetValue( true );
	bSizer19->Add( projectCreateMain_radio, 1, wxALIGN_LEFT|wxALL, 5 );


	bSizer19->Add( 0, 0, 4, wxEXPAND, 5 );


	bSizer16->Add( bSizer19, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxHORIZONTAL );


	bSizer20->Add( 0, 0, 3, wxEXPAND, 5 );

	projectNewMain_label = new wxStaticText( this, wxID_ANY, wxT("File Name"), wxDefaultPosition, wxDefaultSize, 0 );
	projectNewMain_label->Wrap( -1 );
	bSizer20->Add( projectNewMain_label, 1, wxALL, 5 );

	projectNewMain_field = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer20->Add( projectNewMain_field, 8, wxALL, 5 );


	bSizer20->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer16->Add( bSizer20, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxHORIZONTAL );


	bSizer21->Add( 0, 0, 1, wxALIGN_LEFT|wxEXPAND, 5 );

	projectExistingMain_radio = new wxRadioButton( this, wxID_ANY, wxT("Copy Existing File as Main"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer21->Add( projectExistingMain_radio, 1, wxALIGN_LEFT|wxALL, 5 );


	bSizer21->Add( 0, 0, 4, wxEXPAND, 5 );


	bSizer16->Add( bSizer21, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxHORIZONTAL );


	bSizer22->Add( 0, 0, 3, wxEXPAND, 5 );

	projectPathToExistingMain_label = new wxStaticText( this, wxID_ANY, wxT("Path to File"), wxDefaultPosition, wxDefaultSize, 0 );
	projectPathToExistingMain_label->Wrap( -1 );
	bSizer22->Add( projectPathToExistingMain_label, 1, wxALL, 5 );

	projectExistingFile_picker = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.bas"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	projectExistingFile_picker->Enable( false );

	bSizer22->Add( projectExistingFile_picker, 8, wxALL, 5 );


	bSizer22->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer16->Add( bSizer22, 1, wxEXPAND, 5 );


	bSizer16->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer( wxHORIZONTAL );


	bSizer23->Add( 0, 0, 1, wxEXPAND, 5 );

	projectAuthor_label = new wxStaticText( this, wxID_ANY, wxT("Author        "), wxDefaultPosition, wxDefaultSize, 0 );
	projectAuthor_label->Wrap( -1 );
	bSizer23->Add( projectAuthor_label, 1, wxALL, 5 );

	projectAuthor_field = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer23->Add( projectAuthor_field, 8, wxALL, 5 );


	bSizer23->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer16->Add( bSizer23, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxHORIZONTAL );


	bSizer24->Add( 0, 0, 1, wxEXPAND, 5 );

	projectWebsite_label = new wxStaticText( this, wxID_ANY, wxT("Website      "), wxDefaultPosition, wxDefaultSize, 0 );
	projectWebsite_label->Wrap( -1 );
	bSizer24->Add( projectWebsite_label, 1, wxALL, 5 );

	projectWebsite_field = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer24->Add( projectWebsite_field, 8, wxALL, 5 );


	bSizer24->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer16->Add( bSizer24, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxHORIZONTAL );


	bSizer25->Add( 0, 0, 1, wxEXPAND, 5 );

	projectDescription_label = new wxStaticText( this, wxID_ANY, wxT("Description"), wxDefaultPosition, wxDefaultSize, 0 );
	projectDescription_label->Wrap( -1 );
	bSizer25->Add( projectDescription_label, 1, wxALL, 5 );

	projectDescription_field = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	bSizer25->Add( projectDescription_field, 8, wxALL|wxEXPAND, 5 );


	bSizer25->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer16->Add( bSizer25, 5, wxEXPAND, 5 );


	bSizer16->Add( 0, 0, 2, wxEXPAND, 5 );

	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxHORIZONTAL );


	bSizer26->Add( 0, 0, 8, wxEXPAND, 5 );

	cancelNewProject_button = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer26->Add( cancelNewProject_button, 0, wxALL, 5 );

	createNewProject_button = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer26->Add( createNewProject_button, 0, wxALL, 5 );


	bSizer26->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer16->Add( bSizer26, 1, wxEXPAND, 5 );


	bSizer16->Add( 0, 0, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer16 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	projectCreateMain_radio->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( rc_newProject_dialog::createMainSourceRadioSelected ), NULL, this );
	projectExistingMain_radio->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( rc_newProject_dialog::copyExistingSourceRadioSelected ), NULL, this );
	cancelNewProject_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_newProject_dialog::cancelNewProject ), NULL, this );
	createNewProject_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_newProject_dialog::createNewProject ), NULL, this );
}

rc_newProject_dialog::~rc_newProject_dialog()
{
	// Disconnect Events
	projectCreateMain_radio->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( rc_newProject_dialog::createMainSourceRadioSelected ), NULL, this );
	projectExistingMain_radio->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( rc_newProject_dialog::copyExistingSourceRadioSelected ), NULL, this );
	cancelNewProject_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_newProject_dialog::cancelNewProject ), NULL, this );
	createNewProject_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_newProject_dialog::createNewProject ), NULL, this );

}
