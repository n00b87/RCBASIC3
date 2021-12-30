#ifndef __rcbasic_editrc_ideFrame__
#define __rcbasic_editrc_ideFrame__

/**
@file
Subclass of rc_ideFrame, which is generated by wxFormBuilder.
*/

#include "rcbasic_edit.h"

//// end generated include

/** Implementing rc_ideFrame */
class rcbasic_edit_frame : public rc_ideFrame
{
    private:
        bool toolbarVisible;
        bool sideBarVisible;
        bool messageWindowVisible;
	protected:
		// Handlers for rc_ideFrame events.
		void createNewProject( wxCommandEvent& event );
		void toggleToolbar( wxCommandEvent& event );
		void toggleSideBar( wxCommandEvent& event );
		void toggleMessageWindow( wxCommandEvent& event );
	public:
		/** Constructor */
		rcbasic_edit_frame( wxWindow* parent );
	//// end generated class members


};

#endif // __rcbasic_editrc_ideFrame__
