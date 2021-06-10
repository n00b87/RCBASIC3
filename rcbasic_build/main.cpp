#include <iostream>
#include <stack>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include "tokenizer.h"
#include "parser.h"
#include "rc_builtin.h"
#include "rc_vm_asm.h"
#include "file_directory.h"

using namespace std;

struct rc_src
{
    string filename = "";
    uint64_t line_number = 1;
    uint64_t line_position = 0;
};

stack<rc_src> rcbasic_program;
fstream rcbasic_file;

vector<string> inc_once;

void rcbasic_init()
{
    create_type("null");

    //init built-in functions here

    block_state.push(BLOCK_STATE_MAIN);
    current_block_state = BLOCK_STATE_MAIN;

    current_scope = "main";
    vm_asm.push_back(".code");

    init_embedded();

    //cout << "numid_count = " << num_id_count << endl;
    //cout << "strid_count = " << str_id_count << endl << endl;

    block_state.push(BLOCK_STATE_MAIN);
    current_block_state = BLOCK_STATE_MAIN;
    isInFunctionScope = false;

    current_scope = "main";
    vm_asm.push_back(".code");
}

void rcbasic_dev_init()
{
    create_type("null");

    //init built-in functions here

    block_state.push(BLOCK_STATE_MAIN);
    current_block_state = BLOCK_STATE_MAIN;

    current_scope = "main";
    vm_asm.push_back(".code");

    cout << "numid_count = " << num_id_count << endl;
    cout << "strid_count = " << str_id_count << endl << endl;

    block_state.push(BLOCK_STATE_MAIN);
    current_block_state = BLOCK_STATE_MAIN;
    isInFunctionScope = false;

    current_scope = "main";
    vm_asm.push_back(".code");
}

bool rcbasic_loadProgram(string src_file)
{
    rc_src rc_program;
    rc_program.filename = src_file;
    rc_program.line_number = 1;
    rc_program.line_position;
    rcbasic_file.open(src_file.c_str(), fstream::in);
    if(rcbasic_file.is_open())
    {
        rcbasic_program.push(rc_program);
        return true;
    }
    return false;
}

bool rc_preprocessor()
{
    rc_src inc_file;
    if(tmp_token.size()>0)
    {
        if(tmp_token[0].compare("<include>")==0)
        {
            if(tmp_token.size() != 2)
            {
                rc_setError("Expected string literal or flag in INCLUDE");
                return false;
            }

            //cout << "tmp_token[1] == " << tmp_token[1] << endl;

            if(tmp_token[1].compare("<once>")==0)
            {
                tmp_token.clear();
                inc_once.push_back(rcbasic_program.top().filename);
                return true;
            }

            if(tmp_token[1].substr(0,8).compare("<string>")!=0)
            {
                rc_setError("Expected include file as string constant");
                return false;
            }

            inc_file.filename = tmp_token[1].substr(8);
            inc_file.filename = rc_absFilePath(inc_file.filename);

            for(int i = 0; i < inc_once.size(); i++)
            {
                if(inc_once[i].compare(inc_file.filename)==0)
                {
                    tmp_token.clear();
                    //cout << "DEBUG INC_ONCE: " << inc_file.filename << " can only be included once" << endl;
                    return true;
                }
            }

            //cout << "\nDEBUG INCLUDE ABS_PATH:" << inc_file.filename << endl << endl;
            inc_file.line_number = 0;
            inc_file.line_position = 0;
            rcbasic_file.close();
            rcbasic_file.open(inc_file.filename.c_str(), fstream::in);
            if(!rcbasic_file.is_open())
            {
                rc_setError("Could not open " + inc_file.filename);
                return false;
            }

            //increase current file line number before pushing next file on stack
            rcbasic_program.top().line_number++;

            rcbasic_program.push(inc_file);
            tmp_token.clear();
            return true;
        }
    }
    return true;
}

