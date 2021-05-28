#ifndef RC_GLOBAL_INCLUDED
#define RC_GLOBAL_INCLUDED
#include <inttypes.h>

#define CODE_SEGMENT 0
#define DATA_SEGMENT 1

struct rc_label
{
    string label_name="";
    uint64_t label_address=0;
    int label_segment = 0;
};

class rc_vm_asm
{
public:
    vector<string> vm_code;
    vector<rc_label> label;
    int current_segment = 0;
    uint64_t current_address[2];
    uint64_t n_stack_count = 0;
    uint64_t s_stack_count = 0;
    uint64_t max_n_stack_count = 0;
    uint64_t max_s_stack_count = 0;

    void push_back(string s)
    {
        s += " ";
        vm_code.push_back(s);
        if(s.substr(0,s.find_first_of(" ")).compare(".code")==0)
        {
            current_segment = CODE_SEGMENT;
        }
        else if(s.substr(0,s.find_first_of(" ")).compare(".data")==0)
        {
            //cout << "got data son" << endl;
            current_segment = DATA_SEGMENT;
        }
        else if(s.substr(0,s.find_first_of(" ")).compare("label")==0)
        {
            rc_label current_label;
            s = s.substr(s.find_first_of(" "));
            s = s.substr(s.find_first_not_of(" "));
            current_label.label_name = s;
            current_label.label_address = current_address[current_segment];
            current_label.label_segment = current_segment;
            //cout << "got a mutha flippin label: " << current_label.label_name << " : " << current_label.label_segment << endl;
            label.push_back(current_label);
        }
        else if(s.substr(0,s.find_first_of(" ")).compare("mov")==0 || s.substr(0,s.find_first_of(" ")).compare("mov$")==0 ||
           s.substr(0,s.find_first_of(" ")).compare("mov_r")==0 || s.substr(0,s.find_first_of(" ")).compare("mov_r$")==0 ||
           s.substr(0,s.find_first_of(" ")).compare("mov_type")==0 || s.substr(0,s.find_first_of(" ")).compare("add$")==0 ||
           s.substr(0,s.find_first_of(" ")).compare("add")==0 || s.substr(0,s.find_first_of(" ")).compare("sub")==0 ||
           s.substr(0,s.find_first_of(" ")).compare("mul")==0 || s.substr(0,s.find_first_of(" ")).compare("div")==0 ||
           s.substr(0,s.find_first_of(" ")).compare("pow")==0 || s.substr(0,s.find_first_of(" ")).compare("mod")==0 ||
           s.substr(0,s.find_first_of(" ")).compare("shl")==0 || s.substr(0,s.find_first_of(" ")).compare("shr")==0 ||
           s.substr(0,s.find_first_of(" ")).compare("and")==0 || s.substr(0,s.find_first_of(" ")).compare("or")==0 ||
           s.substr(0,s.find_first_of(" ")).compare("xor")==0 || s.substr(0,s.find_first_of(" ")).compare("mov_arr$")==0 ||
           s.substr(0,s.find_first_of(" ")).compare("cmp")==0 || s.substr(0,s.find_first_of(" ")).compare("cmp$")==0 ||
           s.substr(0,s.find_first_of(" ")).compare("cmp_u")==0 || s.substr(0,s.find_first_of(" ")).compare("obj_num1")==0 ||
           s.substr(0,s.find_first_of(" ")).compare("obj_str1")==0 || s.substr(0,s.find_first_of(" ")).compare("obj_usr1")==0 ||
           s.substr(0,s.find_first_of(" ")).compare("dim_type")==0 || s.substr(0,s.find_first_of(" ")).compare("dim_num1")==0 ||
           s.substr(0,s.find_first_of(" ")).compare("dim_str1")==0 || s.substr(0,s.find_first_of(" ")).compare("loop_while")==0 ||
            s.substr(0,s.find_first_of(" ")).compare("loop_until")==0 ||
            s.substr(0,s.find_first_of(" ")).compare("while")==0 || s.substr(0,s.find_first_of(" ")).compare("mov_arr")==0 ||
            s.substr(0,s.find_first_of(" ")).compare("ptr")==0 || s.substr(0,s.find_first_of(" ")).compare("ptr$")==0 ||
            s.substr(0,s.find_first_of(" ")).compare("redim1")==0 || s.substr(0,s.find_first_of(" ")).compare("redim1$")==0 ||
            s.substr(0,s.find_first_of(" ")).compare("for_offset_arr2")==0 )
        {
            current_address[current_segment] += 17; //1 byte for instruction and 8 bytes for each argument
        }
        else if(s.substr(0,s.find_first_of(" ")).compare("push")==0 )
        {
            n_stack_count++;
            if( (n_stack_count+1) > max_n_stack_count)
                max_n_stack_count = n_stack_count+1;
            current_address[current_segment] += 9;
        }
        else if(s.substr(0,s.find_first_of(" ")).compare("push$")==0 )
        {
            s_stack_count++;
            if( (s_stack_count+1) > max_s_stack_count)
                max_s_stack_count = s_stack_count+1;
            current_address[current_segment] += 9;
        }
        else if(s.substr(0,s.find_first_of(" ")).compare("pop")==0)
        {
            n_stack_count--;
            current_address[current_segment] += 9;
        }
        else if(s.substr(0,s.find_first_of(" ")).compare("pop$")==0)
        {
            s_stack_count--;
            current_address[current_segment] += 9;
        }
        else if(s.substr(0,s.find_first_of(" ")).compare("jmp")==0 || s.substr(0,s.find_first_of(" ")).compare("je")==0 ||
                s.substr(0,s.find_first_of(" ")).compare("jne")==0 || s.substr(0,s.find_first_of(" ")).compare("jg")==0 ||
                s.substr(0,s.find_first_of(" ")).compare("jge")==0 || s.substr(0,s.find_first_of(" ")).compare("jl")==0 ||
                s.substr(0,s.find_first_of(" ")).compare("jle")==0 || s.substr(0,s.find_first_of(" ")).compare("obj_num")==0 ||
                s.substr(0,s.find_first_of(" ")).compare("obj_str")==0 || s.substr(0,s.find_first_of(" ")).compare("obj_usr")==0 ||
                s.substr(0,s.find_first_of(" ")).compare("obj_get")==0 || s.substr(0,s.find_first_of(" ")).compare("obj_get$")==0 ||
                s.substr(0,s.find_first_of(" ")).compare("obj_set")==0 || s.substr(0,s.find_first_of(" ")).compare("obj_set$")==0 ||
                s.substr(0,s.find_first_of(" ")).compare("delete")==0 || s.substr(0,s.find_first_of(" ")).compare("delete$")==0 ||
                s.substr(0,s.find_first_of(" ")).compare("get_stack_size")==0 || s.substr(0,s.find_first_of(" ")).compare("get_stack_size$")==0 ||
                s.substr(0,s.find_first_of(" ")).compare("wend")==0 || s.substr(0,s.find_first_of(" ")).compare("loop")==0 ||
                s.substr(0,s.find_first_of(" ")).compare("gosub")==0 || s.substr(0,s.find_first_of(" ")).compare("print")==0 ||
                s.substr(0,s.find_first_of(" ")).compare("print$")==0 || s.substr(0,s.find_first_of(" ")).compare("func")==0 ||
                s.substr(0,s.find_first_of(" ")).compare("not")==0 || s.substr(0,s.find_first_of(" ")).compare("next")==0 ||
                s.substr(0,s.find_first_of(" ")).compare("pop_ptr")==0 || s.substr(0,s.find_first_of(" ")).compare("preset")==0 ||
                s.substr(0,s.find_first_of(" ")).compare("preset$")==0 || s.substr(0,s.find_first_of(" ")).compare("for_offset_arr1")==0)
        {
            current_address[current_segment] += 9; //1 byte for instruction and 8 bytes a single argument
        }
        else if(s.substr(0,s.find_first_of(" ")).compare("obj_num2")==0 || s.substr(0,s.find_first_of(" ")).compare("obj_str2")==0 ||
                s.substr(0,s.find_first_of(" ")).compare("obj_usr2")==0 || s.substr(0,s.find_first_of(" ")).compare("dim_type1")==0 ||
                s.substr(0,s.find_first_of(" ")).compare("dim_num2")==0 || s.substr(0,s.find_first_of(" ")).compare("dim_str2")==0 ||
                s.substr(0,s.find_first_of(" ")).compare("redim2")==0 || s.substr(0,s.find_first_of(" ")).compare("redim2$")==0 ||
                s.substr(0,s.find_first_of(" ")).compare("for_offset_arr3")==0)
        {
            current_address[current_segment] += 25; //1 byte for instruction and 8 bytes for 3 arguments
        }
        else if(s.substr(0,s.find_first_of(" ")).compare("dim_type2")==0 || s.substr(0,s.find_first_of(" ")).compare("dim_num3")==0 ||
                s.substr(0,s.find_first_of(" ")).compare("dim_str3")==0 || s.substr(0,s.find_first_of(" ")).compare("for")==0 ||
                s.substr(0,s.find_first_of(" ")).compare("obj_num3")==0 || s.substr(0,s.find_first_of(" ")).compare("obj_str3")==0 ||
                s.substr(0,s.find_first_of(" ")).compare("redim3")==0 || s.substr(0,s.find_first_of(" ")).compare("redim3$")==0)
        {
            current_address[current_segment] += 33; //1 byte for instruction and 8 bytes for 4 arguments
        }
        else if(s.substr(0,s.find_first_of(" ")).compare("dim_type3")==0)
        {
            current_address[current_segment] += 41; //1 byte for instruction and 8 bytes for 5 arguments
        }
        else if(s.substr(0,s.find_first_of(" ")).compare("end")==0 || s.substr(0,s.find_first_of(" ")).compare("clear_obj")==0 ||
                s.substr(0,s.find_first_of(" ")).compare("push_empty$")==0 || s.substr(0,s.find_first_of(" ")).compare("clear_stack")==0 ||
                s.substr(0,s.find_first_of(" ")).compare("clear_stack$")==0 || s.substr(0,s.find_first_of(" ")).compare("do")==0 ||
                s.substr(0,s.find_first_of(" ")).compare("pop_loop_stack")==0 || s.substr(0,s.find_first_of(" ")).compare("return")==0 ||
                s.substr(0,s.find_first_of(" ")).compare("println")==0 || s.substr(0,s.find_first_of(" ")).compare("for_offset_0")==0 )
        {
            current_address[current_segment] += 1; //1 byte for instruction and no arguments
        }
    }

    void clear()
    {
        vm_code.clear();
    }

    uint64_t size()
    {
        return vm_code.size();
    }
};

rc_vm_asm vm_asm;

//vector<string> vm_asm; //the generated opcodes for the current set of
//vector<string> vm_data_asm;

vector<unsigned char> data_segment;
vector<string> resolveID_id_reg;
vector<int> resolveID_id_type;
vector<int> resolveID_id_ut_index;

int getResolveReg(string arg)
{
    for(int i = 0; i < resolveID_id_reg.size(); i++)
    {
        //cout << "compare (" << arg << " to " << resolveID_id_reg[i] << endl;
        if(resolveID_id_reg[i].compare(arg)==0)
            return i;
    }
    return -1;
}

int rid_count = 0;

#endif // RC_GLOBAL_INCLUDED
