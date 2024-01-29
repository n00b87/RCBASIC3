#ifndef IDENTIFIER_H_INCLUDED
#define IDENTIFIER_H_INCLUDED

#include <inttypes.h>
#include <stack>
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
#define ID_TYPE_BYREF_USER 12
#define ID_TYPE_USER_NUM 13
#define ID_TYPE_USER_STR 14
#define ID_TYPE_USER_NUM_ARRAY 15
#define ID_TYPE_USER_STR_ARRAY 16

#define ID_TYPE_USER_ALL(id_index)   ( id[id_index].type == ID_TYPE_USER || id[id_index].type == ID_TYPE_BYREF_USER || id[id_index].type == ID_TYPE_USER_NUM || id[id_index].type == ID_TYPE_USER_STR || id[id_index].type == ID_TYPE_USER_NUM_ARRAY || id[id_index].type == ID_TYPE_USER_STR_ARRAY )

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
bool isInFunctionScope = false;
int current_fn_id_count = 0;

uint64_t current_for_index = 0;
uint64_t current_while_index = 0;
uint64_t current_do_index = 0;

uint64_t current_if_index = 0;
uint64_t current_select_index = 0;

stack<int> block_state;
stack<string> for_end;
stack<uint64_t> for_counter;
stack<string> do_end;
stack<string> while_end;

bool isFunctionArg_flag = false;

bool enable_presets = true;

struct if_data
{
    uint64_t index = 0;
    uint64_t condition = 0;
    bool else_set = false;
};

struct select_data
{
    int case_type = ID_TYPE_NUM;
    int index = 0;
    int case_index = 0;
    bool default_set = false;
    bool case_set = false;
};

stack<if_data> if_block;
stack<select_data> select_block;

//array dimension structure
struct user_array_dim
{
    int dim_size[3];
};


//user defined type structure
struct rc_type_description
{
    uint32_t nidCount;
    uint32_t nidDim;
    uint32_t nidDimSize[3];

    uint32_t sidCount;
    uint32_t sidDim;
    uint32_t sidDimSize[3];

    uint32_t uidCount;
    uint32_t uidDim;
    uint32_t uidDimSize[3];
    uint32_t uidTypeIndex;
};

struct user_type
{
    string name; //name of the type
    int num_members; //number of members
    vector<string> member_name; //name of the members in the type
    vector<int> member_type; //type of each member
    vector<int> member_vec_pos; //the vector position for each member
    int nidCount = 0;
    int sidCount = 0;
    int uidCount = 0;
    vector<int> member_utype_index;
    vector<int> member_dim_count; //number of dimensions for each member
    vector<user_array_dim> member_dim;  //size of each dimension in an array
};

struct fid_vector_entry
{
    string vec_str;
    int type;
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
    vector<string> fn_reg;
    vector<uint64_t> fn_arg_vec;
    vector<int> fn_arg_type; //function argument type
    vector<int> fn_arg_utype;
    uint64_t vec_pos; //position in num, string, or user type vector for runtime
    bool isBuiltin = false;
    uint64_t vmFunctionIndex = 0;
    bool isArrayArg = false;
    vector<fid_vector_entry> fn_var;
    bool isChild = false;
    int parent_index = -1;
};

uint64_t current_vmFunction_index = 0;

vector<user_type> utype;
vector<identifier> id;

int num_id_count = 0;
int str_id_count = 0;
int usr_id_count = 0;

int fn_numCount = 0;
int fn_strCount = 0;
int fn_usrCount = 0;
int fn_byref_numCount = 0;
int fn_byref_strCount = 0;
int fn_byref_usrCount = 0;

int max_fn_numCount = 0;
int max_fn_strCount = 0;
int max_fn_usrCount = 0;
int max_fn_byref_numCount = 0;
int max_fn_byref_strCount = 0;
int max_fn_byref_usrCount = 0;

bool idExists(string id_name)
{
    id_name = StringToUpper(id_name);
    for(int i = 0; i < id.size(); i++)
    {
        if(id_name.compare(StringToUpper(id[i].name))==0)
            return true;
    }
    return false;
}

