#include <iostream>
#include "tokenizer.h"
using namespace std;

struct rcbasic_id_token
{
    string name;
    int dimensions;
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

bool rc_eval(string line)
{
    //adding an extra character to line to avoid a memory leak
    line += "  ";

    clearTokens();

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

    for(i = 0; i < tmp_token.size(); i++)
    {
        if(tmp_token[i].compare("<dim>")==0)
        {
            dim_token = tmp_token[i];
            dim_scope = 0;
            is_dim_expr = true;
            dim_define = true;
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

            if(dim_scope==1)
                dim_id.dimensions = 1;
        }

        if(tmp_token[i].compare("<par>")==0)
            dim_scope++;

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
            if(dim_define && dim_id.name.compare("")!=0)
                add_id_token(dim_id);

            dim_id.name = "";
            dim_id.dimensions = 0;

            dim_define = false;
            is_dim_expr = false;
        }
    }

    return true;
}