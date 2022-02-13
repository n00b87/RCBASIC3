#include "rcbasic_edit_projectVariableEdit_dialog.h"

rcbasic_edit_projectVariableEdit_dialog::rcbasic_edit_projectVariableEdit_dialog( wxWindow* parent )
:
rc_projectVariableEdit_dialog( parent )
{
    varEdit_flag = VAR_EDIT_CANCEL;
}

void rcbasic_edit_projectVariableEdit_dialog::onCancelButtonClick( wxCommandEvent& event )
{
// TODO: Implement onCancelButtonClick
    Close();
}

void rcbasic_edit_projectVariableEdit_dialog::onOKButtonClick( wxCommandEvent& event )
{
// TODO: Implement onOKButtonClick
    var_name = m_variable_textCtrl->GetValue();
    var_value = m_value_textCtrl->GetValue();
    varEdit_flag = VAR_EDIT_OK;
    Close();
}

int rcbasic_edit_projectVariableEdit_dialog::getVariableEditFlag()
{
    return varEdit_flag;
}

wxString rcbasic_edit_projectVariableEdit_dialog::getVariableName()
{
    return var_name;
}

wxString rcbasic_edit_projectVariableEdit_dialog::getVariableValue()
{
    return var_value;
}

void rcbasic_edit_projectVariableEdit_dialog::setDefaultVariableName(wxString v_name)
{
    var_name = v_name;
    m_variable_textCtrl->SetValue(var_name);
}

void rcbasic_edit_projectVariableEdit_dialog::setDefaultVariableValue(wxString v_value)
{
    var_value = v_value;
    m_value_textCtrl->SetValue(var_value);
}