bool matchCurrentScope(string id_scope, string check_scope = "")
{
    string tmp_current_scope = "";
    string tmp_id_scope = "";

    int cs_i = 0;
    int id_i = 0;

    if(check_scope.compare("")==0)
        check_scope = current_scope;

    while(true)
    {
        tmp_current_scope = "";
        tmp_id_scope = "";
        for(; cs_i < check_scope.length(); cs_i++)
        {
            if(check_scope.substr(cs_i,1).compare(".")==0)
            {
                cs_i++;
                break;
            }
            tmp_current_scope += check_scope.substr(cs_i,1);
        }
        for(; id_i < id_scope.length(); id_i++)
        {
            if(id_scope.substr(id_i,1).compare(".")==0)
            {
                id_i++;
                break;
            }
            tmp_id_scope += id_scope.substr(id_i,1);
        }
        if(tmp_current_scope.compare(tmp_id_scope)!=0)
        {
            return false;
        }
        if(id_i == id_scope.length())
        {
            return true;
        }
    }
    return false;
}

bool idExistsInScope2(string id_name)
{
    id_name = StringToLower(id_name);
    int cs_start = 0;
    int cs_length = 0;
    bool match = true;
    string id_scope = "";
    for(int i = 0; i < id.size(); i++)
    {
        if(id_name.compare(StringToLower(id[i].name) )==0)
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

            //if(current_scope.find(id[i].scope)==0)
            if(matchCurrentScope(id[i].scope))
            {
                //cout << id_name << " -> " << id[i].name << " : " << id[i].scope << " : " << current_scope << endl;
                return true;
            }
        }
    }
    return false;
}

