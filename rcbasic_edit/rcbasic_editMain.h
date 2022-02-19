/***************************************************************
 * Name:      rcbasic_editMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2022-02-13
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef RCBASIC_EDITMAIN_H
#define RCBASIC_EDITMAIN_H



#include "rcbasic_editApp.h"


#include "GUIFrame.h"

class rcbasic_editFrame: public GUIFrame
{
    public:
        rcbasic_editFrame(wxFrame *frame);
        ~rcbasic_editFrame();
    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
};

#endif // RCBASIC_EDITMAIN_H
