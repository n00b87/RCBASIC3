#include "rc_os_defines.h"

#ifdef RC_WEB
#include <emscripten.h>
#endif

#ifdef RC_IOS
#define RC_GETCWD
#include <sys/param.h>
#endif

#ifdef RC_MAC
#define RC_GETCWD
#include <sys/param.h>
#endif

#ifdef RC_ANDROID
#define RC_GETCWD
#endif


#ifdef RC_ANDROID
    #include <jni.h>
    #include <sys/param.h>
    #include <algorithm>
    #define LOGI(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "native-activity", __VA_ARGS__))
#endif // RC_ANDROID

#include <iostream>
#include <inttypes.h>
#include <fstream>
#ifdef RC_ANDROID
	#include "SDL.h"
#else
	#include <SDL2/SDL.h>
#endif
#include <math.h>
#include <vector>
#include <stack>
#include <limits>
#include <iomanip>
#include "rc_defines.h"
#include "rc_stdlib.h"
#include "rc_media.h"

using namespace std;

#define LESS_FLAG 0
#define LESS_EQUAL_FLAG 1
#define GREATER_FLAG 2
#define GREATER_EQUAL_FLAG 3
#define EQUAL_FLAG 4
#define NOT_EQUAL_FLAG 5

#define CODE_SEGMENT 0
#define DATA_SEGMENT 1

bool CMP_FLAG_EQUAL = false;
bool CMP_FLAG_LESS = false;
bool CMP_FLAG_LESS_EQUAL = false;
bool CMP_FLAG_GREATER = false;
bool CMP_FLAG_GREATER_EQUAL = false;
bool CMP_FLAG_NOT_EQUAL = false;

struct n_value
{
    vector<double> value;
};

struct s_value
{
    vector<string> value;
};

struct rc_vm_n
{
    double value;
    n_value * r; //reference
    uint64_t r_index;
};

struct rc_vm_s
{
    string value;
    s_value * r;
    uint64_t r_index;
};

struct rc_numId
{
    n_value * nid_value;
    int dimensions;
    uint64_t dim[3];
    uint64_t byref_offset;
};

struct rc_strId
{
    s_value * sid_value;
    int dimensions;
    uint64_t dim[3];
    uint64_t byref_offset;
};

struct rc_loop
{
    rc_numId * counter;
    double f_end;
    double f_step;
    bool isNegative;
    uint64_t counter_offset;
};

uint64_t for_offset_index[3];
int for_offset_dimensions = 0;

union rc_double
{
    double f;
    unsigned char data[sizeof(double)];
};

union rc_int
{
    uint64_t i;
    unsigned char data[sizeof(uint64_t)];
};

struct addr_entry
{
    uint64_t ptr_id;
    void * ptr_addr;
    int type;
};

stack<addr_entry> byref_addr_table;
stack<uint64_t> byref_var_byref_offset;

uint64_t n_count = 0;
uint64_t s_count = 0;
uint64_t n_stack_size = 0;
uint64_t s_stack_size = 0;
uint64_t loop_stack_size = 0;
uint64_t numID_count = 0;
uint64_t strID_count = 0;
uint64_t code_segment_size = 0;
uint64_t data_segment_size = 0;

struct n_obj_struct
{
    n_value * obj_val;
    uint64_t index;
};

struct s_obj_struct
{
    s_value * obj_val;
    uint64_t index;
};

n_obj_struct num_object;
s_obj_struct str_object;

rc_vm_n * vm_n;
rc_vm_s * vm_s;

stack<rc_vm_n>  n_stack;
stack<rc_vm_s> s_stack;
stack<rc_loop> loop_stack;

int current_n_stack_count = 0;
int current_s_stack_count = 0;
int current_loop_stack_count = 0;

rc_numId * num_var;
rc_strId * str_var;

unsigned char ** segment;

int current_segment = CODE_SEGMENT;
uint64_t current_address = 0;

stack<uint64_t> gosub_return_addr;

rc_int readint_val;
rc_double readdouble_val;

uint64_t arr_ref_id = 0;

int rcbasic_exit_code = 0;

//needed by internal functions so i am declaring it here
void pop_ptr_137(uint64_t n);

uint64_t rcbasic_readInt()
{
    uint64_t i;
    SDL_RWread(rc_fstream[0], &i, sizeof(uint64_t), 1);
    return i;
}


bool rcbasic_load(string filename)
{
    unsigned char rc[3];

    rc_fstream[0] = SDL_RWFromFile(filename.c_str(), "rb");

    if(!rc_fstream[0])
    {
        filename += ".cbc";
        rc_fstream[0] = SDL_RWFromFile(filename.c_str(), "rb");
        if(!rc_fstream[0])
            return false;
    }

    SDL_RWread(rc_fstream[0], rc, 3, 1);

    if(! (rc[0]=='R' && rc[1] =='C' && rc[2]=='3') )
    {
        cout << "This program was not built for this version of the runtime" << endl;
        return false;
    }

    n_count = rcbasic_readInt();
    s_count = rcbasic_readInt();
    n_stack_size = rcbasic_readInt();
    s_stack_size = rcbasic_readInt();
    loop_stack_size = rcbasic_readInt();
    numID_count = rcbasic_readInt();
    strID_count = rcbasic_readInt();
    code_segment_size = rcbasic_readInt();
    data_segment_size = rcbasic_readInt();

    vm_n = new rc_vm_n[n_count];
    vm_s = new rc_vm_s[s_count];
    //n_stack = new double[n_stack_size];
    //s_stack = new string[s_stack_size];
    //loop_stack = new rc_loop[loop_stack_size];

    num_var = new rc_numId[numID_count];
    for(int i = 0; i < numID_count; i++)
    {
        num_var[i].nid_value = new n_value;
        num_var[i].nid_value[0].value.resize(1);
        num_var[i].dimensions = 0;
        num_var[i].byref_offset = 0;
    }

    str_var = new rc_strId[strID_count];
    for(int i = 0; i < strID_count; i++)
    {
        str_var[i].sid_value = new s_value;
        str_var[i].sid_value[0].value.resize(1);
        str_var[i].dimensions = 0;
        str_var[i].byref_offset = 0;
    }

    segment = new unsigned char*[2];
    segment[CODE_SEGMENT] = new unsigned char[code_segment_size];
    segment[DATA_SEGMENT] = new unsigned char[data_segment_size];

    SDL_RWread(rc_fstream[0], segment[CODE_SEGMENT], code_segment_size, 1);
    SDL_RWread(rc_fstream[0], segment[DATA_SEGMENT], data_segment_size, 1);

    SDL_RWclose(rc_fstream[0]);

    rc_fstream[0] = NULL;

    return true;
}

bool rc_checkEvent()
{
    for(int i = 0; i < MAX_WINDOWS; i++)
        if(rc_win[i]!=NULL)
            return true;
    return false;
}

void rc_events()
{
    rc_textinput_flag = false;
    cycleVideo();
    if(rc_checkEvent())
    {
        rc_fingers_pressed.clear();

        rc_mwheelx = 0;
        rc_mwheely = 0;
        for(int i = 0; i < MAX_WINDOWS; i++)
            rc_win_event[i] = 0;
        while(rc_getEvents()){}
        //rc_getEvents();
        #ifndef RC_WINDOWS
            SDL_PumpEvents();
        #endif // RC_WINDOWS
        //SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);//
    }
}

uint64_t readInt()
{
    for(int i = 0; i < sizeof(uint64_t); i++)
    {
        readint_val.data[i] = segment[current_segment][current_address];
        current_address++;
    }
    return readint_val.i;
}

double readDouble()
{
    for(int i = 0; i < sizeof(double); i++)
    {
        readdouble_val.data[i] = segment[current_segment][current_address];
        current_address++;
    }
    return readdouble_val.f;
}

void mov_32(int n1, int n2)
{
    vm_n[n1].value = vm_n[n2].value;
}

void mov_33(int n1, double val)
{
    vm_n[n1].value = val;
    //cout << "n" << n1 << " = " << vm_n[n1].value << endl;
}

void mov_34(int n1, uint64_t nid)
{
    int byref_offset = num_var[nid].byref_offset;
    vm_n[n1].value = num_var[nid].nid_value[0].value[byref_offset];
    vm_n[n1].r = num_var[nid].nid_value;
    vm_n[n1].r_index = byref_offset;
    //cout << "n" << n1 << " = " << vm_n[n1].value << endl;
}

void mov_35(uint64_t nid, int n1)
{
    int byref_offset = num_var[nid].byref_offset;
    num_var[nid].nid_value[0].value[byref_offset] = vm_n[n1].value;
    //cout << "n" << n1 << " = " << vm_n[n1].value << endl;
    //cout << "nvar[" << nid << "] = " << num_var[nid].nid_value[0].value[0] << endl;
}

void movS_36(int s1, int s2)
{
    vm_s[s1].value = vm_s[s2].value;
}

void movS_37(int s1, uint64_t str_addr)
{
    vm_s[s1].value.clear();
    char c = segment[DATA_SEGMENT][str_addr];
    uint64_t i = str_addr;
    while(c != '\0')
    {
        vm_s[s1].value.push_back(c);
        i++;
        c = segment[DATA_SEGMENT][i];
    }
}

void movS_38(int s1, uint64_t sid)
{
    int byref_offset = str_var[sid].byref_offset;
    vm_s[s1].value = str_var[sid].sid_value[0].value[byref_offset];
    vm_s[s1].r = &str_var[sid].sid_value[0];
    vm_s[s1].r_index = byref_offset;
}

void movS_39(uint64_t sid, int s1)
{
    int byref_offset = str_var[sid].byref_offset;
    str_var[sid].sid_value[0].value[byref_offset] = vm_s[s1].value;
}

void mov_r_40(int n1, int n2)
{
    vm_n[n1].r[0].value[ vm_n[n1].r_index ] = vm_n[n2].value;
}

void mov_rS_41(int s1, int s2)
{
    vm_s[s1].r[0].value[ vm_s[s1].r_index ] = vm_s[s2].value;
}

void mov_type_42()
{
}

void addS_43(int s1, int s2)
{
    vm_s[s1].value += vm_s[s2].value;
}

void add_44(int n1, int n2)
{
    vm_n[n1].value += vm_n[n2].value;
}

void sub_45(int n1, int n2)
{
    vm_n[n1].value -= vm_n[n2].value;
}

void mul_46(int n1, int n2)
{
    vm_n[n1].value *= vm_n[n2].value;
}

void div_47(int n1, int n2)
{
    vm_n[n1].value /= vm_n[n2].value;
}

void pow_48(int n1, int n2)
{
    vm_n[n1].value = pow(vm_n[n1].value, vm_n[n2].value);
}

void mod_49(int n1, int n2)
{
    vm_n[n1].value = (int64_t)(vm_n[n1].value) % (int64_t)(vm_n[n2].value);
}

void shl_50(int n1, int n2)
{
    vm_n[n1].value = (int64_t)(vm_n[n1].value) << (int64_t)(vm_n[n2].value);
}

void shr_51(int n1, int n2)
{
    vm_n[n1].value = (int64_t)(vm_n[n1].value) >> (int64_t)(vm_n[n2].value);
}

void and_52(int n1, int n2)
{
    vm_n[n1].value = (int64_t)(vm_n[n1].value) & (int64_t)(vm_n[n2].value);
}

void or_53(int n1, int n2)
{
    vm_n[n1].value = (int64_t)(vm_n[n1].value) | (int64_t)(vm_n[n2].value);
}

void xor_54(int n1, int n2)
{
    vm_n[n1].value = !((int64_t)(vm_n[n1].value)) != !((int64_t)(vm_n[n2].value));
}

void not_55(int n1)
{
    vm_n[n1].value = !((int64_t)vm_n[n1].value);
}

void cmp_56(int n1, int n2)
{
    CMP_FLAG_EQUAL = (vm_n[n1].value == vm_n[n2].value);
    CMP_FLAG_GREATER = (vm_n[n1].value > vm_n[n2].value);
    CMP_FLAG_GREATER_EQUAL = (vm_n[n1].value >= vm_n[n2].value);
    CMP_FLAG_LESS = (vm_n[n1].value < vm_n[n2].value);
    CMP_FLAG_LESS_EQUAL = (vm_n[n1].value <= vm_n[n2].value);
    CMP_FLAG_NOT_EQUAL = (vm_n[n1].value != vm_n[n2].value);
}

void cmpS_57(int s1, int s2)
{
    CMP_FLAG_EQUAL = (vm_s[s1].value.compare(vm_s[s2].value)==0);
    CMP_FLAG_NOT_EQUAL = (vm_s[s1].value.compare(vm_s[s2].value)!=0);
}

void cmp_u_58(int n1, int n2)
{
}

void jmp_59(int n1)
{
    current_address = (uint64_t)vm_n[n1].value;
}

void jmp_60(uint64_t jmp_addr)
{
    current_address = jmp_addr;
}

void je_61(int n1)
{
    if(CMP_FLAG_EQUAL)
        current_address = (uint64_t)vm_n[n1].value;
}

void je_62(uint64_t jmp_addr)
{
    if(CMP_FLAG_EQUAL)
        current_address = jmp_addr;
}

void jne_63(int n1)
{
    if(CMP_FLAG_NOT_EQUAL)
        current_address = (uint64_t)vm_n[n1].value;
}

void jne_64(uint64_t jmp_addr)
{
    if(CMP_FLAG_NOT_EQUAL)
        current_address = jmp_addr;
}

void jg_65(int n1)
{
    if(CMP_FLAG_GREATER)
        current_address = (uint64_t)vm_n[n1].value;
}

void jg_66(uint64_t jmp_addr)
{
    if(CMP_FLAG_GREATER)
        current_address = jmp_addr;
}

void jge_67(int n1)
{
    if(CMP_FLAG_GREATER_EQUAL)
        current_address = (uint64_t)vm_n[n1].value;
}

void jge_68(uint64_t jmp_addr)
{
    if(CMP_FLAG_GREATER_EQUAL)
        current_address = jmp_addr;
}

void jl_69(int n1)
{
    if(CMP_FLAG_LESS)
        current_address = (uint64_t)vm_n[n1].value;
}

void jl_70(uint64_t jmp_addr)
{
    if(CMP_FLAG_LESS)
        current_address = jmp_addr;
}

void jle_71(int n1)
{
    if(CMP_FLAG_LESS_EQUAL)
        current_address = (uint64_t)vm_n[n1].value;
}

void jle_72(uint64_t jmp_addr)
{
    if(CMP_FLAG_LESS_EQUAL)
        current_address = jmp_addr;
}

void obj_num_73(uint64_t nid)
{
    num_object.obj_val = &num_var[nid].nid_value[0];
    int byref_offset = num_var[nid].byref_offset;
    num_object.index = byref_offset;
}

void obj_num1_74(uint64_t nid, int n1)
{
    num_object.obj_val = num_var[nid].nid_value;
    int byref_offset = num_var[nid].byref_offset;
    num_object.index = (uint64_t)vm_n[n1].value + byref_offset;
    //cout << "obj_num index = " << num_object.index << endl;
}

