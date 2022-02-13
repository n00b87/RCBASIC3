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

	m_newFile_menuItem = new wxMenuItem( m_new_menu, wxID_ANY, wxString( wxT("New Source File") ) + wxT('\t') + wxT("Ctrl+N"), wxEmptyString, wxITEM_NORMAL );
	m_new_menu->Append( m_newFile_menuItem );

	m_file_menu->Append( m_new_menuItem );

	m_file_menu->AppendSeparator();

	m_open_menu = new wxMenu();
	wxMenuItem* m_open_menuItem = new wxMenuItem( m_file_menu, wxID_ANY, wxT("Open"), wxEmptyString, wxITEM_NORMAL, m_open_menu );
	m_openProject_menuItem = new wxMenuItem( m_open_menu, wxID_ANY, wxString( wxT("Open Project") ) , wxEmptyString, wxITEM_NORMAL );
	m_open_menu->Append( m_openProject_menuItem );

	wxMenuItem* m_openFile_menuItem;
	m_openFile_menuItem = new wxMenuItem( m_open_menu, wxID_ANY, wxString( wxT("Open Source File") ) + wxT('\t') + wxT("Ctrl+O"), wxEmptyString, wxITEM_NORMAL );
	m_open_menu->Append( m_openFile_menuItem );

	m_file_menu->Append( m_open_menuItem );

	m_recentProjects_menu = new wxMenu();
	wxMenuItem* m_recentProjects_menuItem = new wxMenuItem( m_file_menu, wxID_ANY, wxT("Recent Projects"), wxEmptyString, wxITEM_NORMAL, m_recentProjects_menu );
	m_file_menu->Append( m_recentProjects_menuItem );

	m_recentFiles_menu = new wxMenu();
	wxMenuItem* m_recentFiles_menuItem = new wxMenuItem( m_file_menu, wxID_ANY, wxT("Recent Files"), wxEmptyString, wxITEM_NORMAL, m_recentFiles_menu );
	m_file_menu->Append( m_recentFiles_menuItem );

	m_file_menu->AppendSeparator();

	m_saveFile_menuItem = new wxMenuItem( m_file_menu, wxID_ANY, wxString( wxT("Save File") ) + wxT('\t') + wxT("Ctrl+S"), wxEmptyString, wxITEM_NORMAL );
	m_file_menu->Append( m_saveFile_menuItem );

	m_saveFileAs_menuItem = new wxMenuItem( m_file_menu, wxID_ANY, wxString( wxT("Save File As") ) , wxEmptyString, wxITEM_NORMAL );
	m_file_menu->Append( m_saveFileAs_menuItem );

	m_file_menu->AppendSeparator();

	m_saveProject_menuItem = new wxMenuItem( m_file_menu, wxID_ANY, wxString( wxT("Save Project") ) , wxEmptyString, wxITEM_NORMAL );
	m_file_menu->Append( m_saveProject_menuItem );

	m_saveProjectAs_menuItem = new wxMenuItem( m_file_menu, wxID_ANY, wxString( wxT("Save Project As") ) , wxEmptyString, wxITEM_NORMAL );
	m_file_menu->Append( m_saveProjectAs_menuItem );

	m_file_menu->AppendSeparator();

	m_saveAll_menuItem = new wxMenuItem( m_file_menu, wxID_ANY, wxString( wxT("Save All") ) + wxT('\t') + wxT("Ctrl-Shift+S"), wxEmptyString, wxITEM_NORMAL );
	m_file_menu->Append( m_saveAll_menuItem );

	m_file_menu->AppendSeparator();

	m_closeFile_menuItem = new wxMenuItem( m_file_menu, wxID_ANY, wxString( wxT("Close File") ) + wxT('\t') + wxT("Ctrl+W"), wxEmptyString, wxITEM_NORMAL );
	m_file_menu->Append( m_closeFile_menuItem );

	m_closeProject_menuItem = new wxMenuItem( m_file_menu, wxID_ANY, wxString( wxT("Close Project") ) , wxEmptyString, wxITEM_NORMAL );
	m_file_menu->Append( m_closeProject_menuItem );

	m_closeAll_menuItem = new wxMenuItem( m_file_menu, wxID_ANY, wxString( wxT("Close All") ) + wxT('\t') + wxT("Ctrl-Shift+W"), wxEmptyString, wxITEM_NORMAL );
	m_file_menu->Append( m_closeAll_menuItem );

	m_file_menu->AppendSeparator();

	m_exit_menuItem = new wxMenuItem( m_file_menu, wxID_ANY, wxString( wxT("Exit") ) + wxT('\t') + wxT("Ctrl+Q"), wxEmptyString, wxITEM_NORMAL );
	m_file_menu->Append( m_exit_menuItem );

	m_menubar1->Append( m_file_menu, wxT("File") );

	m_edit_menu = new wxMenu();
	m_undo_menuItem = new wxMenuItem( m_edit_menu, wxID_ANY, wxString( wxT("Undo") ) + wxT('\t') + wxT("Ctrl+Z"), wxEmptyString, wxITEM_NORMAL );
	m_edit_menu->Append( m_undo_menuItem );

	m_redo_menuItem = new wxMenuItem( m_edit_menu, wxID_ANY, wxString( wxT("Redo") ) + wxT('\t') + wxT("Ctrl+Y"), wxEmptyString, wxITEM_NORMAL );
	m_edit_menu->Append( m_redo_menuItem );

	m_edit_menu->AppendSeparator();

	m_cut_menuItem = new wxMenuItem( m_edit_menu, wxID_ANY, wxString( wxT("Cut") ) + wxT('\t') + wxT("Ctrl+X"), wxEmptyString, wxITEM_NORMAL );
	m_edit_menu->Append( m_cut_menuItem );

	m_copy_menuItem = new wxMenuItem( m_edit_menu, wxID_ANY, wxString( wxT("Copy") ) + wxT('\t') + wxT("Ctrl+C"), wxEmptyString, wxITEM_NORMAL );
	m_edit_menu->Append( m_copy_menuItem );

	m_paste_menuItem = new wxMenuItem( m_edit_menu, wxID_ANY, wxString( wxT("Paste") ) + wxT('\t') + wxT("Ctrl+V"), wxEmptyString, wxITEM_NORMAL );
	m_edit_menu->Append( m_paste_menuItem );

	m_delete_menuItem = new wxMenuItem( m_edit_menu, wxID_ANY, wxString( wxT("Delete") ) , wxEmptyString, wxITEM_NORMAL );
	m_edit_menu->Append( m_delete_menuItem );

	m_edit_menu->AppendSeparator();

	m_comment_menuItem = new wxMenuItem( m_edit_menu, wxID_ANY, wxString( wxT("Comment Selected") ) , wxEmptyString, wxITEM_NORMAL );
	m_edit_menu->Append( m_comment_menuItem );

	wxMenuItem* m_uncomment_menuItem;
	m_uncomment_menuItem = new wxMenuItem( m_edit_menu, wxID_ANY, wxString( wxT("UnComment Selected") ) , wxEmptyString, wxITEM_NORMAL );
	m_edit_menu->Append( m_uncomment_menuItem );

	m_menubar1->Append( m_edit_menu, wxT("Edit") );

	m_search_menu = new wxMenu();
	m_find_menuItem = new wxMenuItem( m_search_menu, wxID_ANY, wxString( wxT("Find") ) + wxT('\t') + wxT("Ctrl+F"), wxEmptyString, wxITEM_NORMAL );
	m_search_menu->Append( m_find_menuItem );

	m_findNext_menuItem = new wxMenuItem( m_search_menu, wxID_ANY, wxString( wxT("Find Next") ) + wxT('\t') + wxT("Ctrl+G"), wxEmptyString, wxITEM_NORMAL );
	m_search_menu->Append( m_findNext_menuItem );

	m_findPrevious_menuItem = new wxMenuItem( m_search_menu, wxID_ANY, wxString( wxT("Find Previous") ) + wxT('\t') + wxT("Ctrl-Shift+G"), wxEmptyString, wxITEM_NORMAL );
	m_search_menu->Append( m_findPrevious_menuItem );

	m_replace_menuItem = new wxMenuItem( m_search_menu, wxID_ANY, wxString( wxT("Replace") ) + wxT('\t') + wxT("Ctrl+H"), wxEmptyString, wxITEM_NORMAL );
	m_search_menu->Append( m_replace_menuItem );

	m_search_menu->AppendSeparator();

	m_goto_menuItem = new wxMenuItem( m_search_menu, wxID_ANY, wxString( wxT("Go To Line") ) + wxT('\t') + wxT("Ctrl+L"), wxEmptyString, wxITEM_NORMAL );
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

	m_zoomIn_menuItem = new wxMenuItem( m_view_menu, wxID_ANY, wxString( wxT("Zoom In") ) + wxT('\t') + wxT("Ctrl++"), wxEmptyString, wxITEM_NORMAL );
	m_view_menu->Append( m_zoomIn_menuItem );

	m_zoomOut_menuItem = new wxMenuItem( m_view_menu, wxID_ANY, wxString( wxT("Zoom Out") ) + wxT('\t') + wxT("Ctrl+-"), wxEmptyString, wxITEM_NORMAL );
	m_view_menu->Append( m_zoomOut_menuItem );

	m_normalSize_menuItem = new wxMenuItem( m_view_menu, wxID_ANY, wxString( wxT("Normal Size") ) + wxT('\t') + wxT("Ctrl+0"), wxEmptyString, wxITEM_NORMAL );
	m_view_menu->Append( m_normalSize_menuItem );

	m_menubar1->Append( m_view_menu, wxT("View") );

	m_project_menu = new wxMenu();
	wxMenuItem* m_projectProperties_menuItem;
	m_projectProperties_menuItem = new wxMenuItem( m_project_menu, wxID_ANY, wxString( wxT("Properties") ) , wxEmptyString, wxITEM_NORMAL );
	m_project_menu->Append( m_projectProperties_menuItem );

	wxMenuItem* m_environment_menuItem;
	m_environment_menuItem = new wxMenuItem( m_project_menu, wxID_ANY, wxString( wxT("Environment") ) , wxEmptyString, wxITEM_NORMAL );
	m_project_menu->Append( m_environment_menuItem );

	m_menubar1->Append( m_project_menu, wxT("Project") );

	m_build_menu = new wxMenu();
	m_build_menuItem = new wxMenuItem( m_build_menu, wxID_ANY, wxString( wxT("Build") ) + wxT('\t') + wxT("F8"), wxEmptyString, wxITEM_NORMAL );
	m_build_menu->Append( m_build_menuItem );

	m_run_menuItem = new wxMenuItem( m_build_menu, wxID_ANY, wxString( wxT("Run") ) + wxT('\t') + wxT("F5"), wxEmptyString, wxITEM_NORMAL );
	m_build_menu->Append( m_run_menuItem );

	m_buildRun_menuItem = new wxMenuItem( m_build_menu, wxID_ANY, wxString( wxT("Build and Run") ) + wxT('\t') + wxT("F9"), wxEmptyString, wxITEM_NORMAL );
	m_build_menu->Append( m_buildRun_menuItem );

	m_abort_menuItem = new wxMenuItem( m_build_menu, wxID_ANY, wxString( wxT("Stop Execution") ) , wxEmptyString, wxITEM_NORMAL );
	m_build_menu->Append( m_abort_menuItem );

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

	m_about_menuItem = new wxMenuItem( m_help_menu, wxID_ANY, wxString( wxT("About") ) + wxT('\t') + wxT("F1"), wxEmptyString, wxITEM_NORMAL );
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
	m_mainView_message_splitter->SetMinimumPaneSize( 1 );

	m_panel61 = new wxPanel( m_mainView_message_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	projectFileSizer = new wxBoxSizer( wxVERTICAL );

	m_project_file_splitter = new wxSplitterWindow( m_panel61, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_project_file_splitter->Connect( wxEVT_IDLE, wxIdleEventHandler( rc_ideFrame::m_project_file_splitterOnIdle ), NULL, this );
	m_project_file_splitter->SetMinimumPaneSize( 1 );

	m_sideBar_panel = new wxPanel( m_project_file_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	m_notebook4 = new wxNotebook( m_sideBar_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_project_panel = new wxPanel( m_notebook4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );

	project_tree = new wxTreeCtrl( m_project_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxBORDER_NONE );
	bSizer8->Add( project_tree, 1, wxALL|wxEXPAND, 5 );


	m_project_panel->SetSizer( bSizer8 );
	m_project_panel->Layout();
	bSizer8->Fit( m_project_panel );
	m_notebook4->AddPage( m_project_panel, wxT("Projects"), true );
	m_ = new wxPanel( m_notebook4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );

	symbol_tree = new wxTreeCtrl( m_, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxBORDER_NONE );
	bSizer7->Add( symbol_tree, 1, wxALL|wxEXPAND, 5 );


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

	sourceFile_auinotebook = new wxAuiNotebook( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE|wxBORDER_SIMPLE );

	bSizer6->Add( sourceFile_auinotebook, 1, wxEXPAND | wxALL, 5 );


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

	m_results_notebook = new wxNotebook( m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_buildLog_panel = new wxPanel( m_results_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer56;
	bSizer56 = new wxBoxSizer( wxVERTICAL );

	m_messageWindow_richText = new wxRichTextCtrl( m_buildLog_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
	bSizer56->Add( m_messageWindow_richText, 1, wxEXPAND | wxALL, 5 );


	m_buildLog_panel->SetSizer( bSizer56 );
	m_buildLog_panel->Layout();
	bSizer56->Fit( m_buildLog_panel );
	m_results_notebook->AddPage( m_buildLog_panel, wxT("Build Log"), true );
	m_searchResults_panel = new wxPanel( m_results_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer57;
	bSizer57 = new wxBoxSizer( wxVERTICAL );

	m_searchResults_listBox = new wxListBox( m_searchResults_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0|wxBORDER_NONE );
	bSizer57->Add( m_searchResults_listBox, 1, wxALL|wxEXPAND, 5 );


	m_searchResults_panel->SetSizer( bSizer57 );
	m_searchResults_panel->Layout();
	bSizer57->Fit( m_searchResults_panel );
	m_results_notebook->AddPage( m_searchResults_panel, wxT("Search Results"), false );

	bSizer17->Add( m_results_notebook, 1, wxEXPAND | wxALL, 5 );


	m_panel7->SetSizer( bSizer17 );
	m_panel7->Layout();
	bSizer17->Fit( m_panel7 );
	m_mainView_message_splitter->SplitHorizontally( m_panel61, m_panel7, 500 );
	projectViewSizer->Add( m_mainView_message_splitter, 1, wxEXPAND, 5 );


	mainWindowSizer->Add( projectViewSizer, 1, wxEXPAND, 5 );


	this->SetSizer( mainWindowSizer );
	this->Layout();
	m_statusBar = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( rc_ideFrame::onEditorClose ) );
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( rc_ideFrame::onEditorIdle ) );
	this->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( rc_ideFrame::onEditorUpdateUI ) );
	m_new_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::newProjectMenuSelect ), this, m_newProject_menuItem->GetId());
	m_new_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::newFileMenuSelect ), this, m_newFile_menuItem->GetId());
	m_open_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::openProjectMenuSelect ), this, m_openProject_menuItem->GetId());
	m_open_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::openFileMenuSelect ), this, m_openFile_menuItem->GetId());
	m_file_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onSaveFileMenuSelect ), this, m_saveFile_menuItem->GetId());
	m_file_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onSaveFileAsMenuSelect ), this, m_saveFileAs_menuItem->GetId());
	m_file_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onSaveProjectMenuSelect ), this, m_saveProject_menuItem->GetId());
	m_file_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onSaveProjectAsMenuSelect ), this, m_saveProjectAs_menuItem->GetId());
	m_file_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onSaveAllMenuSelect ), this, m_saveAll_menuItem->GetId());
	m_file_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onCloseFileMenuSelect ), this, m_closeFile_menuItem->GetId());
	m_file_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onCloseProjectMenuSelect ), this, m_closeProject_menuItem->GetId());
	m_file_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onCloseAllMenuSelect ), this, m_closeAll_menuItem->GetId());
	m_file_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onExitMenuSelect ), this, m_exit_menuItem->GetId());
	m_edit_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onUndoMenuSelect ), this, m_undo_menuItem->GetId());
	m_edit_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onRedoMenuSelect ), this, m_redo_menuItem->GetId());
	m_edit_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onCutMenuSelect ), this, m_cut_menuItem->GetId());
	m_edit_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onCopyMenuSelect ), this, m_copy_menuItem->GetId());
	m_edit_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onPasteMenuSelect ), this, m_paste_menuItem->GetId());
	m_edit_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onDeleteMenuSelect ), this, m_delete_menuItem->GetId());
	m_edit_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onCommentMenuSelect ), this, m_comment_menuItem->GetId());
	m_edit_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onUnCommentMenuSelect ), this, m_uncomment_menuItem->GetId());
	m_search_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onFindMenuSelect ), this, m_find_menuItem->GetId());
	m_search_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onFindNextMenuSelect ), this, m_findNext_menuItem->GetId());
	m_search_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onFindPreviousMenuSelect ), this, m_findPrevious_menuItem->GetId());
	m_search_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onReplaceMenuSelect ), this, m_replace_menuItem->GetId());
	m_search_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onGotoMenuSelect ), this, m_goto_menuItem->GetId());
	m_view_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onChangeFontMenuSelect ), this, m_changeFont_menuItem->GetId());
	m_view_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onChangeSchemeMenuSelect ), this, m_changeColors_menuItem->GetId());
	m_view_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::toggleToolbar ), this, m_showToolbar_menuItem->GetId());
	m_view_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::toggleSideBar ), this, m_showSideBar_menuItem->GetId());
	m_view_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::toggleMessageWindow ), this, m_showMessageWindow_menuItem->GetId());
	m_view_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onZoomInMenuSelect ), this, m_zoomIn_menuItem->GetId());
	m_view_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onZoomOutMenuSelect ), this, m_zoomOut_menuItem->GetId());
	m_view_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onNormalSizeMenuSelect ), this, m_normalSize_menuItem->GetId());
	m_project_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onProjectSettingsMenuSelect ), this, m_projectProperties_menuItem->GetId());
	m_project_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onProjectEnvironmentMenuSelect ), this, m_environment_menuItem->GetId());
	m_build_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onBuildMenuSelect ), this, m_build_menuItem->GetId());
	m_build_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onRunMenuSelect ), this, m_run_menuItem->GetId());
	m_build_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onBuildRunMenuSelect ), this, m_buildRun_menuItem->GetId());
	m_build_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onStopExecuteMenuSelect ), this, m_abort_menuItem->GetId());
	m_tools_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onGenKeystoreMenuSelect ), this, m_genKeystore_menuItem->GetId());
	m_tools_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onDistributeMenuSelect ), this, m_distribute_menuItem->GetId());
	m_help_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onDocMenuSelect ), this, m_doc_menuItem->GetId());
	m_help_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onEditorManualMenuSelect ), this, m_editorManual_menuItem->GetId());
	m_help_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( rc_ideFrame::onAboutMenuSelect ), this, m_about_menuItem->GetId());
	this->Connect( m_new_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( rc_ideFrame::newFileMenuSelect ) );
	this->Connect( m_open_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( rc_ideFrame::openFileMenuSelect ) );
	this->Connect( m_save_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( rc_ideFrame::onSaveFileMenuSelect ) );
	this->Connect( m_saveas_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( rc_ideFrame::onSaveFileAsMenuSelect ) );
	this->Connect( m_run_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( rc_ideFrame::onBuildRunMenuSelect ) );
	this->Connect( m_abort_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( rc_ideFrame::onStopExecuteMenuSelect ) );
	project_tree->Connect( wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler( rc_ideFrame::onProjectTreeNodeActivated ), NULL, this );
	project_tree->Connect( wxEVT_COMMAND_TREE_ITEM_MENU, wxTreeEventHandler( rc_ideFrame::onProjectTreeContextMenu ), NULL, this );
	project_tree->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( rc_ideFrame::onProjectTreeSelectionChanged ), NULL, this );
	project_tree->Connect( wxEVT_COMMAND_TREE_SEL_CHANGING, wxTreeEventHandler( rc_ideFrame::onProjectTreeSelectionChanging ), NULL, this );
	symbol_tree->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( rc_ideFrame::onSymbolSelectionChanged ), NULL, this );
	symbol_tree->Connect( wxEVT_COMMAND_TREE_SEL_CHANGING, wxTreeEventHandler( rc_ideFrame::onSymbolSelectionChanging ), NULL, this );
	sourceFile_auinotebook->Connect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( rc_ideFrame::onNotebookPageChanged ), NULL, this );
	sourceFile_auinotebook->Connect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSE, wxAuiNotebookEventHandler( rc_ideFrame::onSourceFileTabClose ), NULL, this );
	m_searchResults_listBox->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( rc_ideFrame::onSearchResultSelection ), NULL, this );
	m_searchResults_listBox->Connect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( rc_ideFrame::onSearchResultSelection ), NULL, this );
}

