#include "rcbasic_edit_fileProperties_dialog.h"
#include "projects.h"

rcbasic_edit_fileProperties_dialog::rcbasic_edit_fileProperties_dialog( wxWindow* parent, rcbasic_project_node* node )
:
rc_fileProperties_dialog( parent )
{
    if(!node)
        return;
    file_node = node;
    wxFileName fname = file_node->getPath();
    fname.MakeAbsolute();
    m_fileName_textCtrl->SetValue(fname.GetFullPath());
    //wxRadioButton m_relative_radioBtn, m_absolute_radioBtn;
    m_relative_radioBtn->SetValue( file_node->getLocationStoreType()==STORE_LOCATION_RELATIVE ? true : false );
    m_absolute_radioBtn->SetValue( !m_relative_radioBtn->GetValue() );
}

void rcbasic_edit_fileProperties_dialog::onCancelButtonClick( wxCommandEvent& event )
{
// TODO: Implement onCancelButtonClick
    Close();
}

void rcbasic_edit_fileProperties_dialog::onOKButtonClick( wxCommandEvent& event )
{
// TODO: Implement onOKButtonClick
    if(!file_node)
        return;

    file_node->setLocationStoreType( m_relative_radioBtn->GetValue() ? STORE_LOCATION_RELATIVE : STORE_LOCATION_ABSOLUTE );
    Close();
}
