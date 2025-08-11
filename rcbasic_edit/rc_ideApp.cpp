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

    wxArrayString args = argv.GetArguments();

    if ( wxsOK )
    {
    	rcbasic_edit_frame* Frame = new rcbasic_edit_frame(0, this->argc, args);
    	#ifdef COS_BASIC
    	Frame->SetTitle(_("Commodore OS BASIC Studio"));
    	#endif // COS_BASIC
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    return wxsOK;

}

int rc_ideApp::OnExit()
{
    #ifdef COS_BASIC
    wxPuts(_("Commodore OS BASIC Shutdown Complete"));
    #else
    wxPuts(_("RCBasic Studio Shutdown Complete"));
    #endif // COS_BASIC
    return 0;
}
