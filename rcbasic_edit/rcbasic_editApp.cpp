/***************************************************************
 * Name:      rcbasic_editApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2022-02-13
 * Copyright:  ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "rcbasic_editApp.h"
#include "rcbasic_editMain.h"

IMPLEMENT_APP(rcbasic_editApp);

bool rcbasic_editApp::OnInit()
{
    rcbasic_editFrame* frame = new rcbasic_editFrame(0L);
    
    frame->Show();
    
    return true;
}
