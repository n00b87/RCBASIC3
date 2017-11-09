#ifndef IDENTIFIER_H_INCLUDED
#define IDENTIFIER_H_INCLUDED

#include <inttypes.h>
#include "rc_global.h"
#include "rc_utility.h"
#include "rc_debug.h"
//identifier structure information

//identifier types
#define ID_TYPE_NUM 1
#define ID_TYPE_STR 2
#define ID_TYPE_FN_NUM 3
#define ID_TYPE_FN_STR 4
#define ID_TYPE_BYREF_NUM 5
#define ID_TYPE_BYREF_STR 6
#define ID_TYPE_ARR_NUM 7
#define ID_TYPE_ARR_STR 8
#define ID_TYPE_SUB 9
#define ID_TYPE_USER 10
#define ID_TYPE_FN_USER 11

#define BLOCK_STATE_MAIN 0
#define BLOCK_STATE_TYPE 1
#define BLOCK_STATE_FUNCTION 2
#define BLOCK_STATE_SUB 3
#define BLOCK_STATE_FOR 4
#define BLOCK_STATE_WHILE 5
#define BLOCK_STATE_DO 6
#define BLOCK_STATE_IF 7
#define BLOCK_STATE_SELECT 8

using namespace std;

string current_scope = "main";
int current_block_state = BLOCK_STATE_MAIN; //This hold different states depending on the type of block the program is currently in ie. type, function, sub, for, while, do, if, select
int current_type_index = 0;
int current_fn_index = 0;

//array dimension structure
struct user_array_dim
{
    int dim_size[3];
};


//user defined type structure
struct user_type
{
    string name; //name of the type
    int num_members; //number of members
    vector<string> member_name; //name of the members in the type
    vector<int> member_type; //type of each member
    vector<int> member_utype_index;
    vector<int> member_dim_count; //number of dimensions for each member
    vector<user_array_dim> member_dim;  //size of each dimension in an array
};

//identifier structure
struct identifier
{
    string name; //variable or function name
    string scope; //the scope this identifier was created in
    int type; //the identifier type, it will be one of the types above
    int type_index;  //if the identifier is a user_type, then this will be the index of the type within the utype vector
    int num_args; //number of arguments in a function or number of dimensions in an array
    uint64_t dim_size[3]; //size of each dimension in an array, up to 3 dimensions are supported
    vector<string> fn_arg; //function argument name
    vector<int> fn_arg_type; //function argument type
    vector<int> fn_arg_utype;
    uint64_t vec_pos; //position in num, string, or user type vector for runtime
};

vector<user_type> utype;
vector<identifier> id;

int num_id_count = 0;
int str_id_count = 0;
int usr_id_count = 0;

bool idExists(string id_name)
{
    for(int i = 0; i < id.size(); i++)
    {
        if(id_name.compare(id[i].name)==0)
            return true;
    }
    return false;
}

bool idExistsInScope(string id_name)
{
    id_name = StringToLower(id_name);
    int cs_start = 0;
    int cs_length = 0;
    bool match = true;
    string id_scope = "";
    for(int i = 0; i < id.size(); i++)
    {
        if(id_name.compare(id[i].name)==0)
        {
            //cout << endl;
            //cout << "ID found in: " << id[i].scope << endl;
            //cout << "Current Scope: " << current_scope << endl;
            //cout << endl;
            //id has to exist in or above current scope
            if(current_scope.length() < id[i].scope.length())
            {
                continue;
            }

            id_scope = "";
            cs_start = 0;
            cs_length = 0;
            match = true;

            for(int n = 0; n < id[i].scope.length(); n++)
            {
                if(id[i].scope.substr(n,1).compare(".")==0 || n == id[i].scope.length()-1)
                {
                    if(id_scope.compare(current_scope.substr(cs_start,id_scope.length()))!=0)
                    {
                        //cout << endl << "Current = " << current_scope.substr(cs_start, id_scope.length()) << endl << "ID = " << id_scope << endl;
                        match = false;
                        break;
                    }
                    id_scope = "";
                    cs_start = n+1;
                }
                else
                {
                    id_scope += id[i].scope.substr(n, 1);
                }
            }

            if(match)
                return true;
        }
    }
    return false;
}

void output_vars()
{
    for(int i = 0; i < id.size(); i++)
    {
        cout << endl;
        cout << "id: " << id[i].name << " : " << id[i].vec_pos << endl;
        cout << "type: " << id[i].type << endl;
        if(id[i].type == ID_TYPE_USER)
            cout << "type_id: " << utype[id[i].type_index].name << endl;
        cout << "scope: " << id[i].scope << endl;
        cout << "dim: " << id[i].num_args << endl;
        for(int n = 0; n < id[i].num_args; n++)
            cout << "dim[" << n << "] = " << id[i].dim_size[n] << endl;
    }
    cout << endl;
}

