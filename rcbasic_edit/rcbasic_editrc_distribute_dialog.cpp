#include "rcbasic_editrc_distribute_dialog.h"
#include "rcbasic_editrc_distProcess_dialog.h"
#include <wx/msgdlg.h>
#include <wx/dir.h>

rcbasic_editrc_distribute_dialog::rcbasic_editrc_distribute_dialog( wxWindow* parent )
:
rc_distribute_dialog( parent )
{
    //wxComboBox m_category_comboBox;
    parent_frame = (rcbasic_edit_frame*)parent;

    //wxPuts(_("PROJECT LOCATUON: ") + parent_frame->getActiveProject()->getLocation());

    m_projectName_textCtrl->SetValue(parent_frame->getActiveProject()->getName());

    m_category_comboBox->Clear();
    m_category_comboBox->Append(_("AudioVideo"));
    m_category_comboBox->Append(_("Audio"));
    m_category_comboBox->Append(_("Video"));
    m_category_comboBox->Append(_("Development"));
    m_category_comboBox->Append(_("Education"));
    m_category_comboBox->Append(_("Game"));
    m_category_comboBox->Append(_("Graphics"));
    m_category_comboBox->Append(_("Network"));
    m_category_comboBox->Append(_("Office"));
    m_category_comboBox->Append(_("Science"));
    m_category_comboBox->Append(_("Settings"));
    m_category_comboBox->Append(_("System"));
    m_category_comboBox->Append(_("Utility"));
    m_category_comboBox->SetSelection(0);

    //wxCheckListBox m_targetPlatforms_checkList;
    m_targetPlatforms_checkList->AppendAndEnsureVisible(_("Windows 32-Bit"));
    m_targetPlatforms_checkList->AppendAndEnsureVisible(_("Windows 64-Bit"));
    m_targetPlatforms_checkList->AppendAndEnsureVisible(_("Linux 32-Bit"));
    m_targetPlatforms_checkList->AppendAndEnsureVisible(_("Linux 64-Bit"));
    m_targetPlatforms_checkList->AppendAndEnsureVisible(_("Mac OS (x86)"));
    m_targetPlatforms_checkList->AppendAndEnsureVisible(_("Android"));
    m_targetPlatforms_checkList->AppendAndEnsureVisible(_("Web App (web assembly)"));

    m_orientation_comboBox->Clear();
    m_orientation_comboBox->Append(_("Default"));
    m_orientation_comboBox->Append(_("Landscape"));
    m_orientation_comboBox->Append(_("Portrait"));
    m_orientation_comboBox->SetSelection(0);

    loadAppProperties();
}

bool rcbasic_editrc_distribute_dialog::java_init_dir(wxFileName java_dir, wxString project_name)
{
    //wxPuts(_("INIT CALLED: ") + java_dir.GetFullPath());
    project_name.Replace(_(" "), _("_"));
    wxString activity_name = _("rcbasic_") + project_name;

    wxString pkg_home;
    wxGetEnv(_("RC_PKG_HOME"), &pkg_home);
	wxFileName rc_java_file_path(pkg_home);
    rc_java_file_path.AppendDir(_("rcbasic_android"));
    rc_java_file_path.AppendDir(_("scripts"));
    rc_java_file_path.SetFullName(_("rcbasic.java"));
    rc_java_file_path.MakeAbsolute();

	wxFile rc_java_file;

	if( !rc_java_file.Open(rc_java_file_path.GetFullPath()) )
    {
        wxMessageBox(_("Could not find Android Java Template: ") + rc_java_file_path.GetFullPath());
		return false;
    }

	wxFile out_java_file;
	wxFileName out_java_file_path = java_dir;
	out_java_file_path.SetFullName(activity_name + _(".java"));

	if( !out_java_file.Open(out_java_file_path.GetFullPath(), wxFile::write) )
    {
        rc_java_file.Close();
        wxMessageBox(_("Could not output to ") + java_dir.GetFullPath());
		return false;
    }

	wxString rc_java_file_data;
	rc_java_file.ReadAll(&rc_java_file_data);

	rc_java_file_data.Replace(_("package_name"), m_appID_textCtrl->GetValue());
	rc_java_file_data.Replace(_("app_name"), activity_name);
    out_java_file.Write(rc_java_file_data);

    //wxPuts(_("Write \n")+rc_java_file_data+_("\n\nDestination: ") + out_java_file_path.GetFullPath()+_("\n\n"));

	out_java_file.Close();
	rc_java_file.Close();

	return true;
}

