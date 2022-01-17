#include "rcbasic_edit_searchWrap_dialog.h"

rcbasic_edit_searchWrap_dialog::rcbasic_edit_searchWrap_dialog( wxWindow* parent, wxString search_term )
:
rc_searchWrap_dialog( parent )
{
    wxString txt = m_searchWrapPrompt_staticText->GetLabelText();
    txt.Replace(_("[text]"), search_term);
    m_searchWrapPrompt_staticText->SetLabelText(txt);
}

void rcbasic_edit_searchWrap_dialog::onSearchWrapCancel( wxCommandEvent& event )
{
// TODO: Implement onSearchWrapCancel
    searchWrap_value = searchWrap_value_CANCEL;
    Close();
}

void rcbasic_edit_searchWrap_dialog::onSearchWrapOk( wxCommandEvent& event )
{
// TODO: Implement onSearchWrapOk
    searchWrap_value = searchWrap_value_OK;
    Close();
}

int rcbasic_edit_searchWrap_dialog::getValue()
{
    return searchWrap_value;
}
