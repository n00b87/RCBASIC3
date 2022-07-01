#ifndef PARSERTHREAD_H_INCLUDED
#define PARSERTHREAD_H_INCLUDED

#include <vector>
#include <wx/wx.h>
#include <wx/thread.h>
#include <wx/event.h>
#include "rcbasic_symbol.h"

BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_EVENT_TYPE(wxEVT_MYTHREAD, -1)
END_DECLARE_EVENT_TYPES()

class parserThread : public wxThread
{
    public:
        parserThread(wxEvtHandler* pParent, int param, wxFrame* p_frame);
        void OnExit();
    private:
        wxFrame* parent_frame;
        int m_param;
        void* Entry();
        wxString file_text;
        std::vector<wxString> contents;
        wxStopWatch sw_timer;

        bool runParser(wxCommandEvent evt);

        std::vector<rcbasic_symbol> s_list;
        std::vector<rcbasic_symbol>* sym_list;


        void readContents();

        bool inSymbolList(rcbasic_symbol sym);

        void addSymbol(rcbasic_symbol sym);
    protected:
        wxEvtHandler* m_pParent;

};

#endif // PARSERTHREAD_H_INCLUDED