void rcbasic_editrc_distribute_dialog::onInitJavaPathButtonClick( wxCommandEvent& event )
{
// TODO: Implement onInitJavaPathButtonClick
    wxFileName java_dir_fname = m_javaPath_dirPicker->GetDirName();

    wxString pkg_home;
    wxGetEnv(_("RC_PKG_HOME"), &pkg_home);
    wxFileName script_java_fname(pkg_home);
    //wxPuts(_("PKG = ") + pkg_home);
    script_java_fname.AppendDir(_("rcbasic_android"));
    script_java_fname.AppendDir(_("scripts"));
    script_java_fname.SetFullName(_("rcbasic.java"));

    if( script_java_fname.Exists() && java_dir_fname.Exists() )
    {
        wxString project_name = m_projectName_textCtrl->GetValue();
        project_name = project_name.substr(project_name.find_first_not_of(_(" ")));
        project_name = project_name.substr(0, project_name.find_last_not_of(_(" "))+1);
        wxString app_name = project_name;
        app_name.Replace(_(" "), _("_"));
        java_init_dir(java_dir_fname, app_name);
    }
}


void rcbasic_editrc_distribute_dialog::setProperty(wxString property_name, wxString property_value)
{
    int index = -1;
    for(int i = 0; i < dist_properties.size(); i++)
    {
        if(dist_properties[i].p_name.compare(property_name)==0)
        {
            index = i;
            break;
        }
    }

    if(index < 0)
    {
        rc_dist_property new_property;
        new_property.p_name = property_name;
        new_property.p_value = property_value;
        dist_properties.push_back(new_property);
    }
    else
    {
        dist_properties[index].p_value = property_value;
    }
}

std::vector<rc_dist_property> rcbasic_editrc_distribute_dialog::getProperties()
{
    return dist_properties;
}

wxString rcbasic_editrc_distribute_dialog::getPropertyValue(wxString property_name)
{
    for(int i = 0; i < dist_properties.size(); i++)
    {
        if(dist_properties[i].p_name.compare(property_name)==0)
        {
            return dist_properties[i].p_value;
        }
    }
    return _("");
}

wxString rcbasic_editrc_distribute_dialog::getPlatformPkgArg(wxString platform_value)
{
    if(platform_value.compare(_("Windows 32-Bit"))==0)
        return _("WIN_32");
    else if(platform_value.compare(_("Windows 64-Bit"))==0)
        return _("WIN_64");
    else if(platform_value.compare(_("Linux 32-Bit"))==0)
        return _("LINUX_32");
    else if(platform_value.compare(_("Linux 64-Bit"))==0)
        return _("LINUX_64");
    else if(platform_value.compare(_("Mac OS (x86)"))==0)
        return _("MAC");
    else if(platform_value.compare(_("Web App (web assembly)"))==0)
        return _("WEB");
    else if(platform_value.compare(_("Android"))==0)
        return _("ANDROID");

    return _("NONE");
}

wxString rcbasic_editrc_distribute_dialog::getTargetPlatforms()
{
    wxString target_platforms;

    for(int i = 0; i < m_targetPlatforms_checkList->GetCount(); i++)
    {
        if(m_targetPlatforms_checkList->IsChecked(i))
        {
            target_platforms.Append(getPlatformPkgArg(m_targetPlatforms_checkList->GetString(i)) + _(","));
        }
    }

    if(target_platforms.Length()>0)
        target_platforms = target_platforms.substr(0, target_platforms.Length()-1);

    return target_platforms;
}

