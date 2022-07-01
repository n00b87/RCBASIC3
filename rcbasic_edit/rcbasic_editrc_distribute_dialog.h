#ifndef __rcbasic_editrc_distribute_dialog__
#define __rcbasic_editrc_distribute_dialog__

/**
@file
Subclass of rc_distribute_dialog, which is generated by wxFormBuilder.
*/

#include "rcbasic_edit.h"
#include "rcbasic_edit_frame.h"

#include <vector>

//// end generated include

struct rc_dist_property
{
    wxString p_name;
    wxString p_value;
};

/** Implementing rc_distribute_dialog */
class rcbasic_editrc_distribute_dialog : public rc_distribute_dialog
{
    private:
        rcbasic_edit_frame* parent_frame;
        wxString editor_path;
        std::vector<rc_dist_property> dist_properties;

	protected:
		// Handlers for rc_distribute_dialog events.
		void onInitJavaPathButtonClick( wxCommandEvent& event );
		void onSaveSettingsButtonClick( wxCommandEvent& event );
		void onMakeAppButtonClick( wxCommandEvent& event );
		void onCloseButtonClick( wxCommandEvent& event );
	public:
		/** Constructor */
		rcbasic_editrc_distribute_dialog( wxWindow* parent );
	//// end generated class members

        bool java_init_dir(wxFileName java_dir, wxString project_name);

        void setProperty(wxString property_name, wxString property_value);
        std::vector<rc_dist_property> getProperties();
        wxString getPropertyValue(wxString property_name);
        wxString getPlatformPkgArg(wxString platform_value);
        wxString getTargetPlatforms();
        void setTargetPlatforms(wxString platform_properties);
        int getTargetPlatformCount();
        void saveAppProperties();
        void loadAppProperties();

};

#endif // __rcbasic_editrc_distribute_dialog__