bool idExistsInScope(string id_name)
{
    bool exists = idExistsInScope2(id_name);
    if(!exists)
    {
        if(id_name.substr(id_name.length()-1,1).compare("$")==0)
            exists = idExistsInScope2(id_name.substr(0, id_name.length()-1));
        else
            exists = idExistsInScope2(id_name + "$");
    }
    return exists;
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
    utype_name = StringToLower(utype_name);
    for(int i = 0; i < utype.size(); i++)
    {
        //cout << "TYPE[" << i << "] = " << utype[i].name << endl;
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
    utype_name = StringToLower(utype_name);
    if(isKeyWord(utype_name) || idExistsInScope(utype_name))
    {
        rc_setError(utype_name + " is not a valid identifier");
        return false;
    }
    else if(getUType(utype_name)>=0)
    {
        rc_setError(utype_name + " already exists");
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

bool add_type_member(string member_name, int member_type, string member_utype_name, int member_dim_count, string dim1 = "n0", string dim2 = "n0", string dim3 = "n0")
{
    int m_utype_index = member_utype_name.compare("")!=0 ? getUType(member_utype_name) : -1;
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

    string dim_mem_type = "";

    switch(member_type)
    {
        case ID_TYPE_NUM:
            dim_mem_type = "!0 !" + rc_intToString(utype_current_member);
            utype[utype_index].member_type.push_back(ID_TYPE_USER_NUM);
            utype[utype_index].member_vec_pos.push_back(utype[utype_index].nidCount);
            utype[utype_index].nidCount++;
            break;
        case ID_TYPE_ARR_NUM:
            dim_mem_type = "!0 !" + rc_intToString(utype_current_member);
            utype[utype_index].member_type.push_back(ID_TYPE_USER_NUM_ARRAY);
            utype[utype_index].member_vec_pos.push_back(utype[utype_index].nidCount);
            utype[utype_index].nidCount++;
            break;
        case ID_TYPE_STR:
            dim_mem_type = "!1 !" + rc_intToString(utype_current_member);
            utype[utype_index].member_type.push_back(ID_TYPE_USER_STR);
            utype[utype_index].member_vec_pos.push_back(utype[utype_index].sidCount);
            utype[utype_index].sidCount++;
            break;
        case ID_TYPE_ARR_STR:
            dim_mem_type = "!1 !" + rc_intToString(utype_current_member);
            utype[utype_index].member_type.push_back(ID_TYPE_USER_STR_ARRAY);
            utype[utype_index].member_vec_pos.push_back(utype[utype_index].sidCount);
            utype[utype_index].sidCount++;
            break;
        case ID_TYPE_USER:
            dim_mem_type = "!2 !" + rc_intToString(utype_current_member);
            utype[utype_index].member_type.push_back(ID_TYPE_USER);
            utype[utype_index].member_vec_pos.push_back(utype[utype_index].uidCount);
            utype[utype_index].uidCount++;
            break;
        default:
            rc_setError("Invalid member type in type definition");
            return false;
            break;
    }

    utype[utype_index].member_dim_count.push_back(member_dim_count);
    utype[utype_index].member_utype_index.push_back(m_utype_index);

    dim1 = dim1.compare("")==0 ? "n0" : dim1;
    dim2 = dim2.compare("")==0 ? "n0" : dim2;
    dim3 = dim3.compare("")==0 ? "n0" : dim3;

    vm_asm.push_back("dim_tfield  !" + rc_intToString(utype_index) + " " + dim_mem_type + " !"
                                    + rc_intToString(member_dim_count) + " "
                                    + dim1 + " " + dim2 + " " + dim3);

    //NOTE: user_array_dim is no longer used
    user_array_dim d;
    //d.dim_size[0] = dim1;
    //d.dim_size[1] = dim2;
    //d.dim_size[2] = dim3;
    utype[utype_index].member_dim.push_back(d);
    //cout << member_name << " has " << member_dim_count << " dimensions" << endl;
    //utype[utype_index].member_dim[utype_current_member].dim_size[1] = dim2;
    //utype[utype_index].member_dim[utype_current_member].dim_size[2] = dim3;
    utype[utype_index].num_members++;
    return true;
}

//return the index of the id name or -1 on failure
int getIDInScope_ByIndex2(string id_name, string check_scope="")
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
        //if(StringToLower(id_name).compare("tst")==0 && StringToLower(id[i].name.substr(0,1)).compare("t")==0)
        //    cout << "CMP: " << id_name << " to " << id[i].name << endl;
        if(id_name.compare(StringToLower(id[i].name))==0)
        {
            //cout << endl;
            //cout << "ID_NAME = " << id[i].name << endl;
            //cout << "ID found in: " << id[i].scope << endl;
            //cout << "Current Scope: " << check_scope << endl;
            //cout << endl;
            //id has to exist in or above current scope
            if(check_scope.length() < id[i].scope.length())
            {
                //cout << "SCOPE CHECK: " << check_scope.length() << " <>  " << id[i].scope.length() << endl;
                continue;
            }

            //if(current_scope.find(id[i].scope)==0)
            if(matchCurrentScope(id[i].scope, check_scope))
            {
                cout << "FOUND MATCH FOR [" << id[i].name << "] : " << id[i].vec_pos << " ; " << i << endl << endl;
                return i;
            }
        }
    }
    return id_match;
}

int getIDInScope_ByIndex(string id_name, string check_scope="")
{
    int id_index = getIDInScope_ByIndex2(id_name, check_scope);

    if(id_index < 0)
    {
        if(id_name.substr(id_name.length()-1,1).compare("$")==0)
            id_index = getIDInScope_ByIndex2(id_name.substr(0, id_name.length()-1), check_scope);
        else
            id_index = getIDInScope_ByIndex2(id_name + "$", check_scope);
    }
    return id_index;
}

//return the index of the id name or -1 on failure
int getIDInScope2(string id_name, string check_scope="")
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
        if(id_name.compare(StringToLower(id[i].name))==0 || id[i].name.compare(id_name+"$")==0)
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

            //if(current_scope.find(id[i].scope)==0)
            if(matchCurrentScope(id[i].scope, check_scope))
            {
                cout << "FOUND MATCH FOR [" << id[i].name << "] : " << id[i].vec_pos << " ; " << i << endl;
                return id[i].vec_pos;
            }
        }
    }
    return id_match_vecpos;
}

