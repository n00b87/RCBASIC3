/***************************************************************
 * Name:      rc_ide2App.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2015-08-18
 * Copyright:  ()
 * License:
 **************************************************************/

//#include "wx_pch.h"
#include "rc_ideApp.h"


#include "rcbasic_edit_frame.h"
#include <wx/image.h>

IMPLEMENT_APP_CONSOLE(rc_ideApp);

bool rc_ideApp::OnInit()
{
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	Frame = new rcbasic_edit_frame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    return wxsOK;

}

int rc_ideApp::OnExit()
{
    wxPuts(_("RCBasic Studio Shutdown Complete"));
    Frame = NULL;
    return 0;
}
