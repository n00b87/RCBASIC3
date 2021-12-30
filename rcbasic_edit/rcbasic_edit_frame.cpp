#include <wx/string.h>

#include "rcbasic_edit_frame.h"
#include "rcbasic_edit_newProject_dialog.h"

rcbasic_edit_frame::rcbasic_edit_frame( wxWindow* parent )
:
rc_ideFrame( parent )
{
    messageWindowVisible = true;
    m_showMessageWindow_menuItem->Check(messageWindowVisible);

    toolbarVisible = true;
    m_showToolbar_menuItem->Check(toolbarVisible);

    sideBarVisible = true;
    m_showSideBar_menuItem->Check(sideBarVisible);
}

void rcbasic_edit_frame::createNewProject( wxCommandEvent& event)
{
    rcbasic_edit_newProject_dialog* newProject_win = new rcbasic_edit_newProject_dialog(this);
    newProject_win->ShowModal();
    newProject_win->Destroy();
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

    //m_messageWindow_panel->Hide();
    //wxSplitterWindow* split = (wxSplitterWindow*)m_messageWindow_panel->GetParent();
    //wxBoxSizer* bsizer = (wxBoxSizer*)split->GetParent();
    //bsizer->Layout();

    //int sashPOS = m_mainView_message_splitter->GetSashPosition();
    //int sashSize = 0;
    //int w, h;
    //this->GetSize(&w, &h);
    //sashSize = h;

    //wxString str, str2;
    //str.Printf(wxT("Sash Position: %d"), sashPOS);
    //str2.Printf(wxT("Sash Size: %d\n"), sashSize);

    //wxPuts(str);
    //wxPuts(str2);
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