bool Array_Macros(int tmp_start_token)
{
    //returning true is just saying there were no syntax errors found
    if(tmp_token[tmp_start_token].length() < 5)
        return true;
    if(StringToLower(tmp_token[tmp_start_token].substr(4)).compare("arraydim")!=0 && StringToLower(tmp_token[tmp_start_token].substr(4)).compare("arraysize")!=0)
        return true;

    int64_t arr_id = 0;
    vector<string> tmp_macro_token;
    vector<string> tmp_current_token;
    //int ArrayDim_id = getIDInScope_ByIndex("ArrayDim");
    for(int i = tmp_start_token; i < tmp_token.size(); i++)
    {
        if(tmp_token[i].substr(0,4).compare("<id>")==0)
        {
            if(StringToLower(tmp_token[i].substr(4)).compare("arraydim")==0)
            {
                if(tmp_token[i+1].compare("<par>")!=0)
                {
                    rc_setError("Invalid use of ArrayDim");
                    return false;
                }
                if(tmp_token[i+2].substr(0,4).compare("<id>")==0)
                {
                    arr_id = getIDInScope_ByIndex(tmp_token[i+2].substr(4));
                    if(arr_id < 0)
                    {
                        rc_setError("Identifier must be declared before call to ArrayDim");
                        return false;
                    }

                    id[arr_id].isArrayArg = true;

                }
                else
                {
                    rc_setError("Expected Identifier in ArrayDim");
                    return false;
                }

                int end_token = i+2;
                int expr_scope = 1;
                for(end_token; end_token < tmp_token.size(); end_token++)
                {
                    if(tmp_token[end_token].compare("<par>")==0 || tmp_token[end_token].compare("<square>")==0)
                        expr_scope++;
                    else if(tmp_token[end_token].compare("</par>")==0 || tmp_token[end_token].compare("</square>")==0)
                        expr_scope--;

                    if(expr_scope==0 && tmp_token[end_token].compare("</par>")==0)
                        break;
                }

                tmp_macro_token.clear();
                for(int n = i; n <= end_token; n++)
                        tmp_macro_token.push_back(tmp_token[n]);

                //cout << "<---- DEBUG ---->" << i << endl;
                //for(int n = 0; n < token.size(); n++)
                //    cout <<"token[" << n << "] = " << token[n] << endl;

                tmp_current_token.clear();
                for(int n = 0; n < token.size(); n++)
                    tmp_current_token.push_back(token[n]);

                token.clear();
                for(int n = 0; n < tmp_macro_token.size(); n++)
                    token.push_back(tmp_macro_token[n]);

                //for(int n = 0; n < token.size(); n++)
                //    cout <<"new token[" << n << "] = " << token[n] << endl;


                if(!eval_expression())
                {
                    rc_setError("Could not evaluate ArrayDim");
                    return false;
                }

                for(int n = i; n <= end_token; n++)
                        tmp_token[n] = token[n-i];

                token.clear();
                for(int n = 0; n < tmp_current_token.size(); n++)
                    token.push_back(tmp_current_token[n]);

                //for(int n = 0; n < token.size(); n++)
                //    cout <<"final token[" << n << "] = " << token[n] << endl;
                return true;

            }
            else if(StringToLower(tmp_token[i].substr(4)).compare("arraysize")==0)
            {
                if(tmp_token[i+1].compare("<par>")!=0)
                {
                    rc_setError("Invalid use of ArraySize");
                    return false;
                }
                if(tmp_token[i+2].substr(0,4).compare("<id>")==0)
                {
                    arr_id = getIDInScope_ByIndex(tmp_token[i+2].substr(4));
                    if(arr_id < 0)
                    {
                        rc_setError("Identifier must be declared before call to ArraySize");
                        return false;
                    }

                    id[arr_id].isArrayArg = true;

                }
                else
                {
                    rc_setError("Expected Identifier in ArraySize");
                    return false;
                }

                int end_token = i+2;
                int expr_scope = 1;
                for(end_token; end_token < tmp_token.size(); end_token++)
                {
                    if(tmp_token[end_token].compare("<par>")==0 || tmp_token[end_token].compare("<square>")==0)
                        expr_scope++;
                    else if(tmp_token[end_token].compare("</par>")==0 || tmp_token[end_token].compare("</square>")==0)
                        expr_scope--;

                    if(expr_scope==0 && tmp_token[end_token].compare("</par>")==0)
                        break;
                }

                tmp_macro_token.clear();
                for(int n = i; n <= end_token; n++)
                        tmp_macro_token.push_back(tmp_token[n]);


                tmp_current_token.clear();
                for(int n = 0; n < token.size(); n++)
                    tmp_current_token.push_back(token[n]);

                token.clear();
                for(int n = 0; n < tmp_macro_token.size(); n++)
                    token.push_back(tmp_macro_token[n]);

                if(!eval_expression(0, token.size()-1, true))//i, end_token))
                {
                    rc_setError("--Could not evaluate ArraySize expression");
                    //for(int n = 0; n < token.size(); n++)
                    //    cout << "token["<< n << "] = " << token[n] << endl;
                    return false;
                }

                for(int n = i; n <= end_token; n++)
                        tmp_token[n] = token[n-i];

                token.clear();
                for(int n = 0; n < tmp_current_token.size(); n++)
                    token.push_back(tmp_current_token[n]);

                return true;
            }
        }
    }
    return false;
}

