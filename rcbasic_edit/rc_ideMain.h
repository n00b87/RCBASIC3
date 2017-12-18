/***************************************************************
 * Name:      rc_ide2Main.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2015-08-18
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef RC_IDEMAIN_H
#define RC_IDEMAIN_H

#include <wx/wx.h>

//(*Headers(rc_ideFrame)
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/aui/aui.h>
#include <wx/toolbar.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

#include <wx/process.h>
#include <wx/stdpaths.h>
#include <wx/stc/stc.h>

#define RC_WINDOWS

class rc_ideFrame: public wxFrame
{
    public:

        rc_ideFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~rc_ideFrame();

    private:

        //(*Handlers(rc_ideFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnNewPage(wxCommandEvent& event);
        void OnPageOpen(wxCommandEvent& event);
        void onSavePage(wxCommandEvent& event);
        void OnSavePageAs(wxCommandEvent& event);
        void OnUndo(wxCommandEvent& event);
        void OnRedo(wxCommandEvent& event);
        void OnCut(wxCommandEvent& event);
        void OnCopy(wxCommandEvent& event);
        void OnPaste(wxCommandEvent& event);
        void OnDelete(wxCommandEvent& event);
        void OnCompile(wxCommandEvent& event);
        void OnRun(wxCommandEvent& event);
        void OnReference(wxCommandEvent& event);
        void OnDocumentKey(wxStyledTextEvent& event);
        void OnStop(wxCommandEvent& event);
        //*)

        //(*Identifiers(rc_ideFrame)
        static const long ID_AUINOTEBOOK1;
        static const long newID;
        static const long openID;
        static const long saveID;
        static const long saveAsID;
        static const long idMenuQuit;
        static const long undoID;
        static const long redoID;
        static const long cutID;
        static const long copyID;
        static const long pasteID;
        static const long deleteID;
        static const long compileID;
        static const long runID;
        static const long idMenuAbout;
        static const long referenceID;
        static const long ID_STATUSBAR1;
        static const long toolNewID;
        static const long toolOpenID;
        static const long toolSaveID;
        static const long toolSaveAsID;
        static const long toolRunID;
        static const long toolStopID;
        static const long ID_TOOLBAR1;
        //*)

        //(*Declarations(rc_ideFrame)
        wxToolBarToolBase* ToolBarItem4;
        wxMenuItem* MenuItem8;
        wxToolBar* ToolBar1;
        wxMenuItem* MenuItem7;
        wxToolBarToolBase* ToolBarItem3;
        wxMenuItem* MenuItem5;
        wxMenu* Menu3;
        wxMenuItem* MenuItem4;
        wxMenuItem* MenuItem14;
        wxMenuItem* MenuItem11;
        wxMenuItem* MenuItem15;
        wxMenuItem* MenuItem13;
        wxMenuItem* MenuItem10;
        wxToolBarToolBase* ToolBarItem6;
        wxMenuItem* MenuItem12;
        wxToolBarToolBase* ToolBarItem1;
        wxMenuItem* MenuItem3;
        wxStatusBar* StatusBar1;
        wxMenuItem* MenuItem6;
        wxAuiNotebook* AuiNotebook1;
        wxToolBarToolBase* ToolBarItem5;
        wxMenuItem* MenuItem9;
        wxToolBarToolBase* ToolBarItem2;
        wxMenu* Menu4;
        //*)

        DECLARE_EVENT_TABLE()
};

class MyProcess : public wxProcess
{
public:
    MyProcess(rc_ideFrame *parent)
        : wxProcess(parent)//, m_cmd(cmd)
    {
        m_parent = parent;
    }

    // instead of overriding this virtual function we might as well process the
    // event from it in the frame class - this might be more convenient in some
    // cases
    virtual void OnTerminate(int pid, int status)
    {
        wxString editor_path = wxStandardPaths::Get().GetExecutablePath();
        #ifndef RC_WINDOWS
        editor_path = editor_path.substr(0, editor_path.find_last_of(_("/"))) +_("/");
        #else
        editor_path = editor_path.substr(0, editor_path.find_last_of(_("\\"))) +_("\\");
        #endif // RC_WINDOWS
        wxSetWorkingDirectory(editor_path);
    }

protected:
    rc_ideFrame *m_parent;
    //wxString m_cmd;
};
#endif // RC_IDEMAIN_H
