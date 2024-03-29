#ifndef __rcbasic_editrc_preference_dialog__
#define __rcbasic_editrc_preference_dialog__

/**
@file
Subclass of rc_preference_dialog, which is generated by wxFormBuilder.
*/

#include "rcbasic_edit.h"

//// end generated include

#define preference_value_CANCEL 0
#define preference_value_OK 1

/** Implementing rc_preference_dialog */
class rcbasic_edit_preference_dialog : public rc_preference_dialog
{
    private:
        wxWindow* parent_frame;
        int preference_dialog_value;
    protected:
        void onCancelButtonClick( wxCommandEvent& event );
        void onOKButtonClick( wxCommandEvent& event );
	public:
		/** Constructor */
		rcbasic_edit_preference_dialog( wxWindow* parent );
		int getPreferenceDialogValue();
		wxString getRCBasicBasePath();
        wxFileName getRCBasicBuildPath();
        wxFileName getRCBasicRunPath();
        bool getParserFlag();
        bool getAutoCompleteFlag();
        bool getPresetFlag();
        wxString getRCBasicDocLink();
        wxString getStudioDocLink();
	//// end generated class members

};

#endif // __rcbasic_editrc_preference_dialog__