bool rc_eval(string line)
{
    //adding an extra character to line to avoid a memory leak
    line += "  ";


    ERROR_MSG = "";
    clearRegs();
    clearTokens();
    if(line.compare("#var")==0)
    {
        output_vars();
        return true;
    }

    //cout << "get tokens" << endl;
    if(!tokens(line))
    {
        //cout << "Error1: " << rc_getError() << endl;
        return false;
    }

    //current_Debug
    //cout << "-------BEFORE PP START TOKENS--------" << endl;
    output_tokens();

    //cout << "get preprocessor" << endl;
    if(!rc_preprocessor())
    {
        return false;
    }

    //cout << "-------AFTER PP START TOKENS--------" << endl;
    //output_tokens();

    //cout << "check rule" << endl;
    //cout << "token: " << token[0] << endl;

    int i = 0;

    int dim_scope = 0;
    bool is_dim_expr = false;
    string dim_token = "";

    for(i = 0; i < tmp_token.size(); i++)
    {
        if(tmp_token[i].compare("<dim>")==0 || tmp_token[i].compare("<redim>")==0)
        {
            dim_token = tmp_token[i];
            dim_scope = 0;
            is_dim_expr = true;
            continue;
        }

        if(tmp_token[i].compare("<par>")==0 || tmp_token[i].compare("<square>")==0)
            dim_scope++;

        if(tmp_token[i].compare("</par>")==0 || tmp_token[i].compare("</square>")==0)
            dim_scope--;

        if(is_dim_expr==true && dim_scope==0 && tmp_token[i].compare("<comma>")==0)
        {
            tmp_token[i] = "<:>";
            tmp_token.insert(tmp_token.begin()+ (i+1), dim_token);
        }

        if(tmp_token[i].compare("<:>")==0)
            is_dim_expr = false;
    }

    i = 0;

    while( i < tmp_token.size())
    {
        token.clear();

        for(; i < tmp_token.size(); i++)
        {
            //cout << "start tmp_token loop :: ";
            //cout << "i = " << i << "     tmp_token_size = " << tmp_token.size() << endl;
            if(tmp_token[i].compare("<:>")==0)
                break;
            else if(!Array_Macros(i))
            {
                cout << "ERROR:" << rc_getError() << endl;
                return false;
            }
            //cout << "### tmp_token[" << i << "] = ";
            //cout << tmp_token[i] << endl;
            token.push_back(tmp_token[i]);
        }
        i++;

        //cout << "start rule" << endl;

        if(!check_rule())
        {
            cout << "ERROR:" << rc_getError() << endl;
            return false;
        }
    }

    return true;

    //if(!eval_expression())
    //    cout << "Error2: " << rc_getError() << endl;
    //cout << endl << endl << "----TOKENS-----" << endl;
    //output_tokens();

    //cout << endl << "VM CODE" << endl << endl;
    //debug_output_VMASM();

    //cout << "F_Error: " << rc_getError() << endl;
}

bool rc_eval_embedded(string line)
{
    //adding an extra character to line to avoid a memory leak
    line += "   ";


    ERROR_MSG = "";
    clearRegs();
    clearTokens();
    if(line.compare("#var")==0)
    {
        output_vars();
    }

    if(!tokens(line))
    {
        cout << "Error1: " << rc_getError() << endl;
        return false;
    }

    if(tmp_token.size()==0)
        return true;
    //cout << "-------START TOKENS--------" << endl;
    //output_tokens();

    token.clear();
    for(int i = 0; i < tmp_token.size(); i++)
        token.push_back(tmp_token[i]);

    if(!check_rule_embedded())
    {
        cout << "---ERROR:" << rc_getError() << endl;
        output_tokens();
        cout << endl;
        return false;
    }

    return true;

    //if(!eval_expression())
    //    cout << "Error2: " << rc_getError() << endl;
    //cout << endl << endl << "----TOKENS-----" << endl;
    //output_tokens();

    //cout << endl << "VM CODE" << endl << endl;
    //debug_output_VMASM();

    //cout << "F_Error: " << rc_getError() << endl;
}

