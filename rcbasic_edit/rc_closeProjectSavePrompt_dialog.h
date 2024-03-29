#ifndef __rcbasic_editrc_closeProjectSavePrompt_dialog__
#define __rcbasic_editrc_closeProjectSavePrompt_dialog__

/**
@file
Subclass of rc_closeProjectSavePrompt_dialog, which is generated by wxFormBuilder.
*/

#include "rcbasic_edit.h"

//// end generated include

#define projectCloseFlag_CANCEL 0
#define projectCloseFlag_DONT_SAVE 1
#define projectCloseFlag_SAVE 2

/** Implementing rc_closeProjectSavePrompt_dialog */
class rcbasic_edit_closeProjectSavePrompt_dialog : public rc_closeProjectSavePrompt_dialog
{
    private:
        int projectCloseFlag;
	protected:
		// Handlers for rc_closeProjectSavePrompt_dialog events.
		void onCloseProjectSaveCancel( wxCommandEvent& event );
		void onCloseProjectSaveDontSave( wxCommandEvent& event );
		void onCloseProjectSaveOk( wxCommandEvent& event );
	public:
		/** Constructor */
		rcbasic_edit_closeProjectSavePrompt_dialog( wxWindow* parent, const wxString& title );
		int getProjectCloseFlag();
	//// end generated class members

};

#endif // __rcbasic_editrc_closeProjectSavePrompt_dialog__
