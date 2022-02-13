///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/toolbar.h>
#include <wx/treectrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/aui/auibook.h>
#include <wx/splitter.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/listbox.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/filepicker.h>
#include <wx/radiobut.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/checkbox.h>
#include <wx/collpane.h>
#include <wx/listctrl.h>
#include <wx/combobox.h>
#include <wx/checklst.h>
#include <wx/gauge.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class rc_ideFrame
///////////////////////////////////////////////////////////////////////////////
class rc_ideFrame : public wxFrame
{
	private:

	protected:
		wxMenuBar* m_menubar1;
		wxMenu* m_file_menu;
		wxMenu* m_new_menu;
		wxMenuItem* m_newProject_menuItem;
		wxMenuItem* m_newFile_menuItem;
		wxMenu* m_open_menu;
		wxMenuItem* m_openProject_menuItem;
		wxMenu* m_recentProjects_menu;
		wxMenu* m_recentFiles_menu;
		wxMenuItem* m_saveFile_menuItem;
		wxMenuItem* m_saveFileAs_menuItem;
		wxMenuItem* m_saveProject_menuItem;
		wxMenuItem* m_saveProjectAs_menuItem;
		wxMenuItem* m_saveAll_menuItem;
		wxMenuItem* m_closeFile_menuItem;
		wxMenuItem* m_closeProject_menuItem;
		wxMenuItem* m_closeAll_menuItem;
		wxMenuItem* m_exit_menuItem;
		wxMenu* m_edit_menu;
		wxMenuItem* m_undo_menuItem;
		wxMenuItem* m_redo_menuItem;
		wxMenuItem* m_cut_menuItem;
		wxMenuItem* m_copy_menuItem;
		wxMenuItem* m_paste_menuItem;
		wxMenuItem* m_delete_menuItem;
		wxMenuItem* m_comment_menuItem;
		wxMenu* m_search_menu;
		wxMenuItem* m_find_menuItem;
		wxMenuItem* m_findNext_menuItem;
		wxMenuItem* m_findPrevious_menuItem;
		wxMenuItem* m_replace_menuItem;
		wxMenuItem* m_goto_menuItem;
		wxMenu* m_view_menu;
		wxMenuItem* m_changeFont_menuItem;
		wxMenuItem* m_changeColors_menuItem;
		wxMenuItem* m_showToolbar_menuItem;
		wxMenuItem* m_showSideBar_menuItem;
		wxMenuItem* m_showMessageWindow_menuItem;
		wxMenuItem* m_zoomIn_menuItem;
		wxMenuItem* m_zoomOut_menuItem;
		wxMenuItem* m_normalSize_menuItem;
		wxMenu* m_project_menu;
		wxMenu* m_build_menu;
		wxMenuItem* m_build_menuItem;
		wxMenuItem* m_run_menuItem;
		wxMenuItem* m_buildRun_menuItem;
		wxMenuItem* m_abort_menuItem;
		wxMenu* m_tools_menu;
		wxMenuItem* m_genKeystore_menuItem;
		wxMenuItem* m_distribute_menuItem;
		wxMenu* m_help_menu;
		wxMenuItem* m_doc_menuItem;
		wxMenuItem* m_editorManual_menuItem;
		wxMenuItem* m_about_menuItem;
		wxBoxSizer* mainWindowSizer;
		wxToolBar* m_toolBar;
		wxToolBarToolBase* m_new_tool;
		wxToolBarToolBase* m_open_tool;
		wxToolBarToolBase* m_save_tool;
		wxToolBarToolBase* m_saveas_tool;
		wxToolBarToolBase* m_run_tool;
		wxToolBarToolBase* m_abort_tool;
		wxBoxSizer* projectViewSizer;
		wxSplitterWindow* m_mainView_message_splitter;
		wxPanel* m_panel61;
		wxBoxSizer* projectFileSizer;
		wxSplitterWindow* m_project_file_splitter;
		wxPanel* m_sideBar_panel;
		wxNotebook* m_notebook4;
		wxPanel* m_project_panel;
		wxTreeCtrl* project_tree;
		wxPanel* m_;
		wxTreeCtrl* symbol_tree;
		wxPanel* m_panel6;
		wxAuiNotebook* sourceFile_auinotebook;
		wxPanel* m_panel7;
		wxNotebook* m_results_notebook;
		wxPanel* m_buildLog_panel;
		wxRichTextCtrl* m_messageWindow_richText;
		wxPanel* m_searchResults_panel;
		wxListBox* m_searchResults_listBox;
		wxStatusBar* m_statusBar;