void obj_num2_75(uint64_t nid, int n1, int n2)
{
    uint64_t arr_pos = (uint64_t)vm_n[n1].value * num_var[nid].dim[1] + (uint64_t)vm_n[n2].value;
    num_object.obj_val = &num_var[nid].nid_value[0];
    int byref_offset = num_var[nid].byref_offset;
    num_object.index = arr_pos + byref_offset;
}

void obj_num3_76(uint64_t nid, int n1, int n2, int n3)
{
    uint64_t arr_pos = ( (uint64_t)vm_n[n1].value * num_var[nid].dim[1] * num_var[nid].dim[2] ) + ((uint64_t)vm_n[n2].value * num_var[nid].dim[2]) + (uint64_t)vm_n[n3].value;
    num_object.obj_val = &num_var[nid].nid_value[0];
    int byref_offset = num_var[nid].byref_offset;
    num_object.index = arr_pos + byref_offset;
}

void obj_str_77(uint64_t sid)
{
    str_object.obj_val = &str_var[sid].sid_value[0];
    int byref_offset = str_var[sid].byref_offset;
    str_object.index = byref_offset;
}

void obj_str1_78(uint64_t sid, int n1)
{
    str_object.obj_val = &str_var[sid].sid_value[0];
    int byref_offset = str_var[sid].byref_offset;
    str_object.index = (uint64_t)vm_n[n1].value + byref_offset;
}

void obj_str2_79(uint64_t sid, int n1, int n2)
{
    uint64_t arr_pos = (uint64_t)vm_n[n1].value * str_var[sid].dim[1] + (uint64_t)vm_n[n2].value;
    str_object.obj_val = &str_var[sid].sid_value[0];
    int byref_offset = str_var[sid].byref_offset;
    str_object.index = arr_pos + byref_offset;
}

void obj_str3_80(uint64_t sid, int n1, int n2, int n3)
{
    uint64_t arr_pos = ( (uint64_t)vm_n[n1].value * str_var[sid].dim[1] * str_var[sid].dim[2] ) + ((uint64_t)vm_n[n2].value * str_var[sid].dim[2]) + (uint64_t)vm_n[n3].value;
    str_object.obj_val = &str_var[sid].sid_value[0];
    int byref_offset = str_var[sid].byref_offset;
    str_object.index = arr_pos + byref_offset;
}

void obj_usr_81()
{
}

void obj_usr1_82()
{
}

void obj_usr2_83()
{
}

void obj_usr3_84()
{
}

void obj_get_85(int n1)
{
    //cout << "var index = " << num_object.index << endl;
    //cout << "store in n" << n1 << endl;
    vm_n[n1].value = num_object.obj_val[0].value[num_object.index];
    //cout  << "t1" << endl;
    vm_n[n1].r = num_object.obj_val;
    //cout << "t2" << endl;
    vm_n[n1].r_index = num_object.index;
    //cout << "t3" << endl;
}

void obj_getS_86(int s1)
{
    vm_s[s1].value = str_object.obj_val[0].value[str_object.index];
    vm_s[s1].r = str_object.obj_val;
    vm_s[s1].r_index = str_object.index;
}

void obj_set_87(int n1)
{
}

void obj_setS_88(int s1)
{
}

void clear_obj_89()
{
}

void dim_type_90()
{
}

void dim_type1_91()
{
}

void dim_type2_92()
{
}

void dim_type3_93()
{
}

void dim_num1_94(uint64_t nid, int n1)
{
    num_var[nid].nid_value[0].value.resize((uint64_t)vm_n[n1].value);
    num_var[nid].dimensions = 1;
    num_var[nid].dim[0] = (uint64_t)vm_n[n1].value;
    num_var[nid].dim[1] = 0;
    num_var[nid].dim[2] = 0;
}

void dim_num2_95(uint64_t nid, int n1, int n2)
{
    num_var[nid].nid_value[0].value.resize((uint64_t)vm_n[n1].value * (uint64_t)vm_n[n2].value);
    num_var[nid].dimensions = 2;
    num_var[nid].dim[0] = (uint64_t)vm_n[n1].value;
    num_var[nid].dim[1] = (uint64_t)vm_n[n2].value;
    num_var[nid].dim[2] = 0;
}

void dim_num3_96(uint64_t nid, int n1, int n2, int n3)
{
    num_var[nid].nid_value[0].value.resize((uint64_t)vm_n[n1].value * (uint64_t)vm_n[n2].value * (uint64_t)vm_n[n3].value);
    num_var[nid].dimensions = 3;
    num_var[nid].dim[0] = (uint64_t)vm_n[n1].value;
    num_var[nid].dim[1] = (uint64_t)vm_n[n2].value;
    num_var[nid].dim[2] = (uint64_t)vm_n[n3].value;
}

void dim_str1_97(uint64_t sid, int n1)
{
    str_var[sid].sid_value[0].value.resize((uint64_t)vm_n[n1].value);
    str_var[sid].dimensions = 1;
    str_var[sid].dim[0] = (uint64_t)vm_n[n1].value;
    str_var[sid].dim[1] = 0;
    str_var[sid].dim[2] = 0;
}

void dim_str2_98(uint64_t sid, int n1, int n2)
{
    str_var[sid].sid_value[0].value.resize((uint64_t)vm_n[n1].value * (uint64_t)vm_n[n2].value);
    str_var[sid].dimensions = 2;
    str_var[sid].dim[0] = (uint64_t)vm_n[n1].value;
    str_var[sid].dim[1] = (uint64_t)vm_n[n2].value;
    str_var[sid].dim[2] = 0;
}

void dim_str3_99(uint64_t sid, int n1, int n2, int n3)
{
    str_var[sid].sid_value[0].value.resize((uint64_t)vm_n[n1].value * (uint64_t)vm_n[n2].value * (uint64_t)vm_n[n3].value);
    str_var[sid].dimensions = 3;
    str_var[sid].dim[0] = (uint64_t)vm_n[n1].value;
    str_var[sid].dim[1] = (uint64_t)vm_n[n2].value;
    str_var[sid].dim[2] = (uint64_t)vm_n[n3].value;
}

void delete_100(uint64_t nid)
{
    num_var[nid].nid_value[0].value.clear();
    num_var[nid].dimensions = 0;
    num_var[nid].dim[0] = 0;
    num_var[nid].dim[1] = 0;
    num_var[nid].dim[2] = 0;
}

void deleteS_101(uint64_t sid)
{
    str_var[sid].sid_value[0].value.clear();
    str_var[sid].dimensions = 0;
    str_var[sid].dim[0] = 0;
    str_var[sid].dim[1] = 0;
    str_var[sid].dim[2] = 0;
}

void push_102(int n1)
{
    //n_stack[current_n_stack_count] = vm_n[n1].value;
    //current_n_stack_count++;
    n_stack.push(vm_n[n1]);
}

void push_103(uint64_t nid)
{
    //n_stack[current_n_stack_count] = num_var[nid].value[0];
    //current_n_stack_count++;
    rc_vm_n n;
    int byref_offset = num_var[nid].byref_offset;
    n.value = num_var[nid].nid_value[0].value[byref_offset];
    n.r_index = byref_offset;
    n_stack.push(n);
}

void pushS_104(int s1)
{
    //s_stack[current_s_stack_count] = vm_s[s1].value;
    //current_s_stack_count++;
    s_stack.push(vm_s[s1]);
}

void pushS_105(uint64_t sid)
{
    //s_stack[current_s_stack_count] = str_var[sid].value[0];
    //current_s_stack_count++;
    rc_vm_s s;
    int byref_offset = str_var[sid].byref_offset;
    s.value = str_var[sid].sid_value[0].value[byref_offset];
    s.r_index = byref_offset;
    s_stack.push(s);
}

void push_emptyS_106()
{
    rc_vm_s s_empty;
    s_empty.value = "";
    //s_stack[current_s_stack_count] = "";
    //current_s_stack_count++;
    s_stack.push(s_empty);
}

void pop_107(int n1)
{
    //current_n_stack_count--;
    //vm_n[n1].value = n_stack[current_n_stack_count];
    vm_n[n1].value = n_stack.top().value;
    vm_n[n1].r = n_stack.top().r;
    vm_n[n1].r_index = n_stack.top().r_index;
    n_stack.pop();
}

void pop_108(uint64_t nid)
{
    //current_n_stack_count--;
    //num_var[nid].value[0] = n_stack[current_n_stack_count];
    int byref_offset = n_stack.top().r_index;
    num_var[nid].nid_value[0].value[byref_offset] = n_stack.top().value;
    num_var[nid].byref_offset = byref_offset;
    n_stack.pop();
}

void popS_109(int s1)
{
    //current_s_stack_count--;
    //vm_s[s1].value = s_stack[current_s_stack_count];
    vm_s[s1].value = s_stack.top().value;
    vm_s[s1].r = s_stack.top().r;
    vm_s[s1].r_index = s_stack.top().r_index;
    s_stack.pop();
}

void popS_110(uint64_t sid)
{
    //current_s_stack_count--;
    //str_var[sid].value[0] = s_stack[current_s_stack_count];
    int byref_offset = s_stack.top().r_index;
    str_var[sid].sid_value[0].value[byref_offset] = s_stack.top().value;
    str_var[sid].byref_offset = byref_offset;
    s_stack.pop();
}

void get_stack_size_111(int n1)
{
    vm_n[n1].value = n_stack.size();
}

void get_stack_sizeS_112(int n1)
{
    vm_n[n1].value = s_stack.size();
}

void clear_stack_113()
{
    //current_n_stack_count = 0;
    n_stack.empty();
}

void clear_stackS_114()
{
    //current_s_stack_count = 0;
    s_stack.empty();
}

void while_115(int n1, uint64_t jmp_addr)
{
    if(vm_n[n1].value == 0)
        current_address = jmp_addr;
    //rc_events();
}

void wend_116(uint64_t jmp_addr)
{
    current_address = jmp_addr;
}

void for_117(uint64_t nid, int n1, int n2, int n3)
{
    rc_loop for_loop;
    for_loop.counter = &num_var[nid];
    for_loop.f_end = vm_n[n2].value;
    for_loop.f_step = vm_n[n3].value;

    switch(for_offset_dimensions)
    {
        case 1:
            for_loop.counter_offset = for_offset_index[0];
            break;
        case 2:
            for_loop.counter_offset = for_offset_index[0] * num_var[nid].dim[1] + for_offset_index[1];
            break;
        case 3:
            for_loop.counter_offset = ( for_offset_index[0] * num_var[nid].dim[1] * num_var[nid].dim[2] ) + (for_offset_index[1] * num_var[nid].dim[2]) + for_offset_index[2];
            break;
        default:
            for_loop.counter_offset = 0;
    }

    int byref_offset = num_var[nid].byref_offset;
    num_var[nid].nid_value[0].value[byref_offset + for_loop.counter_offset] = vm_n[n1].value;


    if( vm_n[n2].value < vm_n[n1].value )
        for_loop.isNegative = true;
    else
        for_loop.isNegative = false;

    loop_stack.push(for_loop);
    //current_loop_stack_count++;
    //cout << "nid = " << nid << " --> " << (uint64_t)(&num_var[nid].nid_value[0].value[0]) << endl;
    //cout << "nid_value = " << num_var[nid].nid_value[0].value[0] << endl;
    //cout << "id[10] = " << num_var[10].nid_value[0].value[0] << " --> " << (uint64_t)(&num_var[10].nid_value[0].value[0]) << endl;
    //cout << "id[11] = " << num_var[11].nid_value[0].value[0] << " --> " << (uint64_t)(&num_var[11].nid_value[0].value[0]) << endl;
    //cin.get();
}

void next_118(uint64_t f_addr)
{
    //int l_index = current_loop_stack_count-1;
    int byref_offset = loop_stack.top().counter[0].byref_offset + loop_stack.top().counter_offset;
    double next_step = loop_stack.top().counter[0].nid_value[0].value[byref_offset] + loop_stack.top().f_step;
    if(loop_stack.top().isNegative && next_step <= loop_stack.top().counter[0].nid_value[0].value[byref_offset] && next_step >= loop_stack.top().f_end)
    {
        loop_stack.top().counter[0].nid_value[0].value[byref_offset] += loop_stack.top().f_step;
        current_address = f_addr;
    }
    else if( (!loop_stack.top().isNegative) && next_step >= loop_stack.top().counter[0].nid_value[0].value[byref_offset] && next_step <= loop_stack.top().f_end)
    {
        loop_stack.top().counter[0].nid_value[0].value[byref_offset] += loop_stack.top().f_step;
        //cout << "current counter = " << loop_stack.top().counter[0].value[0] << "       step = " << loop_stack.top().f_step << endl;
        current_address = f_addr;
    }
    else
    {
        loop_stack.pop();
        //current_loop_stack_count--;
    }
    //cout << "id[10] = " << num_var[10].nid_value[0].value[0] << " --> " << (uint64_t)(&num_var[10].nid_value[0].value[0]) << endl;
    //cout << "id[11] = " << num_var[11].nid_value[0].value[0] << " --> " << (uint64_t)(&num_var[11].nid_value[0].value[0]) << endl;
    //cin.get();
    //there is no point in trying to poll events in a for loop so i disabled it
    //rc_events();
}

void do_119() //I realized that I didn't need this so its here so I can keep numbered order from my initial design
{
}

void loop_120(uint64_t jmp_addr) //not actually used
{
    current_address = jmp_addr;
    //rc_events();
}

void loop_while_121(int n1, uint64_t jmp_addr)
{
    if(vm_n[n1].value != 0)
        current_address = jmp_addr;
    //rc_events();
}

void loop_until_122(int n1, uint64_t jmp_addr)
{
    if(vm_n[n1].value == 0)
        current_address = jmp_addr;
    //rc_events();
}

void pop_loop_stack_123()
{
    loop_stack.pop();
}

void gosub_124(uint64_t sub_addr)
{
    //cout << "gosub" << endl;
    gosub_return_addr.push(current_segment);
    gosub_return_addr.push(current_address);
    current_segment = DATA_SEGMENT;
    current_address = sub_addr;
    //cout << "sub: " << sub_addr << endl;
}

void return_125()
{
    //cout << "\nvar 0 = " << num_var[0].value[0] << endl;
    //cout << "var1 = " << num_var[1].value[0] << endl;
    //cout << "current address = " << current_segment << " : " << current_address << endl;
    current_address = gosub_return_addr.top();
    gosub_return_addr.pop();
    current_segment = gosub_return_addr.top();
    gosub_return_addr.pop();
    //cout << "return to: " << current_segment << " : " << current_address << endl;
}

addr_entry byref_id;

#define BYREF_TYPE_NUM 0
#define BYREF_TYPE_STR 1

void ptr_126(uint64_t nid, int n1)
{
    byref_id.ptr_id = nid;
    byref_id.ptr_addr = &num_var[nid].nid_value[0];
    byref_id.type = BYREF_TYPE_NUM;
    byref_addr_table.push(byref_id);
    byref_var_byref_offset.push(num_var[nid].byref_offset);
    num_var[nid].nid_value = vm_n[n1].r;
    num_var[nid].byref_offset = vm_n[n1].r_index;
}