rc_ideFrame::~rc_ideFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( rc_ideFrame::onEditorClose ) );
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( rc_ideFrame::onEditorIdle ) );
	this->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( rc_ideFrame::onEditorUpdateUI ) );
	this->Disconnect( m_new_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( rc_ideFrame::newFileMenuSelect ) );
	this->Disconnect( m_open_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( rc_ideFrame::openFileMenuSelect ) );
	this->Disconnect( m_save_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( rc_ideFrame::onSaveFileMenuSelect ) );
	this->Disconnect( m_saveas_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( rc_ideFrame::onSaveFileAsMenuSelect ) );
	this->Disconnect( m_run_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( rc_ideFrame::onBuildRunMenuSelect ) );
	this->Disconnect( m_abort_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( rc_ideFrame::onStopExecuteMenuSelect ) );
	project_tree->Disconnect( wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler( rc_ideFrame::onProjectTreeNodeActivated ), NULL, this );
	project_tree->Disconnect( wxEVT_COMMAND_TREE_ITEM_MENU, wxTreeEventHandler( rc_ideFrame::onProjectTreeContextMenu ), NULL, this );
	project_tree->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( rc_ideFrame::onProjectTreeSelectionChanged ), NULL, this );
	project_tree->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGING, wxTreeEventHandler( rc_ideFrame::onProjectTreeSelectionChanging ), NULL, this );
	symbol_tree->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( rc_ideFrame::onSymbolSelectionChanged ), NULL, this );
	symbol_tree->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGING, wxTreeEventHandler( rc_ideFrame::onSymbolSelectionChanging ), NULL, this );
	sourceFile_auinotebook->Disconnect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( rc_ideFrame::onNotebookPageChanged ), NULL, this );
	sourceFile_auinotebook->Disconnect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSE, wxAuiNotebookEventHandler( rc_ideFrame::onSourceFileTabClose ), NULL, this );
	m_searchResults_listBox->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( rc_ideFrame::onSearchResultSelection ), NULL, this );
	m_searchResults_listBox->Disconnect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( rc_ideFrame::onSearchResultSelection ), NULL, this );

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