		// Virtual event handlers, override them in your derived class
		virtual void onEditorClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void onEditorIdle( wxIdleEvent& event ) { event.Skip(); }
		virtual void onEditorUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void newProjectMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void newFileMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void openProjectMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void openFileMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onSaveFileMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onSaveFileAsMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onSaveProjectMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onSaveProjectAsMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onSaveAllMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onCloseFileMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onCloseProjectMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onCloseAllMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onExitMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onUndoMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onRedoMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onCutMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onCopyMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onPasteMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onDeleteMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onCommentMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onUnCommentMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onFindMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onFindNextMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onFindPreviousMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onReplaceMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onGotoMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onChangeFontMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onChangeSchemeMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void toggleToolbar( wxCommandEvent& event ) { event.Skip(); }
		virtual void toggleSideBar( wxCommandEvent& event ) { event.Skip(); }
		virtual void toggleMessageWindow( wxCommandEvent& event ) { event.Skip(); }
		virtual void onZoomInMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onZoomOutMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onNormalSizeMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onProjectSettingsMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onProjectEnvironmentMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onBuildMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onRunMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onBuildRunMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onStopExecuteMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onGenKeystoreMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onDistributeMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onDocMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onEditorManualMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onAboutMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void onProjectTreeNodeActivated( wxTreeEvent& event ) { event.Skip(); }
		virtual void onProjectTreeContextMenu( wxTreeEvent& event ) { event.Skip(); }
		virtual void onProjectTreeSelectionChanged( wxTreeEvent& event ) { event.Skip(); }
		virtual void onProjectTreeSelectionChanging( wxTreeEvent& event ) { event.Skip(); }
		virtual void onSymbolSelectionChanged( wxTreeEvent& event ) { event.Skip(); }
		virtual void onSymbolSelectionChanging( wxTreeEvent& event ) { event.Skip(); }
		virtual void onNotebookPageChanged( wxAuiNotebookEvent& event ) { event.Skip(); }
		virtual void onSourceFileTabClose( wxAuiNotebookEvent& event ) { event.Skip(); }
		virtual void onSearchResultSelection( wxCommandEvent& event ) { event.Skip(); }


	public:

		rc_ideFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("RCBasic Studio"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1163,723 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~rc_ideFrame();

		void m_mainView_message_splitterOnIdle( wxIdleEvent& )
		{
			m_mainView_message_splitter->SetSashPosition( 500 );
			m_mainView_message_splitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( rc_ideFrame::m_mainView_message_splitterOnIdle ), NULL, this );
		}

		void m_project_file_splitterOnIdle( wxIdleEvent& )
		{
			m_project_file_splitter->SetSashPosition( 221 );
			m_project_file_splitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( rc_ideFrame::m_project_file_splitterOnIdle ), NULL, this );
		}

};

///////////////////////////////////////////////////////////////////////////////
/// Class rc_newProject_dialog
///////////////////////////////////////////////////////////////////////////////
class rc_newProject_dialog : public wxDialog
{
	private:

	protected:
		wxStaticText* projectName_label;
		wxStaticText* projectLocation_label;
		wxStaticText* projectNewMain_label;
		wxStaticText* projectPathToExistingMain_label;
		wxStaticText* projectAuthor_label;
		wxStaticText* projectWebsite_label;
		wxStaticText* projectDescription_label;

		// Virtual event handlers, override them in your derived class
		virtual void createMainSourceRadioSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void copyExistingSourceRadioSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void cancelNewProject( wxCommandEvent& event ) { event.Skip(); }
		virtual void createNewProject( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxTextCtrl* projectName_field;
		wxDirPickerCtrl* projectLocation_picker;
		wxRadioButton* projectCreateMain_radio;
		wxTextCtrl* projectNewMain_field;
		wxRadioButton* projectExistingMain_radio;
		wxFilePickerCtrl* projectExistingFile_picker;
		wxTextCtrl* projectAuthor_field;
		wxTextCtrl* projectWebsite_field;
		wxTextCtrl* projectDescription_field;
		wxButton* cancelNewProject_button;
		wxButton* createNewProject_button;

		rc_newProject_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("New Project"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 464,562 ), long style = wxDEFAULT_DIALOG_STYLE );

		~rc_newProject_dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class rc_closeProjectSavePrompt_dialog
///////////////////////////////////////////////////////////////////////////////
class rc_closeProjectSavePrompt_dialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText8;
		wxButton* closeProjectSave_cancelButton;
		wxButton* closeProjectSave_dontSaveButton;
		wxButton* closeProjectSave_saveButton;