void rcbasic_editrc_distribute_dialog::setTargetPlatforms(wxString platform_properties)
{
    for(int i = 0; i < m_targetPlatforms_checkList->GetCount(); i++)
    {
        if(platform_properties.find(getPlatformPkgArg(m_targetPlatforms_checkList->GetString(i))) != wxString::npos)
        {
            m_targetPlatforms_checkList->Check(i);
        }
    }
}

int rcbasic_editrc_distribute_dialog::getTargetPlatformCount()
{
    int num_targets = 0;
    for(int i = 0; i < m_targetPlatforms_checkList->GetCount(); i++)
    {
        if(m_targetPlatforms_checkList->IsChecked(i))
        {
            if(m_targetPlatforms_checkList->GetString(i).compare(_("Android"))==0)
            {
                if(m_androidDebug_checkBox->GetValue())
                    num_targets++;

                if(m_androidRelease_checkBox->GetValue())
                    num_targets++;
            }
            else
                num_targets++;
        }
    }

    return num_targets;
}

void rcbasic_editrc_distribute_dialog::saveAppProperties()
{
    setProperty(_("PROJECT_NAME"), m_projectName_textCtrl->GetValue());
    setProperty(_("SOURCE"), parent_frame->getActiveProject()->getMainSource().GetFullName());
    setProperty(_("PROJECT_CATEGORY"), m_category_comboBox->GetValue());
    setProperty(_("TGT_PLATFORM"), getTargetPlatforms());
    setProperty(_("APP_TYPE"), _("Application"));
    setProperty(_("TERMINAL_FLAG"), m_enableTerminal_checkBox->GetValue() ? _("true") : _("false"));

    wxString project_dir = parent_frame->getActiveProject()->getLocation();
    project_dir = project_dir.substr(0, project_dir.Length()-1);
    setProperty(_("PROJECT_DIR"), project_dir);

    wxString out_dir = m_outputDir_dirPicker->GetDirName().GetFullPath();
    out_dir = out_dir.substr(0, out_dir.Length()-1);
    setProperty(_("OUTPUT_DIR"), out_dir);

	setProperty(_("ENABLE_WEB_THREADS"), m_enableWebThreads_checkBox->GetValue() ? _("true") : _("false"));
    setProperty(_("ICON"), m_icon_filePicker->GetFileName().GetFullPath());

    setProperty(_("ANDROID_APP_ID"), m_appID_textCtrl->GetValue());
    setProperty(_("ANDROID_ORIENTATION"), m_orientation_comboBox->GetValue().Lower());
    setProperty(_("ANDROID_KEYSTORE"), m_keystore_filePicker->GetFileName().GetFullPath());
    wxString android_keystore = getPropertyValue(_("ANDROID_KEYSTORE"));
    android_keystore.Replace(_("\\"), _("\\\\"));
    setProperty(_("ANDROID_KEYSTORE"), android_keystore);
    setProperty(_("ANDROID_ALIAS"), m_alias_textCtrl->GetValue());
    setProperty(_("ANDROID_DEBUG"), m_androidDebug_checkBox->GetValue() ? _("1") : _("0"));
	setProperty(_("ANDROID_RELEASE"), m_androidRelease_checkBox->GetValue() ? _("1") : _("0"));

	wxString android_java_dir = m_javaPath_dirPicker->GetDirName().GetFullPath();
	android_java_dir = android_java_dir.substr(0, android_java_dir.Length()-1);
	setProperty(_("ANDROID_JAVA_DIR"), android_java_dir);

	wxString p_dir = project_dir;
	//wxGetEnv(_("RC_PKG_HOME"), &pkg_dir);
	wxFileName app_properties;
	app_properties.SetPath(p_dir);
	app_properties.SetFullName(_("app.properties"));
	wxFile app_file;
	if(!app_file.Open(app_properties.GetFullPath(), wxFile::write))
    {
        if(!app_file.Create(app_properties.GetFullPath()))
            return;
    }
	for(int i = 0; i < dist_properties.size(); i++)
    {
        //wxPuts(_("PROPERTY:")+dist_properties[i].p_name+_("\nVALUE:")+dist_properties[i].p_value+_("\n\n"));
        app_file.Write(dist_properties[i].p_name + _("=") + dist_properties[i].p_value + _("\n"));
    }
    app_file.Close();
}