void ptrS_127(uint64_t sid, int s1)
{
    byref_id.ptr_id = sid;
    byref_id.ptr_addr = &str_var[sid].sid_value[0];
    byref_id.type = BYREF_TYPE_STR;
    byref_addr_table.push(byref_id);
    byref_var_byref_offset.push(str_var[sid].byref_offset);
    str_var[sid].sid_value = vm_s[s1].r;
    str_var[sid].byref_offset = vm_s[s1].r_index;
}

void rc_print_num(double n)
{
    stringstream s;
    s << fixed << n;
    string s_out = s.str();
    int s_decimal = s_out.find_first_of(".");
    if(s_decimal != string::npos)
    {
        int trail_end = s_out.length();
        for(int i = s_decimal; i < s_out.length(); i++)
        {
            if(s_out[i] != '0')
                trail_end = i+1;
        }
        s_out = s_out.substr(0, trail_end);
        if(s_out.substr(s_out.length()-1,1).compare(".")==0)
            s_out = s_out.substr(0, s_out.length()-1);
    }
    cout << s_out;
}

void print_128(int n1)
{
    rc_print_num(vm_n[n1].value);
}

void printS_129(int s1)
{
    cout << vm_s[s1].value;
}

void rc_push_num(double n_val)
{
    rc_vm_n n;
    n.value = n_val;
    n_stack.push(n);
    //current_n_stack_count++;
}

void rc_push_str(string s_val)
{
    rc_vm_s s;
    s.value = s_val;
    s_stack.push(s);
    //current_s_stack_count++;
}

uint64_t rc_string_array_dim(rc_strId s_var)
{
    return s_var.dimensions;
}

uint64_t rc_string_array_size(rc_strId s_var, int d_num)
{
    switch(d_num)
    {
        case 1:
            return s_var.dim[0];
            break;
        case 2:
            return s_var.dim[1];
            break;
        case 3:
            return s_var.dim[2];
            break;
    }
    return 0;
}

uint64_t rc_number_array_dim(rc_numId n_var)
{
    return n_var.dimensions;
}

uint64_t rc_number_array_size(rc_numId n_var, int d_num)
{
    switch(d_num)
    {
        case 1:
            return n_var.dim[0];
            break;
        case 2:
            return n_var.dim[1];
            break;
        case 3:
            return n_var.dim[2];
            break;
    }
    return 0;
}