rc_closeProjectSavePrompt_dialog::rc_closeProjectSavePrompt_dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxVERTICAL );


	bSizer20->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxHORIZONTAL );


	bSizer21->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText8 = new wxStaticText( this, wxID_ANY, wxT("Do you want to save the project before closing?"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	m_staticText8->SetFont( wxFont( 10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );

	bSizer21->Add( m_staticText8, 1, wxALL|wxEXPAND, 5 );


	bSizer21->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer20->Add( bSizer21, 3, wxEXPAND, 5 );

	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxHORIZONTAL );


	bSizer22->Add( 0, 0, 1, wxEXPAND, 5 );

	closeProjectSave_cancelButton = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer22->Add( closeProjectSave_cancelButton, 0, wxALL, 5 );

	closeProjectSave_dontSaveButton = new wxButton( this, wxID_ANY, wxT("Don't Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer22->Add( closeProjectSave_dontSaveButton, 0, wxALL, 5 );

	closeProjectSave_saveButton = new wxButton( this, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer22->Add( closeProjectSave_saveButton, 0, wxALL, 5 );


	bSizer22->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer20->Add( bSizer22, 1, wxEXPAND, 5 );


	bSizer20->Add( 0, 0, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer20 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	closeProjectSave_cancelButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_closeProjectSavePrompt_dialog::onCloseProjectSaveCancel ), NULL, this );
	closeProjectSave_dontSaveButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_closeProjectSavePrompt_dialog::onCloseProjectSaveDontSave ), NULL, this );
	closeProjectSave_saveButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_closeProjectSavePrompt_dialog::onCloseProjectSaveOk ), NULL, this );
}

rc_closeProjectSavePrompt_dialog::~rc_closeProjectSavePrompt_dialog()
{
	// Disconnect Events
	closeProjectSave_cancelButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_closeProjectSavePrompt_dialog::onCloseProjectSaveCancel ), NULL, this );
	closeProjectSave_dontSaveButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_closeProjectSavePrompt_dialog::onCloseProjectSaveDontSave ), NULL, this );
	closeProjectSave_saveButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_closeProjectSavePrompt_dialog::onCloseProjectSaveOk ), NULL, this );

}

rc_newFile_dialog::rc_newFile_dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer( wxVERTICAL );


	bSizer23->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxHORIZONTAL );


	bSizer24->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText9 = new wxStaticText( this, wxID_ANY, wxT("Filename:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	bSizer24->Add( m_staticText9, 1, wxALL, 5 );

	createNewSource_fileDialog = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_SAVE|wxFLP_SMALL|wxFLP_USE_TEXTCTRL );
	bSizer24->Add( createNewSource_fileDialog, 5, wxALL, 5 );


	bSizer24->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer23->Add( bSizer24, 4, wxEXPAND, 5 );

	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxHORIZONTAL );


	bSizer25->Add( 0, 0, 1, wxEXPAND, 5 );

	createNewSource_addToProject_checkBox = new wxCheckBox( this, wxID_ANY, wxT("Add New File to Current Project"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer25->Add( createNewSource_addToProject_checkBox, 6, wxALL, 5 );


	bSizer25->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer23->Add( bSizer25, 4, wxEXPAND, 5 );

	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxHORIZONTAL );


	bSizer26->Add( 0, 0, 8, wxEXPAND, 5 );

	createNewSource_cancelButton = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer26->Add( createNewSource_cancelButton, 1, wxALL, 5 );

	createNewSource_okButton = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer26->Add( createNewSource_okButton, 1, wxALL, 5 );


	bSizer26->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer23->Add( bSizer26, 1, wxEXPAND, 5 );


	bSizer23->Add( 0, 0, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer23 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	createNewSource_cancelButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_newFile_dialog::onCreateNewSourceCancel ), NULL, this );
	createNewSource_okButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_newFile_dialog::onCreateNewSourceOk ), NULL, this );
}

rc_newFile_dialog::~rc_newFile_dialog()
{
	// Disconnect Events
	createNewSource_cancelButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_newFile_dialog::onCreateNewSourceCancel ), NULL, this );
	createNewSource_okButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_newFile_dialog::onCreateNewSourceOk ), NULL, this );

}