		// Virtual event handlers, override them in your derived class
		virtual void onCloseProjectSaveCancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void onCloseProjectSaveDontSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void onCloseProjectSaveOk( wxCommandEvent& event ) { event.Skip(); }


	public:

		rc_closeProjectSavePrompt_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 385,149 ), long style = wxDEFAULT_DIALOG_STYLE|wxSTAY_ON_TOP );

		~rc_closeProjectSavePrompt_dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class rc_newFile_dialog
///////////////////////////////////////////////////////////////////////////////
class rc_newFile_dialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText9;
		wxFilePickerCtrl* createNewSource_fileDialog;
		wxCheckBox* createNewSource_addToProject_checkBox;
		wxButton* createNewSource_cancelButton;
		wxButton* createNewSource_okButton;

		// Virtual event handlers, override them in your derived class
		virtual void onCreateNewSourceCancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void onCreateNewSourceOk( wxCommandEvent& event ) { event.Skip(); }


	public:

		rc_newFile_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Create New Source File"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 497,200 ), long style = wxDEFAULT_DIALOG_STYLE );

		~rc_newFile_dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class rc_find_dialog
///////////////////////////////////////////////////////////////////////////////
class rc_find_dialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText11;
		wxCheckBox* m_caseSensitive_checkBox;
		wxCheckBox* m_matchWhole_checkBox;
		wxButton* m_mark_button;
		wxButton* m_inProject_button;
		wxButton* m_inFile_button;
		wxButton* m_close_button;
		wxButton* m_previous_button;
		wxButton* m_next_button;

		// Virtual event handlers, override them in your derived class
		virtual void onMarkButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onInProjectButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onInFileButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onCloseButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onPreviousButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onNextButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxTextCtrl* m_search_textCtrl;

		rc_find_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Find"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 438,163 ), long style = wxDEFAULT_DIALOG_STYLE );

		~rc_find_dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class rc_searchWrap_dialog
///////////////////////////////////////////////////////////////////////////////
class rc_searchWrap_dialog : public wxDialog
{
	private:

	protected:
		wxButton* searchWrap_cancelButton;
		wxButton* searchWrap_okButton;

