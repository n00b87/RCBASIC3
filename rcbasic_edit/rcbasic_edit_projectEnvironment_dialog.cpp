#include "rcbasic_edit_projectEnvironment_dialog.h"
#include "rcbasic_edit_projectVariableEdit_dialog.h"
#include <wx/msgdlg.h>
#include <vector>

rcbasic_edit_projectEnvironment_dialog::rcbasic_edit_projectEnvironment_dialog( wxWindow* parent, std::vector<rcbasic_edit_env_var> vars )
:
rc_projectEnvironment_dialog( parent )
{
    //wxListCtrl m_environment_listCtrl;
    m_environment_listCtrl->AppendColumn(_("NAME"));
    m_environment_listCtrl->AppendColumn(_("VALUE"));

    int w, h;
    m_environment_listCtrl->GetSize(&w, &h);

    m_environment_listCtrl->SetColumnWidth(0, w/3-4);
    m_environment_listCtrl->SetColumnWidth(1, w/3*2-4);

    int index = 0;

    for(int i = 0; i < vars.size(); i++)
    {
        index = m_environment_listCtrl->InsertItem(m_environment_listCtrl->GetItemCount(), vars[i].var_name);
        m_environment_listCtrl->SetItem(index, 1, vars[i].var_value);
    }

    projectEnv_flag = PROJECT_ENVIRONMENT_DLG_CANCEL;

    //wxPuts(_("Control Set"));
}

std::vector<rcbasic_edit_env_var> rcbasic_edit_projectEnvironment_dialog::getVars()
{
    return env_vars;
}

int rcbasic_edit_projectEnvironment_dialog::getFlag()
{
    return projectEnv_flag;
}

void rcbasic_edit_projectEnvironment_dialog::onClearAllButtonClick( wxCommandEvent& event )
{
// TODO: Implement onClearAllButtonClick
    //wxListCtrl m_environment_listCtrl;
    m_environment_listCtrl->ClearAll();

    m_environment_listCtrl->AppendColumn(_("NAME"));
    m_environment_listCtrl->AppendColumn(_("VALUE"));

    int w, h;
    m_environment_listCtrl->GetSize(&w, &h);

    m_environment_listCtrl->SetColumnWidth(0, w/3-4);
    m_environment_listCtrl->SetColumnWidth(1, w/3*2-4);
}

void rcbasic_edit_projectEnvironment_dialog::onRemoveSelectedButtonClick( wxCommandEvent& event )
{
// TODO: Implement onRemoveSelectedButtonClick
    //wxListCtrl m_environment_listCtrl;
    int itemIndex = -1;
    std::vector<int> rows_to_delete;

    while ((itemIndex = m_environment_listCtrl->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
    {
        rows_to_delete.push_back(itemIndex);
    }

    for(int i = rows_to_delete.size()-1; i >= 0; i--)
    {
        m_environment_listCtrl->DeleteItem(rows_to_delete[i]);
    }

    rows_to_delete.clear();
}

void rcbasic_edit_projectEnvironment_dialog::onAddVariableButtonClick( wxCommandEvent& event )
{
// TODO: Implement onAddVariableButtonClick
    //wxListCtrl m_environment_listCtrl;
    int index = m_environment_listCtrl->InsertItem(m_environment_listCtrl->GetItemCount(), _("VARIABLE"));
    m_environment_listCtrl->SetItem(index, 1, _("VALUE"));
}

void rcbasic_edit_projectEnvironment_dialog::onEditVariableButtonClick( wxCommandEvent& event )
{
// TODO: Implement onAddVariableButtonClick
    //wxPuts(_("EDIT"));
    //wxListCtrl m_environment_listCtrl;
    rcbasic_edit_projectVariableEdit_dialog v_dialog(this);

    if(m_environment_listCtrl->GetSelectedItemCount() > 1)
    {
        wxMessageBox(_("You can only edit 1 item at a time."));
        return;
    }
    else if(m_environment_listCtrl->GetSelectedItemCount() < 1)
    {
        return;
    }

    long itemIndex = -1;

    while ((itemIndex = m_environment_listCtrl->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
    {
        // Got the selected item index
        //wxPuts(_("ITEM: ") + m_environment_listCtrl->GetItemText(itemIndex));
        v_dialog.setDefaultVariableName(m_environment_listCtrl->GetItemText(itemIndex));
        v_dialog.setDefaultVariableValue(m_environment_listCtrl->GetItemText(itemIndex, 1));
        v_dialog.ShowModal();

        if(v_dialog.getVariableEditFlag()==VAR_EDIT_OK)
        {
            m_environment_listCtrl->SetItem(itemIndex, 0, v_dialog.getVariableName());
            m_environment_listCtrl->SetItem(itemIndex, 1, v_dialog.getVariableValue());
        }
        break;
    }
}

void rcbasic_edit_projectEnvironment_dialog::onCancelButtonClick( wxCommandEvent& event )
{
// TODO: Implement onCancelButtonClick
    Close();
}

void rcbasic_edit_projectEnvironment_dialog::onOKButtonClick( wxCommandEvent& event )
{
// TODO: Implement onOKButtonClick
    projectEnv_flag = PROJECT_ENVIRONMENT_DLG_OK;

    //env_vars

    //long itemIndex = -1;

    //wxListCtrl m_environment_listCtrl;

    for(int i = 0; i < m_environment_listCtrl->GetItemCount(); i++)
    {
        // Got the selected item index
        //wxPuts(_("OK ITEM: ") + m_environment_listCtrl->GetItemText(i));
        rcbasic_edit_env_var var;
        var.var_name = m_environment_listCtrl->GetItemText(i);
        var.var_value = m_environment_listCtrl->GetItemText(i, 1);
        env_vars.push_back(var);
    }

    Close();
}
