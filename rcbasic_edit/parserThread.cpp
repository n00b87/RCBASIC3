#include "parserThread.h"
#include "rcbasic_symbol.h"
#include "eval.h"
#include "rcbasic_edit_frame.h"
#include <wx/stopwatch.h>

DEFINE_EVENT_TYPE(wxEVT_MYTHREAD)

wxSemaphore* page_sem;

bool page_lock()
{
    page_sem->Wait();
}

bool page_unlock()
{
    page_sem->Post();
}


parserThread::parserThread(wxEvtHandler* pParent, int param, wxFrame* p_frame) : wxThread(wxTHREAD_DETACHED), m_pParent(pParent)
{
    //pass parameters into the thread
    m_param = param;
    //file_text = txt + _("\n");
    parent_frame = p_frame;

    rcbasic_edit_frame* frame = (rcbasic_edit_frame*) parent_frame;
    sym_list = new std::vector<rcbasic_symbol>;
    //s_list = frame->getSymbols();
}


void parserThread::readContents()
{
    contents.clear();
    rcbasic_edit_frame* frame = (rcbasic_edit_frame*) parent_frame;
    notebook_mutex.Lock();
    if(frame->getCurrentFile())
    {
        if(frame->getCurrentFile()->getTextCtrl())
        {
            file_text = frame->getCurrentFile()->getTextCtrl()->GetText() + _(" \n");
        }
        else
        {
            notebook_mutex.Unlock();
            return;
        }
    }
    else
    {
        notebook_mutex.Unlock();
        return;
    }

    notebook_mutex.Unlock();

    wxString current_line = _("");
    wxString current_char;

    for(int i = 0; i < file_text.length(); i++)
    {
        current_char = file_text.substr(i,1);
        if(current_char.compare(_("\n"))==0)
        {
            contents.push_back(current_line);
            current_line = _("");
        }
        else
        {
            current_line += current_char;
        }
    }
}


bool parserThread::inSymbolList(rcbasic_symbol sym)
{

    for(int i = 0; i < s_list.size(); i++)
    {

        if(sym.id.compare(s_list[i].id)==0 && sym.line==s_list[i].line && sym.dimensions==s_list[i].dimensions)
        {
            return true;
        }
    }

    return false;
}

void parserThread::addSymbol(rcbasic_symbol sym)
{
    for(int i = 0; i < sym_list->size(); i++)
    {
        rcbasic_symbol list_item = sym_list[0][i];
        if(list_item.id.compare(sym.id)==0 && list_item.token_type == sym.token_type)
        {
            //delete sym;
            return;
        }

    }
    sym_list->push_back(sym);
}

void* parserThread::Entry()
{
    wxCommandEvent evt(wxEVT_MYTHREAD, GetId());

    rcbasic_edit_frame* frame = (rcbasic_edit_frame*) parent_frame;

    bool current_file_flag = false;

    while(true)
    {
        if(TestDestroy())
        {
            break;
        }

        notebook_mutex.Lock();
        current_file_flag = (frame->getCurrentFile()!=NULL);

        if(current_file_flag)
        {
            current_file_flag = (frame->getCurrentFile()->getTextCtrl() && !frame->symbolUpdateInProgress);

            if(current_file_flag)
            {
                frame->symbolUpdateInProgress = true;
                frame->pre_parsed_page = frame->getCurrentFile()->getTextCtrl();
                notebook_mutex.Unlock();
                runParser(evt);
            }
            else
            {
                notebook_mutex.Unlock();
            }
        }
        else
        {
            frame->symbolUpdateInProgress = true;
            frame->pre_parsed_page = NULL;
            notebook_mutex.Unlock();
            //contents.clear();
            wxPostEvent(m_pParent, evt);
        }

        wxMilliSleep(400);
    }

    return NULL;
}

bool parserThread::runParser(wxCommandEvent evt)
{
    if(sym_list)
    {
        //delete sym_list;
        //sym_list = NULL;
        sym_list->clear();
    }

    rcbasic_edit_frame* frame = (rcbasic_edit_frame*) parent_frame;

    s_list = frame->getSymbols();

    readContents();

    int contents_changed = 0;

    bool fn_define = false;

    sw_timer.Start(0);


    for(int i = 0; i < contents.size(); i++)
    {
        if(TestDestroy())
            break;

        rc_eval(std::string(contents[i].mb_str()), &fn_define);
        //wxPuts(_("EVAL RAN"));
        for(int t_count = 0; t_count < id_tokens.size(); t_count++)
        {
            //wxPrintf( wxString(id_tokens[t_count].name.c_str(), wxConvUTF8) + _("[%d]:%d\n"), id_tokens[t_count].dimensions, i+1 );
            rcbasic_symbol sym;// = new rcbasic_symbol();
            sym.id = id_tokens[t_count].name;
            sym.line = i;
            sym.dimensions = id_tokens[t_count].dimensions;
            sym.token_type = id_tokens[t_count].token_type;
            sym.in_list = id_tokens[t_count].is_in_list;

            if(!inSymbolList(sym))
                contents_changed = 1;

            notebook_mutex.Lock();
            addSymbol(sym);
            notebook_mutex.Unlock();

            if(sw_timer.Time()>5)
            {
                wxMilliSleep(5);
                sw_timer.Start(0);
            }
        }

        //if(i%200==0)
        if(sw_timer.Time()>1)
        {
            wxMilliSleep(5);
            sw_timer.Start(0);
        }

    }

    notebook_mutex.Lock();
    if(sym_list->size() != s_list.size())
        contents_changed = 1;

    //can be used to set some identifier for the data
    evt.SetInt(contents_changed);

    frame->parsed_page = frame->pre_parsed_page;
    evt.SetClientData((void*)sym_list);

    wxPostEvent(m_pParent, evt);

    notebook_mutex.Unlock();


    return true;
}

void parserThread::OnExit()
{
    rcbasic_edit_frame* frame = (rcbasic_edit_frame*) parent_frame;
    if(frame->getSymSem())
        frame->getSymSem()->Post();
}
