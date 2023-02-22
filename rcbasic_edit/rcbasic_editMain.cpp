/***************************************************************
 * Name:      rcbasic_editMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2023-02-06
 * Copyright:  ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "rcbasic_editMain.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}



rcbasic_editDialog::rcbasic_editDialog(wxDialog *dlg)
    : GUIDialog(dlg)
{
}

rcbasic_editDialog::~rcbasic_editDialog()
{
}

void rcbasic_editDialog::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void rcbasic_editDialog::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void rcbasic_editDialog::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}
