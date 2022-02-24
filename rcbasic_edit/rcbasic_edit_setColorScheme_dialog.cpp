#include "rcbasic_edit_setColorScheme_dialog.h"
#include <wx/dir.h>
#include <wx/stdpaths.h>

rcbasic_edit_setColorScheme_dialog::rcbasic_edit_setColorScheme_dialog( wxWindow* parent )
:
rc_setColorScheme_dialog( parent )
{
    p_frame = (rcbasic_edit_frame*)parent;
    openFiles = p_frame->getOpenFiles();

    wxString editor_path = wxStandardPaths::Get().GetExecutablePath();

    scheme_path = wxFileName(editor_path);
    scheme_path.AppendDir(_("config"));
    scheme_path.AppendDir(_("schemes"));

    wxDir dir(scheme_path.GetPath());

    wxString f_path;
    wxFileName fname;
    bool hasFiles = dir.GetFirst(&f_path);

    int i = 0;

    rcbasic_edit_scheme current_scheme = p_frame->getScheme();

    while(hasFiles)
    {
        fname.SetFullName(f_path);
        m_scheme_listBox->AppendAndEnsureVisible(fname.GetName());

        if(fname.GetName().compare(current_scheme.scheme_name)==0)
            m_scheme_listBox->SetSelection(i);

        i++;

        hasFiles = dir.GetNext(&f_path);
    }
}

void rcbasic_edit_setColorScheme_dialog::onSchemeSelected( wxCommandEvent& event )
{
// TODO: Implement onSchemeSelected

    int selection = event.GetSelection();

    //wxListBox* m_scheme_listbox;

    wxString scheme = m_scheme_listBox->GetString(selection);

    wxFileName scheme_fname = scheme_path;
    scheme_fname.SetName(scheme);
    scheme_fname.SetExt(_("scheme"));

    if(!scheme_fname.Exists())
        return;

    p_frame->loadScheme(scheme_fname);


    //rcbasic_edit_frame* frame;
    rcbasic_edit_txtCtrl* txtCtrl_obj;
    for(int i = 0; i < openFiles.size(); i++)
    {
        txtCtrl_obj = openFiles[i];
        if(!txtCtrl_obj)
            continue;

        if(!txtCtrl_obj->getTextCtrl())
            continue;

        p_frame->applyScheme(txtCtrl_obj->getTextCtrl());
    }
    p_frame->applyScheme(NULL);
}

void rcbasic_edit_setColorScheme_dialog::onSchemeCloseButtonClick( wxCommandEvent& event )
{
// TODO: Implement onSchemeCloseButtonClick
    wxString editor_path = wxStandardPaths::Get().GetExecutablePath();

    wxFileName view_path(editor_path);
    view_path.AppendDir(_("config"));
    view_path.SetFullName(_("default_view.config"));

    wxFile view_file;

    int selection = m_scheme_listBox->GetSelection();

    if(wxDirExists(view_path.GetPath()))
    {
        if(view_file.Create(view_path.GetFullPath(), true))
        {
            view_file.Write(_("DEFAULT_SCHEME=")+m_scheme_listBox->GetString(selection)+_(".scheme"));
            view_file.Close();
        }
    }

    Close();
}
