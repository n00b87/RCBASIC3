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

//(*AppHeaders
#include "rc_ideMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP_CONSOLE(rc_ideApp);

bool rc_ideApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	rc_ideFrame* Frame = new rc_ideFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
