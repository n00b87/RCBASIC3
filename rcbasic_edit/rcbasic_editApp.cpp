/***************************************************************
 * Name:      rcbasic_editApp.cpp
 * Purpose:   Code for Application Class
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

#include "rcbasic_editApp.h"
#include "rcbasic_editMain.h"

IMPLEMENT_APP(rcbasic_editApp);

bool rcbasic_editApp::OnInit()
{
    
    rcbasic_editDialog* dlg = new rcbasic_editDialog(0L);
    
    dlg->Show();
    return true;
}
