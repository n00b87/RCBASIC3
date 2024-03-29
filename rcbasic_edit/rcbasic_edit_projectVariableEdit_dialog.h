#ifndef __rcbasic_editrc_projectVariableEdit_dialog__
#define __rcbasic_editrc_projectVariableEdit_dialog__

/**
@file
Subclass of rc_projectVariableEdit_dialog, which is generated by wxFormBuilder.
*/

#include "rcbasic_edit.h"

//// end generated include

#define VAR_EDIT_CANCEL 0
#define VAR_EDIT_OK 1

/** Implementing rc_projectVariableEdit_dialog */
class rcbasic_edit_projectVariableEdit_dialog : public rc_projectVariableEdit_dialog
{
    int varEdit_flag;
    wxString var_name;
    wxString var_value;

	protected:
		// Handlers for rc_projectVariableEdit_dialog events.
		void onCancelButtonClick( wxCommandEvent& event );
		void onOKButtonClick( wxCommandEvent& event );
	public:
		/** Constructor */
		rcbasic_edit_projectVariableEdit_dialog( wxWindow* parent );
		int getVariableEditFlag();
		wxString getVariableName();
		wxString getVariableValue();
		void setDefaultVariableName(wxString v_name);
		void setDefaultVariableValue(wxString v_value);
	//// end generated class members

};

#endif // __rcbasic_editrc_projectVariableEdit_dialog__
