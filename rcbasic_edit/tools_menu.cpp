#include "rcbasic_edit_frame.h"
#include "rcbasic_editrc_distribute_dialog.h"

void rcbasic_edit_frame::onDistributeMenuSelect( wxCommandEvent& event )
{
    if(!active_project)
        return;
    notebook_mutex.Lock();
    rcbasic_editrc_distribute_dialog r(this);
    r.ShowModal();
    notebook_mutex.Unlock();
}