void func_130(uint64_t fn)
{
    //need to setup a switch statement for all buitlin fucntions here
    switch(fn)
    {
        case FN_FPrint:
            //cout << "gosub addr size: " << gosub_return_addr.size() << endl;
            //cout << "for stack size: " << loop_stack.size() << endl;
            //cout << "byref addr table: " << byref_addr_table.size() << endl << endl;
            rc_fprint( FPRINT_TXT$ );
            break;
        case FN_Input$:
            rc_push_str( rc_input(INPUT$_PROMPT$) );
            break;
        case FN_StringArrayDim:
            rc_push_num( rc_string_array_dim( str_var[arr_ref_id] ) );
            break;
        case FN_NumberArrayDim:
            rc_push_num( rc_number_array_dim( num_var[arr_ref_id] ) );
            break;
        case FN_StringArraySize:
            rc_push_num( rc_string_array_size( str_var[arr_ref_id], STRINGARRAYSIZE_ARRAY_DIM));
            break;
        case FN_NumberArraySize:
            rc_push_num( rc_number_array_size( num_var[arr_ref_id], NUMBERARRAYSIZE_ARRAY_DIM));
            break;
        case FN_Abs:
            rc_push_num( rc_intern_abs( ABS_N ) );
            break;
        case FN_ACos:
            rc_push_num( rc_intern_aCos( ACOS_N ) );
            break;
        case FN_AndBit:
            rc_push_num( rc_intern_andBit( ANDBIT_A, ANDBIT_B ) );
            break;
        case FN_ASin:
            rc_push_num( rc_intern_aSin( ASIN_N ) );
            break;
        case FN_ATan:
            rc_push_num( rc_intern_aTan( ATAN_N ) );
            break;
        case FN_Bin$:
            rc_push_str( rc_intern_bin( BIN$_N ) );
            break;
        case FN_CInt32:
            rc_push_num( rc_intern_cint32( CINT32_I ));
            break;
        case FN_CInt64:
            rc_push_num( rc_intern_cint64( CINT64_I ));
            break;
        case FN_Cos:
            rc_push_num( rc_intern_cos( COS_N ) );
            break;
        case FN_Degrees:
            rc_push_num( rc_intern_degrees(DEGREES_R));
            break;
        case FN_Exp:
            rc_push_num( rc_intern_exp( EXP_N ) );
            break;
        case FN_Frac:
            rc_push_num( rc_intern_frac( FRAC_N ) );
            break;
        case FN_Hex$:
            rc_push_str( rc_intern_hex( HEX$_N ) );
            break;
        case FN_HexVal:
            rc_push_num( rc_intern_hexInt( HEXVAL_N$ ) );
            break;
        case FN_Int:
            rc_push_num( rc_intern_int( INT_N ) );
            break;
        case FN_Log:
            rc_push_num( rc_intern_log( LOG_N ) );
            break;
        case FN_Max:
            rc_push_num( rc_intern_max( MAX_A, MAX_B ) );
            break;
        case FN_Min:
            rc_push_num( rc_intern_min( MIN_A, MIN_B ) );
            break;
        case FN_OrBit:
            rc_push_num( rc_intern_orBit( ORBIT_A, ORBIT_B ) );
            break;
        case FN_Radians:
            rc_push_num( rc_intern_radians(RADIANS_D));
            break;
        case FN_Randomize:
            rc_push_num( rc_intern_randomize( RANDOMIZE_N ) );
            break;
        case FN_Rand:
            rc_push_num( rc_intern_rand( RAND_N ) );
            break;
        case FN_Round:
            rc_push_num( rc_intern_round( ROUND_N ) );
            break;
        case FN_Sign:
            rc_push_num( rc_intern_sign( SIGN_N ) );
            break;
        case FN_Sin:
            rc_push_num( rc_intern_sin( SIN_N ) );
            break;
        case FN_Sqrt:
            rc_push_num( rc_intern_sqrt( SQRT_N ) );
            break;
        case FN_Tan:
            rc_push_num( rc_intern_tan( TAN_N ) );
            break;
        case FN_XOrBit:
            rc_push_num( rc_intern_xorbit( XORBIT_A, XORBIT_B ) );
            break;
        case FN_Asc:
            rc_push_num( rc_intern_asc( ASC_C$ ) );
            break;
        case FN_Chr$:
            rc_push_str( rc_intern_chr( CHR$_N ) );
            break;
        case FN_Insert$:
            rc_push_str( rc_intern_insert( INSERT$_SRC$, INSERT$_TGT$, INSERT$_POS ) );
            break;
        case FN_InStr:
            rc_push_num( rc_intern_instr( INSTR_SRC$, INSTR_SUBSTR$ ) );
            break;
        case FN_LCase$:
            rc_push_str( rc_intern_lcase( LCASE$_SRC$ ) );
            break;
        case FN_Left$:
            rc_push_str( rc_intern_left( LEFT$_SRC$, LEFT$_N ) );
            break;
        case FN_Len:
            rc_push_num( rc_intern_length( LEN_SRC$ ) );
            break;
        case FN_Length:
            rc_push_num( rc_intern_length( LENGTH_SRC$ ) );
            break;
        case FN_LTrim$:
            rc_push_str( rc_intern_ltrim( LTRIM$_SRC$ ) );
            break;
        case FN_Mid$:
            rc_push_str( rc_intern_mid( MID$_SRC$, MID$_START, MID$_N ) );
            break;
        case FN_ReplaceSubstr$:
            rc_push_str( rc_intern_replaceSubstr( REPLACESUBSTR$_SRC$, REPLACESUBSTR$_RPC$, REPLACESUBSTR$_POS) );
            break;
        case FN_Replace$:
            rc_push_str( rc_intern_replace( REPLACE$_SRC$, REPLACE$_TGT$, REPLACE$_RPC$ ) );
            break;
        case FN_Reverse$:
            rc_push_str( rc_intern_reverse( REVERSE$_SRC$ ) );
            break;
        case FN_Right$:
            rc_push_str( rc_intern_right( RIGHT$_SRC$, RIGHT$_N ) );
            break;
        case FN_RTrim$:
            rc_push_str( rc_intern_rtrim( RTRIM$_SRC$ ) );
            break;
        case FN_StringFill$:
            rc_push_str( rc_intern_stringfill( STRINGFILL$_SRC$, STRINGFILL$_N ) );
            break;
        case FN_Str$:
            rc_push_str( rc_intern_str( STR$_N ) );
            break;
        case FN_Str_F$:
            rc_push_str( rc_intern_str_f( STR_F$_N ) );
            break;
        case FN_Str_S$:
            rc_push_str( rc_intern_str_s( STR_S$_N ) );
            break;
        case FN_Tally:
            rc_push_num( rc_intern_tally( TALLY_SRC$, TALLY_SUBSTR$ ) );
            break;
        case FN_Trim$:
            rc_push_str( rc_intern_trim( TRIM$_SRC$ ) );
            break;
        case FN_UCase$:
            rc_push_str( rc_intern_ucase( UCASE$_SRC$ ) );
            break;
        case FN_Val:
            rc_push_num( rc_intern_val( VAL_N$ ) );
            break;
        case FN_Stack_N: //Sub Procedure
            if(STACK_N_N >= 0 && STACK_N_N <= (MAX_USER_STACKS-1))
                rc_user_active_n_stack = STACK_N_N;
            else
                cout << "Stack_N Error: Exceeds available stacks" << endl;
            break;
        case FN_Stack_S: //Sub Procedure
            if(STACK_S_N >= 0 && STACK_S_N <= (MAX_USER_STACKS-1))
                rc_user_active_s_stack = STACK_S_N;
            else
                cout << "Stack_S Error: Exceeds available stacks" << endl;
            break;
        case FN_Push_N:
            rc_intern_push_n( PUSH_N_N );
            break;
        case FN_Pop_N:
            rc_push_num( rc_intern_pop_n() );
            break;
        case FN_Push_S:
            rc_intern_push_s( PUSH_S_S$ );
            break;
        case FN_Pop_S$:
            rc_push_str( rc_intern_pop_s() );
            break;
        case FN_Stack_Size_N:
            rc_push_num( rc_intern_n_stack_size() );
            break;
        case FN_Stack_Size_S:
            rc_push_num( rc_intern_s_stack_size() );
            break;
        case FN_FileOpen:
            rc_push_num( rc_intern_fileOpen( FILEOPEN_STREAM, FILEOPEN_FILENAME$, FILEOPEN_MODE ) );
            break;
        case FN_FileClose:
            rc_intern_fileClose( FILECLOSE_STREAM );
            break;
        case FN_ReadByte:
            rc_push_num( rc_intern_fileReadByte( READBYTE_STREAM ) );
            break;
        case FN_WriteByte:
            rc_intern_fileWriteByte( WRITEBYTE_STREAM, WRITEBYTE_BYTE );
            break;
        case FN_ReadLine$:
            rc_push_str( rc_intern_fileReadLine( READLINE$_STREAM ) );
            break;
        case FN_Write:
            rc_intern_fileWrite( WRITE_STREAM, WRITE_TXT$ );
            break;
        case FN_WriteLine:
            rc_intern_fileWriteLine( WRITELINE_STREAM, WRITELINE_TXT$ );
            break;
        case FN_CopyFile:
            rc_intern_fileCopy( COPYFILE_SRC$, COPYFILE_DST$ );
            break;
        case FN_RemoveFile:
            rc_push_num( rc_intern_fileDelete( REMOVEFILE_FILENAME$ ) );
            break;
        case FN_FileExists:
            rc_push_num( rc_intern_fileExist( FILEEXISTS_FILENAME$ ) );
            break;
        case FN_MoveFile:
            rc_push_num( rc_intern_fileMove( MOVEFILE_SRC$, MOVEFILE_DST$ ) );
            break;
        case FN_RenameFile:
            rc_push_num( rc_intern_fileRename( RENAMEFILE_SRC$, RENAMEFILE_DST$ ) );
            break;
        case FN_FileLength:
            rc_push_num( rc_intern_fileLength( FILELENGTH_FILENAME$ ) );
            break;
        case FN_Tell:
            rc_push_num( rc_intern_fileTell( TELL_STREAM ) );
            break;
        case FN_Seek:
            rc_push_num( rc_intern_fileSeek( SEEK_STREAM, SEEK_POS ) );
            break;
        case FN_EOF:
            rc_push_num( rc_intern_eof( EOF_STREAM ) );
            break;
        case FN_FreeFile:
            rc_push_num( rc_intern_freeFile() );
            break;
        case FN_ChangeDir:
            rc_intern_dirChange( CHANGEDIR_P$ );
            break;
        case FN_DirExists:
            rc_push_num( rc_intern_dirExist( DIREXISTS_P$ ) );
            break;
        case FN_DirFirst$:
            rc_push_str( rc_intern_dirFirst() );
            break;
        case FN_Dir$:
            rc_push_str( rc_intern_dir() );
            break;
        case FN_DirNext$:
            rc_push_str( rc_intern_dirNext() );
            break;
        case FN_MakeDir:
            rc_push_num( rc_intern_dirCreate( MAKEDIR_P$ ) );
            break;
        case FN_RemoveDir:
            rc_push_num( rc_intern_dirDelete( REMOVEDIR_P$ ) );
            break;
        case FN_Date$:
            rc_push_str( rc_intern_date() );
            break;
        case FN_Easter$:
            rc_push_str( rc_intern_easter(EASTER$_YEAR) );
            break;
        case FN_Ticks:
            rc_push_num( rc_intern_ticks() );
            break;
        case FN_Time$:
            rc_push_str( rc_intern_time() );
            break;
        case FN_Timer:
            rc_push_num( rc_intern_timer() );
            break;
        case FN_Wait:
            rc_intern_wait( WAIT_M_SEC );
            break;
        case FN_WindowOpen: //Sub Procedure
            rc_media_openWindow_hw( WINDOWOPEN_WIN, WINDOWOPEN_TITLE$, WINDOWOPEN_X, WINDOWOPEN_Y, WINDOWOPEN_W, WINDOWOPEN_H, WINDOWOPEN_FLAG, WINDOWOPEN_VSYNC);
            break;
        case FN_WindowClose: //Sub Procedure
            rc_media_closeWindow_hw( WINDOWCLOSE_WIN );
            break;
        case FN_RaiseWindow: //Sub Procedure
            rc_media_raiseWindow( RAISEWINDOW_WIN );
            break;
        case FN_Window: //Sub Procedure
            rc_media_setActiveWindow( WINDOW_WIN );
            break;
        case FN_Update: //Sub Procedure
            //cout << "update call" << endl;
            rc_events();
            rc_media_updateWindow_hw();
            #ifdef RC_WEB
                emscripten_sleep(0);
            #else
                SDL_Delay(0);
            #endif // RC_WEB
            break;
        case FN_Cls: //Sub Procedure
            rc_media_cls();
            break;
        case FN_SetClearColor:
            rc_media_setClearColor( SETCLEARCOLOR_C );
            break;
        case FN_ShowWindow: //Sub Procedure
            rc_media_showWindow( SHOWWINDOW_WIN );
            break;
        case FN_HideWindow: //Sub Procedure
            rc_media_hideWindow( HIDEWINDOW_WIN );
            break;
        case FN_SetWindowTitle: //Sub Procedure
            rc_media_setWindowTitle( SETWINDOWTITLE_WIN, SETWINDOWTITLE_TITLE$ );
            break;
        case FN_WindowTitle$: //String Function
            rc_push_str( rc_media_getWindowTitle( WINDOWTITLE$_WIN ));
            break;
        case FN_SetWindowPosition: //Sub Procedure
            rc_media_setWindowPosition( SETWINDOWPOSITION_WIN, SETWINDOWPOSITION_X, SETWINDOWPOSITION_Y );
            break;
        case FN_GetWindowPosition: //Sub Procedure
            rc_media_getWindowPosition( SETWINDOWPOSITION_WIN, &SETWINDOWPOSITION_X, &SETWINDOWPOSITION_Y );
            break;
        case FN_SetWindowSize: //Sub Procedure
            rc_media_setWindowSize( SETWINDOWSIZE_WIN, SETWINDOWSIZE_W, SETWINDOWSIZE_H );
            break;
        case FN_GetWindowSize: //Sub Procedure
            rc_media_getWindowSize( GETWINDOWSIZE_WIN, &GETWINDOWSIZE_W, &GETWINDOWSIZE_H);
            break;
        case FN_SetWindowMinSize: //Sub Procedure
            rc_media_setWindowMinSize( SETWINDOWMINSIZE_WIN, SETWINDOWMINSIZE_W, SETWINDOWMINSIZE_H );
            break;
        case FN_GetWindowMinSize: //Sub Procedure
            rc_media_getWindowMinSize( GETWINDOWMINSIZE_WIN, &GETWINDOWMINSIZE_W, &GETWINDOWMINSIZE_H );
            break;
        case FN_SetWindowMaxSize: //Sub Procedure
            rc_media_setWindowMaxSize( SETWINDOWMAXSIZE_WIN, SETWINDOWMAXSIZE_W, SETWINDOWMAXSIZE_H );
            break;
        case FN_GetWindowMaxSize: //Sub Procedure
            rc_media_getWindowMaxSize( GETWINDOWMAXSIZE_WIN, &GETWINDOWMAXSIZE_W, &GETWINDOWMAXSIZE_H );
            break;
        case FN_WindowIsFullscreen: //Number Function
            rc_push_num( rc_media_windowIsFullscreen( WINDOWISFULLSCREEN_WIN ) );
            break;
        case FN_WindowIsVisible: //Number Function
            rc_push_num( rc_media_windowIsVisible( WINDOWISVISIBLE_WIN ) );
            break;
        case FN_WindowIsBordered: //Number Function
            rc_push_num( rc_media_windowIsBordered( WINDOWISBORDERED_WIN ) );
            break;
        case FN_WindowIsResizable: //Number Function
            rc_push_num( rc_media_windowIsResizable( WINDOWISRESIZABLE_WIN ) );
            break;
        case FN_WindowIsMinimized: //Number Function
            rc_push_num( rc_media_windowIsMinimized( WINDOWISMINIMIZED_WIN ) );
            break;
        case FN_WindowIsMaximized: //Number Function
            rc_push_num( rc_media_windowIsMaximized( WINDOWISMAXIMIZED_WIN ) );
            break;
        case FN_WindowHasInputFocus: //Number Function
            rc_push_num( rc_media_windowHasInputFocus( WINDOWHASINPUTFOCUS_WIN ) );
            break;
        case FN_WindowHasMouseFocus: //Number Function
            rc_push_num( rc_media_windowHasMouseFocus( WINDOWHASMOUSEFOCUS_WIN ) );
            break;
        case FN_SetWindowFullscreen: //Sub Procedure
            rc_media_setWindowFullscreen( SETWINDOWFULLSCREEN_WIN, SETWINDOWFULLSCREEN_FLAG );
            rc_media_cls();
            break;
        case FN_MaximizeWindow: //Sub Procedure
            rc_media_maximizeWindow( MAXIMIZEWINDOW_WIN );
            break;
        case FN_MinimizeWindow: //Sub Procedure
            rc_media_minimizeWindow( MINIMIZEWINDOW_WIN );
            break;
        case FN_SetWindowBorder: //Sub Procedure
            rc_media_setWindowBordered( SETWINDOWBORDER_WIN, SETWINDOWBORDER_FLAG );
            break;
        case FN_WindowClip: //Sub Procedure
            rc_media_getWindowClip_hw( WINDOWCLIP_SLOT, WINDOWCLIP_X, WINDOWCLIP_Y, WINDOWCLIP_W, WINDOWCLIP_H );
            break;
        case FN_WindowExists: //Number Function
            rc_push_num( rc_media_windowExists( WINDOWEXISTS_WIN ) );
            break;
        case FN_NumWindows: //Number Function
            rc_push_num( rc_media_numWindows() );
            break;
        case FN_WindowEvent_Close: //Number Function
            rc_push_num( rc_media_windowEvent_Close( WINDOWEVENT_CLOSE_WIN ) );
            break;
        case FN_WindowEvent_Maximize: //Number Function
            rc_push_num( rc_media_windowEvent_Maximize( WINDOWEVENT_MAXIMIZE_WIN ) );
            break;
        case FN_WindowEvent_Minimize: //Number Function
            rc_push_num( rc_media_windowEvent_Minimize( WINDOWEVENT_MINIMIZE_WIN ) );
            break;
        case FN_ActiveWindow:
            rc_push_num(rc_active_window);
            break;
        case FN_SetWindowIcon:
            rc_media_setWindowIcon( SETWINDOWICON_WIN, SETWINDOWICON_SLOT );
            break;
        case FN_FPS:
            rc_push_num(rc_fps[rc_active_window]);
            break;
        case FN_CanvasOpen: //Sub Procedure
            rc_media_openScreen_hw( CANVASOPEN_C_NUM, CANVASOPEN_W, CANVASOPEN_H, CANVASOPEN_VIEWPORT_X, CANVASOPEN_VIEWPORT_Y, CANVASOPEN_VIEWPORT_W, CANVASOPEN_VIEWPORT_H, CANVASOPEN_MODE);
            break;
        case FN_CanvasClose: //Sub Procedure
            rc_media_closeScreen_hw( CANVASCLOSE_C_NUM );
            break;
        case FN_SetCanvasVisible: //Sub Procedure
            rc_media_setScreenVisible( SETCANVASVISIBLE_C_NUM, SETCANVASVISIBLE_FLAG );
            break;
        case FN_CanvasIsVisible: //Number Function
            rc_push_num( rc_media_screenIsVisible( CANVASISVISIBLE_C_NUM ) );
            break;
        case FN_SetCanvasViewport: //Sub Procedure
            rc_media_setScreenViewport( SETCANVASVIEWPORT_CNUM, SETCANVASVIEWPORT_X, SETCANVASVIEWPORT_Y, SETCANVASVIEWPORT_W, SETCANVASVIEWPORT_H );
            break;
        case FN_GetCanvasViewport: //Sub Procedure
            rc_media_getScreenViewport( GETCANVASVIEWPORT_C_NUM, &GETCANVASVIEWPORT_X, &GETCANVASVIEWPORT_Y, &GETCANVASVIEWPORT_W, &GETCANVASVIEWPORT_H );
            break;
        case FN_Canvas: //Sub Procedure
            rc_media_screen_hw( CANVAS_C_NUM );
            break;
        case FN_SetCanvasOffset: //Sub Procedure
            rc_media_screenOffset( SETCANVASOFFSET_C_NUM, SETCANVASOFFSET_X, SETCANVASOFFSET_Y );
            break;
        case FN_GetCanvasOffset: //Sub Procedure
            rc_media_getScreenOffset( GETCANVASOFFSET_C_NUM, &GETCANVASOFFSET_X, &GETCANVASOFFSET_Y );
            break;
        case FN_GetCanvasSize: //Sub Procedure
            rc_media_getScreenSize( GETCANVASSIZE_C_NUM, &GETCANVASSIZE_W, &GETCANVASSIZE_H );
            break;
        case FN_ClearCanvas: //Sub Procedure
            rc_media_clearScreen_hw();
            break;
        case FN_SetCanvasAlpha: //Sub Procedure
            rc_media_setScreenAlpha_hw( SETCANVASALPHA_C_NUM, SETCANVASALPHA_A );
            break;
        case FN_CanvasAlpha:
            rc_push_num(rc_media_ScreenAlpha_hw(CANVASALPHA_C_NUM));
            break;
        case FN_SetCanvasBlendMode:
            rc_push_num(rc_media_setScreenBlendMode_hw(SETCANVASBLENDMODE_C_NUM, SETCANVASBLENDMODE_BLEND_MODE));
            break;
        case FN_CanvasBlendMode:
            rc_push_num(rc_media_screenBlendMode_hw(CANVASBLENDMODE_C_NUM));
            break;
        case FN_SetCanvasColorMod:
            rc_push_num(rc_media_setScreenColorMod_hw(SETCANVASCOLORMOD_C_NUM, SETCANVASCOLORMOD_C));
            break;
        case FN_CanvasColorMod:
            rc_push_num(rc_media_screenColorMod_hw(CANVASCOLORMOD_C_NUM));
            break;
        case FN_CopyCanvas: //Sub Procedure
            rc_media_copyScreen_hw( COPYCANVAS_SRC, COPYCANVAS_X, COPYCANVAS_Y, COPYCANVAS_W, COPYCANVAS_H, COPYCANVAS_DST, COPYCANVAS_DX, COPYCANVAS_DY );
            break;
        case FN_CloneCanvas: //Sub Procedure
            rc_media_cloneScreen_hw( CLONECANVAS_SRC, CLONECANVAS_DST );
            break;
        case FN_SetCanvasZ: //Sub Procedure
            rc_media_setScreenZ( SETCANVASZ_C_NUM, SETCANVASZ_Z );
            break;
        case FN_CanvasZ:
            rc_push_num( rc_media_screenZ( CANVASZ_C_NUM) );
            break;
        case FN_CanvasClip: //Sub Procedure
            rc_media_getScreenClip2_hw( CANVASCLIP_SLOT, CANVASCLIP_X, CANVASCLIP_Y, CANVASCLIP_W, CANVASCLIP_H, CANVASCLIP_FLAG );
            break;
        case FN_ActiveCanvas:
            rc_push_num(rc_active_screen);
            break;
        case FN_Box: //Sub Procedure
            rc_media_box_hw( BOX_X1, BOX_Y1, BOX_X2, BOX_Y2 );
            break;
        case FN_BoxFill: //Sub Procedure
            rc_media_boxFill_hw( BOXFILL_X1, BOXFILL_Y1, BOXFILL_X2, BOXFILL_Y2 );
            break;
        case FN_Circle: //Sub Procedure
            rc_media_circle_hw( CIRCLE_X, CIRCLE_Y, CIRCLE_RADIUS );
            break;
        case FN_CircleFill: //Sub Procedure
            rc_media_circleFill_hw( CIRCLEFILL_X, CIRCLEFILL_Y, CIRCLEFILL_RADIUS );
            break;
        case FN_Ellipse: //Sub Procedure
            rc_media_ellipse_hw( ELLIPSE_X, ELLIPSE_Y, ELLIPSE_RX, ELLIPSE_RY );
            break;
        case FN_EllipseFill: //Sub Procedure
            rc_media_ellipseFill_hw( ELLIPSEFILL_X, ELLIPSEFILL_Y, ELLIPSEFILL_RX, ELLIPSEFILL_RY );
            break;
        case FN_FloodFill: //Sub Procedure
            //cout << "FLOOD_X = " << FLOODFILL_X << endl;
            rc_media_floodFill_hw( FLOODFILL_X, FLOODFILL_Y );
            break;
        case FN_GetPixel: //Number Function
            rc_push_num( rc_media_getPixel_hw( GETPIXEL_X, GETPIXEL_Y ) );
            break;
        case FN_SetColor: //Sub Procedure
            rc_media_ink( SETCOLOR_C );
            break;
        case FN_Line: //Sub Procedure
            rc_media_line_hw( LINE_X1, LINE_Y1, LINE_X2, LINE_Y2 );
            break;
        case FN_Poly: //Sub Procedure
            rc_media_poly( POLY_N, &POLY_X, &POLY_Y );
            break;
        case FN_PolyFill: //Sub Procedure
            rc_media_polyfill( POLYFILL_N, &POLYFILL_X, &POLYFILL_Y );
            break;
        case FN_Rect: //Sub Procedure
            rc_media_rectangle( RECT_X, RECT_Y, RECT_W, RECT_H );
            break;
        case FN_RectFill: //Sub Procedure
            rc_media_rectangleFill( RECTFILL_X, RECTFILL_Y, RECTFILL_W, RECTFILL_H );
            break;
        case FN_RoundRect: //Sub Procedure
            rc_media_roundRect( ROUNDRECT_X, ROUNDRECT_Y, ROUNDRECT_W, ROUNDRECT_H, ROUNDRECT_R);
            break;
        case FN_RoundRectFill: //Sub Procedure
            rc_media_roundRectFill( ROUNDRECTFILL_X, ROUNDRECTFILL_Y, ROUNDRECTFILL_W, ROUNDRECTFILL_H, ROUNDRECTFILL_R );
            break;
        case FN_RGB: //Sub Procedure
            rc_push_num( rc_media_rgb( RGB_R, RGB_G, RGB_B ) );
            break;
        case FN_RGBA: //Sub Procedure
            rc_push_num( rc_media_rgba( RGBA_R, RGBA_G, RGBA_B, RGBA_A ) );
            break;
        case FN_PSet: //Sub Procedure
            rc_media_drawPixel_hw( PSET_X, PSET_Y );
            break;
        case FN_LoadImage: //Sub Procedure
            rc_media_loadImage_hw( LOADIMAGE_SLOT, LOADIMAGE_IMG$ );
            break;
        case FN_LoadImage_Ex: //Sub Procedure
            rc_media_loadImage_ex_hw( LOADIMAGE_EX_SLOT, LOADIMAGE_EX_IMG$, LOADIMAGE_EX_COLKEY );
            break;
        case FN_ImageFromBuffer: //Sub Procedure
            rc_media_createImage_hw( IMAGEFROMBUFFER_SLOT, IMAGEFROMBUFFER_W, IMAGEFROMBUFFER_H, &IMAGEFROMBUFFER_BUFFER );
            break;
        case FN_ImageFromBuffer_Ex: //Sub Procedure
            rc_media_createImage_Ex_hw( IMAGEFROMBUFFER_EX_SLOT, IMAGEFROMBUFFER_EX_W, IMAGEFROMBUFFER_EX_H, &IMAGEFROMBUFFER_EX_BUFFER, IMAGEFROMBUFFER_EX_COLKEY );
            break;
        case FN_BufferFromImage:
            rc_media_bufferFromImage(BUFFERFROMIMAGE_SLOT, &BUFFERFROMIMAGE_BUFFER);
            break;
        case FN_ImageExists: //Number Function
            rc_push_num( rc_media_imageExist_hw( IMAGEEXISTS_SLOT ) );
            break;
        case FN_ColorKey: //Sub Procedure
            rc_media_colorKey_hw( COLORKEY_SLOT, COLORKEY_C );
            break;
        case FN_CopyImage: //Sub Procedure
            rc_media_copyImage_hw( COPYIMAGE_SRC, COPYIMAGE_DST );
            break;
        case FN_DeleteImage: //Sub Procedure
            rc_media_deleteImage_hw( DELETEIMAGE_SLOT );
            break;
        case FN_SetImageAlpha: //Sub Procedure
            rc_media_setImageAlpha_hw( SETIMAGEALPHA_SLOT, SETIMAGEALPHA_A );
            break;
        case FN_ImageAlpha: //Number Function
            rc_push_num( rc_media_getImageAlpha_hw( IMAGEALPHA_SLOT ) );
            break;
        case FN_GetImageSize: //Sub Procedure
            rc_media_getImageSize_hw( GETIMAGESIZE_SLOT, &GETIMAGESIZE_W, &GETIMAGESIZE_H );
            break;
        case FN_SetImageBlendMode:
            rc_push_num(rc_media_setImageBlendMode_hw(SETIMAGEBLENDMODE_SLOT, SETIMAGEBLENDMODE_BLEND_MODE));
            break;
        case FN_ImageBlendMode:
            rc_push_num(rc_media_imageBlendMode_hw(IMAGEBLENDMODE_SLOT));
            break;
        case FN_SetImageColorMod:
            rc_push_num(rc_media_setImageColorMod_hw(SETIMAGECOLORMOD_SLOT, SETIMAGECOLORMOD_C));
            break;
        case FN_ImageColorMod:
            rc_push_num(rc_media_imageColorMod_hw(IMAGECOLORMOD_SLOT));
            break;
        case FN_DrawImage: //Sub Procedure
            rc_media_drawImage_hw( DRAWIMAGE_SLOT, DRAWIMAGE_X, DRAWIMAGE_Y );
            break;
        case FN_DrawImage_Blit: //Sub Procedure
            rc_media_drawImage_Clip_hw( DRAWIMAGE_BLIT_SLOT, DRAWIMAGE_BLIT_X, DRAWIMAGE_BLIT_Y, DRAWIMAGE_BLIT_SRC_X, DRAWIMAGE_BLIT_SRC_Y, DRAWIMAGE_BLIT_SRC_W, DRAWIMAGE_BLIT_SRC_H );
            break;
        case FN_DrawImage_Blit_Ex: //Sub Procedure
            rc_media_drawImage_Blit_hw( DRAWIMAGE_BLIT_EX_SLOT, DRAWIMAGE_BLIT_EX_X, DRAWIMAGE_BLIT_EX_Y, DRAWIMAGE_BLIT_EX_W, DRAWIMAGE_BLIT_EX_H,
                                        DRAWIMAGE_BLIT_EX_SRC_X, DRAWIMAGE_BLIT_EX_SRC_Y, DRAWIMAGE_BLIT_EX_SRC_W, DRAWIMAGE_BLIT_EX_SRC_H );
            break;
        case FN_DrawImage_Rotate: //Sub Procedure
            rc_media_rotateImage_hw( DRAWIMAGE_ROTATE_SLOT, DRAWIMAGE_ROTATE_X, DRAWIMAGE_ROTATE_Y, DRAWIMAGE_ROTATE_ANGLE );
            break;
        case FN_DrawImage_Rotate_Ex: //Sub Procedure
            rc_media_rotateImageEX_hw( DRAWIMAGE_ROTATE_EX_SLOT, DRAWIMAGE_ROTATE_EX_X, DRAWIMAGE_ROTATE_EX_Y, DRAWIMAGE_ROTATE_EX_SRC_X, DRAWIMAGE_ROTATE_EX_SRC_Y,
                                       DRAWIMAGE_ROTATE_EX_SRC_W, DRAWIMAGE_ROTATE_EX_SRC_H, DRAWIMAGE_ROTATE_EX_ANGLE );
            break;
        case FN_DrawImage_Zoom: //Sub Procedure
            rc_media_zoomImage_hw( DRAWIMAGE_ZOOM_SLOT, DRAWIMAGE_ZOOM_X, DRAWIMAGE_ZOOM_Y, DRAWIMAGE_ZOOM_ZX, DRAWIMAGE_ZOOM_ZY );
            break;
        case FN_DrawImage_Zoom_Ex: //Sub Procedure
            rc_media_zoomImageEX_hw( DRAWIMAGE_ZOOM_EX_SLOT, DRAWIMAGE_ZOOM_EX_X, DRAWIMAGE_ZOOM_EX_Y, DRAWIMAGE_ZOOM_EX_SRC_X, DRAWIMAGE_ZOOM_EX_SRC_Y,
                                     DRAWIMAGE_ZOOM_EX_SRC_W, DRAWIMAGE_ZOOM_EX_SRC_H, DRAWIMAGE_ZOOM_EX_ZX, DRAWIMAGE_ZOOM_EX_ZY );
            break;
        case FN_DrawImage_Rotozoom: //Sub Procedure
            rc_media_rotozoomImage_hw( DRAWIMAGE_ROTOZOOM_SLOT, DRAWIMAGE_ROTOZOOM_X, DRAWIMAGE_ROTOZOOM_Y, DRAWIMAGE_ROTOZOOM_ANGLE,
                                       DRAWIMAGE_ROTOZOOM_ZX, DRAWIMAGE_ROTOZOOM_ZY );
            break;
        case FN_DrawImage_Rotozoom_Ex: //Sub Procedure
            rc_media_rotozoomImageEX_hw( DRAWIMAGE_ROTOZOOM_EX_SLOT, DRAWIMAGE_ROTOZOOM_EX_X, DRAWIMAGE_ROTOZOOM_EX_Y, DRAWIMAGE_ROTOZOOM_EX_SRC_X, DRAWIMAGE_ROTOZOOM_EX_SRC_Y,
                                         DRAWIMAGE_ROTOZOOM_EX_SRC_W, DRAWIMAGE_ROTOZOOM_EX_SRC_H, DRAWIMAGE_ROTOZOOM_EX_ANGLE, DRAWIMAGE_ROTOZOOM_EX_ZX, DRAWIMAGE_ROTOZOOM_EX_ZY );
            break;
        case FN_DrawImage_Flip:
            rc_media_drawImage_Flip( DRAWIMAGE_FLIP_SLOT, DRAWIMAGE_FLIP_X, DRAWIMAGE_FLIP_Y, DRAWIMAGE_FLIP_H, DRAWIMAGE_FLIP_V );
            break;
        case FN_DrawImage_Flip_Ex:
            rc_media_drawImage_Flip_Ex(DRAWIMAGE_FLIP_EX_SLOT, DRAWIMAGE_FLIP_EX_X, DRAWIMAGE_FLIP_EX_Y, DRAWIMAGE_FLIP_EX_SRC_X, DRAWIMAGE_FLIP_EX_SRC_Y, DRAWIMAGE_FLIP_EX_SRC_W,
                                       DRAWIMAGE_FLIP_EX_SRC_H, DRAWIMAGE_FLIP_EX_H, DRAWIMAGE_FLIP_EX_V);
            break;
        case FN_InKey: //Number Function
            rc_push_num( rc_media_inkey() );
            break;
        case FN_Key: //Number Function
            rc_push_num( rc_media_key( KEY_KEY_CODE ) );
            break;
        case FN_WaitKey: //Number Function
            rc_push_num( rc_media_waitKey() );
            break;
        case FN_HideMouse: //Sub Procedure
            rc_media_hideMouse();
            break;
        case FN_ShowMouse: //Sub Procedure
            rc_media_showMouse();
            break;
        case FN_MouseIsVisible: //Number Function
            rc_push_num( rc_media_mouseIsVisible() );
            break;
        case FN_GetMouse: //Sub Procedure
            rc_media_getMouse( &GETMOUSE_X, &GETMOUSE_Y, &GETMOUSE_MB1, &GETMOUSE_MB2, &GETMOUSE_MB3 );
            break;
        case FN_MouseX: //Number Function
            rc_push_num( rc_media_mouseX() );
            break;
        case FN_MouseY: //Number Function
            rc_push_num( rc_media_mouseY() );
            break;
        case FN_MouseButton: //Number Function
            rc_push_num( rc_media_mouseButton( MOUSEBUTTON_MB ) );
            break;
        case FN_GetMouseWheel: //Sub Procedure
            rc_media_getMouseWheel( &GETMOUSEWHEEL_X_AXIS, &GETMOUSEWHEEL_Y_AXIS );
            break;
        case FN_MouseWheelX: //Number Function
            rc_push_num( rc_media_mouseWheelX() );
            break;
        case FN_MouseWheelY: //Number Function
            rc_push_num( rc_media_mouseWheelY() );
            break;
        case FN_SoundFromBuffer: //Sub Procedure
            rc_media_createSound( SOUNDFROMBUFFER_SLOT, &SOUNDFROMBUFFER_BUFFER, SOUNDFROMBUFFER_BUFFER_SIZE, SOUNDFROMBUFFER_VOL );
            break;
        case FN_LoadSound: //Sub Procedure
            rc_media_loadSound( LOADSOUND_SLOT, LOADSOUND_SND_FILE$ );
            break;
        case FN_LoadMusic: //Sub Procedure
            rc_media_loadMusic( LOADMUSIC_MUSIC_FILE$ );
            break;
        case FN_PlaySound: //Sub Procedure
            rc_media_playSound( PLAYSOUND_SLOT, PLAYSOUND_CHANNEL, PLAYSOUND_LOOPS );
            break;
        case FN_PlaySoundTimed: //Sub Procedure
            rc_media_playSoundTimed( PLAYSOUNDTIMED_SLOT, PLAYSOUNDTIMED_CHANNEL, PLAYSOUNDTIMED_LOOPS, PLAYSOUNDTIMED_MS );
            break;
        case FN_PlayMusic: //Sub Procedure
            rc_media_playMusic( PLAYMUSIC_MLOOPS );
            break;
        case FN_PauseSound: //Sub Procedure
            rc_media_pauseSound( PAUSESOUND_CHANNEL );
            break;
        case FN_ResumeSound: //Sub Procedure
            rc_media_resumeSound( RESUMESOUND_CHANNEL );
            break;
        case FN_PauseMusic: //Sub Procedure
            rc_media_pauseMusic();
            break;
        case FN_ResumeMusic: //Sub Procedure
            rc_media_resumeMusic();
            break;
        case FN_DeleteSound: //Sub Procedure
            rc_media_deleteSound( DELETESOUND_SLOT );
            break;
        case FN_DeleteMusic: //Sub Procedure
            rc_media_deleteMusic();
            break;
        case FN_FadeMusicIn: //Sub Procedure
            rc_media_fadeMusicIn( FADEMUSICIN_FADE_TIME, FADEMUSICIN_LOOPS );
            break;
        case FN_FadeMusicOut: //Sub Procedure
            rc_media_fadeMusicOut( FADEMUSICOUT_FADE_TIME );
            break;
        case FN_MusicExists: //Number Function
            rc_push_num( rc_media_musicExists() );
            break;
        case FN_SetMusicVolume: //Sub Procedure
            rc_media_setMusicVolume( SETMUSICVOLUME_VOL );
            break;
        case FN_MusicVolume: //Number Function
            rc_push_num( rc_media_getMusicVolume() );
            break;
        case FN_SetMusicPosition: //Sub Procedure
            rc_media_setMusicPosition( SETMUSICPOSITION_POS );
            break;
        case FN_MusicPosition: //Number Function
            rc_push_num( rc_media_getMusicPosition() );
            break;
        case FN_RewindMusic: //Sub Procedure
            rc_media_rewindMusic();
            break;
        case FN_SetSoundChannels: //Sub Procedure
            rc_media_setSoundChannels( SETSOUNDCHANNELS_MAX_CHANNELS );
            break;
        case FN_NumSoundChannels: //Number Function
            rc_push_num( rc_media_getSoundChannels() );
            break;
        case FN_SoundIsEnabled: //Number Function
            rc_push_num( rc_media_soundIsEnabled() );
            break;
        case FN_SoundExists: //Number Function
            rc_push_num( rc_media_soundExists( SOUNDEXISTS_SLOT ) );
            break;
        case FN_SetChannelVolume: //Sub Procedure
            rc_media_setChannelVolume( SETCHANNELVOLUME_CHANNEL, SETCHANNELVOLUME_VOL );
            break;
        case FN_ChannelVolume: //Number Function
            rc_push_num( rc_media_getChannelVolume( CHANNELVOLUME_CHANNEL ) );
            break;
        case FN_SetSoundVolume: //Sub Procedure
            rc_media_setSoundVolume( SETSOUNDVOLUME_SLOT, SETSOUNDVOLUME_VOL );
            break;
        case FN_SoundVolume: //Number Function
            rc_push_num( rc_media_getSoundVolume( SOUNDVOLUME_SLOT ) );
            break;
        case FN_StopMusic: //Sub Procedure
            rc_media_stopMusic();
            break;
        case FN_StopSound: //Sub Procedure
            rc_media_stopSound( STOPSOUND_CHANNEL );
            break;
        case FN_ChannelIsPlaying:
            rc_push_num( rc_media_channelIsPlaying( CHANNELISPLAYING_CHANNEL ));
            break;
        case FN_ChannelIsPaused:
            rc_push_num( rc_media_channelIsPaused( CHANNELISPAUSED_CHANNEL ));
            break;
        case FN_SetChannelDistance:
            rc_push_num( rc_media_setChannelDistance( SETCHANNELDISTANCE_CHANNEL, SETCHANNELDISTANCE_DIST_VALUE ) );
            break;
        case FN_SetChannelPanning:
            rc_push_num( rc_media_setChannelPanning( SETCHANNELPANNING_CHANNEL, SETCHANNELPANNING_LEFT_VALUE, SETCHANNELPANNING_RIGHT_VALUE ) );
            break;
        case FN_NumJoysticks: //Number Function
            rc_push_num( rc_media_numJoysticks() );
            break;
        case FN_NumJoyAxes: //Number Function
            rc_push_num( rc_media_numJoyAxes( NUMJOYAXES_JOY_NUM ) );
            break;
        case FN_NumJoyButtons: //Number Function
            rc_push_num( rc_media_numJoyButtons( NUMJOYBUTTONS_JOY_NUM ) );
            break;
        case FN_NumJoyHats: //Number Function
            rc_push_num( rc_media_numJoyHats( NUMJOYHATS_JOY_NUM ) );
            break;
        case FN_NumJoyTrackBalls: //Number Function
            rc_push_num( rc_media_numJoyTrackBalls( NUMJOYTRACKBALLS_JOY_NUM ) );
            break;
        case FN_JoyAxis: //Number Function
            rc_push_num( rc_media_joyAxis( JOYAXIS_JOY_NUM, JOYAXIS_JOY_AXIS ) );
            break;
        case FN_JoyButton: //Number Function
            rc_push_num( rc_media_joyButton( JOYBUTTON_JOY_NUM, JOYBUTTON_JOY_BUTTON ) );
            break;
        case FN_JoyHat: //Number Function
            rc_push_num( rc_media_joyHat( JOYHAT_JOY_NUM, JOYHAT_JOY_HAT ) );
            break;
        case FN_GetJoyTrackBall: //Sub Procedure
            rc_media_getJoyTrackBall( GETJOYTRACKBALL_JOY_NUM, GETJOYTRACKBALL_BALL, &GETJOYTRACKBALL_DX, &GETJOYTRACKBALL_DY );
            break;
        case FN_JoyName$: //String Function
            rc_push_str( rc_media_joystickName( JOYNAME$_JOY_NUM ) );
            break;
        case FN_JoystickIsConnected: //Number Function
            rc_push_num( rc_media_joystickIsConnected( JOYSTICKISCONNECTED_JOY_NUM ) );
            break;
        case FN_GetCursor: //Sub Procedure
            rc_media_getCursor( &GETCURSOR_X, &GETCURSOR_Y );
            break;
        case FN_PrintS: //Sub Procedure
            rc_media_printS_hw( PRINTS_TXT$ );
            break;
        case FN_InputS$: //String Function
            rc_push_str( rc_media_inputS_hw( INPUTS$_PROMPT$ ) );
            break;
        case FN_ZoneInputS$: //String Function
            rc_push_str( rc_media_ZoneInputS_hw( ZONEINPUTS$_X, ZONEINPUTS$_Y, ZONEINPUTS$_W, ZONEINPUTS$_H ) );
            break;
        case FN_Locate: //Sub Procedure
            rc_media_locate( LOCATE_X, LOCATE_Y );
            break;
        case FN_ReadInput_Start: //Sub Procedure
            rc_media_ReadInput_Start();
            break;
        case FN_ReadInput_Stop: //Sub Procedure
            rc_media_ReadInput_Stop();
            break;
        case FN_ReadInput_Text$: //String Function
            rc_push_str( rc_media_ReadInput_Text() );
            break;
        case FN_ReadInput_SetText: //Sub Procedure
            rc_media_ReadInput_SetText( READINPUT_SETTEXT_TXT$ );
            break;
        case FN_ReadInput_ToggleBackspace: //Sub Procedure
            rc_media_ReadInput_ToggleBackspace( READINPUT_TOGGLEBACKSPACE_FLAG );
            break;
        case FN_LoadFont: //Sub Procedure
            rc_media_LoadFont( LOADFONT_SLOT, LOADFONT_FNT_FILE$, LOADFONT_SIZE );
            break;
        case FN_DeleteFont: //Sub Procedure
            rc_media_DeleteFont( DELETEFONT_SLOT );
            break;
        case FN_FontIsLoaded: //Number Function
            rc_push_num( rc_media_fontIsLoaded( FONTISLOADED_SLOT ) );
            break;
        case FN_Font: //Sub Procedure
            rc_media_font( FONT_SLOT );
            break;
        case FN_SetFontStyle: //Sub Procedure
            rc_media_setFontStyle( SETFONTSTYLE_SLOT, SETFONTSTYLE_STYLE );
            break;
        case FN_DrawText: //Sub Procedure
            rc_media_drawText_hw( DRAWTEXT_TXT$, DRAWTEXT_X, DRAWTEXT_Y );
            break;
        case FN_DrawText_Shaded: //Sub Procedure
            rc_media_drawText_shaded_hw( DRAWTEXT_SHADED_TXT$, DRAWTEXT_SHADED_X, DRAWTEXT_SHADED_Y, DRAWTEXT_SHADED_FG_COLOR, DRAWTEXT_SHADED_BG_COLOR );
            break;
        case FN_DrawText_Blended: //Sub Procedure
            rc_media_drawText_blended_hw( DRAWTEXT_BLENDED_TXT$, DRAWTEXT_BLENDED_X, DRAWTEXT_BLENDED_Y );
            break;
        case FN_RenderText: //Sub Procedure
            rc_media_GetRenderedText_hw( RENDERTEXT_SLOT, RENDERTEXT_TXT$ );
            break;
        case FN_GetTextSize: //Sub Procedure
            rc_media_getTextSize( GETTEXTSIZE_SLOT, GETTEXTSIZE_TXT$, &GETTEXTSIZE_W, &GETTEXTSIZE_H );
            break;
        case FN_TouchPressure: //Number Function
            rc_push_num( rc_media_touchPressure() );
            break;
        case FN_GetTouch: //Sub Procedure
            rc_media_getTouch( &GETTOUCH_STATUS, &GETTOUCH_X, &GETTOUCH_Y, &GETTOUCH_DX, &GETTOUCH_DY );
            break;
        case FN_GetMultiTouch: //Sub Procedure
            rc_media_getMultiTouch( &GETMULTITOUCH_STATUS, &GETMULTITOUCH_X, &GETMULTITOUCH_Y, &GETMULTITOUCH_FINGERS, &GETMULTITOUCH_DIST, &GETMULTITOUCH_THETA );
            break;
        case FN_GetTouchFinger: //Sub Procedure
            rc_media_getTouchFinger( GETTOUCHFINGER_FINGER, &GETTOUCHFINGER_X, &GETTOUCHFINGER_Y, &GETTOUCHFINGER_PRESSURE );
            break;
        case FN_NumFingers: //Number Function
            rc_push_num( rc_media_numFingers() );
            break;
        case FN_CheckSockets:
            rc_push_num( rc_net_checkSockets( CHECKSOCKETS_TIMEOUT_MS ) );
            break;
        case FN_TCP_SocketReady:
            rc_push_num( rc_net_tcp_socketReady( TCP_SOCKETREADY_SOCKET ) );
            break;
        case FN_UDP_SocketReady:
            rc_push_num( rc_net_udp_socketReady( UDP_SOCKETREADY_SOCKET ) );
            break;
        case FN_TCP_SocketOpen: //Number Function
            rc_push_num( rc_net_tcp_openSocket(TCP_SOCKETOPEN_SOCKET, TCP_SOCKETOPEN_HOST$, TCP_SOCKETOPEN_PORT ) );
            break;
        case FN_TCP_SocketClose: //Sub Procedure
            rc_net_tcp_closeSocket( TCP_SOCKETCLOSE_SOCKET );
            break;
        case FN_TCP_RemoteHost: //Number Function
            rc_push_num( rc_net_tcp_remoteHost( TCP_REMOTEHOST_SOCKET ) );
            break;
        case FN_TCP_RemotePort: //Number Function
            rc_push_num( rc_net_tcp_remotePort( TCP_REMOTEPORT_SOCKET ) );
            break;
        case FN_TCP_GetData: //Number Function
            rc_push_num( rc_net_tcp_getData_str( TCP_GETDATA_SOCKET, &TCP_GETDATA_SDATA$, TCP_GETDATA_NUMBYTES ) );
            break;
        case FN_TCP_SendData: //Sub Procedure
            rc_net_tcp_sendData( TCP_SENDDATA_SOCKET, TCP_SENDDATA_SDATA$.c_str(), TCP_SENDDATA_SDATA$.length() );
            break;
        case FN_TCP_AcceptSocket: //Number Function
            rc_push_num( rc_net_tcp_acceptSocket( TCP_ACCEPTSOCKET_SERVER, TCP_ACCEPTSOCKET_CLIENT ) );
            break;
        case FN_UDP_SocketOpen: //Number Function
            rc_push_num( rc_net_udp_openSocket( UDP_SOCKETOPEN_SOCKET, UDP_SOCKETOPEN_PORT ) );
            break;
        case FN_UDP_SocketClose: //Sub Procedure
            rc_push_num(rc_net_udp_closeSocket( UDP_SOCKETCLOSE_SOCKET ));
            break;
        case FN_UDP_GetData: //Number Function
            rc_push_num( rc_net_udp_readStream( UDP_GETDATA_SOCKET, &UDP_GETDATA_SDATA$, &UDP_GETDATA_HOST$, &UDP_GETDATA_PORT ) );
            break;
        case FN_UDP_Length: //Number Function
            rc_push_num( rc_net_udp_len());
            break;
        case FN_UDP_MaxLength: //Number Function
            rc_push_num( rc_net_udp_maxlen() );
            break;
        case FN_UDP_RemoteHost$: //String Function
            rc_push_str( rc_net_udp_getRemoteHost( UDP_REMOTEHOST$_SOCKET ) );
            break;
        case FN_UDP_RemotePort: //Number Function
            rc_push_num( rc_net_udp_getRemotePort( UDP_REMOTEPORT_SOCKET ) );
            break;
        case FN_UDP_SendData: //Sub Procedure
            rc_net_udp_sendData( UDP_SENDDATA_SOCKET, UDP_SENDDATA_HOST$, UDP_SENDDATA_PORT, UDP_SENDDATA_SDATA$ );
            break;
        case FN_LoadVideo: //Sub Procedure
            rc_media_loadVideo( LOADVIDEO_VID$ );
            break;
        case FN_PlayVideo: //Sub Procedure
            rc_media_playVideo( PLAYVIDEO_VLOOPS );
            break;
        case FN_PauseVideo: //Sub Procedure
            rc_media_pauseVideo();
            break;
        case FN_StopVideo: //Sub Procedure
            rc_media_stopVideo();
            break;
        case FN_SetVideoPosition: //Sub Procedure
            rc_media_setVideoPosition( SETVIDEOPOSITION_POS );
            break;
        case FN_ResumeVideo: //Sub Procedure
            rc_media_resumeVideo();
            break;
        case FN_VideoPosition: //Number Function
            rc_push_num( rc_media_videoPosition() );
            break;
        case FN_DeleteVideo: //Sub Procedure
            rc_media_deleteVideo();
            break;
        case FN_VideoIsPlaying: //Number Function
            rc_push_num( rc_media_videoIsPlaying() );
            break;
        case FN_VideoEnd: //Number Function
            rc_push_num( rc_media_videoEnd() );
            break;
        case FN_GetVideoStats: //Sub Procedure
            rc_media_getVideoStats( GETVIDEOSTATS_VFILE$, &GETVIDEOSTATS_VLEN, &GETVIDEOSTATS_VFPS, &GETVIDEOSTATS_FRAME_W, &GETVIDEOSTATS_FRAME_H );
            break;
        case FN_SetVideoDrawRect: //Sub Procedure
            rc_media_setVideoDrawRect( SETVIDEODRAWRECT_X, SETVIDEODRAWRECT_Y, SETVIDEODRAWRECT_W, SETVIDEODRAWRECT_H );
            break;
        case FN_GetVideoDrawRect: //Sub Procedure
            rc_media_getVideoDrawRect( &GETVIDEODRAWRECT_X, &GETVIDEODRAWRECT_Y, &GETVIDEODRAWRECT_W, &GETVIDEODRAWRECT_H );
            break;
        case FN_GetVideoSize: //Sub Procedure
            rc_media_getVideoSize( &GETVIDEOSIZE_W, &GETVIDEOSIZE_H );
            break;
        case FN_VideoExists: //Number Function
            rc_push_num( rc_media_videoExists() );
            break;
        case FN_SetVideoAlpha: //Sub Procedure
            rc_media_setVideoAlpha( SETVIDEOALPHA_A );
            break;
        case FN_System: //Number Function
            rc_push_num( rc_intern_system( SYSTEM_CMD$ ) );
            break;
        case FN_OS$: //String Function
            rc_push_str( rc_intern_OS());
            break;
        case FN_Command$: //String Function
            rc_push_str( rc_intern_command( COMMAND$_ARG ) );
            break;
        case FN_NumCommands: //Number Function
            rc_push_num( rc_intern_numCommands() );
            break;
        case FN_Env$: //String Function
            rc_push_str( rc_intern_env( ENV$_V$ ) );
            break;
        case FN_SetEnv: //Sub Procedure
            rc_intern_setEnv( SETENV_VAR$, SETENV_VALUE$, SETENV_OVERWRITE );
            break;
        case FN_PrefPath$: //String Function
            rc_push_str( rc_intern_prefPath( PREFPATH$_ORG_NAME$, PREFPATH$_APP_NAME$ ) );
            break;
        case FN_ClipboardText$:
            rc_push_str( rc_media_getClipboardText() );
            break;
        case FN_SetClipboardText:
            rc_media_setClipboardText( SETCLIPBOARDTEXT_TXT$ );
            break;
        case FN_HasClipboardText:
            rc_push_num( rc_media_hasClipboardText() );
            break;
        case FN_Android_GetExternalStoragePath$:
            rc_push_str( rc_intern_android_getExternalStoragePath() );
            break;
        case FN_Android_GetExternalStorageState:
            rc_push_num( rc_intern_android_getExternalStorageState() );
            break;
        case FN_Android_GetInternalStoragePath$:
            rc_push_str( rc_intern_android_getInternalStoragePath() );
            break;
        case FN_Android_JNI_Message$:
            rc_push_str( rc_intern_android_jni_message( ANDROID_JNI_MESSAGE$_ARG$ ));
            break;
        case FN_Runtime_Utility_Message$:
            rc_push_str( rc_intern_runtime_utility( RUNTIME_UTILITY_MESSAGE$_ARG$ ));
            break;
        case FN_GetDesktopDisplayMode: //Sub Procedure
            rc_media_getDesktopDisplayMode( GETDESKTOPDISPLAYMODE_INDEX, &GETDESKTOPDISPLAYMODE_W, &GETDESKTOPDISPLAYMODE_H, &GETDESKTOPDISPLAYMODE_FREQ);
            break;
        case FN_DrawImage_Transform: //Sub Procedure
            rc_media_drawImage_Transform(DRAWIMAGE_TRANSFORM_SLOT, DRAWIMAGE_TRANSFORM_X, DRAWIMAGE_TRANSFORM_Y, DRAWIMAGE_TRANSFORM_W, DRAWIMAGE_TRANSFORM_H,
                                         DRAWIMAGE_TRANSFORM_SRC_X, DRAWIMAGE_TRANSFORM_SRC_Y, DRAWIMAGE_TRANSFORM_W, DRAWIMAGE_TRANSFORM_H, DRAWIMAGE_TRANSFORM_ANGLE,
                                         DRAWIMAGE_TRANSFORM_CENTER_X, DRAWIMAGE_TRANSFORM_CENTER_Y, DRAWIMAGE_TRANSFORM_FLIP_H, DRAWIMAGE_TRANSFORM_FLIP_V);
            break;
        case FN_GetPowerInfo: //Sub Procedure
            rc_intern_getPowerInfo(&GETPOWERINFO_STATUS, &GETPOWERINFO_SECS, &GETPOWERINFO_PCT);
            break;
        case FN_SystemRam: //Number Function
            rc_push_num( rc_intern_systemRam() );
            break;
        case FN_SetRenderScaleQuality: //Number Function
            rc_push_num( rc_media_setRenderScaleQuality((int)SETRENDERSCALEQUALITY_N) );
            break;
        case FN_EvalJS$: //String Function
            rc_push_str( rc_intern_evalJS( EVALJS$_JS_CODE$) );
            break;
        case FN_GetRenderScaleQuality: //Number Function
            rc_push_num( rc_media_getRenderScaleQuality() );
            break;
        case FN_GetGlobalMouse: //Sub Procedure
            rc_media_getGlobalMouse(&GETGLOBALMOUSE_X, &GETGLOBALMOUSE_Y, &GETGLOBALMOUSE_MB1, &GETGLOBALMOUSE_MB2, &GETGLOBALMOUSE_MB3);
            break;
        case FN_GlobalMouseX: //Number Function
            rc_push_num( rc_media_globalMouseX() );
            break;
        case FN_GlobalMouseY: //Number Function
            rc_push_num( rc_media_globalMouseY() );
            break;
        case FN_GetAccel: //Sub Procedure
            rc_media_getAccel( GETACCEL_ACCEL_NUM, &GETACCEL_X, &GETACCEL_Y, &GETACCEL_Z );
            break;
        case FN_AccelName$: //String Function
            rc_push_str( rc_media_accelName( ACCELNAME$_ACCEL_NUM ) );
            break;
        case FN_NumAccels: //Number Function
            rc_push_num( rc_media_numAccels() );
            break;
        case FN_GetGyro: //Sub Procedure
            rc_media_getGyro( GETGYRO_GYRO_NUM, &GETGYRO_X, &GETGYRO_Y, &GETGYRO_Z );
            break;
        case FN_GyroName$: //String Function
            rc_push_str( rc_media_gyroName( GYRONAME$_GYRO_NUM ));
            break;
        case FN_NumGyros: //Number Function
            rc_push_num( rc_media_numGyros() );
            break;
        case FN_JoyRumblePlay: //Sub Procedure
            rc_media_joyRumblePlay( JOYRUMBLEPLAY_JOY_NUM, JOYRUMBLEPLAY_STRENGTH, JOYRUMBLEPLAY_DURATION );
            break;
        case FN_JoyRumbleStop: //Sub Procedure
            rc_media_joyRumbleStop( JOYRUMBLESTOP_JOY_NUM );
            break;
        case FN_JoystickIsHaptic: //Number Function
            rc_push_num( rc_media_joystickIsHaptic( JOYSTICKISHAPTIC_JOY_NUM ) );
            break;
        case FN_WriteByteBuffer: //Number Function
            rc_push_num( rc_intern_fileWriteByteBuffer( WRITEBYTEBUFFER_STREAM, &WRITEBYTEBUFFER_BUF, WRITEBYTEBUFFER_BUF_SIZE ) );
            break;
        case FN_ReadByteBuffer: //Number Function
            rc_push_num( rc_intern_fileReadByteBuffer( READBYTEBUFFER_STREAM, &READBYTEBUFFER_BUF, READBYTEBUFFER_BUF_SIZE ) );
            break;
        case FN_WindowEvent_Resize: //Number Function
            rc_push_num( rc_media_windowEvent_Resize( WINDOWEVENT_RESIZE_WIN ) );
            break;
        case FN_SetWindowAutoClose: //Sub Procedure
            rc_media_windowEvent_setExitOnClose( SETWINDOWAUTOCLOSE_WIN, SETWINDOWAUTOCLOSE_EXIT_ON_CLOSE );
            break;
        case FN_SetWindowResizable:
            rc_media_setWindowResizable(SETWINDOWRESIZABLE_WIN, SETWINDOWRESIZABLE_FLAG);
            break;
        case FN_SystemReturnStdOut$:
            rc_push_str( rc_intern_sysReturnOutput(SYSTEMRETURNSTDOUT$_CMD$) );
            break;
        case FN_WindowMode:
            rc_push_num( rc_media_windowMode(WINDOWMODE_VISIBLE, WINDOWMODE_FULLSCREEN, WINDOWMODE_RESIZABLE, WINDOWMODE_BORDERLESS, WINDOWMODE_HIGHDPI) );
            break;
        case FN_WindowFlags:
            rc_push_num( rc_media_windowFlags(WINDOWFLAGS_WIN) );
            break;
        case FN_RestoreWindow:
            rc_media_restoreWindow(RESTOREWINDOW_WIN);
            break;
        case FN_UpdateAllWindows:
            rc_events();
            rc_media_updateAllWindow_hw();
            #ifdef RC_WEB
                emscripten_sleep(0);
            #else
                SDL_Delay(0);
            #endif // RC_WEB
            break;
        case FN_QueryAudioSpec:
            rc_push_num( rc_media_queryAudioSpec(&QUERYAUDIOSPEC_FREQ, &QUERYAUDIOSPEC_FORMAT, &QUERYAUDIOSPEC_CHANNELS) );
            break;
    }
}

