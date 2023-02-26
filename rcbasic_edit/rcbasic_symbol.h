#ifndef RCBASIC_SYMBOL_H_INCLUDED
#define RCBASIC_SYMBOL_H_INCLUDED

#include <wx/wx.h>
#include <wx/treectrl.h>
#include <wx/filename.h>

struct rcbasic_symbol
{
    wxString id;
    int line;
    int dimensions;
    int token_type;
    bool in_list;
    wxString upper_id; //storing id uppercase to speed up sort
    wxFileName source_file;
    bool is_global=false;
};

class rc_symbol_treeItem_data : public wxTreeItemData
{
    public:
        rcbasic_symbol symbol;
        rc_symbol_treeItem_data(rcbasic_symbol sym)
        {
            symbol = sym;
        }
};

#endif // RCBASIC_SYMBOL_H_INCLUDED
