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
		wxMenuItem* m_findInFiles_menuItem;
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
		wxTreeCtrl* m_treeCtrl6;
		wxPanel* m_;
		wxTreeCtrl* m_treeCtrl5;
		wxPanel* m_panel6;
		wxAuiNotebook* m_auinotebook1;
		wxPanel* m_panel7;
		wxRichTextCtrl* m_messageWindow_richText;

		// Virtual event handlers, override them in your derived class
		virtual void createNewProject( wxCommandEvent& event ) { event.Skip(); }
		virtual void toggleToolbar( wxCommandEvent& event ) { event.Skip(); }
		virtual void toggleSideBar( wxCommandEvent& event ) { event.Skip(); }
		virtual void toggleMessageWindow( wxCommandEvent& event ) { event.Skip(); }


	public:

		rc_ideFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1163,723 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

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
		wxTextCtrl* projectName_field;
		wxStaticText* projectLocation_label;
		wxDirPickerCtrl* projectLocation_picker;
		wxRadioButton* projectCreateMain_radio;
		wxStaticText* projectNewMain_label;
		wxTextCtrl* projectNewMain_field;
		wxRadioButton* projectExistingMain_radio;
		wxStaticText* projectPathToExistingMain_label;
		wxFilePickerCtrl* projectExistingFile_picker;
		wxStaticText* projectAuthor_label;
		wxTextCtrl* projectAuthor_field;
		wxStaticText* projectWebsite_label;
		wxTextCtrl* projectWebsite_field;
		wxStaticText* projectDescription_label;
		wxTextCtrl* projectDescription_field;
		wxButton* cancelNewProject_button;
		wxButton* createNewProject_button;

		// Virtual event handlers, override them in your derived class
		virtual void createMainSourceRadioSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void copyExistingSourceRadioSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void cancelNewProject( wxCommandEvent& event ) { event.Skip(); }
		virtual void createNewProject( wxCommandEvent& event ) { event.Skip(); }


	public:

		rc_newProject_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("New Project"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 464,562 ), long style = wxDEFAULT_DIALOG_STYLE );

		~rc_newProject_dialog();

};

