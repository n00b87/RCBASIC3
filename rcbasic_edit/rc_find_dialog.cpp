#include "rc_find_dialog.h"

rcbasic_edit_find_dialog::rcbasic_edit_find_dialog( wxWindow* parent )
:
rc_find_dialog( parent )
{
    parent_frame = (rcbasic_edit_frame*) parent;
    current_project = parent_frame->getActiveProject();
    current_file = parent_frame->getCurrentFile();
    wxString selected_text = current_file->getTextCtrl()->GetSelectedText();
    if(selected_text.Length() > 0 && selected_text.Length() <= 80)
        m_search_textCtrl->SetValue(current_file->getTextCtrl()->GetSelectedText());
    else
        m_search_textCtrl->SetValue(parent_frame->search_term);
    find_dialog_flags = 0;
}

int rcbasic_edit_find_dialog::getValue()
{
    return find_dialog_value;
}

int rcbasic_edit_find_dialog::getFlags()
{
    return find_dialog_flags;
}

wxString rcbasic_edit_find_dialog::getSearchText()
{
    return search_text;
}

void rcbasic_edit_find_dialog::onMarkButtonClick( wxCommandEvent& event )
{
// TODO: Implement onMarkButtonClick
    find_dialog_value = find_dialog_value_MARK;

    if(!current_file)
        return;

    wxStyledTextCtrl* t = current_file->getTextCtrl();

    if(!t)
        return;

    int flag = m_matchWhole_checkBox->GetValue() ? wxSTC_FIND_WHOLEWORD : 0;
    flag = m_caseSensitive_checkBox->GetValue() ? (flag | wxSTC_FIND_MATCHCASE) : flag;

    find_dialog_flags = flag;

    wxString selText= m_search_textCtrl->GetLineText(0);
    int selLen = selText.Len();
    int selStart= 0;

    int totalLen = t->GetTextLength();
    int searchStart=0;
    int foundLoc = 0;

    t->SetSearchFlags(flag);

    t->IndicatorSetStyle(8,wxSTC_INDIC_STRAIGHTBOX);
    t->SetIndicatorCurrent(8);
    t->IndicatorSetForeground(8, wxColour(255,128,0) );
    t->IndicatorClearRange(0,totalLen);

    while(foundLoc!=-1)
    {
        t->SetTargetStart(searchStart);
        t->SetTargetEnd(totalLen);

        foundLoc= t->SearchInTarget(selText);
        searchStart= foundLoc+selLen;

        if(foundLoc!=-1)
        {
            t->IndicatorFillRange(foundLoc,selLen);
        }
    }

    //t->IndicatorClearRange(0, t->GetTextLength());


    Close();
}

void rcbasic_edit_find_dialog::onInProjectButtonClick( wxCommandEvent& event )
{
// TODO: Implement onInProjectButtonClick
    find_dialog_value = find_dialog_value_INPROJECT;

    int flag = m_matchWhole_checkBox->GetValue() ? wxSTC_FIND_WHOLEWORD : 0;
    flag = m_caseSensitive_checkBox->GetValue() ? (flag | wxSTC_FIND_MATCHCASE) : flag;

    find_dialog_flags = flag;
    search_text = m_search_textCtrl->GetLineText(0);

    Close();
}

void rcbasic_edit_find_dialog::onInFileButtonClick( wxCommandEvent& event )
{
// TODO: Implement onInFileButtonClick
    find_dialog_value = find_dialog_value_INFILE;

    int flag = m_matchWhole_checkBox->GetValue() ? wxSTC_FIND_WHOLEWORD : 0;
    flag = m_caseSensitive_checkBox->GetValue() ? (flag | wxSTC_FIND_MATCHCASE) : flag;

    find_dialog_flags = flag;
    search_text = m_search_textCtrl->GetLineText(0);

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
    if(!current_file)
        return;

    wxStyledTextCtrl* t = current_file->getTextCtrl();

    if(!t)
        return;

    //int previous_pos = t->FindText(t->GetCurrentPos()+1, t->GetLastPosition(), m_search_textCtrl->GetLineText(0));
    int flag = m_matchWhole_checkBox->GetValue() ? wxSTC_FIND_WHOLEWORD : 0;
    flag = m_caseSensitive_checkBox->GetValue() ? (flag | wxSTC_FIND_MATCHCASE) : flag;
    t->SearchAnchor();
    int previous_pos = t->SearchPrev(flag, m_search_textCtrl->GetLineText(0));
    //wxPrintf(_("Prev POS = %d\n"), previous_pos);
    if(previous_pos >= 0)
    {
        t->GotoPos(previous_pos);
        t->SetSelection(t->GetCurrentPos(), t->GetCurrentPos() + m_search_textCtrl->GetLineText(0).length());
    }
}

void rcbasic_edit_find_dialog::onNextButtonClick( wxCommandEvent& event )
{
// TODO: Implement onFindNextClick

    if(!current_file)
        return;

    wxStyledTextCtrl* t = current_file->getTextCtrl();

    if(!t)
        return;

    //int previous_pos = t->FindText(t->GetCurrentPos()+1, t->GetLastPosition(), m_search_textCtrl->GetLineText(0));
    if(m_search_textCtrl->GetLineText(0).compare(search_text)!=0 || current_search_pos < 0)
    {
        search_text = m_search_textCtrl->GetLineText(0);
        current_search_pos = 0;
    }

    t->SetTargetStart(current_search_pos);
    t->SetTargetEnd(t->GetTextLength());

    int flag = m_matchWhole_checkBox->GetValue() ? wxSTC_FIND_WHOLEWORD : 0;
    flag = m_caseSensitive_checkBox->GetValue() ? (flag | wxSTC_FIND_MATCHCASE) : flag;
    t->SetSearchFlags(flag);
    t->SearchAnchor();
    int next_pos = t->SearchInTarget(m_search_textCtrl->GetLineText(0));
    //wxPrintf(_("Prev POS = %d\n"), previous_pos);
    if(next_pos >= 0)
    {
        current_search_pos = next_pos + 1;
        t->GotoPos(next_pos);
        t->SetSelection(t->GetCurrentPos(), t->GetCurrentPos() + search_text.length());
    }
}