void push_131(double num)
{
    rc_vm_n tmp_n;
    tmp_n.value = num;
    n_stack.push(tmp_n);
    //current_n_stack_count++;
}

void println_132()
{
    cout << endl;
}

void mov_133(int n1, int flag)
{
    switch(flag)
    {
        case LESS_FLAG:
            vm_n[n1].value = CMP_FLAG_LESS;
            break;
        case LESS_EQUAL_FLAG:
            vm_n[n1].value = CMP_FLAG_LESS_EQUAL;
            break;
        case GREATER_FLAG:
            vm_n[n1].value = CMP_FLAG_GREATER;
            break;
        case GREATER_EQUAL_FLAG:
            vm_n[n1].value = CMP_FLAG_GREATER_EQUAL;
            break;
        case EQUAL_FLAG:
            vm_n[n1].value = CMP_FLAG_EQUAL;
            break;
        case NOT_EQUAL_FLAG:
            vm_n[n1].value = CMP_FLAG_NOT_EQUAL;
            break;
    }
    //cout << "n" << n1 << " = " << vm_n[n1].value << endl;
}

void cmp_134(int n1, double num)
{
    CMP_FLAG_EQUAL = (vm_n[n1].value == num);
    CMP_FLAG_GREATER = (vm_n[n1].value > num);
    CMP_FLAG_GREATER_EQUAL = (vm_n[n1].value >= num);
    CMP_FLAG_LESS = (vm_n[n1].value < num);
    CMP_FLAG_LESS_EQUAL = (vm_n[n1].value <= num);
    CMP_FLAG_NOT_EQUAL = (vm_n[n1].value != num);
}