int getUType(string utype_name)
{
    for(int i = 0; i < utype.size(); i++)
    {
        if(utype_name.compare(utype[i].name)==0)
        {
            return i;
        }
    }
    rc_setError(utype_name + " does not name a type");
    return -1;
}

bool create_type(string utype_name)
{
    if(isKeyWord(utype_name) || idExistsInScope(utype_name))
    {
        rc_setError(utype_name + " is not a valid identifier");
        return false;
    }
    current_type_index = utype.size();
    //cout << "current type_index = " << current_type_index << endl;
    user_type ut;
    ut.name = utype_name;
    ut.num_members = 0;
    utype.push_back(ut);
    return true;
}

bool memberExists(string member_name)
{
    for(int i = 0; i < utype[current_type_index].num_members; i++)
    {
        if(utype[current_type_index].member_name[i].compare(member_name)==0)
            return true;
    }
    return false;
}

bool add_type_member(string member_name, int member_type, string member_utype_name, int member_dim_count, int dim1 = 0, int dim2 = 0, int dim3 = 0)
{
    int m_utype_index = getUType(member_utype_name);
    if(m_utype_index == current_type_index)
    {
        //cout << "you canno do is" << endl;
        rc_setError("Cannot create member of type from within itself");
        return false;
    }
    //cout << "utype index = " << current_type_index << endl;
    int utype_index = current_type_index;
    int utype_current_member = utype[utype_index].num_members;
    utype[utype_index].member_name.push_back(member_name);
    utype[utype_index].member_type.push_back(member_type);
    utype[utype_index].member_dim_count.push_back(member_dim_count);
    utype[utype_index].member_utype_index.push_back(m_utype_index);
    user_array_dim d;
    d.dim_size[0] = dim1;
    d.dim_size[1] = dim2;
    d.dim_size[2] = dim3;
    utype[utype_index].member_dim.push_back(d);
    //cout << member_name << " has " << member_dim_count << " dimensions" << endl;
    //utype[utype_index].member_dim[utype_current_member].dim_size[1] = dim2;
    //utype[utype_index].member_dim[utype_current_member].dim_size[2] = dim3;
    utype[utype_index].num_members++;
    return true;
}

//return the index of the id name or -1 on failure
int getIDInScope_ByIndex(string id_name, string check_scope="")
{
    id_name = StringToLower(id_name);
    int cs_start = 0;
    int cs_length = 0;
    bool match = true;
    string id_scope = "";
    if(check_scope.compare("")==0)
        check_scope = current_scope;
    int scope_match = 0;
    int tmp_match = 0;
    int id_match = -1;
    for(int i = 0; i < id.size(); i++)
    {
        if(id_name.compare(id[i].name)==0)
        {
            //cout << endl;
            //cout << "ID_NAME = " << id[i].name << endl;
            //cout << "ID found in: " << id[i].scope << endl;
            //cout << "Current Scope: " << check_scope << endl;
            //cout << endl;
            //id has to exist in or above current scope
            if(check_scope.length() < id[i].scope.length())
            {
                continue;
            }

            id_scope = "";
            cs_start = 0;
            cs_length = 0;
            match = true;
            tmp_match = 0;

            for(int n = 0; n < id[i].scope.length(); n++)
            {
                if(id[i].scope.substr(n,1).compare(".")==0 || n == id[i].scope.length()-1)
                {
                    if(id_scope.compare(check_scope.substr(cs_start,id_scope.length()))!=0)
                    {
                        //cout << endl << "Current = " << check_scope.substr(cs_start, id_scope.length()) << endl << "ID = " << id_scope << endl;
                        match = false;
                        tmp_match = 0;
                        break;
                    }
                    id_scope = "";
                    cs_start = n+1;
                    tmp_match++;
                }
                else
                {
                    id_scope += id[i].scope.substr(n, 1);
                }
            }

            if(match && tmp_match > scope_match)
            {
                //cout << "FOUND MATCH FOR [" << id[i].name << "] : " << id[i].vec_pos << " ; " << i << endl;
                id_match = i;
                scope_match = tmp_match;
                //return id[i].vec_pos;
            }
        }
    }
    return id_match;
}