void rcbasic_editrc_distribute_dialog::loadAppProperties()
{
    wxString p_dir = getPropertyValue(_("PROJECT_DIR"));
	//wxGetEnv(_("RC_PKG_HOME"), &pkg_dir);
	wxFileName app_properties;
	app_properties.SetPath(p_dir);
	app_properties.SetFullName(_("app.properties"));
	if(!app_properties.Exists())
        return;
	wxFile app_file;
	if(!app_file.Open(app_properties.GetFullPath()))
    {
        return;
    }

	wxString app_file_data;
	app_file.ReadAll(&app_file_data);
    app_file.Close();

    wxString property;
    wxString value;

    for(int i = 0; i < app_file_data.length(); i++)
    {
        int vpos = app_file_data.find_first_of(_("="));
        if(vpos == wxString::npos)
            break;
        property = app_file_data.substr(0, vpos).Trim();
        property = property.substr(property.find_first_not_of(_(" ")));

        value = app_file_data.substr(vpos+1);
        value = value.substr(0, value.find_first_of(_("\n")));

        if(property.compare(_("PROJECT_CATEGORY"))==0)
        {
            m_category_comboBox->SetValue(value);
        }
        else if(property.compare(_("TGT_PLATFORM"))==0)
        {
            setTargetPlatforms(value);
        }
        else if(property.compare(_("TERMINAL_FLAG"))==0)
        {
            m_enableTerminal_checkBox->SetValue( value.compare(_("true")) == 0 ? true : false  );
        }
        else if(property.compare(_("OUTPUT_DIR"))==0)
        {
            wxFileName dname;
            dname.SetPath(value);
            m_outputDir_dirPicker->SetDirName( dname );
        }
        else if(property.compare(_("ENABLE_WEB_THREADS"))==0)
        {
            m_enableWebThreads_checkBox->SetValue( value.compare(_("true")) == 0 ? true : false );
        }
        else if(property.compare(_("ICON"))==0)
        {
            m_icon_filePicker->SetFileName( wxFileName(value) );
        }
        else if(property.compare(_("ANDROID_APP_ID"))==0)
        {
            m_appID_textCtrl->SetValue(value);
        }
        else if(property.compare(_("ANDROID_ORIENTATION"))==0)
        {
            m_orientation_comboBox->SetValue(value);
        }
        else if(property.compare(_("ANDROID_KEYSTORE"))==0)
        {
            value.Replace(_("\\\\"), _("\\"));
            m_keystore_filePicker->SetFileName( wxFileName(value) );
        }
        else if(property.compare(_("ANDROID_ALIAS"))==0)
        {
            m_alias_textCtrl->SetValue(value);
        }
        else if(property.compare(_("ANDROID_DEBUG"))==0)
        {
            m_androidDebug_checkBox->SetValue( value.find_first_of(_("1")) != wxString::npos ? true : false );
        }
        else if(property.compare(_("ANDROID_RELEASE"))==0)
        {
            m_androidRelease_checkBox->SetValue( value.find_first_of(_("1")) != wxString::npos ? true : false );
        }
        else if(property.compare(_("ANDROID_JAVA_DIR"))==0)
        {
            wxFileName dname;
            dname.SetPath(value);
            m_javaPath_dirPicker->SetDirName( wxFileName(dname) );
        }
        else
        {
            //wxPuts(_("PROPERTY: ") + property);
            //wxPuts(_("VALUE: ") + value);
            //wxPuts(_(""));
        }

        app_file_data = app_file_data.substr(app_file_data.find_first_of(_("\n"))+1);
    }

    //saveAppProperties();
}


void rcbasic_editrc_distribute_dialog::onSaveSettingsButtonClick( wxCommandEvent& event )
{
// TODO: Implement onSaveSettingsButtonClick
    saveAppProperties();
}