void mov_arr_135(int n1, uint64_t nid)
{
    arr_ref_id = nid;
    vm_n[n1].r = num_var[nid].nid_value;
}

void mov_arrS_136(int s1, uint64_t sid)
{
    arr_ref_id = sid;
    vm_s[s1].r = str_var[sid].sid_value;
}

void pop_ptr_137(uint64_t n)
{
    //cout << "pop_ptr " << n << endl;
    //cout << "b_stack_size = " << byref_addr_table.size() << endl;
    for(int i = 0; i < n; i++)
    {
        //cout << "byref i = " << i << endl;
        switch(byref_addr_table.top().type)
        {
            case BYREF_TYPE_NUM:
                num_var[byref_addr_table.top().ptr_id].nid_value = (n_value*)byref_addr_table.top().ptr_addr;
                num_var[byref_addr_table.top().ptr_id].byref_offset = byref_var_byref_offset.top();
                break;
            case BYREF_TYPE_STR:
                str_var[byref_addr_table.top().ptr_id].sid_value = (s_value*)byref_addr_table.top().ptr_addr;
                str_var[byref_addr_table.top().ptr_id].byref_offset = byref_var_byref_offset.top();
                break;
        }
        byref_addr_table.pop();
        byref_var_byref_offset.pop();
    }
}

