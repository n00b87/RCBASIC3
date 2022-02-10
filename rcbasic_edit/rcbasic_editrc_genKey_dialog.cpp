#include "rcbasic_editrc_genKey_dialog.h"
#include <wx/msgdlg.h>

rcbasic_editrc_genKey_dialog::rcbasic_editrc_genKey_dialog( wxWindow* parent )
:
rc_genKey_dialog( parent )
{

}

void rcbasic_editrc_genKey_dialog::onOKButtonClick( wxCommandEvent& event )
{
// TODO: Implement onOKButtonClick

    wxFileDialog openFileDialog(this, _("Save Keystore As"), _(""), _(""), _("Keystore (*.keystore)|*.keystore"), wxFD_SAVE);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user changed idea...

    wxFileName fname(openFileDialog.GetPath());

    if(fname.GetFullName().Length() <= 0)
    {
        wxMessageBox(_("Not a valid keystore name"));
        return;
    }

    wxString keystore_name = fname.GetFullName();
    wxString keystore_alias = m_alias_textCtrl->GetValue();
    wxString keystore_pw = m_password_textCtrl->GetValue();
    bool keystore_pw_confirm = keystore_pw.compare(m_confirmPassword_textCtrl->GetValue())==0;
    wxString user_name = m_name_textCtrl->GetValue();
    wxString orgUnit = m_orgUnit_textCtrl->GetValue();
    wxString org = m_org_textCtrl->GetValue();
    wxString city = m_city_textCtrl->GetValue();
    wxString state = m_state_textCtrl->GetValue();
    wxString country = m_country_textCtrl->GetValue();

    if(keystore_name.Length() <= 0)
    {
        wxMessageBox(_("Missing Keystore name"));
        return;
    }

    if(keystore_alias.Length() <= 0)
    {
        wxMessageBox(_("Missing Keystore alias"));
        return;
    }

    if(!keystore_pw_confirm)
    {
        wxMessageBox(_("Confirmed Password does not match"));
        return;
    }

    if(keystore_pw.Length() <= 0)
    {
        wxMessageBox(_("Missing Password for keystore"));
    }

    wxString keystore_cmd = _("cd &KEYSTORE_DIR && echo y | keytool -genkeypair -dname \"cn=&USR_NAME, ou=&ORG_UNIT, o=&ORG_NAME, s=&STATE, c=&COUNTRY_CODE\" -alias &ALIAS -keyalg RSA -keypass &PASSWORD -keystore &KEYSTORE_NAME -storepass &PASSWORD -validity 20000");


    keystore_cmd.Replace(_("&USR_NAME"), user_name);
    keystore_cmd.Replace(_("&ORG_UNIT"), orgUnit);
    keystore_cmd.Replace(_("&ORG_NAME"), org);
    keystore_cmd.Replace(_("&STATE"), state);
    keystore_cmd.Replace(_("&COUNTRY_CODE"), country);
    keystore_cmd.Replace(_("&ALIAS"), keystore_alias);
    keystore_cmd.Replace(_("&PASSWORD"), keystore_pw);
    keystore_cmd.Replace(_("&KEYSTORE_NAME"), keystore_name);
    keystore_cmd.Replace(_("&KEYSTORE_DIR"), fname.GetPath());

    //wxPuts(_("\nKeystore cmd = ") + keystore_cmd);
    //wxPuts(_("\n"));

    int exit_code = wxSystem(keystore_cmd);

    if(exit_code != 0)
    {
        wxMessageBox(_("Failed to create keystore."));
        return;
    }

    wxMessageBox(_("Keystore was successfully created"));
    Close();
}

void rcbasic_editrc_genKey_dialog::onCancelButtonClick( wxCommandEvent& event )
{
// TODO: Implement onCancelButtonClick
    Close();
}
