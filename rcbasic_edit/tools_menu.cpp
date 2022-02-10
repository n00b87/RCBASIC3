#include "rcbasic_edit_frame.h"
#include "rcbasic_editrc_distribute_dialog.h"
#include "rcbasic_editrc_genKey_dialog.h"

void rcbasic_edit_frame::onDistributeMenuSelect( wxCommandEvent& event )
{
    if(!active_project)
        return;
    notebook_mutex.Lock();
    rcbasic_editrc_distribute_dialog r(this);
    r.ShowModal();
    notebook_mutex.Unlock();
}

void rcbasic_edit_frame::onGenKeystoreMenuSelect( wxCommandEvent& event )
{
    notebook_mutex.Lock();
    rcbasic_editrc_genKey_dialog gk_dialog(this);
    gk_dialog.ShowModal();
    notebook_mutex.Unlock();
}