rc_src rc_last_line;

bool rc_getline(string &line)
{
    line = "";
    while(true)
    {
        getline(rcbasic_file, line);

        if(!rcbasic_file.eof())
        {
            return true;
        }
        else if(rcbasic_program.size()>1)
        {
            //execute last line in included file
            if(!rc_eval(line))
            {
                cout << "Error on Line " << rcbasic_program.top().line_number << " in " << rcbasic_program.top().filename << ": " << rc_getError() << endl;
                //output_tokens();
                cout << endl;
                return false;
            }

            rcbasic_program.pop();
            rcbasic_file.close();
            rcbasic_file.open(rcbasic_program.top().filename.c_str(), fstream::in);
            if(!rcbasic_file.is_open())
            {
                cout << "Could not open " << rcbasic_program.top().filename << endl;
                return false;
            }
            rcbasic_file.seekg(rcbasic_program.top().line_position);
        }
        else
        {
            if(rcbasic_program.size()==1)
                rc_last_line = rcbasic_program.top();
            rcbasic_program.pop();
            rcbasic_file.close();
            return false;
        }
    }
    if(line.compare("")==0)
        return false;
    return true;
}

bool rcbasic_compile()
{
    int current_file = 0;
    string line = "";
    fstream f;

    string rc_asm_file = "main.rc_asm";
    string rc_str_data = "main_str_data.sdata";

    if(is_file_exist(rc_asm_file.c_str()))
    {
        if(remove(rc_asm_file.c_str())!=0)
        {
            cout << "Could not clear asm file" << endl;
            return false;
        }
    }

    if(is_file_exist(rc_str_data.c_str()))
    {
        if(remove(rc_str_data.c_str())!=0)
        {
            cout << "Could not clear sdata file" << endl;
            return false;
        }
    }

    while( rc_getline(line) )
    {
        //cout << "line " << rcbasic_program.top().line_number << ": " << rcbasic_file.tellg() << " -> " << line << endl;
        rcbasic_program.top().line_position = rcbasic_file.tellg();
        //vm_asm.push_back("mov n0 " + rc_intToString(rcbasic_program.top().line_number));
        //vm_asm.push_back("print n0");
        if(!rc_eval(line))
        {
            cout << "Error on Line " << rcbasic_program.top().line_number << " in " << rcbasic_program.top().filename << ": " << rc_getError() << endl;
            //output_tokens();
            cout << endl;
            return false;
        }
        rcbasic_program.top().line_number++;
//        if(rcbasic_program.top().line_number % 500 == 0)
//        {
//            f.open(rc_asm_file.c_str(), fstream::app);
//            for(int i = 0; i < vm_asm.vm_code.size(); i++)
//                f << vm_asm.vm_code[i] << endl;
//            f.close();
//            vm_asm.clear();
//
//            f.open(rc_str_data.c_str(), fstream::app | fstream::binary);
//            for(int i = 0; i < data_segment.size(); i++)
//                f.put(data_segment[i]);
//            f.close();
//            data_segment.clear();
//        }
    }

    if(!rc_eval(line))
    {
        cout << "Error on Line " << rc_last_line.line_number << " in " << rc_last_line.filename << ": " << rc_getError() << endl;
        //output_tokens();
        cout << endl;
        return false;
    }

    vm_asm.push_back("end");

    f.open(rc_asm_file.c_str(), fstream::app);
    for(int i = 0; i < vm_asm.vm_code.size(); i++)
        f << vm_asm.vm_code[i] << endl;
    f.close();
    vm_asm.clear();

    f.open(rc_str_data.c_str(), fstream::app | fstream::binary);
    for(int i = 0; i < data_segment.size(); i++)
        f.put(data_segment[i]);
    f.close();
    data_segment.clear();

    return true;

    //f.open("tst_var_output.txt", fstream::out | fstream::trunc);

    //for(int i = 0; i < id.size(); i++)
    //    f << id[i].name << " -> " << id[i].vec_pos << endl;
    //f.close();

    //cout << endl << "VM Code" << endl << "---------------------" << endl;
    //debug_output_VMASM();
}

