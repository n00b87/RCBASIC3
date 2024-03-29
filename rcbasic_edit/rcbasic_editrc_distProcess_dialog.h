#ifndef __rcbasic_editrc_distProcess_dialog__
#define __rcbasic_editrc_distProcess_dialog__

/**
@file
Subclass of rc_distProcess_dialog, which is generated by wxFormBuilder.
*/

#include "rcbasic_edit.h"

#include <wx/process.h>

//// end generated include

/** Implementing rc_distProcess_dialog */
class rcbasic_editrc_distProcess_dialog : public rc_distProcess_dialog
{
    private:
        wxProcess* dist_process;
        int dist_pid;
        bool isRunning;
        int target_count;
        int current_count;
	protected:
		// Handlers for rc_distProcess_dialog events.
		void onDistProcessUpdateUI( wxUpdateUIEvent& event );
		void onCancelButtonClick( wxCommandEvent& event );
		void onCloseButtonClick( wxCommandEvent& event );
	public:
		/** Constructor */
		rcbasic_editrc_distProcess_dialog( wxWindow* parent, wxString dist_cmd, int num_targets );
	//// end generated class members
	void onDistProcessTerminate( wxProcessEvent& event );

};

#endif // __rcbasic_editrc_distProcess_dialog__