//return the index of the id name or -1 on failure
int getIDInScope(string id_name, string check_scope="")
{
    id_name = StringToLower(id_name);
    int cs_start = 0;
    int cs_length = 0;
    bool match = true;
    string id_scope = "";
    if(check_scope.compare("")==0)
        check_scope = current_scope;
    int scope_match = 0;
    int tmp_match = 0;
    int id_match_vecpos = -1;
    for(int i = 0; i < id.size(); i++)
    {
        if(id_name.compare(id[i].name)==0)
        {
            //cout << endl;
            //cout << "ID_NAME = " << id[i].name << endl;
            //cout << "ID found in: " << id[i].scope << endl;
            //cout << "Current Scope: " << check_scope << endl;
            //cout << endl;
            //id has to exist in or above current scope
            if(check_scope.length() < id[i].scope.length())
            {
                continue;
            }

            id_scope = "";
            cs_start = 0;
            cs_length = 0;
            match = true;
            tmp_match = 0;

            for(int n = 0; n < id[i].scope.length(); n++)
            {
                if(id[i].scope.substr(n,1).compare(".")==0 || n == id[i].scope.length()-1)
                {
                    if(id_scope.compare(check_scope.substr(cs_start,id_scope.length()))!=0)
                    {
                        //cout << endl << "Current = " << check_scope.substr(cs_start, id_scope.length()) << endl << "ID = " << id_scope << endl;
                        match = false;
                        tmp_match = 0;
                        break;
                    }
                    id_scope = "";
                    cs_start = n+1;
                    tmp_match++;
                }
                else
                {
                    id_scope += id[i].scope.substr(n, 1);
                }
            }

            if(match && tmp_match > scope_match)
            {
                //cout << "FOUND MATCH FOR [" << id[i].name << "] : " << id[i].vec_pos << " ; " << i << endl;
                id_match_vecpos = id[i].vec_pos;
                scope_match = tmp_match;
                //return id[i].vec_pos;
            }
        }
    }
    return id_match_vecpos;
}

bool isValidIDName(string name)
{
    name = StringToLower(name);
    if(name.compare("")==0)
        return false;

    if(name.substr(name.length()-1,1).compare("$")==0)
    {
        name = name.substr(0, name.length()-1);

        if(name.compare("")==0)
            return false;
    }

    if(!isalpha(name[0]))
        return false;

    for(int i = 0; i < name.length(); i++)
    {
        if( (!isalnum(name[i])) && (name.substr(i,1).compare("_")!=0) )
            return false;
    }

    if(isKeyWord(name))
        return false;

    return true;
}

void set_vectorPosition(identifier &var)
{
    if(var.type == ID_TYPE_ARR_NUM || var.type == ID_TYPE_NUM)
    {
        var.vec_pos = num_id_count;
        num_id_count++;
    }
    else if(var.type == ID_TYPE_STR || var.type == ID_TYPE_ARR_STR)
    {
        var.vec_pos = str_id_count;
        str_id_count++;
    }
    else if(var.type == ID_TYPE_USER)
    {
        var.vec_pos = usr_id_count;
        usr_id_count++;
    }
}

int get_vectorPosition(string scope, string id_name)
{
    return -1;
}

bool id_emit(identifier var)
{
    //alloc_xxx  ID,  DIM_COUNT,  DIM1_SIZE,  DIM2_SIZE,  DIM3_SIZE
    string emit_asm = "";
    string var_id = "";
    string dim_count = "";
    string dim_size[3];
    if(var.type == ID_TYPE_ARR_NUM || var.type == ID_TYPE_NUM)
    {
        emit_asm = "alloc_num ";
    }
    else if(var.type == ID_TYPE_ARR_STR || var.type == ID_TYPE_STR)
    {
        emit_asm = "alloc_str ";
    }
    else if(var.type == ID_TYPE_USER)
    {
        emit_asm = "alloc_usr ";
    }
    else
    {
        rc_setError("Could not identify type");
        return false;
    }

    var_id = rc_intToString(getIDInScope(var.name, var.scope));
    dim_count = rc_intToString(var.num_args);
    dim_size[0] = rc_intToString(var.dim_size[0]);
    dim_size[1] = rc_intToString(var.dim_size[1]);
    dim_size[2] = rc_intToString(var.dim_size[2]);

    emit_asm += var.scope + "->" + var.name + " : " + var_id + " " + dim_count + " " + dim_size[0] + " " + dim_size[1] + " " + dim_size[2];
    vm_asm.push_back(emit_asm);

    return true;
}