void preset_138(uint64_t nid)
{
    int nid_size = 1;
    switch(num_var[nid].dimensions)
    {
        case 3:
            nid_size *= num_var[nid].dim[2];
        case 2:
            nid_size *= num_var[nid].dim[1];
        case 1:
            nid_size *= num_var[nid].dim[0];
            break;
    }
    for(int i = 0; i < nid_size; i++)
        num_var[nid].nid_value[0].value[i] = 0;
}

void presetS_139(uint64_t sid)
{
    int sid_size = 1;
    switch(str_var[sid].dimensions)
    {
        case 3:
            sid_size *= str_var[sid].dim[2];
        case 2:
            sid_size *= str_var[sid].dim[1];
        case 1:
            sid_size *= str_var[sid].dim[0];
            break;
    }
    for(int i = 0; i < sid_size; i++)
        str_var[sid].sid_value[0].value[i] = "";
}

void redim_140(uint64_t nid, int n1)
{
    num_var[nid].nid_value[0].value.resize((uint64_t)vm_n[n1].value);
    num_var[nid].dimensions = 1;
    num_var[nid].dim[0] = (uint64_t)vm_n[n1].value;
    num_var[nid].dim[1] = 0;
    num_var[nid].dim[2] = 0;
}

void redim_141(uint64_t nid, int n1, int n2)
{
    num_var[nid].nid_value[0].value.resize( (uint64_t)vm_n[n1].value * (uint64_t)vm_n[n2].value );
    num_var[nid].dimensions = 2;
    num_var[nid].dim[0] = (uint64_t)vm_n[n1].value;
    num_var[nid].dim[1] = (uint64_t)vm_n[n2].value;
    num_var[nid].dim[2] = 0;
}

void redim_142(uint64_t nid, int n1, int n2, int n3)
{
    num_var[nid].nid_value[0].value.resize( (uint64_t)vm_n[n1].value * (uint64_t)vm_n[n2].value * (uint64_t)vm_n[n3].value);
    num_var[nid].dimensions = 3;
    num_var[nid].dim[0] = (uint64_t)vm_n[n1].value;
    num_var[nid].dim[1] = (uint64_t)vm_n[n2].value;
    num_var[nid].dim[2] = (uint64_t)vm_n[n3].value;
}

void redimS_143(uint64_t sid, int n1)
{
    str_var[sid].sid_value[0].value.resize((uint64_t)vm_n[n1].value);
    str_var[sid].dimensions = 1;
    str_var[sid].dim[0] = (uint64_t)vm_n[n1].value;
    str_var[sid].dim[1] = 0;
    str_var[sid].dim[2] = 0;
}

void redimS_144(uint64_t sid, int n1, int n2)
{
    str_var[sid].sid_value[0].value.resize( (uint64_t)vm_n[n1].value * (uint64_t)vm_n[n2].value );
    str_var[sid].dimensions = 2;
    str_var[sid].dim[0] = (uint64_t)vm_n[n1].value;
    str_var[sid].dim[1] = (uint64_t)vm_n[n2].value;
    str_var[sid].dim[2] = 0;
}

void redimS_145(uint64_t sid, int n1, int n2, int n3)
{
    str_var[sid].sid_value[0].value.resize( (uint64_t)vm_n[n1].value * (uint64_t)vm_n[n2].value * (uint64_t)vm_n[n3].value);
    str_var[sid].dimensions = 3;
    str_var[sid].dim[0] = (uint64_t)vm_n[n1].value;
    str_var[sid].dim[1] = (uint64_t)vm_n[n2].value;
    str_var[sid].dim[2] = (uint64_t)vm_n[n3].value;
}

void for_offset_arr1_146(int n1)
{
    for_offset_index[0] = vm_n[n1].value;
    for_offset_dimensions = 1;
}

void for_offset_arr2_147(int n1, int n2)
{
    for_offset_index[0] = vm_n[n1].value;
    for_offset_index[1] = vm_n[n2].value;
    for_offset_dimensions = 2;
}

void for_offset_arr3_148(int n1, int n2, int n3)
{
    for_offset_index[0] = vm_n[n1].value;
    for_offset_index[1] = vm_n[n2].value;
    for_offset_index[2] = vm_n[n3].value;
    for_offset_dimensions = 3;
}

void for_offset_0_149()
{
    for_offset_dimensions = 0;
}

void end_x_150(int n1)
{
    rcbasic_exit_code = (int)vm_n[n1].value;
}

