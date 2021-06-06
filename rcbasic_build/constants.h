#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include <vector>

struct rc_user_constant
{
    string const_name;
    vector<string> const_tokens;
};

vector<rc_user_constant> rc_constants;

int create_constant(string c_name)
{
    for(int i = 0; i < rc_constants.size(); i++)
    {
        if(rc_constants[i].const_name.compare(c_name)==0)
            return -1; //constant already exists
    }
    int const_id = rc_constants.size();

    rc_user_constant c;
    c.const_name = c_name;

    rc_constants.push_back(c);
    return const_id;
}

void add_const_token(int c_id, string c_token)
{
    rc_constants[i].const_tokens.push_back(c_token);
}

#endif // CONSTANTS_H_INCLUDED