		// Virtual event handlers, override them in your derived class
		virtual void onSearchWrapCancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void onSearchWrapOk( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxStaticText* m_searchWrapPrompt_staticText;

		rc_searchWrap_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Search"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 385,149 ), long style = wxDEFAULT_DIALOG_STYLE|wxSTAY_ON_TOP );

		~rc_searchWrap_dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class rc_replace_dialog
///////////////////////////////////////////////////////////////////////////////
class rc_replace_dialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText11;
		wxTextCtrl* m_search_textCtrl;
		wxStaticText* m_staticText15;
		wxTextCtrl* m_replace_textCtrl;
		wxCheckBox* m_caseSensitive_checkBox;
		wxCheckBox* m_matchWhole_checkBox;
		wxCollapsiblePane* m_collapsiblePane1;
		wxButton* m_replaceInProject_button;
		wxButton* m_replaceInFile_button;
		wxButton* m_replaceInSelection_button;
		wxButton* m_find_button;
		wxButton* m_button29;
		wxButton* m_button13;

		// Virtual event handlers, override them in your derived class
		virtual void onReplaceInProjectClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onReplaceInFileClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onReplaceInSelectionClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onFindNextClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onReplaceClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onReplaceCloseClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		rc_replace_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Replace"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 467,238 ), long style = wxDEFAULT_DIALOG_STYLE );

		~rc_replace_dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class rc_gotoLine_dialog
///////////////////////////////////////////////////////////////////////////////
class rc_gotoLine_dialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText17;
		wxTextCtrl* m_goto_textCtrl;
		wxButton* m_button28;
		wxButton* m_button29;

		// Virtual event handlers, override them in your derived class
		virtual void onCancelButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onOKButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		rc_gotoLine_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Go To Line"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 310,118 ), long style = wxDEFAULT_DIALOG_STYLE );

		~rc_gotoLine_dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class rc_closeFileSavePrompt_dialog
///////////////////////////////////////////////////////////////////////////////
class rc_closeFileSavePrompt_dialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText8;
		wxButton* closeFileSave_cancelButton;
		wxButton* closeFileSave_dontSaveButton;
		wxButton* closeFileSave_saveButton;

		// Virtual event handlers, override them in your derived class
		virtual void onCloseFileSaveCancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void onCloseFileSaveDontSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void onCloseFileSaveOk( wxCommandEvent& event ) { event.Skip(); }


	public:

		rc_closeFileSavePrompt_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Close File"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 385,149 ), long style = wxDEFAULT_DIALOG_STYLE|wxSTAY_ON_TOP );

		~rc_closeFileSavePrompt_dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class rc_setColorScheme_dialog
///////////////////////////////////////////////////////////////////////////////
class rc_setColorScheme_dialog : public wxDialog
{
	private:

	protected:
		wxListBox* m_scheme_listBox;
		wxButton* m_schemeClose_button;

		// Virtual event handlers, override them in your derived class
		virtual void onSchemeSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void onSchemeCloseButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		rc_setColorScheme_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Color Schemes"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 418,353 ), long style = wxDEFAULT_DIALOG_STYLE );

		~rc_setColorScheme_dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class rc_projectSettings_dialog
///////////////////////////////////////////////////////////////////////////////
class rc_projectSettings_dialog : public wxDialog
{
	private:

	protected:
		wxNotebook* m_notebook3;
		wxPanel* m_panel9;
		wxStaticText* m_staticText16;
		wxTextCtrl* m_projectName_textCtrl;
		wxStaticText* m_staticText17;
		wxTextCtrl* m_mainSource_textCtrl;
		wxListBox* m_mainSource_listBox;
		wxStaticText* m_staticText18;
		wxTextCtrl* m_author_textCtrl;
		wxStaticText* m_staticText19;
		wxTextCtrl* m_website_textCtrl;
		wxStaticText* m_staticText20;
		wxTextCtrl* m_description_textCtrl;
		wxPanel* m_panel10;
		wxListBox* m_files_listBox;
		wxButton* m_addFile_button;
		wxButton* m_removeFile_button;
		wxButton* m_fileProperties_button;
		wxPanel* m_panel11;
		wxButton* m_cancel_button;
		wxButton* m_ok_button;

		// Virtual event handlers, override them in your derived class
		virtual void onMainSourceListBoxSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void onFileSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void onFileDoubleClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onAddFilesButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onRemoveSelectedButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onFilePropertiesButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onCancelButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onOKButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		rc_projectSettings_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Project Properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 517,553 ), long style = wxDEFAULT_DIALOG_STYLE );

		~rc_projectSettings_dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class rc_fileProperties_dialog
///////////////////////////////////////////////////////////////////////////////
class rc_fileProperties_dialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText21;
		wxTextCtrl* m_fileName_textCtrl;
		wxStaticText* m_staticText23;
		wxRadioButton* m_relative_radioBtn;
		wxRadioButton* m_absolute_radioBtn;
		wxButton* m_cancel_button;
		wxButton* m_ok_button;

		// Virtual event handlers, override them in your derived class
		virtual void onCancelButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onOKButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		rc_fileProperties_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("File Properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 494,185 ), long style = wxDEFAULT_DIALOG_STYLE );

		~rc_fileProperties_dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class rc_projectEnvironment_dialog
///////////////////////////////////////////////////////////////////////////////
class rc_projectEnvironment_dialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText24;
		wxStaticText* m_projectName_staticText;
		wxListCtrl* m_environment_listCtrl;
		wxButton* m_clearAll_button;
		wxButton* m_removeSelected_button;
		wxButton* m_addVariable_button;
		wxButton* m_editVariable_button;
		wxButton* m_cancel_button;
		wxButton* m_ok_button;

		// Virtual event handlers, override them in your derived class
		virtual void onClearAllButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onRemoveSelectedButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onAddVariableButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onEditVariableButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onCancelButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onOKButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		rc_projectEnvironment_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Project Environment Settings"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 487,298 ), long style = wxDEFAULT_DIALOG_STYLE );

		~rc_projectEnvironment_dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class rc_projectVariableEdit_dialog
///////////////////////////////////////////////////////////////////////////////
class rc_projectVariableEdit_dialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText25;
		wxTextCtrl* m_variable_textCtrl;
		wxStaticText* m_staticText26;
		wxTextCtrl* m_value_textCtrl;
		wxButton* m_cancel_button;
		wxButton* m_ok_button;

		// Virtual event handlers, override them in your derived class
		virtual void onCancelButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onOKButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		rc_projectVariableEdit_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 489,176 ), long style = wxDEFAULT_DIALOG_STYLE );