void rcbasic_export_dev()
{
    string fn_line = "";
    fstream f("rcbasic_dev.txt", fstream::out | fstream::trunc);
    fstream f2("rcbasic_dev2.txt", fstream::out | fstream::trunc);
    fstream f3("rcbasic_dev3.txt", fstream::out | fstream::trunc);

    if(!f.is_open())
        return;
    string output_line = "";
    for(int i = 0; i < id.size(); i++)
    {
        fn_line = "#define FN_" + id[i].name + " " + rc_intToString(id[i].vmFunctionIndex);

        output_line = "embed_function(\"" + id[i].name +"\", ";
        switch(id[i].type)
        {
            case ID_TYPE_FN_NUM:
                output_line += "ID_TYPE_FN_NUM);";
                f2 << fn_line << endl;
                f3 << "case FN_" << id[i].name << ": //Number Function" << endl << "break;" << endl;
                break;
            case ID_TYPE_FN_STR:
                output_line += "ID_TYPE_FN_STR);";
                f2 << fn_line << endl;
                f3 << "case FN_" << id[i].name << ": //String Function" << endl << "break;" << endl;
                break;
            case ID_TYPE_SUB:
                output_line += "ID_TYPE_SUB);";
                f2 << fn_line << endl;
                f3 << "case FN_" << id[i].name << ": //Sub Procedure" << endl << "break;" << endl;
                break;
            default:
                continue;
        }
        f << output_line << endl;
        output_line = "";
        for(int n = 0; n < id[i].num_args; n++)
        {
            fn_line = "#define " + StringToUpper(id[i].name + "_" + id[i].fn_arg[n]) + " ";

            output_line = "add_embedded_arg(\"" + id[i].fn_arg[n] + "\", ";
            switch(id[i].fn_arg_type[n])
            {
                case ID_TYPE_NUM:
                    output_line += "ID_TYPE_NUM);";
                    //fn_line += "num_var[" + rc_intToString(id[i].fn_arg_vec[n]) + "].nid_value[0].value[0]";
                    fn_line += "num_var[" + rc_intToString(id[i].fn_arg_vec[n]) + "].nid_value[0].value[ num_var[" + rc_intToString(id[i].fn_arg_vec[n]) + "].byref_offset ]";
                    break;
                case ID_TYPE_BYREF_NUM:
                    output_line += "ID_TYPE_BYREF_NUM);";
                    fn_line += "num_var[" + rc_intToString(id[i].fn_arg_vec[n]) + "].nid_value[0].value[ num_var[" + rc_intToString(id[i].fn_arg_vec[n]) + "].byref_offset ]";
                    break;
                case ID_TYPE_STR:
                    output_line += "ID_TYPE_STR);";
                    fn_line += "str_var[" + rc_intToString(id[i].fn_arg_vec[n]) + "].sid_value[0].value[ str_var[" + rc_intToString(id[i].fn_arg_vec[n]) + "].byref_offset ]";
                    break;
                case ID_TYPE_BYREF_STR:
                    output_line += "ID_TYPE_BYREF_STR);";
                    fn_line += "str_var[" + rc_intToString(id[i].fn_arg_vec[n]) + "].sid_value[0].value[ str_var[" + rc_intToString(id[i].fn_arg_vec[n]) + "].byref_offset ]";
                    break;
            }
            f2 << fn_line << endl;
            f << output_line << endl;
        }

    }
    f.close();
    f2.close();
    f3.close();
    cout << "rcbasic_dev file was created" << endl;
}

bool rcbasic_embedded()
{
    int current_file = 0;
    string line = "";

    while( getline(rcbasic_file, line) )
    {
        cout << "line " << rcbasic_program.top().line_number << ": " << rcbasic_file.tellg() << " -> " << line << endl;
        //rcbasic_program.top().line_position = rcbasic_file.tellg();
        if(!rc_eval_embedded(line))
        {
            cout << "Error on Line " << rcbasic_program.top().line_number << ": " << rc_getError() << endl;
            return false;
        }
        rcbasic_program.top().line_number++;
    }

    cout << endl << "VM Code" << endl << "---------------------" << endl;
    debug_output_VMASM();
    return true;
}

void rcbasic_clean()
{
    if(rcbasic_file.is_open())
        rcbasic_file.close();

}

