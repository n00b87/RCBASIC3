#ifndef __rcbasic_editrc_fileProperties_dialog__
#define __rcbasic_editrc_fileProperties_dialog__

/**
@file
Subclass of rc_fileProperties_dialog, which is generated by wxFormBuilder.
*/

#include "rcbasic_edit.h"
#include "projects.h"

//// end generated include

/** Implementing rc_fileProperties_dialog */
class rcbasic_edit_fileProperties_dialog : public rc_fileProperties_dialog
{
    private:
        rcbasic_project_node* file_node;
	protected:
		// Handlers for rc_fileProperties_dialog events.
		void onCancelButtonClick( wxCommandEvent& event );
		void onOKButtonClick( wxCommandEvent& event );
	public:
		/** Constructor */
		rcbasic_edit_fileProperties_dialog( wxWindow* parent, rcbasic_project_node* node );
	//// end generated class members



};

#endif // __rcbasic_editrc_fileProperties_dialog__
