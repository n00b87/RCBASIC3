/***************************************************************
 * Name:      rc_ide2App.h
 * Purpose:   Defines Application Class
 * Author:     ()
 * Created:   2015-08-18
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef RC_IDEAPP_H
#define RC_IDEAPP_H

#include <wx/app.h>
#include "rcbasic_edit_frame.h"

class rc_ideApp : public wxApp
{
    public:
        rcbasic_edit_frame* Frame;
        virtual bool OnInit();
        virtual int OnExit();
};

#endif // RC_IDEAPP_H
