/***************************************************************
 * Name:      rcbasic_editMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2023-02-06
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef RCBASIC_EDITMAIN_H
#define RCBASIC_EDITMAIN_H



#include "rcbasic_editApp.h"



#include "GUIDialog.h"

class rcbasic_editDialog: public GUIDialog
{
    public:
        rcbasic_editDialog(wxDialog *dlg);
        ~rcbasic_editDialog();
    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
};
#endif // RCBASIC_EDITMAIN_H
