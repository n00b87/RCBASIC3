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
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/filepicker.h>
#include <wx/radiobut.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/checkbox.h>
#include <wx/combobox.h>
#include <wx/listbox.h>

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
		wxMenuItem* m_open_menuItem;
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
		wxMenuItem* m_blockComment_menuItem;
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
		wxMenu* m_build_menu;
		wxMenuItem* m_build_menuItem;
		wxMenuItem* m_run_menuItem;
		wxMenuItem* m_buildRun_menuItem;
		wxMenuItem* m_debugRun_menuItem;
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
		wxTreeCtrl* m_treeCtrl5;
		wxPanel* m_panel6;
		wxAuiNotebook* sourceFile_auinotebook;
		wxPanel* m_panel7;
		wxRichTextCtrl* m_messageWindow_richText;

		// Virtual event handlers, override them in your derived class
		virtual void createNewProject( wxCommandEvent& event ) { event.Skip(); }
		virtual void onSaveProject( wxCommandEvent& event ) { event.Skip(); }
		virtual void onSaveProjectAs( wxCommandEvent& event ) { event.Skip(); }
		virtual void toggleToolbar( wxCommandEvent& event ) { event.Skip(); }
		virtual void toggleSideBar( wxCommandEvent& event ) { event.Skip(); }
		virtual void toggleMessageWindow( wxCommandEvent& event ) { event.Skip(); }
		virtual void onProjectTreeNodeActivated( wxTreeEvent& event ) { event.Skip(); }
		virtual void onProjectTreeContextMenu( wxTreeEvent& event ) { event.Skip(); }
		virtual void onSourceFileTabClose( wxAuiNotebookEvent& event ) { event.Skip(); }


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
			m_project_file_splitter->SetSashPosition( 215 );
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
		wxTextCtrl* m_textCtrl6;
		wxCheckBox* m_checkBox2;
		wxCheckBox* m_checkBox3;
		wxButton* m_button10;
		wxButton* m_button11;
		wxButton* m_button12;
		wxButton* m_button13;
		wxButton* m_button14;
		wxButton* m_button15;

	public:

		rc_find_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Find"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 438,163 ), long style = wxDEFAULT_DIALOG_STYLE );

		~rc_find_dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class rc_replace_dialog
///////////////////////////////////////////////////////////////////////////////
class rc_replace_dialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText11;
		wxTextCtrl* m_textCtrl6;
		wxStaticText* m_staticText15;
		wxTextCtrl* m_textCtrl9;
		wxCheckBox* m_checkBox2;
		wxCheckBox* m_checkBox3;
		wxButton* m_button10;
		wxButton* m_button11;
		wxButton* m_button12;
		wxButton* m_button13;
		wxButton* m_button14;
		wxButton* m_button15;

	public:

		rc_replace_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Find"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 467,202 ), long style = wxDEFAULT_DIALOG_STYLE );

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
		wxTextCtrl* m_textCtrl10;
		wxButton* m_button28;
		wxButton* m_button29;

	public:

		rc_gotoLine_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Go To Line"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 310,118 ), long style = wxDEFAULT_DIALOG_STYLE );

		~rc_gotoLine_dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class rc_changeFont_dialog
///////////////////////////////////////////////////////////////////////////////
class rc_changeFont_dialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText18;
		wxComboBox* m_comboBox1;
		wxStaticText* m_staticText19;
		wxComboBox* m_comboBox2;
		wxStaticText* m_staticText20;
		wxComboBox* m_comboBox3;
		wxStaticText* m_staticText21;
		wxTextCtrl* m_textCtrl11;
		wxButton* m_button30;
		wxButton* m_button31;

	public:

		rc_changeFont_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Font"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 346,280 ), long style = wxDEFAULT_DIALOG_STYLE );

		~rc_changeFont_dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class rc_setColorScheme_dialog
///////////////////////////////////////////////////////////////////////////////
class rc_setColorScheme_dialog : public wxDialog
{
	private:

	protected:
		wxListBox* m_listBox2;
		wxButton* m_button32;

	public:

		rc_setColorScheme_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Color Schemes"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 418,353 ), long style = wxDEFAULT_DIALOG_STYLE );

		~rc_setColorScheme_dialog();

};