bool create_type_members(int id_index, int type_index)
{
    //cout << "start type_member" << endl;
    //cout << "id_index = " << id_index << endl;
    //cout << "utype_index = " << id[id_index].type_index << endl;
    //cout << "num_members = " << utype[0].num_members << endl;
    identifier var;
    int utype_index = id[id_index].type_index;
    int member_index = 0;
    user_array_dim d;
    if( (id_index < 0 || id_index >= id.size()) || (utype_index < 0 || utype_index >= utype.size()) )
        return true;
    for(int i = 0; i < utype[utype_index].num_members; i++)
    {
        member_index = id.size();
        var.name = utype[utype_index].member_name[i];
        var.type = utype[utype_index].member_type[i];
        var.type_index = utype[utype_index].member_utype_index[i];
        set_vectorPosition(var);
        //cout << "vec -> " << var.vec_pos << endl;
        var.scope = id[id_index].scope + "." + id[id_index].name;
        var.num_args = utype[utype_index].member_dim_count[i];
        var.dim_size[0] = utype[utype_index].member_dim[i].dim_size[0];
        var.dim_size[1] = utype[utype_index].member_dim[i].dim_size[1];
        var.dim_size[2] = utype[utype_index].member_dim[i].dim_size[2];
        //cout << "member = " << var.name << " : " << var.vec_pos << endl;
        //cout << "member_type = " << var.type << endl;
        //cout << "member_type_index = " << var.type_index << endl;

        id.push_back(var);
        //id_emit(var);
        if(var.type = ID_TYPE_USER)
        {
            if(!create_type_members(member_index, var.type_index))
            {
                rc_setError("Could not create member " + var.name + " inside " + var.scope);
                return false;
            }
        }
    }
    //cout << "end type_member" << endl;
    return true;
}

bool create_variable(string name, int type, string utype_name="")
{
    identifier var;
    var.name = name;
    var.type = type;
    var.scope = current_scope;
    if(var.type == ID_TYPE_USER)
    {
        var.type_index = getUType(utype_name);
        if(var.type_index < 0)
        {
            return false;
        }
        int var_index = id.size();
        var.num_args = 0;
        set_vectorPosition(var);
        id.push_back(var);
        id_emit(var);
        //create all sub variables here
        create_type_members(var_index, var.type_index);
    }
    else
    {
        var.num_args = 0;
        set_vectorPosition(var);
        id.push_back(var);
        id_emit(var);
    }
    return true;
}

bool create_array(string name, int type, string utype_name, int dim_count)
{
    identifier var;
    var.name = name;
    var.type = type;
    var.scope = current_scope;
    if(var.type == ID_TYPE_USER)
    {
        var.type_index = getUType(utype_name);
        if(var.type_index < 0)
        {
            rc_setError(utype_name + " does not name a type");
            return false;
        }
        var.num_args = dim_count;
        if(dim_count < 1 || dim_count > 3)
        {
            rc_setError("Array must be in the range of 1 to 3 dimensions");
            return false;
        }
        int var_index = id.size();
        set_vectorPosition(var);
        id.push_back(var);
        //id_emit(var);
        //create all sub variables here
        create_type_members(var_index, var.type_index);
    }
    else
    {
        var.num_args = dim_count;
        if(dim_count < 1 || dim_count > 3)
        {
            rc_setError("Array must be in the range of 1 to 3 dimensions");
            return false;
        }
        set_vectorPosition(var);
        id.push_back(var);
        id_emit(var);
    }
    return true;
}

bool create_function(string name, int type, string utype_name)
{
    identifier fn;
    fn.name = name;
    fn.type = type;
    if(fn.type == ID_TYPE_FN_USER)
    {
        fn.type_index = getUType(utype_name);
        if(fn.type_index < 0)
        {
            rc_setError(utype_name + " does not name a type");
            return false;
        }
    }
    fn.num_args = 0;  //function args default to 0; args are added with add_function_args
    current_fn_index = id.size();
    id.push_back(fn);
    return true;
}

bool add_function_arg(string arg_name, int arg_type, string utype_name)
{
    int fn_index = current_fn_index;
    id[fn_index].fn_arg.push_back(arg_name);
    id[fn_index].fn_arg_type.push_back(arg_type);
    if(arg_type == ID_TYPE_USER)
    {
        int arg_utype = getUType(utype_name);
        if(arg_utype < 0)
        {
            rc_setError(utype_name + " does not name a type");
            return false;
        }
        id[fn_index].fn_arg_utype.push_back(arg_utype);
    }
    id[fn_index].num_args++;
    return true;
}

bool set_scope(string scope)
{
    current_scope = scope;
    return false;
}

bool exit_scope(int num_levels)
{
    if(num_levels <= 0)
        return false;
    int lv = 0;
    string scope = current_scope;
    for(int i = scope.length()-1; i > 0; i--)
    {
        if(scope.substr(i,1).compare(".")==0)
        {
            lv++;
            scope = scope.substr(0,i);
            if(lv==num_levels)
            {
                current_scope = scope;
                return true;
            }
        }
    }
    current_scope = scope;
    return false;
}

bool enter_scope(string sub_scope)
{
    return false;
}
#endif // IDENTIFIER_H_INCLUDED
