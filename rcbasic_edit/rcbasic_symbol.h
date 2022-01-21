#ifndef RCBASIC_SYMBOL_H_INCLUDED
#define RCBASIC_SYMBOL_H_INCLUDED

struct rcbasic_symbol
{
    wxString id;
    int line;
    int dimensions;
    int token_type;
};

#endif // RCBASIC_SYMBOL_H_INCLUDED
