#include "rcbasic_edit_preference_dialog.h"
#include "rcbasic_edit_frame.h"

rcbasic_edit_preference_dialog::rcbasic_edit_preference_dialog( wxWindow* parent )
:
rc_preference_dialog( parent )
{
    parent_frame = parent;

    rcbasic_edit_frame* pframe = (rcbasic_edit_frame*) parent_frame;

    m_pref_rcPath_dirPicker->SetPath(pframe->getRCBasicBasePath());
    m_pref_compilerPath_filePicker->SetFileName(wxFileName(pframe->getRCBasicBuildPath()));
    m_pref_runtimePath_filePicker->SetFileName(wxFileName(pframe->getRCBasicRunPath()));
    m_rcbasicManual_textCtrl->SetValue(pframe->getRCBasicDocLink());
    m_editorManual_textCtrl->SetValue(pframe->getStudioDocLink());

    m_enableParser_checkBox->SetValue(pframe->getParserFlag());
    m_enableCodeCompletion_checkBox->SetValue(pframe->getAutoCompleteFlag());
    m_enablePresets_checkBox->SetValue(pframe->getPresetFlag());
}

int rcbasic_edit_preference_dialog::getPreferenceDialogValue()
{
    return preference_dialog_value;
}

void rcbasic_edit_preference_dialog::onCancelButtonClick( wxCommandEvent& event )
{
    preference_dialog_value = preference_value_CANCEL;
    Close();
}

void rcbasic_edit_preference_dialog::onOKButtonClick( wxCommandEvent& event )
{
    preference_dialog_value = preference_value_OK;
    Close();
}

wxString rcbasic_edit_preference_dialog::getRCBasicBasePath()
{
    return m_pref_rcPath_dirPicker->GetPath();
}

wxFileName rcbasic_edit_preference_dialog::getRCBasicBuildPath()
{
    return m_pref_compilerPath_filePicker->GetFileName();
}

wxFileName rcbasic_edit_preference_dialog::getRCBasicRunPath()
{
    return m_pref_runtimePath_filePicker->GetFileName();
}

bool rcbasic_edit_preference_dialog::getParserFlag()
{
    return m_enableParser_checkBox->GetValue();
}

bool rcbasic_edit_preference_dialog::getAutoCompleteFlag()
{
    return m_enableCodeCompletion_checkBox->GetValue();
}

bool rcbasic_edit_preference_dialog::getPresetFlag()
{
    return m_enablePresets_checkBox->GetValue();
}

wxString rcbasic_edit_preference_dialog::getRCBasicDocLink()
{
    return m_rcbasicManual_textCtrl->GetValue();
}

wxString rcbasic_edit_preference_dialog::getStudioDocLink()
{
    return m_editorManual_textCtrl->GetValue();
}