bool rcbasic_run()
{
    unsigned char rcbasic_cmd;
    double d[6];
    uint64_t i[6];
    bool end_of_program = false;
    while(!end_of_program)
    {
        rcbasic_cmd = segment[current_segment][current_address];
        current_address++;

        //cout << "n3 = " << vm_n[3].value << endl;
        //cout << "x = " << num_var[0].value[0] << endl;
        //cout << "\ncmd = " << (int)rcbasic_cmd << endl;

        switch(rcbasic_cmd)
        {
            case 0:
                end_of_program = true;
                rcbasic_exit_code = 0;
                break;
            case 32:
                i[0] = readInt();
                i[1] = readInt();
                mov_32(i[0], i[1]);
                break;
            case 33:
                i[0] = readInt();
                d[0] = readDouble();
                mov_33(i[0], d[0]);
                break;
            case 34:
                i[0] = readInt();
                i[1] = readInt();
                mov_34(i[0], i[1]);
                break;
            case 35:
                i[0] = readInt();
                i[1] = readInt();
                //cout << "mov_35 x is " << i[0] << endl;
                //cout << "mov_35 is using n" << i[1] << endl;
                mov_35(i[0], i[1]);
                break;
            case 36:
                i[0] = readInt();
                i[1] = readInt();
                movS_36(i[0], i[1]);
                break;
            case 37:
                i[0] = readInt();
                i[1] = readInt();
                movS_37(i[0], i[1]);
                break;
            case 38:
                i[0] = readInt();
                i[1] = readInt();
                movS_38(i[0], i[1]);
                break;
            case 39:
                i[0] = readInt();
                i[1] = readInt();
                movS_39(i[0], i[1]);
                break;
            case 40:
                i[0] = readInt();
                i[1] = readInt();
                mov_r_40(i[0], i[1]);
                break;
            case 41:
                i[0] = readInt();
                i[1] = readInt();
                mov_rS_41(i[0], i[1]);
                break;
            case 42:
                //mov_type  is not currently used
                break;
            case 43:
                i[0] = readInt();
                i[1] = readInt();
                addS_43(i[0], i[1]);
                break;
            case 44:
                i[0] = readInt();
                i[1] = readInt();
                add_44(i[0], i[1]);
                break;
            case 45:
                i[0] = readInt();
                i[1] = readInt();
                sub_45(i[0], i[1]);
                break;
            case 46:
                i[0] = readInt();
                i[1] = readInt();
                mul_46(i[0], i[1]);
                break;
            case 47:
                i[0] = readInt();
                i[1] = readInt();
                div_47(i[0], i[1]);
                break;
            case 48:
                i[0] = readInt();
                i[1] = readInt();
                pow_48(i[0], i[1]);
                break;
            case 49:
                i[0] = readInt();
                i[1] = readInt();
                mod_49(i[0], i[1]);
                break;
            case 50:
                i[0] = readInt();
                i[1] = readInt();
                shl_50(i[0], i[1]);
                break;
            case 51:
                i[0] = readInt();
                i[1] = readInt();
                shr_51(i[0], i[1]);
                break;
            case 52:
                i[0] = readInt();
                i[1] = readInt();
                and_52(i[0], i[1]);
                break;
            case 53:
                i[0] = readInt();
                i[1] = readInt();
                or_53(i[0], i[1]);
                break;
            case 54:
                i[0] = readInt();
                i[1] = readInt();
                xor_54(i[0], i[1]);
                break;
            case 55:
                i[0] = readInt();
                not_55(i[0]);
                break;
            case 56:
                i[0] = readInt();
                i[1] = readInt();
                cmp_56(i[0], i[1]);
                break;
            case 57:
                i[0] = readInt();
                i[1] = readInt();
                cmpS_57(i[0], i[1]);
                break;
            case 58:
                i[0] = readInt();
                i[1] = readInt();
                cmp_u_58(i[0], i[1]);
                break;
            case 59:
                i[0] = readInt();
                jmp_59(i[0]);
                break;
            case 60:
                i[0] = readInt();
                jmp_60(i[0]);
                break;
            case 61:
                i[0] = readInt();
                je_61(i[0]);
                break;
            case 62:
                i[0] = readInt();
                je_62(i[0]);
                break;
            case 63:
                i[0] = readInt();
                jne_63(i[0]);
                break;
            case 64:
                i[0] = readInt();
                jne_64(i[0]);
                break;
            case 65:
                i[0] = readInt();
                jg_65(i[0]);
                break;
            case 66:
                i[0] = readInt();
                jg_66(i[0]);
                break;
            case 67:
                i[0] = readInt();
                jge_67(i[0]);
                break;
            case 68:
                i[0] = readInt();
                jge_68(i[0]);
                break;
            case 69:
                i[0] = readInt();
                jl_69(i[0]);
                break;
            case 70:
                i[0] = readInt();
                jl_70(i[0]);
                break;
            case 71:
                i[0] = readInt();
                jle_71(i[0]);
                break;
            case 72:
                i[0] = readInt();
                jle_72(i[0]);
                break;
            case 73:
                i[0] = readInt();
                obj_num_73(i[0]);
                break;
            case 74:
                i[0] = readInt();
                i[1] = readInt();
                obj_num1_74(i[0], i[1]);
                break;
            case 75:
                i[0] = readInt();
                i[1] = readInt();
                i[2] = readInt();
                obj_num2_75(i[0], i[1], i[2]);
                break;
            case 76:
                i[0] = readInt();
                i[1] = readInt();
                i[2] = readInt();
                i[3] = readInt();
                obj_num3_76(i[0], i[1], i[2], i[3]);
                break;
            case 77:
                i[0] = readInt();
                obj_str_77(i[0]);
                break;
            case 78:
                i[0] = readInt();
                i[1] = readInt();
                obj_str1_78(i[0], i[1]);
                break;
            case 79:
                i[0] = readInt();
                i[1] = readInt();
                i[2] = readInt();
                obj_str2_79(i[0], i[1], i[2]);
                break;
            case 80:
                i[0] = readInt();
                i[1] = readInt();
                i[2] = readInt();
                i[3] = readInt();
                obj_str3_80(i[0], i[1], i[2], i[3]);
                break;
            case 81:
                //obj_usr  not used yet
                break;
            case 82:
                //obj_usr1  not used yet
                break;
            case 83:
                //obj_usr2  not used yet
                break;
            case 84:
                //obj_usr3  not used yet
                break;
            case 85:
                i[0] = readInt();
                obj_get_85(i[0]);
                break;
            case 86:
                i[0] = readInt();
                obj_getS_86(i[0]);
                break;
            case 87:
                i[0] = readInt();
                obj_set_87(i[0]);
                break;
            case 88:
                i[0] = readInt();
                obj_setS_88(i[0]);
                break;
            case 89:
                clear_obj_89();
                break;
            case 90:
                //dim_type  not used yet
                break;
            case 91:
                //dim_type1  not used yet
                break;
            case 92:
                //dim_type2  not used yet
                break;
            case 93:
                //dim_type3  not used yet
                break;
            case 94:
                i[0] = readInt();
                i[1] = readInt();
                dim_num1_94(i[0], i[1]);
                break;
            case 95:
                i[0] = readInt();
                i[1] = readInt();
                i[2] = readInt();
                dim_num2_95(i[0], i[1], i[2]);
                break;
            case 96:
                i[0] = readInt();
                i[1] = readInt();
                i[2] = readInt();
                i[3] = readInt();
                dim_num3_96(i[0], i[1], i[2], i[3]);
                break;
            case 97:
                i[0] = readInt();
                i[1] = readInt();
                dim_str1_97(i[0], i[1]);
                break;
            case 98:
                i[0] = readInt();
                i[1] = readInt();
                i[2] = readInt();
                dim_str2_98(i[0], i[1], i[2]);
                break;
            case 99:
                i[0] = readInt();
                i[1] = readInt();
                i[2] = readInt();
                i[3] = readInt();
                dim_str3_99(i[0], i[1], i[2], i[3]);
                break;
            case 100:
                i[0] = readInt();
                delete_100(i[0]);
                break;
            case 101:
                i[0] = readInt();
                deleteS_101(i[0]);
                break;
            case 102:
                i[0] = readInt();
                push_102(i[0]);
                break;
            case 103:
                i[0] = readInt();
                push_103(i[0]);
                break;
            case 104:
                i[0] = readInt();
                pushS_104(i[0]);
                break;
            case 105:
                i[0] = readInt();
                pushS_105(i[0]);
                break;
            case 106:
                push_emptyS_106();
                break;
            case 107:
                i[0] = readInt();
                pop_107(i[0]);
                break;
            case 108:
                i[0] = readInt();
                pop_108(i[0]);
                break;
            case 109:
                i[0] = readInt();
                popS_109(i[0]);
                break;
            case 110:
                i[0] = readInt();
                popS_110(i[0]);
                break;
            case 111:
                i[0] = readInt();
                get_stack_size_111(i[0]);
                break;
            case 112:
                i[0] = readInt();
                get_stack_sizeS_112(i[0]);
                break;
            case 113:
                clear_stack_113();
                break;
            case 114:
                clear_stackS_114();
                break;
            case 115:
                i[0] = readInt();
                i[1] = readInt();
                while_115(i[0], i[1]);
                break;
            case 116:
                i[0] = readInt();
                wend_116(i[0]);
                break;
            case 117:
                i[0] = readInt();
                i[1] = readInt();
                i[2] = readInt();
                i[3] = readInt();
                //cout << "step = " << vm_n[i[3]].value << endl;
                //cout << "for counter = " << vm_n[i[1]].value << " to " << vm_n[i[2]].value << " step " << vm_n[i[3]].value << endl;
                for_117(i[0], i[1], i[2], i[3]);
                //cout << "for info: " << current_segment << " " << current_address << endl << endl;
                //cout << "for counter = " << vm_n[i[1]].value << " to " << vm_n[i[2]].value << " step " << vm_n[i[3]].value << endl;
                break;
            case 118:
                i[0] = readInt();
                next_118(i[0]);
                //cout << endl << "next to: " << i[0] << endl;
                break;
            case 119:
                //do  not really needed, so
                break;
            case 120:
                i[0] = readInt();
                loop_120(i[0]);
                break;
            case 121:
                i[0] = readInt();
                i[1] = readInt();
                loop_while_121(i[0], i[1]);
                break;
            case 122:
                i[0] = readInt();
                i[1] = readInt();
                loop_until_122(i[0], i[1]);
                break;
            case 123:
                pop_loop_stack_123();
                break;
            case 124:
                i[0] = readInt();
                gosub_124(i[0]);
                break;
            case 125:
                return_125();
                break;
            case 126:
                i[0] = readInt();
                i[1] = readInt();
                ptr_126(i[0], i[1]);
                break;
            case 127:
                i[0] = readInt();
                i[1] = readInt();
                ptrS_127(i[0], i[1]);
                break;
            case 128:
                i[0] = readInt();
                print_128(i[0]);
                break;
            case 129:
                i[0] = readInt();
                printS_129(i[0]);
                break;
            case 130:
                i[0] = readInt();
                //cout << "func " << i[0] << endl;
                func_130(i[0]);
                break;
            case 131:
                d[0] = readDouble();
                push_131(d[0]);
                break;
            case 132:
                println_132();
                break;
            case 133:
                i[0] = readInt();
                i[1] = readInt();
                mov_133(i[0], i[1]);
                break;
            case 134:
                i[0] = readInt();
                d[0] = readDouble();
                cmp_134(i[0], d[0]);
                break;
            case 135:
                i[0] = readInt();
                i[1] = readInt();
                mov_arr_135(i[0], i[1]);
                break;
            case 136:
                i[0] = readInt();
                i[1] = readInt();
                mov_arrS_136(i[0], i[1]);
                break;
            case 137:
                i[0] = readInt();
                pop_ptr_137(i[0]);
                break;
            case 138:
                i[0] = readInt();
                preset_138(i[0]);
                break;
            case 139:
                i[0] = readInt();
                presetS_139(i[0]);
                break;
            case 140:
                i[0] = readInt();
                i[1] = readInt();
                redim_140(i[0], i[1]);
                break;
            case 141:
                i[0] = readInt();
                i[1] = readInt();
                i[2] = readInt();
                redim_141(i[0], i[1], i[2]);
                break;
            case 142:
                i[0] = readInt();
                i[1] = readInt();
                i[2] = readInt();
                i[3] = readInt();
                redim_142(i[0], i[1], i[2], i[3]);
                break;
            case 143:
                i[0] = readInt();
                i[1] = readInt();
                redimS_143(i[0], i[1]);
                break;
            case 144:
                i[0] = readInt();
                i[1] = readInt();
                i[2] = readInt();
                redimS_144(i[0], i[1], i[2]);
                break;
            case 145:
                i[0] = readInt();
                i[1] = readInt();
                i[2] = readInt();
                i[3] = readInt();
                redimS_145(i[0], i[1], i[2], i[3]);
                break;
            case 146:
                i[0] = readInt();
                for_offset_arr1_146(i[0]);
                break;
            case 147:
                i[0] = readInt();
                i[1] = readInt();
                for_offset_arr2_147(i[0], i[1]);
                break;
            case 148:
                i[0] = readInt();
                i[1] = readInt();
                i[2] = readInt();
                for_offset_arr3_148(i[0], i[1], i[2]);
                break;
            case 149:
                for_offset_0_149();
                break;
            case 150:
                i[0] = readInt();
                end_x_150(i[0]);
                end_of_program = true;
                break;
            default:
                cout << "invalid cmd: " << rcbasic_cmd << endl;
                rcbasic_exit_code = 1;
                return 0;
        }
    }
    return 1;
}

void rcbasic_init()
{
    for(int i = 0; i < RC_MAX_FILES; i++)
        rc_fstream[i] = NULL;
    rc_media_init();
}

void rcbasic_clean()
{
    rc_media_quit();
    byref_addr_table.empty();
    loop_stack.empty();
    n_stack.empty();
    s_stack.empty();
    gosub_return_addr.empty();
}

void rcbasic_test()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window * win = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer * ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
    SDL_Rect src;
    src.x = 50;
    src.y = 50;
    src.w = 100;
    src.h = 100;
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    SDL_RenderFillRect(ren, &src);
    SDL_RenderPresent(ren);
    SDL_Delay(5000);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
}

int main(int argc, char * argv[])
{
    //rcbasic_test();
    //return 0;

    //cout << "RCBASIC RUNTIME START" << endl;
    #ifdef RC_WINDOWS
        TCHAR buf[MAX_PATH];
        GetCurrentDirectory(MAX_PATH, buf);
        rc_dir_path = buf;
    #else
		#ifdef RC_GETCWD
			char buf[2048];
			getcwd(buf, 2048);
			rc_dir_path = (string)buf;
		#else
			rc_dir_path = get_current_dir_name();
		#endif
    #endif // RC_WINDOWS

    string rc_filename = "";

    if(argc > 1)
        rc_filename = argv[1];
    else
        #ifdef RC_WINDOWS
        {
            rc_filename = argv[0];
            rc_filename = rc_filename.substr(0, rc_filename.length()-3) + "cbc";
        }
        #else
        {
            rc_filename = argv[0];
            rc_filename += ".cbc";
        }
        #endif // RC_WINDOWS

    if(rc_filename.compare("--version")==0)
    {
        cout << "RCBASIC Runtime version PI" << endl;
        return 0;
    }

    //DEBUG START
    //rc_filename = "/home/n00b/Projects/RCBASIC3/rcbasic_build/tst.cbc";
    //DEBUG END

    if(argc >1)
    {
        rc_cmd_count = argc - 1;
        rc_cmd_args = new string[rc_cmd_count];
        for(int i = 1; i < argc; i++)
            rc_cmd_args[i-1] = argv[i];
    }

    rcbasic_init();

    if(rc_filename.length()>=4)
    {
        if(rc_filename.substr(rc_filename.length()-4, 4).compare(".cbc")!=0)
            rc_filename += ".cbc";
    }
    else
    {
        rc_filename += ".cbc";
    }

#ifdef RC_ANDROID
    rc_filename = "main.cbc";
#endif

#ifdef RC_IOS
    if( rc_intern_dirChange("assets")!=0)
    {
        cout << "could not set path" << endl;
        return 0;
    }
    rc_filename = "main.cbc";
#endif

    //cout << "starting: " << rc_filename << endl;

    #ifdef RC_WEB
        rc_filename = "main.cbc";
    #endif

    if(rcbasic_load(rc_filename))
    {
        //cout << "n_count = " << n_count << endl;
        //cout << "s_count = " << s_count << endl;
        //cout << "n_stack_size = " << n_stack_size << endl;
        //cout << "s_stack_size = " << s_stack_size << endl;
        //cout << "loop_stack_size = " << loop_stack_size << endl;
        //cout << "numID_count = " << numID_count << endl;
        //cout << "strID_count = " << strID_count << endl;
        //cout << "code_segment_size = " << code_segment_size << endl;
        //cout << "data_segment_size = " << data_segment_size << endl;
        //cout << "last code = " << (int)segment[CODE_SEGMENT][code_segment_size-1] << endl;
        //cout << "last data = " << (int)segment[DATA_SEGMENT][data_segment_size-1] << endl << endl;

        rcbasic_run();
    }
    else
        cout << "++Could not load rcbasic program" << endl;

    rcbasic_clean();

    exit(rcbasic_exit_code);
    //cout << "Hello world!" << endl;
    return 0;
}
