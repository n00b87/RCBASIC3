#ifndef EVAL_H_INCLUDED
#define EVAL_H_INCLUDED

#include <iostream>
#include "tokenizer.h"
//#include <wx/wx.h>
using namespace std;

#define TOKEN_TYPE_VARIABLE 0
#define TOKEN_TYPE_FUNCTION 1

struct rcbasic_id_token
{
    string name;
    int dimensions;
    int token_type;
    string d1;
    string d2;
    string d3;
};

vector<rcbasic_id_token> id_tokens;

void add_id_token(rcbasic_id_token t)
{
    for(int i = 0; i < id_tokens.size(); i++)
        if(id_tokens[i].name.compare(t.name)==0)
            return;
    id_tokens.push_back(t);
}

bool rc_eval(string line, bool* isInFunction)
{
    //adding an extra character to line to avoid a memory leak
    line += "  ";

    bool fn_define = *isInFunction;

    clearTokens();
    id_tokens.clear();

    if(!tokens(line))
    {
        return false;
    }


    int i = 0;

    int dim_scope = 0;
    bool is_dim_expr = false;
    string dim_token = "";

    bool dim_define = false;

    rcbasic_id_token dim_id;

    dim_id.name = "";
    dim_id.dimensions = 0;

    tmp_token.push_back("<:>");

    int expr_token_index = 0;

    bool fn_expr = false;

    rcbasic_id_token fn_id;

    for(i = 0; i < tmp_token.size(); i++)
    {
        if(expr_token_index == 0)
        {
            expr_token_index++;

            if(tmp_token.size() > (i + 1))
            {
                if(tmp_token[i].substr(0, 4).compare("<id>")==0 && tmp_token[i+1].compare("<equal>")==0 && (!fn_define))
                {
                    dim_id.name = tmp_token[i].substr(4);
                    dim_id.dimensions = 0;
                    dim_id.token_type = TOKEN_TYPE_VARIABLE;
                    add_id_token(dim_id);

                    dim_id.name = "";
                    dim_id.dimensions = 0;
                }
                else if( (tmp_token[i].compare("<function>")==0 || tmp_token[i].compare("<subp>")==0) && tmp_token[i+1].substr(0,4).compare("<id>")==0 )
                {
                    fn_define = true;
                    fn_expr = true;

                    dim_id.token_type = TOKEN_TYPE_FUNCTION;
                    dim_id.dimensions = 0;

                    dim_define = false;
                    is_dim_expr = false;
                    dim_scope = 0;
                    dim_id.name = tmp_token[i+1].substr(4);
                    //wxPuts(_("found function: ") + dim_id.name);
                }
                else if(tmp_token[i].compare("<end>")==0 && (tmp_token[i+1].compare("<function>")==0 || tmp_token[i+1].compare("<subp>")==0))
                {
                    //wxPuts(_("END FUNC"));
                    fn_define = false;
                    i++;
                    continue;
                }
            }
        }

        if(tmp_token[i].compare("<dim>")==0 && (!fn_define))
        {
            dim_token = tmp_token[i];
            dim_scope = 0;
            is_dim_expr = true;
            dim_define = true;
            dim_id.token_type = TOKEN_TYPE_VARIABLE;
            continue;
        }
        else if(tmp_token[i].compare("<redim>")==0)
        {
            dim_token = tmp_token[i];
            dim_scope = 0;
            is_dim_expr = true;
            dim_define = false;
            continue;
        }


        if(tmp_token[i].compare("<square>")==0)
        {
            dim_scope++;

            if(dim_scope==1 && dim_id.token_type==TOKEN_TYPE_VARIABLE)
                dim_id.dimensions = 1;
        }

        if(tmp_token[i].compare("<par>")==0)
        {
            dim_scope++;

            if(dim_scope==1 && dim_id.token_type==TOKEN_TYPE_FUNCTION)
                dim_id.dimensions = 1;
        }


        if(tmp_token[i].compare("</par>")==0 || tmp_token[i].compare("</square>")==0)
            dim_scope--;

        if(tmp_token[i].compare("<comma>")==0 && dim_scope==1)
            dim_id.dimensions++;

        if(is_dim_expr==true && dim_scope==0)
        {
            if(tmp_token[i].compare("<comma>")==0)
            {
                if(dim_define && dim_id.name.compare("")!=0)
                    add_id_token(dim_id);

                dim_id.name = "";
                dim_id.dimensions = 0;

                tmp_token[i] = "<:>";
                tmp_token.insert(tmp_token.begin()+ (i+1), dim_token);
            }
            else if(tmp_token[i].substr(0,4).compare("<id>")==0)
            {
                dim_id.name = tmp_token[i].substr(4);
            }
        }

        if(tmp_token[i].compare("<:>")==0)
        {
            expr_token_index = 0;

            if((!fn_define) && dim_define && dim_id.name.compare("")!=0)
                add_id_token(dim_id);
            else if(fn_expr && dim_id.name.compare("")!=0)
                add_id_token(dim_id);

            dim_id.name = "";
            dim_id.dimensions = 0;

            dim_define = false;
            is_dim_expr = false;
            fn_expr = false;
        }
    }

    isInFunction[0] = fn_define;

    return true;
}

#endif // EVAL_H_INCLUDED
