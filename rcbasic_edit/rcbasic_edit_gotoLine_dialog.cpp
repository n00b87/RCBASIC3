#include "rcbasic_edit_gotoLine_dialog.h"

rcbasic_edit_gotoLine_dialog::rcbasic_edit_gotoLine_dialog( wxWindow* parent )
:
rc_gotoLine_dialog( parent )
{
    parent_frame = (rcbasic_edit_frame*) parent;
    current_file = parent_frame->getCurrentFile();
    if(!current_file)
        Close();
}

void rcbasic_edit_gotoLine_dialog::onCancelButtonClick( wxCommandEvent& event )
{
    Close();
}

void rcbasic_edit_gotoLine_dialog::onOKButtonClick( wxCommandEvent& event )
{
    if(!current_file)
        return;

    wxStyledTextCtrl* t = current_file->getTextCtrl();
    if(!t)
        return;

    wxTextCtrl* goto_txt = m_goto_textCtrl;

    long line_num = 0;
    goto_txt->GetValue().ToLong(&line_num);
    line_num = line_num - 1;

    t->GotoLine(line_num);
    t->SetSelection(t->GetCurrentPos(), t->GetCurrentPos() + t->GetLineText(line_num).length());
    Close();
}
