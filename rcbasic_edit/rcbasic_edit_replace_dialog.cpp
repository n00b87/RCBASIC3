#include "rcbasic_edit_replace_dialog.h"

rcbasic_edit_replace_dialog::rcbasic_edit_replace_dialog( wxWindow* parent )
:
rc_replace_dialog( parent )
{
    parent_frame = (rcbasic_edit_frame*) parent;
    current_project = parent_frame->getActiveProject();
    current_file = parent_frame->getCurrentFile();
    current_search_pos = -1;
    wxString selected_text = current_file->getTextCtrl()->GetSelectedText();
    if(selected_text.Length() > 0 && selected_text.Length() <= 80)
        m_search_textCtrl->SetValue(current_file->getTextCtrl()->GetSelectedText());
    else
        m_search_textCtrl->SetValue(parent_frame->search_term);
}


void rcbasic_edit_replace_dialog::replaceInFile(rcbasic_edit_txtCtrl* txtCtrl_obj, wxString search_txt, wxString replace_txt, int flag)
{
    if(!txtCtrl_obj)
        return;

    wxStyledTextCtrl* t = txtCtrl_obj->getTextCtrl();

    if(!t)
        return;

    t->BeginUndoAction();


    wxString selText= search_txt;
    int selLen = selText.Len();
    int selStart= 0;

    int totalLen = t->GetTextLength();
    int searchStart=0;
    int foundLoc = 0;

    t->SetSearchFlags(flag);

    wxFileName fname;

    std::vector<rcbasic_edit_txtCtrl*> open_files = parent_frame->getOpenFiles();

    for(int i = 0; i < open_files.size(); i++)
    {
        if(open_files[i]->getTextCtrl()==t)
        {
            fname = open_files[i]->getSourcePath();
            break;
        }
    }

    while(foundLoc!=-1)
    {
        t->SetTargetStart(searchStart);
        t->SetTargetEnd(totalLen);

        foundLoc= t->SearchInTarget(selText);
        searchStart= foundLoc+selLen;

        if(foundLoc!=-1)
        {
            t->Replace(foundLoc, foundLoc + selText.length(), replace_txt);
            txtCtrl_obj->setTextChangedFlag(true);
            //r.pos = foundLoc;
            //r.line = t->LineFromPosition(foundLoc);
            //wxString line_str;
            //line_str.Printf(_(":%d:    "), r.line+1);
            //m_searchResults_listBox->AppendAndEnsureVisible( fname.GetFullName() + line_str + t->GetLineText(r.line) );
            //search_results.push_back(r);
        }
    }

    t->EndUndoAction();
}

void rcbasic_edit_replace_dialog::replaceInSelection(rcbasic_edit_txtCtrl* txtCtrl_obj, wxString search_txt, wxString replace_txt, int flag)
{
    if(!txtCtrl_obj)
        return;

    wxStyledTextCtrl* t = txtCtrl_obj->getTextCtrl();

    if(!t)
        return;


    wxString selText= search_txt;
    int selLen = selText.Len();
    int selStart= 0;

    int totalLen = t->GetTextLength();
    int searchStart = -1;
    int searchEnd = -1;
    int foundLoc = 0;

    t->GetSelection(&searchStart, &searchEnd);

    if(searchStart < 0 || searchEnd < 0)
        return;

    t->BeginUndoAction();

    t->SetSearchFlags(flag);

    wxFileName fname;

    std::vector<rcbasic_edit_txtCtrl*> open_files = parent_frame->getOpenFiles();

    for(int i = 0; i < open_files.size(); i++)
    {
        if(open_files[i]->getTextCtrl()==t)
        {
            fname = open_files[i]->getSourcePath();
            break;
        }
    }

    while(foundLoc!=-1)
    {
        t->SetTargetStart(searchStart);
        t->SetTargetEnd(searchEnd);

        foundLoc= t->SearchInTarget(selText);
        searchStart= foundLoc+selLen;

        if(foundLoc!=-1)
        {
            t->Replace(foundLoc, foundLoc + selText.length(), replace_txt);
            txtCtrl_obj->setTextChangedFlag(true);
            //r.pos = foundLoc;
            //r.line = t->LineFromPosition(foundLoc);
            //wxString line_str;
            //line_str.Printf(_(":%d:    "), r.line+1);
            //m_searchResults_listBox->AppendAndEnsureVisible( fname.GetFullName() + line_str + t->GetLineText(r.line) );
            //search_results.push_back(r);
        }
    }

    t->EndUndoAction();
}


