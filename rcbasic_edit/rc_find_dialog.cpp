#include "rc_find_dialog.h"

rcbasic_edit_find_dialog::rcbasic_edit_find_dialog( wxWindow* parent )
:
rc_find_dialog( parent )
{
    frame = (rcbasic_edit_frame*) parent;
    current_project = frame->getActiveProject();
    current_file = frame->getCurrentFile();
}

void rcbasic_edit_find_dialog::onMarkButtonClick( wxCommandEvent& event )
{
// TODO: Implement onMarkButtonClick
    find_dialog_value = find_dialog_value_MARK;
    Close();
}

void rcbasic_edit_find_dialog::onInProjectButtonClick( wxCommandEvent& event )
{
// TODO: Implement onInProjectButtonClick
    find_dialog_value = find_dialog_value_INPROJECT;
    Close();
}

void rcbasic_edit_find_dialog::onInFileButtonClick( wxCommandEvent& event )
{
// TODO: Implement onInFileButtonClick
    find_dialog_value = find_dialog_value_INFILE;
    Close();
}

void rcbasic_edit_find_dialog::onCloseButtonClick( wxCommandEvent& event )
{
// TODO: Implement onCloseButtonClick
    find_dialog_value = find_dialog_value_CLOSE;
    Close();
}

void rcbasic_edit_find_dialog::onPreviousButtonClick( wxCommandEvent& event )
{
// TODO: Implement onPreviousButtonClick
    wxStyledTextCtrl* t = current_file->getTextCtrl();

    if(!t)
        return;

    int previous_pos = t->FindText(t->GetCurrentPos()+1, t->GetLastPosition(), m_search_textCtrl->GetLineText(0));
    if(previous_pos >= 0)
        t->GotoPos(previous_pos);
}

void rcbasic_edit_find_dialog::onNextButtonClick( wxCommandEvent& event )
{
// TODO: Implement onNextButtonClick
}
