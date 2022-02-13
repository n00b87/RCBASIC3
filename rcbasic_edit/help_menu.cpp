#include "rcbasic_edit_frame.h"

void rcbasic_edit_frame::onDocMenuSelect( wxCommandEvent& event )
{
    wxString editor_path_str = wxStandardPaths::Get().GetExecutablePath();
    wxFileName editor_path(editor_path_str);
    editor_path.SetFullName(_(""));
    wxString cwd = wxGetCwd();
    wxSetWorkingDirectory(editor_path.GetFullPath());
    wxLaunchDefaultBrowser(RCBasic_Documentation_Link);
    wxSetWorkingDirectory(cwd);
}

void rcbasic_edit_frame::onEditorManualMenuSelect( wxCommandEvent& event )
{
    wxString editor_path_str = wxStandardPaths::Get().GetExecutablePath();
    wxFileName editor_path(editor_path_str);
    editor_path.SetFullName(_(""));
    wxString cwd = wxGetCwd();
    wxSetWorkingDirectory(editor_path.GetFullPath());
    wxLaunchDefaultBrowser(Studio_Documentation_Link);
    wxSetWorkingDirectory(cwd);
}

void rcbasic_edit_frame::onAboutMenuSelect( wxCommandEvent& event )
{
    wxString msg = _("RCBASIC Studio [Version]\nCopyright (C) 2022 Rodney Cunningham ( aka n00b )\n\nFor latest release, updates, and info go to \nhttp://www.rcbasic.com\n\nAnd the forum at \nhttp://rcbasic.freeforums.net");
    msg.Replace(_("[Version]"), RCBasic_Studio_Version);
    wxMessageBox(msg);
}