rc_find_dialog::rc_find_dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxHORIZONTAL );


	bSizer28->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText11 = new wxStaticText( this, wxID_ANY, wxT("Search for:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizer28->Add( m_staticText11, 2, wxALL, 5 );

	m_search_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer28->Add( m_search_textCtrl, 8, wxALL, 5 );


	bSizer28->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer27->Add( bSizer28, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxHORIZONTAL );


	bSizer29->Add( 0, 0, 1, wxEXPAND, 5 );

	m_caseSensitive_checkBox = new wxCheckBox( this, wxID_ANY, wxT("Case Sensitive"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer29->Add( m_caseSensitive_checkBox, 0, wxALL, 5 );

	m_matchWhole_checkBox = new wxCheckBox( this, wxID_ANY, wxT("Match only a whole word"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer29->Add( m_matchWhole_checkBox, 0, wxALL, 5 );


	bSizer29->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer27->Add( bSizer29, 2, wxEXPAND, 5 );

	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxHORIZONTAL );


	bSizer31->Add( 0, 0, 4, wxEXPAND, 5 );

	m_mark_button = new wxButton( this, wxID_ANY, wxT("Mark"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer31->Add( m_mark_button, 0, wxALL, 5 );

	m_inProject_button = new wxButton( this, wxID_ANY, wxT("In Project"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer31->Add( m_inProject_button, 0, wxALL, 5 );

	m_inFile_button = new wxButton( this, wxID_ANY, wxT("In File"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer31->Add( m_inFile_button, 0, wxALL, 5 );


	bSizer31->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer30->Add( bSizer31, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer32;
	bSizer32 = new wxBoxSizer( wxHORIZONTAL );


	bSizer32->Add( 0, 0, 4, wxEXPAND, 5 );

	m_close_button = new wxButton( this, wxID_ANY, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer32->Add( m_close_button, 0, wxALL, 5 );

	m_previous_button = new wxButton( this, wxID_ANY, wxT("Previous"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer32->Add( m_previous_button, 0, wxALL, 5 );

	m_next_button = new wxButton( this, wxID_ANY, wxT("Next"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer32->Add( m_next_button, 0, wxALL, 5 );


	bSizer32->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer30->Add( bSizer32, 2, wxEXPAND, 5 );


	bSizer27->Add( bSizer30, 2, wxEXPAND, 5 );


	bSizer27->Add( 0, 0, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer27 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_mark_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_find_dialog::onMarkButtonClick ), NULL, this );
	m_inProject_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_find_dialog::onInProjectButtonClick ), NULL, this );
	m_inFile_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_find_dialog::onInFileButtonClick ), NULL, this );
	m_close_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_find_dialog::onCloseButtonClick ), NULL, this );
	m_previous_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_find_dialog::onPreviousButtonClick ), NULL, this );
	m_next_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_find_dialog::onNextButtonClick ), NULL, this );
}

rc_find_dialog::~rc_find_dialog()
{
	// Disconnect Events
	m_mark_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_find_dialog::onMarkButtonClick ), NULL, this );
	m_inProject_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_find_dialog::onInProjectButtonClick ), NULL, this );
	m_inFile_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_find_dialog::onInFileButtonClick ), NULL, this );
	m_close_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_find_dialog::onCloseButtonClick ), NULL, this );
	m_previous_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_find_dialog::onPreviousButtonClick ), NULL, this );
	m_next_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_find_dialog::onNextButtonClick ), NULL, this );

}

rc_searchWrap_dialog::rc_searchWrap_dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxVERTICAL );


	bSizer20->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxHORIZONTAL );


	bSizer21->Add( 0, 0, 1, wxEXPAND, 5 );

	m_searchWrapPrompt_staticText = new wxStaticText( this, wxID_ANY, wxT("Did not find \"[text]\".\nWrap and search again?"), wxDefaultPosition, wxDefaultSize, 0 );
	m_searchWrapPrompt_staticText->Wrap( -1 );
	m_searchWrapPrompt_staticText->SetFont( wxFont( 10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );

	bSizer21->Add( m_searchWrapPrompt_staticText, 1, wxALL|wxEXPAND, 5 );


	bSizer21->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer20->Add( bSizer21, 3, wxEXPAND, 5 );

	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxHORIZONTAL );


	bSizer22->Add( 0, 0, 1, wxEXPAND, 5 );

	searchWrap_cancelButton = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer22->Add( searchWrap_cancelButton, 0, wxALL, 5 );

	searchWrap_okButton = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer22->Add( searchWrap_okButton, 0, wxALL, 5 );


	bSizer22->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer20->Add( bSizer22, 1, wxEXPAND, 5 );


	bSizer20->Add( 0, 0, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer20 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	searchWrap_cancelButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_searchWrap_dialog::onSearchWrapCancel ), NULL, this );
	searchWrap_okButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_searchWrap_dialog::onSearchWrapOk ), NULL, this );
}

rc_searchWrap_dialog::~rc_searchWrap_dialog()
{
	// Disconnect Events
	searchWrap_cancelButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_searchWrap_dialog::onSearchWrapCancel ), NULL, this );
	searchWrap_okButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_searchWrap_dialog::onSearchWrapOk ), NULL, this );

}

rc_replace_dialog::rc_replace_dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer45;
	bSizer45 = new wxBoxSizer( wxHORIZONTAL );


	bSizer45->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText11 = new wxStaticText( this, wxID_ANY, wxT("Search for:    "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizer45->Add( m_staticText11, 2, wxALL, 5 );

	m_search_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer45->Add( m_search_textCtrl, 8, wxALL, 5 );


	bSizer45->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer28->Add( bSizer45, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer46;
	bSizer46 = new wxBoxSizer( wxHORIZONTAL );


	bSizer46->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText15 = new wxStaticText( this, wxID_ANY, wxT("Replace with:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	bSizer46->Add( m_staticText15, 2, wxALL, 5 );

	m_replace_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer46->Add( m_replace_textCtrl, 8, wxALL, 5 );


	bSizer46->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer28->Add( bSizer46, 1, wxEXPAND, 5 );


	bSizer27->Add( bSizer28, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxHORIZONTAL );


	bSizer29->Add( 0, 0, 1, wxEXPAND, 5 );

	m_caseSensitive_checkBox = new wxCheckBox( this, wxID_ANY, wxT("Case Sensitive"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer29->Add( m_caseSensitive_checkBox, 0, wxALL, 5 );

	m_matchWhole_checkBox = new wxCheckBox( this, wxID_ANY, wxT("Match only a whole word"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer29->Add( m_matchWhole_checkBox, 0, wxALL, 5 );


	bSizer29->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer27->Add( bSizer29, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxVERTICAL );

	m_collapsiblePane1 = new wxCollapsiblePane( this, wxID_ANY, wxT("Replace All"), wxDefaultPosition, wxDefaultSize, wxCP_DEFAULT_STYLE|wxCP_NO_TLW_RESIZE );
	m_collapsiblePane1->Collapse( true );

	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxHORIZONTAL );


	bSizer31->Add( 0, 0, 1, wxEXPAND, 5 );

	m_replaceInProject_button = new wxButton( m_collapsiblePane1->GetPane(), wxID_ANY, wxT("In Project"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer31->Add( m_replaceInProject_button, 1, wxALL, 5 );

	m_replaceInFile_button = new wxButton( m_collapsiblePane1->GetPane(), wxID_ANY, wxT("In File"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer31->Add( m_replaceInFile_button, 1, wxALL, 5 );

	m_replaceInSelection_button = new wxButton( m_collapsiblePane1->GetPane(), wxID_ANY, wxT("In Selection"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer31->Add( m_replaceInSelection_button, 1, wxALL, 5 );


	bSizer31->Add( 0, 0, 1, wxEXPAND, 5 );


	m_collapsiblePane1->GetPane()->SetSizer( bSizer31 );
	m_collapsiblePane1->GetPane()->Layout();
	bSizer31->Fit( m_collapsiblePane1->GetPane() );
	bSizer30->Add( m_collapsiblePane1, 3, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer32;
	bSizer32 = new wxBoxSizer( wxHORIZONTAL );


	bSizer32->Add( 0, 0, 4, wxEXPAND, 5 );

	m_find_button = new wxButton( this, wxID_ANY, wxT("Find Next"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer32->Add( m_find_button, 1, wxALL, 5 );

	m_button29 = new wxButton( this, wxID_ANY, wxT("Replace"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer32->Add( m_button29, 1, wxALL, 5 );

	m_button13 = new wxButton( this, wxID_ANY, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer32->Add( m_button13, 1, wxALL, 5 );


	bSizer32->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer30->Add( bSizer32, 1, wxEXPAND, 5 );


	bSizer27->Add( bSizer30, 1, wxEXPAND, 5 );


	bSizer27->Add( 0, 0, 3, wxEXPAND, 5 );


	this->SetSizer( bSizer27 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_replaceInProject_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_replace_dialog::onReplaceInProjectClick ), NULL, this );
	m_replaceInFile_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_replace_dialog::onReplaceInFileClick ), NULL, this );
	m_replaceInSelection_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_replace_dialog::onReplaceInSelectionClick ), NULL, this );
	m_find_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_replace_dialog::onFindNextClick ), NULL, this );
	m_button29->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_replace_dialog::onReplaceClick ), NULL, this );
	m_button13->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_replace_dialog::onReplaceCloseClick ), NULL, this );
}

rc_replace_dialog::~rc_replace_dialog()
{
	// Disconnect Events
	m_replaceInProject_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_replace_dialog::onReplaceInProjectClick ), NULL, this );
	m_replaceInFile_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_replace_dialog::onReplaceInFileClick ), NULL, this );
	m_replaceInSelection_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_replace_dialog::onReplaceInSelectionClick ), NULL, this );
	m_find_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_replace_dialog::onFindNextClick ), NULL, this );
	m_button29->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_replace_dialog::onReplaceClick ), NULL, this );
	m_button13->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_replace_dialog::onReplaceCloseClick ), NULL, this );

}

rc_gotoLine_dialog::rc_gotoLine_dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer47;
	bSizer47 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer48;
	bSizer48 = new wxBoxSizer( wxHORIZONTAL );


	bSizer48->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText17 = new wxStaticText( this, wxID_ANY, wxT("Line:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	bSizer48->Add( m_staticText17, 2, wxALL, 5 );

	m_goto_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer48->Add( m_goto_textCtrl, 8, wxALL, 5 );


	bSizer48->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer47->Add( bSizer48, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer49;
	bSizer49 = new wxBoxSizer( wxHORIZONTAL );


	bSizer49->Add( 0, 0, 4, wxEXPAND, 5 );

	m_button28 = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer49->Add( m_button28, 0, wxALL, 5 );

	m_button29 = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer49->Add( m_button29, 0, wxALL, 5 );


	bSizer49->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer47->Add( bSizer49, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer47 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_button28->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_gotoLine_dialog::onCancelButtonClick ), NULL, this );
	m_button29->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_gotoLine_dialog::onOKButtonClick ), NULL, this );
}