void rcbasic_edit_replace_dialog::onReplaceInProjectClick( wxCommandEvent& event )
{
// TODO: Implement onReplaceInProjectClick
    replace_dialog_value = replace_dialog_INPROJECT;

    if(!current_project)
        return;

    int flag = m_matchWhole_checkBox->GetValue() ? wxSTC_FIND_WHOLEWORD : 0;
    flag = m_caseSensitive_checkBox->GetValue() ? (flag | wxSTC_FIND_MATCHCASE) : flag;

    wxString search_txt= m_search_textCtrl->GetLineText(0);

    wxString replace_txt = m_replace_textCtrl->GetLineText(0);

    rcbasic_edit_txtCtrl* project_file_obj;
    rcbasic_project_node* p_node;

    std::vector<rcbasic_project_node*> source_files = current_project->getSourceFiles();

    std::vector<rcbasic_edit_txtCtrl*> open_files;

    for(int i = 0; i < source_files.size(); i++)
    {
        open_files = parent_frame->getOpenFiles();
        int open_file_index = parent_frame->getOpenFileFromPath(source_files[i]->getPath());
        if(open_file_index < 0)
        {
            parent_frame->openSourceFile(source_files[i]->getPath());
            open_files = parent_frame->getOpenFiles();

            open_file_index = parent_frame->getOpenFileFromPath(source_files[i]->getPath());
            if(open_file_index < 0)
                continue;
        }

        project_file_obj = open_files[open_file_index];

        if(!project_file_obj)
            continue;

        replaceInFile(project_file_obj, search_txt, replace_txt, flag);
    }
    Close();
}

void rcbasic_edit_replace_dialog::onReplaceInFileClick( wxCommandEvent& event )
{
// TODO: Implement onReplaceInFileClick
    replace_dialog_value = replace_dialog_INFILE;

    if(!current_file)
        return;

    int flag = m_matchWhole_checkBox->GetValue() ? wxSTC_FIND_WHOLEWORD : 0;
    flag = m_caseSensitive_checkBox->GetValue() ? (flag | wxSTC_FIND_MATCHCASE) : flag;

    wxString search_txt= m_search_textCtrl->GetLineText(0);

    wxString replace_txt = m_replace_textCtrl->GetLineText(0);

    replaceInFile(current_file, search_txt, replace_txt, flag);

}

void rcbasic_edit_replace_dialog::onReplaceInSelectionClick( wxCommandEvent& event )
{
// TODO: Implement onReplaceInSelectionClick
    replace_dialog_value = replace_dialog_INSELECTION;

    if(!current_file)
        return;

    int flag = m_matchWhole_checkBox->GetValue() ? wxSTC_FIND_WHOLEWORD : 0;
    flag = m_caseSensitive_checkBox->GetValue() ? (flag | wxSTC_FIND_MATCHCASE) : flag;

    wxString search_txt= m_search_textCtrl->GetLineText(0);

    wxString replace_txt = m_replace_textCtrl->GetLineText(0);

    replaceInSelection(current_file, search_txt, replace_txt, flag);
}

int rcbasic_edit_replace_dialog::getValue()
{
    return replace_dialog_value;
}

wxString rcbasic_edit_replace_dialog::getSearchText()
{
    return m_search_textCtrl->GetValue();
}

wxString rcbasic_edit_replace_dialog::getReplaceText()
{
    return m_replace_textCtrl->GetValue();
}

int rcbasic_edit_replace_dialog::getFlags()
{
    int flag = m_matchWhole_checkBox->GetValue() ? wxSTC_FIND_WHOLEWORD : 0;
    flag = m_caseSensitive_checkBox->GetValue() ? (flag | wxSTC_FIND_MATCHCASE) : flag;
    return flag;
}

void rcbasic_edit_replace_dialog::onFindNextClick( wxCommandEvent& event )
{
// TODO: Implement onFindNextClick

    if(!current_file)
        return;

    wxStyledTextCtrl* t = current_file->getTextCtrl();

    if(!t)
        return;

    //int previous_pos = t->FindText(t->GetCurrentPos()+1, t->GetLastPosition(), m_search_textCtrl->GetLineText(0));
    if(m_search_textCtrl->GetLineText(0).compare(search_term)!=0 || current_search_pos < 0)
    {
        search_term = m_search_textCtrl->GetLineText(0);
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
        t->SetSelection(t->GetCurrentPos(), t->GetCurrentPos() + search_term.length());
    }
}

void rcbasic_edit_replace_dialog::onReplaceClick( wxCommandEvent& event )
{
// TODO: Implement onReplaceClick
    if(!current_file)
        return;

    wxStyledTextCtrl* t = current_file->getTextCtrl();

    if(!t)
        return;

    if(current_search_pos < 0)
        return;

    long from_pos = -1;
    long to_pos = -1;
    t->GetSelection(&from_pos, &to_pos);

    if(from_pos < 0 || to_pos < 0)
        return;

    //wxTextCtrl* p;

    t->BeginUndoAction();
    t->Replace(from_pos, to_pos, m_replace_textCtrl->GetValue());
    t->EndUndoAction();
}

void rcbasic_edit_replace_dialog::onReplaceCloseClick( wxCommandEvent& event )
{
// TODO: Implement onReplaceCloseClick
    Close();
}