void rcbasic_editrc_distribute_dialog::onMakeAppButtonClick( wxCommandEvent& event )
{
// TODO: Implement onMakeAppButtonClick
    saveAppProperties();

    wxDir out_dir(getPropertyValue(_("OUTPUT_DIR")));

    if( (!out_dir.IsOpened()) || (!wxDirExists(getPropertyValue(_("OUTPUT_DIR")))) )
    {
        if(out_dir.IsOpened())
            out_dir.Close();
        wxMessageBox(_("Output Directory was not found or not accessible"));
        return;
    }

    /*if(out_dir.HasFiles())
    {
        out_dir.Close();
        wxMessageBox(_("You must select an empty directory for output"));
        return;
    }*/

    out_dir.Close();

    //bool web_build_flag = getPropertyValue(_("TGT_PLATFORM")).Replace(_("WEB"), _("")).compare(getPropertyValue(_("TGT_PLATFORM")))==0 ? false : true;

    wxString app_pkg_args;
    app_pkg_args.Append(_("TGT_PLATFORM=[TGT_ARGS] PROJECT_NAME=\"[PRJ_NAME]\" "));
	app_pkg_args.Append(_("PROJECT_CATEGORY=[PRJ_CAT] APP_TYPE=[APT] "));
	app_pkg_args.Append(_("TERMINAL_FLAG=[TRM_FLG] PROJECT_DIR=\"[PRJ_DIR]\" "));
	app_pkg_args.Append(_("OUTPUT_DIR=\"[OUT_DIR]\" ENABLE_WEB_THREADS=[WEB_THD] ICON=\"[ICN]\" "));
	app_pkg_args.Append(_("SOURCE=\"[SRC]\" "));
	app_pkg_args.Append(_("ANDROID_APP_ID=\"[ANDROID_APP_ID]\" "));
	app_pkg_args.Append(_("ANDROID_ORIENTATION=\"[ANDROID_ORIENTATION]\" "));
	app_pkg_args.Append(_("ANDROID_KEYSTORE=\"[ANDROID_KEYSTORE]\" "));
	app_pkg_args.Append(_("ANDROID_KEYSTORE_PASS=\"[ANDROID_KEYSTORE_PASS]\" "));
	app_pkg_args.Append(_("ANDROID_ALIAS=\"[ANDROID_ALIAS]\" "));
	app_pkg_args.Append(_("ANDROID_ALIAS_PASS=\"[ANDROID_ALIAS_PASS]\" "));
	app_pkg_args.Append(_("ANDROID_RELEASE=[ANDROID_RELEASE] "));
	app_pkg_args.Append(_("ANDROID_DEBUG=[ANDROID_DEBUG] "));
	app_pkg_args.Append(_("ANDROID_JAVA_DIR=\"[JAVA_DIR]\" "));
	app_pkg_args.Append(_("RCBASIC_STUDIO=1 "));

        //MAIN APP SETTINGS
    app_pkg_args.Replace(_("[TGT_ARGS]"), getPropertyValue(_("TGT_PLATFORM")));
	app_pkg_args.Replace(_("[PRJ_NAME]"), getPropertyValue(_("PROJECT_NAME")));
	app_pkg_args.Replace(_("[PRJ_CAT]"), getPropertyValue(_("PROJECT_CATEGORY")));
	app_pkg_args.Replace(_("[APT]"), getPropertyValue(_("APP_TYPE")));
	app_pkg_args.Replace(_("[TRM_FLG]"), getPropertyValue(_("TERMINAL_FLAG")));
	app_pkg_args.Replace(_("[PRJ_DIR]"), getPropertyValue(_("PROJECT_DIR")));
	app_pkg_args.Replace(_("[OUT_DIR]"), getPropertyValue(_("OUTPUT_DIR")));
	app_pkg_args.Replace(_("[WEB_THD]"), getPropertyValue(_("ENABLE_WEB_THREADS")));
	app_pkg_args.Replace(_("[ICN]"), getPropertyValue(_("ICON")));
	app_pkg_args.Replace(_("[SRC]"), getPropertyValue(_("SOURCE")));

    //ANDROID SETTINGS
	app_pkg_args.Replace(_("[ANDROID_APP_ID]"), getPropertyValue(_("ANDROID_APP_ID")));
	app_pkg_args.Replace(_("[ANDROID_ORIENTATION]"), getPropertyValue(_("ANDROID_ORIENTATION")));
	app_pkg_args.Replace(_("[ANDROID_KEYSTORE]"), getPropertyValue(_("ANDROID_KEYSTORE")));
	app_pkg_args.Replace(_("[ANDROID_KEYSTORE_PASS]"), m_password_textCtrl->GetValue());
	app_pkg_args.Replace(_("[ANDROID_ALIAS]"), getPropertyValue(_("ANDROID_ALIAS")));
	app_pkg_args.Replace(_("[ANDROID_ALIAS_PASS]"), m_password_textCtrl->GetValue());
	app_pkg_args.Replace(_("[ANDROID_RELEASE]"), getPropertyValue(_("ANDROID_RELEASE")));
	app_pkg_args.Replace(_("[ANDROID_DEBUG]"), getPropertyValue(_("ANDROID_DEBUG")));
	app_pkg_args.Replace(_("[JAVA_DIR]"), getPropertyValue(_("ANDROID_JAVA_DIR")));

	//wxMessageBox(_("\n\nCMD: ") + app_pkg_args + _("\n\n"));

	wxString pkg_home;
	wxGetEnv(_("RC_PKG_HOME"), &pkg_home);
	wxFileName pkg_path(pkg_home);
	pkg_path.SetFullName(_("pkg.cbc"));
	wxFileName rcbasic_run_fname = parent_frame->getRCRunnerPath();
	rcbasic_run_fname.MakeAbsolute();

	wxFile pf_file;
	wxFileName pf_file_fname = pkg_path;
	pf_file_fname.SetFullName(_("current_build_pfiles.txt"));

	if(pf_file.Create(pf_file_fname.GetFullPath(), true))
    {
        rcbasic_project* current_project = parent_frame->getActiveProject();
        std::vector<rcbasic_project_node*> source_files = current_project->getSourceFiles();

        for(int i = 0; i < source_files.size(); i++)
        {
            wxFileName fname = source_files[i]->getPath();
            fname.MakeRelativeTo(current_project->getLocation());
            pf_file.Write(fname.GetFullPath() + _("\n"));
        }
        pf_file.Close();
    }


	//wxString dist_cmd = _("\"") + rcbasic_run_fname.GetFullPath() + _("\" \"") + pkg_path.GetFullPath() + _("\" ") +app_pkg_args;
	//wxString dist_cmd = _("rcbasic_studio_run  studio_app_build \"") + getPropertyValue(_("PROJECT_DIR")) + _("\" \"") + getPropertyValue(_("SOURCE")) + _("\" ") + m_password_textCtrl->GetValue();
	wxString dist_cmd = _("rcbasic_studio_run  pkg ") + app_pkg_args;

	wxFile cmd_log;
	wxFileName cmd_log_path(pkg_home);
	cmd_log_path.SetFullName(_("cmd_log.txt"));
	if(cmd_log.Create(cmd_log_path.GetFullPath(), true))
    {
        cmd_log.Write(dist_cmd);
        cmd_log.Close();
    }
	//wxPrintf(_("\nTGTS: %d\n"), getTargetPlatformCount());
	//return;
	//wxMessageBox(_("\n\nDIST-CMD: ") + dist_cmd + _("\n\n")); return;
	rcbasic_editrc_distProcess_dialog dp_dialog(this, dist_cmd, getTargetPlatformCount());
	dp_dialog.ShowModal();
	//wxSystem(_("taskkill /F /IM rcbasic_studio_run.exe"));
	//wxPuts(_("\n\n")+dist_cmd);
	//dist_pid = wxExecute(dist_cmd, wxEXEC_SHOW_CONSOLE | wxEXEC_ASYNC, dist_process, NULL);
	//isRunning = true;
}

void rcbasic_editrc_distribute_dialog::onCloseButtonClick( wxCommandEvent& event )
{
// TODO: Implement onCloseButtonClick
    Close();
}