rc_gotoLine_dialog::~rc_gotoLine_dialog()
{
	// Disconnect Events
	m_button28->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_gotoLine_dialog::onCancelButtonClick ), NULL, this );
	m_button29->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_gotoLine_dialog::onOKButtonClick ), NULL, this );

}

rc_closeFileSavePrompt_dialog::rc_closeFileSavePrompt_dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxVERTICAL );


	bSizer20->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxHORIZONTAL );


	bSizer21->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText8 = new wxStaticText( this, wxID_ANY, wxT("Do you wish to save this file before closing?"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	m_staticText8->SetFont( wxFont( 10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );

	bSizer21->Add( m_staticText8, 1, wxALL|wxEXPAND, 5 );


	bSizer21->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer20->Add( bSizer21, 3, wxEXPAND, 5 );

	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxHORIZONTAL );


	bSizer22->Add( 0, 0, 1, wxEXPAND, 5 );

	closeFileSave_cancelButton = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer22->Add( closeFileSave_cancelButton, 0, wxALL, 5 );

	closeFileSave_dontSaveButton = new wxButton( this, wxID_ANY, wxT("Don't Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer22->Add( closeFileSave_dontSaveButton, 0, wxALL, 5 );

	closeFileSave_saveButton = new wxButton( this, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer22->Add( closeFileSave_saveButton, 0, wxALL, 5 );


	bSizer22->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer20->Add( bSizer22, 1, wxEXPAND, 5 );


	bSizer20->Add( 0, 0, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer20 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	closeFileSave_cancelButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_closeFileSavePrompt_dialog::onCloseFileSaveCancel ), NULL, this );
	closeFileSave_dontSaveButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_closeFileSavePrompt_dialog::onCloseFileSaveDontSave ), NULL, this );
	closeFileSave_saveButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_closeFileSavePrompt_dialog::onCloseFileSaveOk ), NULL, this );
}

rc_closeFileSavePrompt_dialog::~rc_closeFileSavePrompt_dialog()
{
	// Disconnect Events
	closeFileSave_cancelButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_closeFileSavePrompt_dialog::onCloseFileSaveCancel ), NULL, this );
	closeFileSave_dontSaveButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_closeFileSavePrompt_dialog::onCloseFileSaveDontSave ), NULL, this );
	closeFileSave_saveButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_closeFileSavePrompt_dialog::onCloseFileSaveOk ), NULL, this );

}

rc_setColorScheme_dialog::rc_setColorScheme_dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer57;
	bSizer57 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer58;
	bSizer58 = new wxBoxSizer( wxHORIZONTAL );


	bSizer58->Add( 0, 0, 1, wxEXPAND, 5 );

	m_scheme_listBox = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer58->Add( m_scheme_listBox, 8, wxALL|wxEXPAND, 5 );


	bSizer58->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer57->Add( bSizer58, 8, wxEXPAND, 5 );

	wxBoxSizer* bSizer59;
	bSizer59 = new wxBoxSizer( wxHORIZONTAL );


	bSizer59->Add( 0, 0, 8, wxEXPAND, 5 );

	m_schemeClose_button = new wxButton( this, wxID_ANY, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer59->Add( m_schemeClose_button, 1, wxALL, 5 );


	bSizer59->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer57->Add( bSizer59, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer57 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_scheme_listBox->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( rc_setColorScheme_dialog::onSchemeSelected ), NULL, this );
	m_scheme_listBox->Connect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( rc_setColorScheme_dialog::onSchemeSelected ), NULL, this );
	m_schemeClose_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_setColorScheme_dialog::onSchemeCloseButtonClick ), NULL, this );
}

rc_setColorScheme_dialog::~rc_setColorScheme_dialog()
{
	// Disconnect Events
	m_scheme_listBox->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( rc_setColorScheme_dialog::onSchemeSelected ), NULL, this );
	m_scheme_listBox->Disconnect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( rc_setColorScheme_dialog::onSchemeSelected ), NULL, this );
	m_schemeClose_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_setColorScheme_dialog::onSchemeCloseButtonClick ), NULL, this );

}