		~rc_projectVariableEdit_dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class rc_genKey_dialog
///////////////////////////////////////////////////////////////////////////////
class rc_genKey_dialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText27;
		wxTextCtrl* m_keystore_textCtrl;
		wxStaticText* m_staticText28;
		wxTextCtrl* m_alias_textCtrl;
		wxStaticText* m_staticText29;
		wxTextCtrl* m_password_textCtrl;
		wxStaticText* m_staticText30;
		wxTextCtrl* m_confirmPassword_textCtrl;
		wxStaticText* m_staticText31;
		wxTextCtrl* m_name_textCtrl;
		wxStaticText* m_staticText32;
		wxTextCtrl* m_orgUnit_textCtrl;
		wxStaticText* m_staticText33;
		wxTextCtrl* m_org_textCtrl;
		wxStaticText* m_staticText34;
		wxTextCtrl* m_city_textCtrl;
		wxStaticText* m_staticText35;
		wxTextCtrl* m_state_textCtrl;
		wxStaticText* m_staticText36;
		wxTextCtrl* m_country_textCtrl;
		wxButton* m_ok_button;
		wxButton* m_cancel_button;

		// Virtual event handlers, override them in your derived class
		virtual void onOKButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onCancelButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		rc_genKey_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Generate Keystore"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 639,552 ), long style = wxDEFAULT_DIALOG_STYLE );

		~rc_genKey_dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class rc_distribute_dialog
///////////////////////////////////////////////////////////////////////////////
class rc_distribute_dialog : public wxDialog
{
	private:

	protected:
		wxNotebook* m_notebook4;
		wxPanel* m_panel12;
		wxStaticText* m_staticText37;
		wxTextCtrl* m_projectName_textCtrl;
		wxStaticText* m_staticText38;
		wxComboBox* m_category_comboBox;
		wxStaticText* m_staticText39;
		wxFilePickerCtrl* m_icon_filePicker;
		wxStaticText* m_staticText41;
		wxCheckBox* m_enableTerminal_checkBox;
		wxCheckBox* m_enableWebThreads_checkBox;
		wxStaticText* m_staticText49;
		wxDirPickerCtrl* m_outputDir_dirPicker;
		wxPanel* m_panel20;
		wxStaticText* m_staticText42;
		wxCheckListBox* m_targetPlatforms_checkList;
		wxPanel* m_panel13;
		wxStaticText* m_staticText43;
		wxTextCtrl* m_appID_textCtrl;
		wxStaticText* m_staticText44;
		wxComboBox* m_orientation_comboBox;
		wxStaticText* m_staticText45;
		wxFilePickerCtrl* m_keystore_filePicker;
		wxStaticText* m_staticText46;
		wxTextCtrl* m_alias_textCtrl;
		wxStaticText* m_staticText47;
		wxTextCtrl* m_password_textCtrl;
		wxStaticText* m_staticText48;
		wxDirPickerCtrl* m_javaPath_dirPicker;
		wxButton* m_initJavaPath_button;
		wxCheckBox* m_androidDebug_checkBox;
		wxCheckBox* m_androidRelease_checkBox;
		wxButton* m_saveSettings_button;
		wxButton* m_makeApp_button;
		wxButton* m_close_button;

		// Virtual event handlers, override them in your derived class
		virtual void onInitJavaPathButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onSaveSettingsButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onMakeAppButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onCloseButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		rc_distribute_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Distribute"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 576,359 ), long style = wxDEFAULT_DIALOG_STYLE );

		~rc_distribute_dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class rc_distProcess_dialog
///////////////////////////////////////////////////////////////////////////////
class rc_distProcess_dialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText49;
		wxGauge* m_status_gauge;
		wxTextCtrl* m_consoleLog_textCtrl;
		wxButton* m_cancel_button;
		wxButton* m_close_button;

		// Virtual event handlers, override them in your derived class
		virtual void onDistProcessUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void onCancelButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onCloseButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		rc_distProcess_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Building Application"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 655,330 ), long style = wxCAPTION );

		~rc_distProcess_dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class rc_cancelDistProcess_dialog
///////////////////////////////////////////////////////////////////////////////
class rc_cancelDistProcess_dialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText50;
		wxButton* m_yes_button;
		wxButton* m_no_button;

		// Virtual event handlers, override them in your derived class
		virtual void onYesButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onNoButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		rc_cancelDistProcess_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Cancel Building App"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 389,150 ), long style = wxCAPTION|wxSTAY_ON_TOP );

		~rc_cancelDistProcess_dialog();

};