int getIDInScope(string id_name, string check_scope="")
{
    if(check_scope.compare("")==0)
        check_scope = current_scope;

    int id_vec = getIDInScope2(id_name, check_scope);
    if(id_vec < 0)
    {
        if(id_name.substr(id_name.length()-1,1).compare("$")==0)
            id_vec = getIDInScope2(id_name.substr(0, id_name.length()-1), check_scope);
        else
            id_vec = getIDInScope2(id_name + "$", check_scope);
    }
    return id_vec;
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

void set_vectorPosition(identifier &var, bool isMember = false, int utype_index = 0, int member_index = 0)
{
    if(isMember)
    {
        var.vec_pos = utype[utype_index].member_vec_pos[member_index];
        return;
    }

    if(var.type == ID_TYPE_ARR_NUM || var.type == ID_TYPE_NUM || var.type == ID_TYPE_BYREF_NUM)
    {
        var.vec_pos = num_id_count;
        num_id_count++;
    }
    else if(var.type == ID_TYPE_STR || var.type == ID_TYPE_ARR_STR || var.type == ID_TYPE_BYREF_STR)
    {
        var.vec_pos = str_id_count;
        str_id_count++;
    }
    else if(var.type == ID_TYPE_USER || var.type == ID_TYPE_BYREF_USER)
    {
        var.vec_pos = usr_id_count;
        usr_id_count++;
    }
}

int get_vectorPosition(string scope, string id_name)
{
    return -1;
}

bool id_emit(identifier var, string dim1="_", string dim2="_", string dim3="_")
{
    //alloc_xxx  ID,  DIM_COUNT,  DIM1_SIZE,  DIM2_SIZE,  DIM3_SIZE
    string emit_asm = "";
    string var_id = "";
    string dim_count = "";
    string dim_size[3];
    if(var.type == ID_TYPE_ARR_NUM)
    {
        if(var.num_args > 0)
        {
            emit_asm += rc_intToString(var.num_args);
            if(var.num_args == 1 && dim1.substr(0,1).compare("n")==0)
                emit_asm = "dim_num1 ";
            else if(var.num_args == 2 && dim1.substr(0,1).compare("n")==0 && dim2.substr(0,1).compare("n")==0)
                emit_asm = "dim_num2 ";
            else if(var.num_args == 3 && dim1.substr(0,1).compare("n")==0 && dim2.substr(0,1).compare("n")==0 && dim3.substr(0,1).compare("n")==0)
                emit_asm = "dim_num3 ";
            else
            {
                rc_setError("Invalid number of arguments for " + var.name);
                return false;
            }
        }
        else
        {
            rc_setError("Must have atleast 1 dimension in array");
        }


        var_id = rc_intToString(getIDInScope(var.name, var.scope));

        emit_asm += "!" + var_id + " ";

        if(var.num_args == 1)
            emit_asm += dim1;
        else if(var.num_args == 2)
            emit_asm += dim1 + " " + dim2;
        else if(var.num_args == 3)
            emit_asm += dim1 + " " + dim2 + " " + dim3;

        vm_asm.push_back(emit_asm);
        return true;
    }
    else if(var.type == ID_TYPE_ARR_STR)
    {
        if(var.num_args > 0)
        {
            emit_asm += rc_intToString(var.num_args);
            if(var.num_args == 1 && dim1.substr(0,1).compare("n")==0)
                emit_asm = "dim_str1 ";
            else if(var.num_args == 2 && dim1.substr(0,1).compare("n")==0 && dim2.substr(0,1).compare("n")==0)
                emit_asm = "dim_str2 ";
            else if(var.num_args == 3 && dim1.substr(0,1).compare("n")==0 && dim2.substr(0,1).compare("n")==0 && dim3.substr(0,1).compare("n")==0)
                emit_asm = "dim_str3 ";
            else
            {
                rc_setError("Invalid number of arguments for " + var.name);
                return false;
            }
        }
        else
        {
            rc_setError("Must have atleast 1 dimension in array");
        }


        var_id = rc_intToString(getIDInScope(var.name, var.scope));

        emit_asm += "!" + var_id + " ";

        if(var.num_args == 1)
            emit_asm += dim1;
        else if(var.num_args == 2)
            emit_asm += dim1 + " " + dim2;
        else if(var.num_args == 3)
            emit_asm += dim1 + " " + dim2 + " " + dim3;

        vm_asm.push_back(emit_asm);
        return true;
    }
    else if(var.type == ID_TYPE_USER)
    {
        emit_asm = "dim_type ";

        if(var.num_args > 0)
        {
            emit_asm += rc_intToString(var.num_args);
            if(var.num_args == 1 && dim1.substr(0,1).compare("n")==0)
                emit_asm = "dim_type1 ";
            else if(var.num_args == 2 && dim1.substr(0,1).compare("n")==0 && dim2.substr(0,1).compare("n")==0)
                emit_asm = "dim_type2 ";
            else if(var.num_args == 3 && dim1.substr(0,1).compare("n")==0 && dim2.substr(0,1).compare("n")==0 && dim3.substr(0,1).compare("n")==0)
                emit_asm = "dim_type3 ";
            else
            {
                rc_setError("Invalid number of arguments for " + var.name);
                return false;
            }
        }

        var_id = rc_intToString(getIDInScope(var.name, var.scope));

        emit_asm += "!" + var_id + " !" + rc_intToString(var.type_index) + " ";

        if(var.num_args == 1)
            emit_asm += dim1;
        else if(var.num_args == 2)
            emit_asm += dim1 + " " + dim2;
        else if(var.num_args == 3)
            emit_asm += dim1 + " " + dim2 + " " + dim3;


        vm_asm.push_back(emit_asm);
        return true;
    }
    else
    {
        //rc_setError("Could not identify type");
        //return false;
    }

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
        var.isChild = true;
        var.parent_index = id_index;
        set_vectorPosition(var, true, utype_index, i);
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

bool create_variable(string name, int type, string utype_name="", int vec = -1)
{
    identifier var;
    var.name = name;
    var.type = type;
    var.isArrayArg = false;
    if(name.substr(0,1).compare("#")==0)
        var.scope = "main";
    else
        var.scope = current_scope;
    if(var.type == ID_TYPE_USER || var.type == ID_TYPE_BYREF_USER)
    {
        var.type_index = getUType(utype_name);
        if(var.type_index < 0)
        {
            rc_setError("Type \"" + utype_name +"\" does not exists");
            return false;
        }
        int var_index = id.size();
        var.num_args = 0;
        var.parent_index = -1;
        set_vectorPosition(var);
        id.push_back(var);
        id_emit(var);
        //create all sub variables here
        create_type_members(var_index, var.type_index);
    }
    else
    {
        var.num_args = 0;
        if(vec == -1)
        {
            set_vectorPosition(var);
            //cout << var.name << " <==> " << var.vec_pos << endl;
        }
        else
        {
            //cout << "set " << name << " to " << vec << endl;
            var.vec_pos = vec;
        }


        id.push_back(var);
        id_emit(var);
    }

    if(isInFunctionScope && !isFunctionArg_flag)
    {
        if(var.type == ID_TYPE_NUM || var.type == ID_TYPE_ARR_NUM)
            vm_asm.push_back("preset !" + rc_intToString(var.vec_pos) );
        else if(var.type == ID_TYPE_STR || var.type == ID_TYPE_ARR_STR)
            vm_asm.push_back("preset$ !" + rc_intToString(var.vec_pos));
    }
    isFunctionArg_flag = false;

    return true;
}

bool create_array(string name, int type, string utype_name, int dim_count, string dim1="", string dim2="", string dim3="", int vec = -1)
{
    identifier var;
    var.name = name;
    var.type = type;
    var.scope = current_scope;
    var.isArrayArg = false;
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
        id_emit(var, dim1, dim2, dim3);
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
        if(vec == -1)
        {
            set_vectorPosition(var);
            id.push_back(var);
            id_emit(var, dim1, dim2, dim3);
        }
        else
        {
            var.vec_pos = vec;
            id.push_back(var);
        }
    }

    if((isInFunctionScope && !isFunctionArg_flag) && enable_presets)
    {
        if(var.type == ID_TYPE_NUM || var.type == ID_TYPE_ARR_NUM)
            vm_asm.push_back("preset !" + rc_intToString(var.vec_pos) );
        else if(var.type == ID_TYPE_STR || var.type == ID_TYPE_ARR_STR)
            vm_asm.push_back("preset$ !" + rc_intToString(var.vec_pos));
    }
    isFunctionArg_flag = false;

    return true;
}

bool embed_function(string name, int type)
{
    if(getIDInScope(name) >= 0)
    {
        rc_setError("Identifier [" + name + "] already exists in this scope");
        return false;
    }

    current_scope = "main." + name;
    isInFunctionScope = true;

    switch(type)
    {
        case ID_TYPE_SUB:
            current_block_state = BLOCK_STATE_SUB;
            break;
        case ID_TYPE_FN_NUM:
        case ID_TYPE_FN_STR:
            current_block_state = BLOCK_STATE_FUNCTION;
            break;
        default:
            rc_setError("Invalid type for function definition");
            return false;
    }

    fn_numCount = 0;
    fn_strCount = 0;
    fn_usrCount = 0;
    fn_byref_numCount = 0;
    fn_byref_strCount = 0;
    fn_byref_usrCount = 0;

    identifier fn;
    fn.name = name;
    fn.scope = "main";
    fn.type = type;
    fn.isBuiltin = true;
    fn.vmFunctionIndex = current_vmFunction_index;
    current_vmFunction_index++;

    fn.num_args = 0;  //function args default to 0; args are added with add_function_args
    current_fn_index = id.size();
    id.push_back(fn);
    return true;
}

bool add_embedded_arg(string arg_name, int arg_type)
{
    //fn_arg
    //fn_arg_type
    //fn_arg_utype
    int fn_index = current_fn_index;
    id[fn_index].fn_arg.push_back(arg_name);
    id[fn_index].fn_arg_type.push_back(arg_type);

    string fn_id = "";
    int fn_id_index = -1;

    if(arg_type == ID_TYPE_NUM)
    {
        fn_id = "#fn" + rc_intToString(fn_numCount);
        if(getIDInScope(fn_id) < 0)
            create_variable(fn_id, ID_TYPE_NUM, "");
        fn_numCount++;
    }
    else if(arg_type == ID_TYPE_STR)
    {
        fn_id = "#fs" + rc_intToString(fn_strCount);
        if(getIDInScope(fn_id) < 0)
            create_variable(fn_id, ID_TYPE_STR);
        fn_strCount++;
    }
    else if(arg_type == ID_TYPE_BYREF_NUM)
    {
        fn_id = "#fn" + rc_intToString(fn_numCount);
        if(getIDInScope(fn_id) < 0)
            create_variable(fn_id, ID_TYPE_BYREF_NUM);
        fn_numCount++;
    }
    else if(arg_type == ID_TYPE_BYREF_STR)
    {
        fn_id = "#fs" + rc_intToString(fn_strCount);
        if(getIDInScope(fn_id) < 0)
            create_variable(fn_id, ID_TYPE_BYREF_STR);
        fn_strCount++;
    }
    else
    {
        rc_setError("Invalid type in function definition");
        return false;
    }

    int fn_arg_vec = getIDInScope(fn_id);
    //cout << fn_id << " ====> " << fn_arg_vec << endl;

    isFunctionArg_flag = true;

    create_variable(arg_name, arg_type, "", fn_arg_vec);

    id[fn_index].fn_reg.push_back( fn_id );
    id[fn_index].fn_arg_vec.push_back(fn_arg_vec);
    id[fn_index].num_args++;

    fid_vector_entry f_entry;
    f_entry.type = arg_type;
    f_entry.vec_str = "!" + rc_intToString(fn_arg_vec);

    id[fn_index].fn_var.push_back( f_entry );

    return true;
}

bool create_function(string name, int type, string utype_name)
{
    if(getIDInScope(name) >= 0)
    {
        rc_setError("Identifier [" + name + "] already exists in this scope");
        return false;
    }

    current_scope += "." + name;
    isInFunctionScope = true;
    current_fn_id_count = 0;

    switch(type)
    {
        case ID_TYPE_SUB:
            current_block_state = BLOCK_STATE_SUB;
            break;
        case ID_TYPE_FN_NUM:
        case ID_TYPE_FN_STR:
            current_block_state = BLOCK_STATE_FUNCTION;
            break;
        case ID_TYPE_FN_USER:
            current_block_state = BLOCK_STATE_FUNCTION;
            break;
        default:
            rc_setError("Invalid type for function definition");
            return false;
    }

    fn_numCount = 0;
    fn_strCount = 0;
    fn_usrCount = 0;
    fn_byref_numCount = 0;
    fn_byref_strCount = 0;
    fn_byref_usrCount = 0;

    vm_asm.push_back(".data");
    vm_asm.push_back("label " + name);

    identifier fn;
    fn.name = name;
    fn.scope = "main";
    fn.type = type;
    fn.type_index = getUType(utype_name);

    if(fn.type_index < 0)
    {
        rc_setError("Type \"" + utype_name + "\" does not exists");
        return false;
    }

    fn.isBuiltin = false;
    fn.isArrayArg = false;
    fn.fn_var.clear();

    fn.num_args = 0;  //function args default to 0; args are added with add_function_args
    current_fn_index = id.size();
    id.push_back(fn);
    return true;
}

bool add_function_arg(string arg_name, int arg_type, string utype_name)
{
    //fn_arg
    //fn_arg_type
    //fn_arg_utype
    int fn_index = current_fn_index;
    id[fn_index].fn_arg.push_back(arg_name);
    id[fn_index].fn_arg_type.push_back(arg_type);

    isFunctionArg_flag = true;

    if(!create_variable(arg_name, arg_type, utype_name))
    {
        rc_setError("Invalid argument in Function definition");
        return false;
    }

    //id[fn_index].fn_reg.push_back( fn_id );
    int arg_id_vec = getIDInScope(arg_name);
    int arg_id_index = getIDInScope_ByIndex(arg_name);

    if(arg_id_index < 0)
    {
        rc_setError("Could not create argument of type \"" + utype_name + "\"");
        return false;
    }

    id[fn_index].fn_arg_vec.push_back( arg_id_vec );
    id[fn_index].fn_arg_utype.push_back( id[arg_id_index].type_index );
    id[fn_index].num_args++;

    return true;
}

bool create_function_variable(string arg_name, int arg_type, string utype_name)
{
    //fn_arg
    //fn_arg_type
    //fn_arg_utype
    int fn_index = current_fn_index;

    create_variable(arg_name, arg_type);

    return true;
}

bool create_function_array(string arg_name, int arg_type, int dim_count, string dim1, string dim2, string dim3)
{
    //fn_arg
    //fn_arg_type
    //fn_arg_utype
    int fn_index = current_fn_index;

    create_array(arg_name, arg_type, "", dim_count, dim1, dim2, dim3);

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

int getIDIndex(string id_name)
{
    id_name = StringToLower(id_name);

    for(int i = 0; i < id.size(); i++)
    {
        if(id[i].name.compare(id_name)==0)
            return i;
    }
    return -1;
}


/*type definitions header
-------------------------------
num types

type #1  num fields
	field #1 type (0 - num, 1 - str, 3 - udt)
	field #1 num dimensions
	...
	field #<num fields> type (0 - num, 1 - str, 3 - udt)
	field #<num fields> num dimensions

type #<num types>  num fields
	field #1 type (0 - num, 1 - str, 3 - udt)
	field #1 num dimensions
	...
	field #<num fields> type (0 - num, 1 - str, 3 - udt)
	field #<num fields> num dimensions
*/

#endif // IDENTIFIER_H_INCLUDED