rc_projectSettings_dialog::rc_projectSettings_dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer55;
	bSizer55 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer75;
	bSizer75 = new wxBoxSizer( wxVERTICAL );

	m_notebook3 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel9 = new wxPanel( m_notebook3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer63;
	bSizer63 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer56;
	bSizer56 = new wxBoxSizer( wxHORIZONTAL );


	bSizer56->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText16 = new wxStaticText( m_panel9, wxID_ANY, wxT("Project Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	bSizer56->Add( m_staticText16, 1, wxALL, 5 );

	m_projectName_textCtrl = new wxTextCtrl( m_panel9, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer56->Add( m_projectName_textCtrl, 4, wxALL, 5 );


	bSizer56->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer63->Add( bSizer56, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer57;
	bSizer57 = new wxBoxSizer( wxHORIZONTAL );


	bSizer57->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText17 = new wxStaticText( m_panel9, wxID_ANY, wxT("Main Source"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	bSizer57->Add( m_staticText17, 1, wxALL, 5 );

	m_mainSource_textCtrl = new wxTextCtrl( m_panel9, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer57->Add( m_mainSource_textCtrl, 4, wxALL, 5 );


	bSizer57->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer63->Add( bSizer57, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer74;
	bSizer74 = new wxBoxSizer( wxHORIZONTAL );


	bSizer74->Add( 0, 0, 2, wxEXPAND, 5 );

	m_mainSource_listBox = new wxListBox( m_panel9, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_ALWAYS_SB|wxLB_SORT );
	bSizer74->Add( m_mainSource_listBox, 4, wxALL|wxEXPAND, 5 );


	bSizer74->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer63->Add( bSizer74, 3, wxEXPAND, 5 );


	bSizer63->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer58;
	bSizer58 = new wxBoxSizer( wxHORIZONTAL );


	bSizer58->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText18 = new wxStaticText( m_panel9, wxID_ANY, wxT("Author"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	bSizer58->Add( m_staticText18, 1, wxALL, 5 );

	m_author_textCtrl = new wxTextCtrl( m_panel9, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer58->Add( m_author_textCtrl, 4, wxALL, 5 );


	bSizer58->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer63->Add( bSizer58, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer59;
	bSizer59 = new wxBoxSizer( wxHORIZONTAL );


	bSizer59->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText19 = new wxStaticText( m_panel9, wxID_ANY, wxT("Website"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText19->Wrap( -1 );
	bSizer59->Add( m_staticText19, 1, wxALL, 5 );

	m_website_textCtrl = new wxTextCtrl( m_panel9, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer59->Add( m_website_textCtrl, 4, wxALL, 5 );


	bSizer59->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer63->Add( bSizer59, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer60;
	bSizer60 = new wxBoxSizer( wxHORIZONTAL );


	bSizer60->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText20 = new wxStaticText( m_panel9, wxID_ANY, wxT("Description"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	bSizer60->Add( m_staticText20, 1, wxALL, 5 );

	m_description_textCtrl = new wxTextCtrl( m_panel9, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_WORDWRAP );
	bSizer60->Add( m_description_textCtrl, 4, wxALL|wxEXPAND, 5 );


	bSizer60->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer63->Add( bSizer60, 2, wxEXPAND, 5 );


	bSizer63->Add( 0, 0, 1, wxEXPAND, 5 );


	m_panel9->SetSizer( bSizer63 );
	m_panel9->Layout();
	bSizer63->Fit( m_panel9 );
	m_notebook3->AddPage( m_panel9, wxT("General"), true );
	m_panel10 = new wxPanel( m_notebook3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer64;
	bSizer64 = new wxBoxSizer( wxVERTICAL );

	m_files_listBox = new wxListBox( m_panel10, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_SORT );
	bSizer64->Add( m_files_listBox, 3, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer65;
	bSizer65 = new wxBoxSizer( wxHORIZONTAL );


	bSizer65->Add( 0, 0, 1, wxEXPAND, 5 );

	m_addFile_button = new wxButton( m_panel10, wxID_ANY, wxT("Add Files"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer65->Add( m_addFile_button, 1, wxALL, 5 );

	m_removeFile_button = new wxButton( m_panel10, wxID_ANY, wxT("Remove Selected"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer65->Add( m_removeFile_button, 1, wxALL, 5 );

	m_fileProperties_button = new wxButton( m_panel10, wxID_ANY, wxT("File Properties"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer65->Add( m_fileProperties_button, 1, wxALL, 5 );


	bSizer64->Add( bSizer65, 1, wxEXPAND, 5 );


	m_panel10->SetSizer( bSizer64 );
	m_panel10->Layout();
	bSizer64->Fit( m_panel10 );
	m_notebook3->AddPage( m_panel10, wxT("Files"), false );

	bSizer75->Add( m_notebook3, 1, wxEXPAND | wxALL, 5 );


	bSizer55->Add( bSizer75, 8, wxEXPAND, 5 );

	m_panel11 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer66;
	bSizer66 = new wxBoxSizer( wxHORIZONTAL );


	bSizer66->Add( 0, 0, 10, wxEXPAND, 5 );

	m_cancel_button = new wxButton( m_panel11, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer66->Add( m_cancel_button, 1, wxALIGN_CENTER|wxALL, 5 );

	m_ok_button = new wxButton( m_panel11, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer66->Add( m_ok_button, 1, wxALIGN_CENTER|wxALL, 5 );


	bSizer66->Add( 0, 0, 1, wxEXPAND, 5 );


	m_panel11->SetSizer( bSizer66 );
	m_panel11->Layout();
	bSizer66->Fit( m_panel11 );
	bSizer55->Add( m_panel11, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer55 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_mainSource_listBox->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( rc_projectSettings_dialog::onMainSourceListBoxSelection ), NULL, this );
	m_mainSource_listBox->Connect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( rc_projectSettings_dialog::onMainSourceListBoxSelection ), NULL, this );
	m_files_listBox->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( rc_projectSettings_dialog::onFileSelection ), NULL, this );
	m_files_listBox->Connect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( rc_projectSettings_dialog::onFileDoubleClick ), NULL, this );
	m_addFile_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_projectSettings_dialog::onAddFilesButtonClick ), NULL, this );
	m_removeFile_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_projectSettings_dialog::onRemoveSelectedButtonClick ), NULL, this );
	m_fileProperties_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_projectSettings_dialog::onFilePropertiesButtonClick ), NULL, this );
	m_cancel_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_projectSettings_dialog::onCancelButtonClick ), NULL, this );
	m_ok_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_projectSettings_dialog::onOKButtonClick ), NULL, this );
}

rc_projectSettings_dialog::~rc_projectSettings_dialog()
{
	// Disconnect Events
	m_mainSource_listBox->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( rc_projectSettings_dialog::onMainSourceListBoxSelection ), NULL, this );
	m_mainSource_listBox->Disconnect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( rc_projectSettings_dialog::onMainSourceListBoxSelection ), NULL, this );
	m_files_listBox->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( rc_projectSettings_dialog::onFileSelection ), NULL, this );
	m_files_listBox->Disconnect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( rc_projectSettings_dialog::onFileDoubleClick ), NULL, this );
	m_addFile_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_projectSettings_dialog::onAddFilesButtonClick ), NULL, this );
	m_removeFile_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_projectSettings_dialog::onRemoveSelectedButtonClick ), NULL, this );
	m_fileProperties_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_projectSettings_dialog::onFilePropertiesButtonClick ), NULL, this );
	m_cancel_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_projectSettings_dialog::onCancelButtonClick ), NULL, this );
	m_ok_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_projectSettings_dialog::onOKButtonClick ), NULL, this );

}

rc_fileProperties_dialog::rc_fileProperties_dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer67;
	bSizer67 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer68;
	bSizer68 = new wxBoxSizer( wxHORIZONTAL );


	bSizer68->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText21 = new wxStaticText( this, wxID_ANY, wxT("File Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	bSizer68->Add( m_staticText21, 3, wxALL, 5 );

	m_fileName_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer68->Add( m_fileName_textCtrl, 15, wxALL, 5 );


	bSizer68->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer67->Add( bSizer68, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer69;
	bSizer69 = new wxBoxSizer( wxHORIZONTAL );


	bSizer69->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText23 = new wxStaticText( this, wxID_ANY, wxT("File Location from Project:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	bSizer69->Add( m_staticText23, 3, wxALL, 5 );

	m_relative_radioBtn = new wxRadioButton( this, wxID_ANY, wxT("Relative"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer69->Add( m_relative_radioBtn, 2, wxALL, 5 );

	m_absolute_radioBtn = new wxRadioButton( this, wxID_ANY, wxT("Absolute"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer69->Add( m_absolute_radioBtn, 2, wxALL, 5 );


	bSizer69->Add( 0, 0, 6, wxEXPAND, 5 );


	bSizer67->Add( bSizer69, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer70;
	bSizer70 = new wxBoxSizer( wxHORIZONTAL );


	bSizer70->Add( 0, 0, 1, wxEXPAND, 5 );

	m_cancel_button = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer70->Add( m_cancel_button, 0, wxALL, 5 );

	m_ok_button = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer70->Add( m_ok_button, 0, wxALL, 5 );


	bSizer67->Add( bSizer70, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer67 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_cancel_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_fileProperties_dialog::onCancelButtonClick ), NULL, this );
	m_ok_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_fileProperties_dialog::onOKButtonClick ), NULL, this );
}

rc_fileProperties_dialog::~rc_fileProperties_dialog()
{
	// Disconnect Events
	m_cancel_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_fileProperties_dialog::onCancelButtonClick ), NULL, this );
	m_ok_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_fileProperties_dialog::onOKButtonClick ), NULL, this );

}

rc_projectEnvironment_dialog::rc_projectEnvironment_dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer71;
	bSizer71 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer72;
	bSizer72 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText24 = new wxStaticText( this, wxID_ANY, wxT("Project:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	bSizer72->Add( m_staticText24, 1, wxALL, 5 );

	m_projectName_staticText = new wxStaticText( this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_projectName_staticText->Wrap( -1 );
	bSizer72->Add( m_projectName_staticText, 9, wxALL, 5 );


	bSizer72->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer71->Add( bSizer72, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer73;
	bSizer73 = new wxBoxSizer( wxVERTICAL );

	m_environment_listCtrl = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_VRULES );
	bSizer73->Add( m_environment_listCtrl, 1, wxALL|wxEXPAND, 5 );


	bSizer71->Add( bSizer73, 4, wxEXPAND, 5 );

	wxBoxSizer* bSizer74;
	bSizer74 = new wxBoxSizer( wxHORIZONTAL );

	m_clearAll_button = new wxButton( this, wxID_ANY, wxT("Clear All"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer74->Add( m_clearAll_button, 1, wxALL, 5 );

	m_removeSelected_button = new wxButton( this, wxID_ANY, wxT("Remove Selected"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer74->Add( m_removeSelected_button, 1, wxALL, 5 );

	m_addVariable_button = new wxButton( this, wxID_ANY, wxT("Add Variable"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer74->Add( m_addVariable_button, 1, wxALL, 5 );

	m_editVariable_button = new wxButton( this, wxID_ANY, wxT("Edit Variable"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer74->Add( m_editVariable_button, 1, wxALL, 5 );


	bSizer71->Add( bSizer74, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer75;
	bSizer75 = new wxBoxSizer( wxHORIZONTAL );


	bSizer75->Add( 0, 0, 4, wxEXPAND, 5 );

	m_cancel_button = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer75->Add( m_cancel_button, 1, wxALL, 5 );

	m_ok_button = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer75->Add( m_ok_button, 1, wxALL, 5 );


	bSizer71->Add( bSizer75, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer71 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_clearAll_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_projectEnvironment_dialog::onClearAllButtonClick ), NULL, this );
	m_removeSelected_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_projectEnvironment_dialog::onRemoveSelectedButtonClick ), NULL, this );
	m_addVariable_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_projectEnvironment_dialog::onAddVariableButtonClick ), NULL, this );
	m_editVariable_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_projectEnvironment_dialog::onEditVariableButtonClick ), NULL, this );
	m_cancel_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_projectEnvironment_dialog::onCancelButtonClick ), NULL, this );
	m_ok_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_projectEnvironment_dialog::onOKButtonClick ), NULL, this );
}

rc_projectEnvironment_dialog::~rc_projectEnvironment_dialog()
{
	// Disconnect Events
	m_clearAll_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_projectEnvironment_dialog::onClearAllButtonClick ), NULL, this );
	m_removeSelected_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_projectEnvironment_dialog::onRemoveSelectedButtonClick ), NULL, this );
	m_addVariable_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_projectEnvironment_dialog::onAddVariableButtonClick ), NULL, this );
	m_editVariable_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_projectEnvironment_dialog::onEditVariableButtonClick ), NULL, this );
	m_cancel_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_projectEnvironment_dialog::onCancelButtonClick ), NULL, this );
	m_ok_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_projectEnvironment_dialog::onOKButtonClick ), NULL, this );

}

rc_projectVariableEdit_dialog::rc_projectVariableEdit_dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer78;
	bSizer78 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer79;
	bSizer79 = new wxBoxSizer( wxHORIZONTAL );


	bSizer79->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText25 = new wxStaticText( this, wxID_ANY, wxT("Variable"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	bSizer79->Add( m_staticText25, 1, wxALL, 5 );

	m_variable_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer79->Add( m_variable_textCtrl, 8, wxALL, 5 );


	bSizer79->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer78->Add( bSizer79, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer80;
	bSizer80 = new wxBoxSizer( wxHORIZONTAL );


	bSizer80->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText26 = new wxStaticText( this, wxID_ANY, wxT("Value    "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( -1 );
	bSizer80->Add( m_staticText26, 1, wxALL, 5 );

	m_value_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer80->Add( m_value_textCtrl, 8, wxALL, 5 );


	bSizer80->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer78->Add( bSizer80, 2, wxEXPAND, 5 );

	wxBoxSizer* bSizer81;
	bSizer81 = new wxBoxSizer( wxHORIZONTAL );


	bSizer81->Add( 0, 0, 2, wxEXPAND, 5 );

	m_cancel_button = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer81->Add( m_cancel_button, 1, wxALL, 5 );

	m_ok_button = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer81->Add( m_ok_button, 1, wxALL, 5 );


	bSizer78->Add( bSizer81, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer78 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_cancel_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_projectVariableEdit_dialog::onCancelButtonClick ), NULL, this );
	m_ok_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_projectVariableEdit_dialog::onOKButtonClick ), NULL, this );
}

rc_projectVariableEdit_dialog::~rc_projectVariableEdit_dialog()
{
	// Disconnect Events
	m_cancel_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_projectVariableEdit_dialog::onCancelButtonClick ), NULL, this );
	m_ok_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_projectVariableEdit_dialog::onOKButtonClick ), NULL, this );

}