//a file with functions to add to rcbasic
void rcbasic_dev(string dev_input_file)
{
    rcbasic_dev_init();

    if(rcbasic_loadProgram(dev_input_file))
    {
        rcbasic_embedded();
        rcbasic_export_dev();
        rcbasic_clean();
    }
}

int main(int argc, char * argv[])
{
    string line = "";

    //rcbasic_dev("embedded_functions.bas"); return 0;

    string rc_filename = "";// = "tst.bas";

    //DEBUG START
    rc_filename = "tst.bas";
    //DEBUG END

    if(argc > 1)
        rc_filename = argv[1];

    if(rc_filename.compare("-v")==0)
    {
        cout << "RCBASIC Compiler v3.14" << endl;
        return 0;
    }

    //rc_filename = "tst.bas";

    cout << "Source: " << rc_filename << endl;

    string cbc_file = rc_filename.substr(0, rc_filename.find_last_of(".")) + ".cbc";
    if(is_file_exist(cbc_file.c_str()))
        remove(cbc_file.c_str());

    if(rc_filename.compare("")==0)
        return 0;

    rcbasic_init();

    if(rc_filename.find_first_of(".") == string::npos)
    {
        cout << "file must have extension" << endl;
        return 0;
    }

    //if(rcbasic_loadProgram("tst.bas"))
    if(rcbasic_loadProgram(rc_filename))
    {
        if(!rcbasic_compile())
        {
            cout << "Compile Failed" << endl;
            rcbasic_clean();
            return 0;
        }
        else if(current_block_state != BLOCK_STATE_MAIN)
        {
            switch(current_block_state)
            {
            case BLOCK_STATE_DO:
                cout << "Compile Error: Failed to close DO loop" << endl;
                break;
            case BLOCK_STATE_WHILE:
                cout << "Compile Error: Failed to close WHILE loop" << endl;
                break;
            case BLOCK_STATE_FOR:
                cout << "Compile Error: Failed to close FOR loop" << endl;
                break;
            case BLOCK_STATE_FUNCTION:
                cout << "Compile Error: Failed to close FUNCTION" << endl;
                break;
            case BLOCK_STATE_SUB:
                cout << "Compile Error: Failed to close SUB" << endl;
                break;
            case BLOCK_STATE_SELECT:
                cout << "Compile Error: Failed to close SELECT" << endl;
                break;
            case BLOCK_STATE_IF:
                cout << "Compile Error: Failed to close IF" << endl;
                break;
            }
            cout << "Compile Failed" << endl;
            return 0;
        }
        else
            rcbasic_clean();

        //Debug
        //return 0;

        //for(int i = 0; i < vm_asm.label.size(); i++)
        //    cout << vm_asm.label[i].label_name << " = " << vm_asm.label[i].label_address << endl;

        //cout << "for_loop = " << max_for_count << endl;
        //cout << "max_n = " << max_n_reg << endl;
        //cout << "max_s = " << max_s_reg << endl;
        //cout << "n_stack_size = " << vm_asm.max_n_stack_count << endl;
        //cout << "s_stack_size = " << vm_asm.max_s_stack_count << endl;

        //n_count
        //s_count
        //n_stack_count
        //s_stack_count
        //loop_stack_count
        //numID_count
        //strID_count
        //label_count
        //labels

        fstream f("main.rc_data", fstream::trunc | fstream::out);
        f << max_n_reg << endl;
        f << max_s_reg << endl;
        f << vm_asm.max_n_stack_count << endl;
        f << vm_asm.max_s_stack_count << endl;
        f << max_for_count << endl;
        f << num_id_count << endl;
        f << str_id_count << endl;
        f << vm_asm.label.size() << endl;
        for(int i = 0; i < vm_asm.label.size(); i++)
            f << vm_asm.label[i].label_name << " " << vm_asm.label[i].label_address << " " << vm_asm.label[i].label_segment << endl;
        f.close();

        rc_cbc_assembler::rc_assemble(cbc_file, RC_NO_CLEAN_AFTER_BUILD);
    }
    else
    {
        cout << "Could not load program" << endl;
        return 0;
    }

    cout << endl << "Compiled Successfully" << endl << endl << endl; //skip 3 lines so that start of program is not right below this line

    return 0;

    while(getline(cin, line))
    {
        rc_eval(line);
    }
    return 0;
}