rc_genKey_dialog::rc_genKey_dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer80;
	bSizer80 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer82;
	bSizer82 = new wxBoxSizer( wxHORIZONTAL );


	bSizer82->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText28 = new wxStaticText( this, wxID_ANY, wxT("Alias"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText28->Wrap( -1 );
	bSizer82->Add( m_staticText28, 1, wxALL, 5 );

	m_alias_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer82->Add( m_alias_textCtrl, 5, wxALL, 5 );


	bSizer82->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer80->Add( bSizer82, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer83;
	bSizer83 = new wxBoxSizer( wxHORIZONTAL );


	bSizer83->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText29 = new wxStaticText( this, wxID_ANY, wxT("Password               "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText29->Wrap( -1 );
	bSizer83->Add( m_staticText29, 1, wxALL, 5 );

	m_password_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer83->Add( m_password_textCtrl, 5, wxALL, 5 );


	bSizer83->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer80->Add( bSizer83, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer84;
	bSizer84 = new wxBoxSizer( wxHORIZONTAL );


	bSizer84->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText30 = new wxStaticText( this, wxID_ANY, wxT("Confirm Password"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	bSizer84->Add( m_staticText30, 1, wxALL, 5 );

	m_confirmPassword_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer84->Add( m_confirmPassword_textCtrl, 5, wxALL, 5 );


	bSizer84->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer80->Add( bSizer84, 1, wxEXPAND, 5 );


	bSizer80->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer85;
	bSizer85 = new wxBoxSizer( wxHORIZONTAL );


	bSizer85->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText31 = new wxStaticText( this, wxID_ANY, wxT("First and Last Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	bSizer85->Add( m_staticText31, 1, wxALL, 5 );

	m_name_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer85->Add( m_name_textCtrl, 5, wxALL, 5 );


	bSizer85->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer80->Add( bSizer85, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer86;
	bSizer86 = new wxBoxSizer( wxHORIZONTAL );


	bSizer86->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText32 = new wxStaticText( this, wxID_ANY, wxT("Organizational Unit"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText32->Wrap( -1 );
	bSizer86->Add( m_staticText32, 1, wxALL, 5 );

	m_orgUnit_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer86->Add( m_orgUnit_textCtrl, 5, wxALL, 5 );


	bSizer86->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer80->Add( bSizer86, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer87;
	bSizer87 = new wxBoxSizer( wxHORIZONTAL );


	bSizer87->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText33 = new wxStaticText( this, wxID_ANY, wxT("Organization       "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText33->Wrap( -1 );
	bSizer87->Add( m_staticText33, 1, wxALL, 5 );

	m_org_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer87->Add( m_org_textCtrl, 5, wxALL, 5 );


	bSizer87->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer80->Add( bSizer87, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer88;
	bSizer88 = new wxBoxSizer( wxHORIZONTAL );


	bSizer88->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText34 = new wxStaticText( this, wxID_ANY, wxT("City or Locality   "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText34->Wrap( -1 );
	bSizer88->Add( m_staticText34, 1, wxALL, 5 );

	m_city_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer88->Add( m_city_textCtrl, 5, wxALL, 5 );


	bSizer88->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer80->Add( bSizer88, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer89;
	bSizer89 = new wxBoxSizer( wxHORIZONTAL );


	bSizer89->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText35 = new wxStaticText( this, wxID_ANY, wxT("State or Province"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText35->Wrap( -1 );
	bSizer89->Add( m_staticText35, 1, wxALL, 5 );

	m_state_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer89->Add( m_state_textCtrl, 5, wxALL, 5 );


	bSizer89->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer80->Add( bSizer89, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer90;
	bSizer90 = new wxBoxSizer( wxHORIZONTAL );


	bSizer90->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText36 = new wxStaticText( this, wxID_ANY, wxT("Country               "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText36->Wrap( -1 );
	bSizer90->Add( m_staticText36, 1, wxALL, 5 );

	m_country_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer90->Add( m_country_textCtrl, 5, wxALL, 5 );


	bSizer90->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer80->Add( bSizer90, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer91;
	bSizer91 = new wxBoxSizer( wxHORIZONTAL );


	bSizer91->Add( 0, 0, 6, wxEXPAND, 5 );

	m_ok_button = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer91->Add( m_ok_button, 1, wxALL, 5 );

	m_cancel_button = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer91->Add( m_cancel_button, 1, wxALL, 5 );


	bSizer91->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer80->Add( bSizer91, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer80 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_ok_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_genKey_dialog::onOKButtonClick ), NULL, this );
	m_cancel_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_genKey_dialog::onCancelButtonClick ), NULL, this );
}

rc_genKey_dialog::~rc_genKey_dialog()
{
	// Disconnect Events
	m_ok_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_genKey_dialog::onOKButtonClick ), NULL, this );
	m_cancel_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_genKey_dialog::onCancelButtonClick ), NULL, this );

}

rc_distribute_dialog::rc_distribute_dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer92;
	bSizer92 = new wxBoxSizer( wxVERTICAL );

	m_notebook4 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel12 = new wxPanel( m_notebook4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer95;
	bSizer95 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer93;
	bSizer93 = new wxBoxSizer( wxHORIZONTAL );


	bSizer93->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText37 = new wxStaticText( m_panel12, wxID_ANY, wxT("Project Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText37->Wrap( -1 );
	bSizer93->Add( m_staticText37, 1, wxALL, 5 );

	m_projectName_textCtrl = new wxTextCtrl( m_panel12, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer93->Add( m_projectName_textCtrl, 7, wxALL, 5 );


	bSizer93->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer95->Add( bSizer93, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer98;
	bSizer98 = new wxBoxSizer( wxHORIZONTAL );


	bSizer98->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText38 = new wxStaticText( m_panel12, wxID_ANY, wxT("Category"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText38->Wrap( -1 );
	bSizer98->Add( m_staticText38, 1, wxALL, 5 );

	m_category_comboBox = new wxComboBox( m_panel12, wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer98->Add( m_category_comboBox, 7, wxALL, 5 );


	bSizer98->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer95->Add( bSizer98, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer99;
	bSizer99 = new wxBoxSizer( wxHORIZONTAL );


	bSizer99->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText39 = new wxStaticText( m_panel12, wxID_ANY, wxT("Icon"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText39->Wrap( -1 );
	bSizer99->Add( m_staticText39, 1, wxALL, 5 );

	m_icon_filePicker = new wxFilePickerCtrl( m_panel12, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizer99->Add( m_icon_filePicker, 6, wxALL, 5 );


	bSizer99->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer95->Add( bSizer99, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer102;
	bSizer102 = new wxBoxSizer( wxHORIZONTAL );


	bSizer102->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText41 = new wxStaticText( m_panel12, wxID_ANY, wxT("Additional Settings"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	bSizer102->Add( m_staticText41, 1, wxALL, 5 );

	m_enableTerminal_checkBox = new wxCheckBox( m_panel12, wxID_ANY, wxT("Enable Terminal"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer102->Add( m_enableTerminal_checkBox, 2, wxALL, 5 );

	m_enableWebThreads_checkBox = new wxCheckBox( m_panel12, wxID_ANY, wxT("Enable Web Threads (Web Build Only)"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer102->Add( m_enableWebThreads_checkBox, 2, wxALL, 5 );


	bSizer102->Add( 0, 0, 4, wxEXPAND, 5 );


	bSizer95->Add( bSizer102, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer124;
	bSizer124 = new wxBoxSizer( wxHORIZONTAL );


	bSizer124->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText49 = new wxStaticText( m_panel12, wxID_ANY, wxT("Output Dir"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText49->Wrap( -1 );
	bSizer124->Add( m_staticText49, 1, wxALL, 5 );

	m_outputDir_dirPicker = new wxDirPickerCtrl( m_panel12, wxID_ANY, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE );
	bSizer124->Add( m_outputDir_dirPicker, 7, wxALL, 5 );


	bSizer124->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer95->Add( bSizer124, 1, wxEXPAND, 5 );


	m_panel12->SetSizer( bSizer95 );
	m_panel12->Layout();
	bSizer95->Fit( m_panel12 );
	m_notebook4->AddPage( m_panel12, wxT("General Settings"), true );
	m_panel20 = new wxPanel( m_notebook4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer114;
	bSizer114 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer115;
	bSizer115 = new wxBoxSizer( wxHORIZONTAL );


	bSizer115->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText42 = new wxStaticText( m_panel20, wxID_ANY, wxT("Platforms"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText42->Wrap( -1 );
	bSizer115->Add( m_staticText42, 1, wxALL, 5 );

	wxArrayString m_targetPlatforms_checkListChoices;
	m_targetPlatforms_checkList = new wxCheckListBox( m_panel20, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_targetPlatforms_checkListChoices, 0 );
	bSizer115->Add( m_targetPlatforms_checkList, 7, wxALL|wxEXPAND, 5 );


	bSizer115->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer114->Add( bSizer115, 1, wxEXPAND, 5 );


	m_panel20->SetSizer( bSizer114 );
	m_panel20->Layout();
	bSizer114->Fit( m_panel20 );
	m_notebook4->AddPage( m_panel20, wxT("Target Platforms"), false );
	m_panel13 = new wxPanel( m_notebook4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer116;
	bSizer116 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer117;
	bSizer117 = new wxBoxSizer( wxHORIZONTAL );


	bSizer117->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText43 = new wxStaticText( m_panel13, wxID_ANY, wxT("App ID"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText43->Wrap( -1 );
	bSizer117->Add( m_staticText43, 1, wxALL, 5 );

	m_appID_textCtrl = new wxTextCtrl( m_panel13, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer117->Add( m_appID_textCtrl, 7, wxALL, 5 );


	bSizer117->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer116->Add( bSizer117, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer118;
	bSizer118 = new wxBoxSizer( wxHORIZONTAL );


	bSizer118->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText44 = new wxStaticText( m_panel13, wxID_ANY, wxT("Orientation"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText44->Wrap( -1 );
	bSizer118->Add( m_staticText44, 1, wxALL, 5 );

	m_orientation_comboBox = new wxComboBox( m_panel13, wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer118->Add( m_orientation_comboBox, 7, wxALL, 5 );


	bSizer118->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer116->Add( bSizer118, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer119;
	bSizer119 = new wxBoxSizer( wxHORIZONTAL );


	bSizer119->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText45 = new wxStaticText( m_panel13, wxID_ANY, wxT("Keystore"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText45->Wrap( -1 );
	bSizer119->Add( m_staticText45, 1, wxALL, 5 );

	m_keystore_filePicker = new wxFilePickerCtrl( m_panel13, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizer119->Add( m_keystore_filePicker, 7, wxALL, 5 );


	bSizer119->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer116->Add( bSizer119, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer120;
	bSizer120 = new wxBoxSizer( wxHORIZONTAL );


	bSizer120->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText46 = new wxStaticText( m_panel13, wxID_ANY, wxT("Alias"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText46->Wrap( -1 );
	bSizer120->Add( m_staticText46, 1, wxALL, 5 );

	m_alias_textCtrl = new wxTextCtrl( m_panel13, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer120->Add( m_alias_textCtrl, 7, wxALL, 5 );


	bSizer120->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer116->Add( bSizer120, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer121;
	bSizer121 = new wxBoxSizer( wxHORIZONTAL );


	bSizer121->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText47 = new wxStaticText( m_panel13, wxID_ANY, wxT("Password"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText47->Wrap( -1 );
	bSizer121->Add( m_staticText47, 1, wxALL, 5 );

	m_password_textCtrl = new wxTextCtrl( m_panel13, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer121->Add( m_password_textCtrl, 7, wxALL, 5 );


	bSizer121->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer116->Add( bSizer121, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer122;
	bSizer122 = new wxBoxSizer( wxHORIZONTAL );


	bSizer122->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText48 = new wxStaticText( m_panel13, wxID_ANY, wxT("Java Src Path"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText48->Wrap( -1 );
	bSizer122->Add( m_staticText48, 1, wxALL, 5 );

	m_javaPath_dirPicker = new wxDirPickerCtrl( m_panel13, wxID_ANY, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE );
	bSizer122->Add( m_javaPath_dirPicker, 6, wxALL, 5 );

	m_initJavaPath_button = new wxButton( m_panel13, wxID_ANY, wxT("Initialize"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer122->Add( m_initJavaPath_button, 1, wxALL, 5 );


	bSizer122->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer116->Add( bSizer122, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer125;
	bSizer125 = new wxBoxSizer( wxHORIZONTAL );


	bSizer125->Add( 0, 0, 1, wxEXPAND, 5 );

	m_androidDebug_checkBox = new wxCheckBox( m_panel13, wxID_ANY, wxT("Debug"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer125->Add( m_androidDebug_checkBox, 2, wxALL, 5 );

	m_androidRelease_checkBox = new wxCheckBox( m_panel13, wxID_ANY, wxT("Release (Requires Keystore)"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer125->Add( m_androidRelease_checkBox, 2, wxALL, 5 );


	bSizer125->Add( 0, 0, 4, wxEXPAND, 5 );


	bSizer116->Add( bSizer125, 1, wxEXPAND, 5 );


	m_panel13->SetSizer( bSizer116 );
	m_panel13->Layout();
	bSizer116->Fit( m_panel13 );
	m_notebook4->AddPage( m_panel13, wxT("Android Settings"), false );

	bSizer92->Add( m_notebook4, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer109;
	bSizer109 = new wxBoxSizer( wxHORIZONTAL );

	m_saveSettings_button = new wxButton( this, wxID_ANY, wxT("Save Settings"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer109->Add( m_saveSettings_button, 1, wxALL|wxEXPAND, 5 );

	m_makeApp_button = new wxButton( this, wxID_ANY, wxT("Make App"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer109->Add( m_makeApp_button, 1, wxALL|wxEXPAND, 5 );

	m_close_button = new wxButton( this, wxID_ANY, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer109->Add( m_close_button, 1, wxALL|wxEXPAND, 5 );


	bSizer92->Add( bSizer109, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer92 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_initJavaPath_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_distribute_dialog::onInitJavaPathButtonClick ), NULL, this );
	m_saveSettings_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_distribute_dialog::onSaveSettingsButtonClick ), NULL, this );
	m_makeApp_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_distribute_dialog::onMakeAppButtonClick ), NULL, this );
	m_close_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_distribute_dialog::onCloseButtonClick ), NULL, this );
}

rc_distribute_dialog::~rc_distribute_dialog()
{
	// Disconnect Events
	m_initJavaPath_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_distribute_dialog::onInitJavaPathButtonClick ), NULL, this );
	m_saveSettings_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_distribute_dialog::onSaveSettingsButtonClick ), NULL, this );
	m_makeApp_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_distribute_dialog::onMakeAppButtonClick ), NULL, this );
	m_close_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_distribute_dialog::onCloseButtonClick ), NULL, this );

}

rc_distProcess_dialog::rc_distProcess_dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer110;
	bSizer110 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer111;
	bSizer111 = new wxBoxSizer( wxHORIZONTAL );


	bSizer111->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText49 = new wxStaticText( this, wxID_ANY, wxT("Status"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText49->Wrap( -1 );
	bSizer111->Add( m_staticText49, 1, wxALL, 5 );

	m_status_gauge = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	m_status_gauge->SetValue( 0 );
	bSizer111->Add( m_status_gauge, 7, wxALL, 5 );


	bSizer111->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer110->Add( bSizer111, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer112;
	bSizer112 = new wxBoxSizer( wxHORIZONTAL );


	bSizer112->Add( 0, 0, 1, wxEXPAND, 5 );

	m_consoleLog_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	bSizer112->Add( m_consoleLog_textCtrl, 8, wxALL|wxEXPAND, 5 );


	bSizer112->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer110->Add( bSizer112, 7, wxEXPAND, 5 );

	wxBoxSizer* bSizer113;
	bSizer113 = new wxBoxSizer( wxHORIZONTAL );


	bSizer113->Add( 0, 0, 7, wxEXPAND, 5 );

	m_cancel_button = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer113->Add( m_cancel_button, 1, wxALL, 5 );

	m_close_button = new wxButton( this, wxID_ANY, wxT("Finished"), wxDefaultPosition, wxDefaultSize, 0 );
	m_close_button->Enable( false );

	bSizer113->Add( m_close_button, 1, wxALL, 5 );


	bSizer113->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer110->Add( bSizer113, 1, wxEXPAND, 5 );


	bSizer110->Add( 0, 0, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer110 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( rc_distProcess_dialog::onDistProcessUpdateUI ) );
	m_cancel_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_distProcess_dialog::onCancelButtonClick ), NULL, this );
	m_close_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_distProcess_dialog::onCloseButtonClick ), NULL, this );
}

rc_distProcess_dialog::~rc_distProcess_dialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( rc_distProcess_dialog::onDistProcessUpdateUI ) );
	m_cancel_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_distProcess_dialog::onCancelButtonClick ), NULL, this );
	m_close_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_distProcess_dialog::onCloseButtonClick ), NULL, this );

}

rc_cancelDistProcess_dialog::rc_cancelDistProcess_dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer114;
	bSizer114 = new wxBoxSizer( wxVERTICAL );


	bSizer114->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer115;
	bSizer115 = new wxBoxSizer( wxHORIZONTAL );


	bSizer115->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText50 = new wxStaticText( this, wxID_ANY, wxT("Your App is still being packaged.  \nAre you sure you want to cancel?"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText50->Wrap( -1 );
	bSizer115->Add( m_staticText50, 0, wxALL, 5 );


	bSizer115->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer114->Add( bSizer115, 2, wxEXPAND, 5 );

	wxBoxSizer* bSizer116;
	bSizer116 = new wxBoxSizer( wxHORIZONTAL );


	bSizer116->Add( 0, 0, 1, wxEXPAND, 5 );

	m_yes_button = new wxButton( this, wxID_ANY, wxT("Yes"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer116->Add( m_yes_button, 0, wxALL, 5 );

	m_no_button = new wxButton( this, wxID_ANY, wxT("No"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer116->Add( m_no_button, 0, wxALL, 5 );


	bSizer116->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer114->Add( bSizer116, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer114 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_yes_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_cancelDistProcess_dialog::onYesButtonClick ), NULL, this );
	m_no_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_cancelDistProcess_dialog::onNoButtonClick ), NULL, this );
}

rc_cancelDistProcess_dialog::~rc_cancelDistProcess_dialog()
{
	// Disconnect Events
	m_yes_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_cancelDistProcess_dialog::onYesButtonClick ), NULL, this );
	m_no_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rc_cancelDistProcess_dialog::onNoButtonClick ), NULL, this );

}
