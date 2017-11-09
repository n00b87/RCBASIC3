#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "tokenizer.h"
#include "identifier.h"
#include "rc_global.h"
#include <inttypes.h>

using namespace std;

//vm registers
int max_n_reg = 0;
int max_s_reg = 0;
int n_reg = 0;
int s_reg = 0;

//expression result
string expr_result = "";


bool pre_parse(int start_token, int end_token, int pp_flags = 0); //puts number and string values and variables inside number and string registers
//void getBlock(int& start_block, int& end_block); //gets the start and end index of the next block to evaluate (first and last token if there isnt a block left to evaluate
bool eval_pow(int start_block, int end_block);
bool eval_muldiv(int start_block, int end_block); //MOD operator is also evaluated in this function
bool eval_addsub(int start_block, int end_block);
bool eval_tokens(); //evaluates the tokens and generates vm_asm opcodes

void debug_output_VMASM()
{
    for(int i = 0; i < vm_asm.size(); i++)
        cout << vm_asm[i] << endl;
}

void clear_asm()
{
    vm_asm.clear();
}

//end block will be set to -1 if a block was opened but wasn't closed
void getBlock(int start_token, int end_token, int& start_block, int& end_block)
{
    start_block = start_token; //start_block is set to 0, if there is no block started it will automatically start at the first token
    //end_block = token.size()-1; //end_block is set to the last token, if there is no block started or ended then it will be the last token

    if(end_token > 0)
        end_block = end_token;
    else
        end_block = token.size()-1;

    //this loop will go through every token until it finds a start_block and end_block
    for(int i = start_token; i <= end_token; i++)
    {
        //sets the start_block to the last open block token it discovers
        if(token[i].compare("<par>")==0 || token[i].compare("<square>")==0 || token[i].compare("<curly>")==0)
            start_block = i;

        //if an ending block was encountered and it matches the current start block then the current end_block will be set to the current token
        if( (token[i].compare("</par>")==0 && token[start_block].compare("<par>")==0) ||
            (token[i].compare("</square>")==0 && token[start_block].compare("<square>")==0) ||
            (token[i].compare("</curly>")==0 && token[start_block].compare("<curly>")==0))
        {
            end_block = i;

            //put a ! at the beginning of the start and end block tokens so that they won't be evaluated the next time this function is called
            token[start_block] = "!" + token[start_block];
            token[end_block] = "!" + token[end_block];

            return;
        }
        //if there is a ending block discovered that did not have a matching start block then we set end_block to -1 and set an error message
        else if(token[i].compare("</par>")==0 || token[i].compare("</square>")==0 || token[i].compare("</curly>")==0)
        {
            if(token[i].compare("</par>")==0)
                rc_setError("Found \")\" without \"(\"");
            else if(token[i].compare("</square>")==0)
                rc_setError("Found \"]\" without \"[\"");
            else if(token[i].compare("</curly>")==0)
                rc_setError("Found \"}\" without \"{\"");
            end_block = -1;
            return;
        }
    }
    //if start_block is a bracket and the closing bracket was not found before the end of the loop then end_block is set to -1 and we set an error message
    if(token[start_block].compare("<par>")==0)
    {
        rc_setError("Found \"(\" without \")\"");
        end_block = -1;
    }
    else if(token[start_block].compare("<square>")==0)
    {
        rc_setError("Found \"[\" without \"]\"");
        end_block = -1;
    }
    else if(token[start_block].compare("<curly>")==0)
    {
        rc_setError("Found \"{\" without \"}\"");
        end_block = -1;
    }

}

//This function checks to see if a token can be exempt from the token check that eval functions do
bool token_exemption(int i)
{
    if(token[i].substr(0,1).compare("!")==0)
        return true;
    return false;
}

//This function will clear every token from the first operand to the second operand and set the start operand token to solution
void set_op_solution(int start_op, int end_op, string solution)
{
    for(int i = start_op; i <= end_op; i++)
        token[i] = "";
    token[start_op] = solution;
}

bool eval_pow(int start_block, int end_block)
{
    int op_flag = 0;
    string operand1 = "";
    string operand2 = "";

    int op1_index = 0;
    int op2_index = 0;

    cout << "debug_POW " << start_block << " " << end_block << endl;
    //cout << "t_size" << token.size() << endl;

    for(int i = start_block; i <= end_block; i++)
    {
        if(token_exemption(i))
            continue;

        if(token[i].compare("")!=0 && token[i].compare("<pow>")!=0 && (op_flag == 0 || op_flag == 2))
        {
            switch(op_flag)
            {
                case 0:
                    operand1 = token[i];
                    cout << "op1 = " << operand1 << endl;
                    op1_index = i;
                    op_flag = 1;
                    break;
                case 2:
                    operand2 = token[i];
                    cout << "op2 = " << operand2 << endl;
                    op2_index = i;
                    op_flag = 3;
                    break;
            }
        }
        else if(token[i].compare("<pow>")==0)
        {
            if(op_flag != 1)
            {
                rc_setError("Missing operand for exponent operation");
                return false;
            }
            op_flag = 2;
        }
        else if(token[i].compare("")!=0)
        {
            cout << "reset -- " << token[i] << endl;
            op_flag = 0;
        }

        if(op_flag==3)
        {
            if(operand1.substr(0,1).compare("n")!=0 || operand2.substr(0,1).compare("n")!=0)
            {
                rc_setError("Expected number operand for exponent operation");
                return false;
            }
            vm_asm.push_back("pow " + operand1 + " " + operand2);
            set_op_solution(op1_index, op2_index, operand1);
            op_flag = 0;
            i = start_block-1;
        }
    }
    return true;
}

bool eval_muldiv(int start_block, int end_block)
{
    int op_flag = 0;
    string operand1 = "";
    string operand2 = "";

    int op1_index = 0;
    int op2_index = 0;
    int operation = 0; //0 - mul, 1 - div, 2 - mod

    cout << "debug_MDM " << start_block << " " << end_block << endl;
    cout << "t_size" << token.size() << endl;

    for(int i = start_block; i <= end_block; i++)
    {
        if(token_exemption(i))
            continue;

        if(token[i].compare("")!=0 &&
           token[i].compare("<mul>")!=0 &&
           token[i].compare("<div>")!=0 &&
           token[i].compare("<mod>")!=0 &&
           (op_flag == 0 || op_flag == 2))
        {
            switch(op_flag)
            {
                case 0:
                    operand1 = token[i];
                    cout << "op1 = " << operand1 << endl;
                    op1_index = i;
                    op_flag = 1;
                    break;
                case 2:
                    operand2 = token[i];
                    op2_index = i;
                    op_flag = 3;
                    break;
            }
        }
        else if(token[i].compare("<mul>")==0)
        {
            if(op_flag != 1)
            {
                rc_setError("Missing operand for mul/div operation");
                return false;
            }
            op_flag = 2;
            operation = 0;
        }
        else if(token[i].compare("<div>")==0)
        {
            if(op_flag != 1)
            {
                rc_setError("Missing operand for mul/div operation");
                return false;
            }
            op_flag = 2;
            operation = 1;
        }
        else if(token[i].compare("<mod>")==0)
        {
            if(op_flag != 1)
            {
                rc_setError("Missing operand for mul/div operation");
                return false;
            }
            op_flag = 2;
            operation = 2;
        }
        else if(token[i].compare("")!=0)
        {
            op_flag = 0;
        }

        if(op_flag==3)
        {
            if(operand1.substr(0,1).compare("n")!=0 || operand2.substr(0,1).compare("n")!=0)
            {
                rc_setError("Expected number operand for mul/div operation");
                return false;
            }
            switch(operation)
            {
                case 0:
                    vm_asm.push_back("mul " + operand1 + " " + operand2);
                    break;
                case 1:
                    vm_asm.push_back("div " + operand1 + " " + operand2);
                    break;
                case 2:
                    vm_asm.push_back("mod " + operand1 + " " + operand2);
                    break;
            }
            set_op_solution(op1_index, op2_index, operand1);
            op_flag = 0;
            i = start_block-1;
        }
    }
    return true;
}

bool eval_addsub(int start_block, int end_block)
{
    int op_flag = 0;
    string operand1 = "";
    string operand2 = "";

    int op1_index = 0;
    int op2_index = 0;
    int operation = 0; //0 - add, 1 - sub

    cout << "debug_AS " << start_block << " " << end_block << endl;
    cout << "t_size" << token.size() << endl;

    for(int i = start_block; i <= end_block; i++)
    {
        if(token_exemption(i))
            continue;

        if(token[i].compare("")!=0 &&
           token[i].compare("<add>")!=0 &&
           token[i].compare("<sub>")!=0 &&
           (op_flag == 0 || op_flag == 2))
        {
            switch(op_flag)
            {
                case 0:
                    operand1 = token[i];
                    cout << "op1 = " << operand1 << endl;
                    op1_index = i;
                    op_flag = 1;
                    break;
                case 2:
                    operand2 = token[i];
                    op2_index = i;
                    op_flag = 3;
                    break;
            }
        }
        else if(token[i].compare("<add>")==0)
        {
            if(op_flag != 1)
            {
                rc_setError("Missing operand for add/sub operation");
                return false;
            }
            op_flag = 2;
            operation = 0;

        }
        else if(token[i].compare("<sub>")==0)
        {
            if(op_flag != 1)
            {
                rc_setError("Missing operand for add/sub operation");
                return false;
            }
            op_flag = 2;
            operation = 1;
        }
        else if(token[i].compare("")!=0)
        {
            op_flag = 0;
        }

        if(op_flag==3)
        {
            if(operand1.substr(0,1).compare("n")!=0 || operand2.substr(0,1).compare("n")!=0)
            {
                rc_setError("Expected number operand for add/sub operation");
                return false;
            }
            switch(operation)
            {
                case 0:
                    vm_asm.push_back("add " + operand1 + " " + operand2);
                    break;
                case 1:
                    vm_asm.push_back("sub " + operand1 + " " + operand2);
                    break;
            }
            set_op_solution(op1_index, op2_index, operand1);
            op_flag = 0;
            i = start_block-1;
        }
    }
    return true;
}

void inc_n(int x)
{
    n_reg += x;
    if(n_reg > max_n_reg)
        max_n_reg = n_reg + 1;
}

void inc_s(int x)
{
    s_reg += x;
    if(s_reg > max_s_reg)
        max_s_reg = s_reg + 1;
}

//still need to store negative numbers properly
#define PP_FLAG_NONE 0
#define PP_FLAG_ARRAY 1

bool pre_parse(int start_token = 0, int end_token = -1, int pp_flags)
{
    //n_reg = 0;
    //s_reg = 0;

    if(end_token == -1)
    {
        end_token = token.size();
    }

    int n_flag = 0; // id num ] ) } ,
    string n = "";
    string s = "";
    int expr_id = -1;

    for(int i = start_token; i <= end_token; i++)
    {
        if(token[i].substr(0,5).compare("<num>")==0)
        {
            //cout << "WISHING FOR A MIRACLE" << endl;
            n = "n" + rc_intToString(n_reg);
            vm_asm.push_back("mov " + n + " " + token[i].substr(5));
            token[i] = n;
            inc_n(1);
        }
        else if(token[i].substr(0,4).compare("<id>")==0)
        {
            //more needs to be done here
            n = "n" + rc_intToString(n_reg);
            s = "s" + rc_intToString(s_reg);
            expr_id = getIDInScope_ByIndex(token[i].substr(4));

            if(expr_id < 0)
            {
                rc_setError(token[i].substr(4) + " was not found in this scope");
                return false;
            }
            else if(id[expr_id].type == ID_TYPE_NUM)
            {
                //cout << endl << "COME ON: " << id[expr_id].name << endl;
                vm_asm.push_back("mov " + n + " !" + rc_intToString(id[expr_id].vec_pos));
                token[i] = n;
                inc_n(1);
            }
            else if(id[expr_id].type == ID_TYPE_STR)
            {
                vm_asm.push_back("mov$ " + s + " !" + rc_intToString(id[expr_id].vec_pos));
                token[i] = s;
                inc_s(1);
            }
            else if( (id[expr_id].type == ID_TYPE_ARR_NUM || id[expr_id].type == ID_TYPE_ARR_STR) && pp_flags == PP_FLAG_ARRAY)
            {
                int s_scope = 0;
                int arr_token_start = i;
                int arr_token_end = i;
                string args[3];
                int num_args = 0;
                if( (i+1) <= end_token)
                {
                    if(token[i+1].compare("!<square>")==0)
                    {
                        s_scope = 1;
                        for(i += 2; (i <= end_token) && (s_scope != 0); i++)
                        {
                            if(token[i].compare("!</square>")==0)
                            {
                                s_scope--;
                                if(s_scope == 0)
                                {
                                    num_args++;
                                    arr_token_end = i;
                                }
                            }
                            else if(token[i].compare("!<square>")==0)
                                s_scope++;
                            else if(token[i].compare("!<comma>")==0)
                                num_args++;
                            else if(token[i].substr(0,1).compare("n")==0)
                                args[num_args] = token[i];
                            else
                            {
                                rc_setError("Expected number");
                                return false;
                            }
                        }
                    }
                }
                //cout << endl << "ID_ARRAY: " << id[expr_id].name << endl;
                //cout << "NUM_ARGS_EXPECTED: " << id[expr_id].num_args << endl;
                //cout << "NUM_ARGS_FOUND: " << num_args << endl;

                if(id[expr_id].num_args != num_args)
                {
                    rc_setError("In " + id[expr_id].name + " Expected " + rc_intToString(id[expr_id].num_args) + " dimensions and found " + rc_intToString(num_args));
                    return false;
                }

                for(int n = 0; n < id[expr_id].num_args; n++)
                {
                    //cout << "arg " << n << ": " << args[n] << endl;
                    if(args[n].substr(0,1).compare("n")!=0)
                    {
                        rc_setError("Invalid number of args in array");
                        return false;
                    }
                }

                string token_replace = "";

                switch(num_args)
                {

                    case 1:
                        if(id[expr_id].type == ID_TYPE_ARR_NUM)
                        {
                            vm_asm.push_back("clear_obj");
                            vm_asm.push_back("obj_num1 " + rc_intToString(id[expr_id].vec_pos) + " " + args[0]);
                            token_replace = "n" + rc_intToString(n_reg);
                            inc_n(1);
                            vm_asm.push_back("obj_get " + token_replace);
                        }
                        else
                        {
                            vm_asm.push_back("clear_obj");
                            vm_asm.push_back("obj_str1 " + rc_intToString(id[expr_id].vec_pos) + " " + args[0]);
                            token_replace = "s" + rc_intToString(s_reg);
                            inc_s(1);
                            vm_asm.push_back("obj_get$ " + token_replace);
                        }
                        break;
                    case 2:
                        if(id[expr_id].type == ID_TYPE_ARR_NUM)
                        {
                            vm_asm.push_back("clear_obj");
                            vm_asm.push_back("obj_num2 " + rc_intToString(id[expr_id].vec_pos) + " " + args[0] + " " + args[1]);
                            token_replace = "n" + rc_intToString(n_reg);
                            inc_n(1);
                            vm_asm.push_back("obj_get " + token_replace);
                        }
                        else
                        {
                            vm_asm.push_back("clear_obj");
                            vm_asm.push_back("obj_str2 " + rc_intToString(id[expr_id].vec_pos) + " " + args[0] + " " + args[1]);
                            token_replace = "s" + rc_intToString(s_reg);
                            inc_s(1);
                            vm_asm.push_back("obj_get$ " + token_replace);
                        }
                        break;
                    case 3:
                        if(id[expr_id].type == ID_TYPE_ARR_NUM)
                        {
                            vm_asm.push_back("clear_obj");
                            vm_asm.push_back("obj_num3 " + rc_intToString(id[expr_id].vec_pos) + " " + args[0] + " " + args[1] + " " + args[2]);
                            token_replace = "n" + rc_intToString(n_reg);
                            inc_n(1);
                            vm_asm.push_back("obj_get " + token_replace);
                        }
                        else
                        {
                            vm_asm.push_back("clear_obj");
                            vm_asm.push_back("obj_str3 " + rc_intToString(id[expr_id].vec_pos) + " " + args[0] + " " + args[1] + " " + args[2]);
                            token_replace = "s" + rc_intToString(s_reg);
                            inc_s(1);
                            vm_asm.push_back("obj_get$ " + token_replace);
                        }
                        break;
                    default:
                        rc_setError("Invalid number of dimensions in array");
                        return false;
                }

                for(int p = arr_token_start; p <= arr_token_end; p++)
                    token[p] = "";

                if(token_replace.compare("")==0)
                {
                    rc_setError("could not resolve array " + id[expr_id].name);
                    return false;
                }

                token[arr_token_start] = token_replace;

            }
        }
    }
    return true;
}

// I really hate Wal-Mart

struct block_argument
{
    int arg_start = -1;
    int arg_end = -1;
};

vector<block_argument> block_args;
vector<string> block_arg_data;

bool getArgBlockStuff(int start_block, int& arg_count)
{
    block_args.clear();
    int end_block = -1;
    arg_count = 0;
    //string block_type = token[start_block];
    //string block_end_type = "";
    block_argument b_arg;

//    if(block_type.compare("<square>")==0)
//        block_end_type = "</square>";
//    else if(block_type.compare("<par>")==0)
//        block_end_type = "</par>";
//    else if(block_type.compare("<curly>")==0)
//        block_end_type = "</curly>";
//    else
//    {
//        rc_setError("Expected Start of Control Block");
//        return false;
//    }

    if(token.size() > start_block)
    {
        //if its not a bracketed block then there is no need to check for arguments
        if(token[start_block].compare("!<par>")!=0 && token[start_block].compare("!<square>")!=0 && token[start_block].compare("!<curly>")!=0)
        {
            arg_count = 0;
            return true;
        }

        int scope = 1;
        b_arg.arg_start = start_block + 1;
        for(int i = start_block+1; i < token.size(); i++)
        {
            if(token[i].compare("!<par>")==0 || token[i].compare("!<square>")==0 || token[i].compare("!<curly>")==0)
                scope++;
            else if(token[i].compare("!</par>")==0 || token[i].compare("!</square>")==0 || token[i].compare("!</curly>")==0)
                scope--;

            if(scope == 0)
            {
                //getBlock should take care of this check already
                //
                //if(token[i].compare(block_end_type)!=0)
                //{
                //    rc_setError("Block was not ended correctly");
                //    return false;
                //}
                //else
                //    end_block = i;

                arg_count++;
                b_arg.arg_end = i - 1;
                block_args.push_back(b_arg);
                break;
            }
            else if(scope == 1)
            {
                if(token[i].compare("<comma>")==0)
                {
                    token[i] = "!" + token[i];
                    arg_count++;

                    b_arg.arg_end = i-1;
                    block_args.push_back(b_arg);
                    b_arg.arg_start = i + 1;
                }
            }
        }
    }

    return true;
}

bool getBlockArg(int arg_num, int& start_arg, int& end_arg)
{
    if(arg_num < block_args.size())
    {
        start_arg = block_args[arg_num].arg_start;
        end_arg = block_args[arg_num].arg_end;
    }
    else
    {
        start_arg = -1;
        end_arg = -1;
        return false;
    }
    return true;
}

string multi_arg[64];
int multi_arg_count = 0;

bool eval_expression(int start_token = 0, int end_token = 0, bool allow_multi_arg = false)
{
    int start_block = start_token; //will hold the index of the token the current block starts on
    int end_block = end_token; //will hold the index of the token the current block ends on
    int arg_start = 0;
    int arg_end = 0;
    int arg_count = 0;

    int current_block_start = 0;
    int current_block_end = 0;

    if(end_token==0)
        end_token = token.size()-1;

    pre_parse(start_token, end_token);

    //cout << "EXPRESSION" << endl;
    //output_tokens();
    //cout << "------------------------" << endl;

    //cout << "POST PRE_PARSE" << endl;
    //for(int i = start_token; i <= end_token; i++)
    //cout << "Token[" << i << "]= " << token[i] << endl;

    string arg_result = "";

    multi_arg_count = 0;

    do
    {
        getBlock(start_token, end_token, start_block, end_block); //sets the current start_block and end_block

        if(!pre_parse(start_block, end_block, PP_FLAG_ARRAY))
        {
            return false;
        }

        getArgBlockStuff(start_block, arg_count);

        if(end_block < 0) //if end_block is less than 0 then an error occurred so this function will return false
        {
            //cout << "End block < 0" << endl;
            rc_setError("Could not evaluate expression");
            return false;
        }

        /* ORDER OF OPERATIONS
        1. powers
        2. multiplication, division, modulous
        3. addition, subtraction
        */
        if(arg_count > 1)
        {
            for(int i = 0; i < arg_count; i++)
            {
                getBlockArg(i, arg_start, arg_end);

                if(!eval_pow(arg_start, arg_end))
                    return false;
                if(!eval_muldiv(arg_start, arg_end))
                    return false;
                if(!eval_addsub(arg_start, arg_end))
                    return false;

                for(int n = arg_start; n <= arg_end; n++)
                {
                    if(token[n].size()>0)
                    {
                        if(token[n].substr(0,1).compare("n")==0 || token[n].substr(0,1).compare("s")==0)
                           arg_result = token[n];
                    }
                    token[n] = "";
                }
                token[arg_start] = arg_result;
            }
        }
        else
        {
            if(!eval_pow(start_block, end_block))
                return false;
            if(!eval_muldiv(start_block, end_block))
                return false;
            if(!eval_addsub(start_block, end_block))
                return false;
            //cout << "end here" << endl;
        }

    }while(!(start_block==start_token && end_block==end_token));

    int result_count = 0;

    for(int i = start_token; i <= end_token; i++)
    {
        if(token[i].length()>0)
        {
            if(token[i].substr(0,1).compare("!")!=0)
            {
                expr_result = token[i];
                multi_arg[multi_arg_count] = token[i];
                multi_arg_count++;
                result_count++;
            }
        }

        if(result_count > 1 && !allow_multi_arg)
        {
            //cout << "ST:ET = " << start_block << ", " << end_block << endl;
            rc_setError("--Could not evaluate expression");
            return false;
        }
    }

    return true;
}

int constant_arg[64];
int constant_arg_count = 0;

bool eval_constantExpression(int start_token, int end_token)
{
    //cout << "constant_start = " << token[start_token] << endl;
    //cout << "constant_end = " << token[end_token] << endl;
    constant_arg_count = 0;
    constant_arg[0] = 0;
    constant_arg[1] = 0;
    constant_arg[2] = 0;
    for(int i = start_token; i <= end_token; i++)
    {
        if(rc_substr(token[i], 0, 5).compare("<num>")==0)
        {
            constant_arg[constant_arg_count] = rc_stringToInt(token[i].substr(5));
            //cout << "array dim[" << constant_arg_count << "] = " << constant_arg[constant_arg_count] << endl;
            if(token.size() > (i+1))
            {
                if(token[i+1].compare("<comma>")!=0 && token[i+1].compare("</square>")!=0)
                {
                    //cout << "Next token is " << token[i+1] << endl;
                    rc_setError("Expected <comma> after number constant");
                    return false;
                }
            }
        }
        else if(rc_substr(token[i],0, 7).compare("<comma>")==0)
        {
            constant_arg_count++;
            if(constant_arg_count >= 3)
            {
                rc_setError("Too many arguments in member definition");
                return false;
            }
        }
        else
        {
            rc_setError("Expected constant in member definition");
            return false;
        }

    }
    constant_arg_count++;
    return true;
}

bool resolveID(string expr_id, string &rid, bool &resolve_pass)
{
    clearTokens();
    resolve_pass = false;
    //cout << "EXPR_ID = " << expr_id << endl;
    expr_id += ".";
    int expr_base_index = getIDInScope_ByIndex(expr_id.substr(0, expr_id.find_first_of(".")));
    if(expr_base_index >= 0)
    {
        if(id[expr_base_index].type != ID_TYPE_USER)
        {
            rid = "";
            return true;
        }
    }
    else
    {
        resolve_pass = true;
        return false;
    }

    int scope_length = expr_id.find_last_of(".");
    vector<string> scope_items;
    string scope = expr_id.substr(0, scope_length);
    string eid = "";
    if(expr_id.length() > (scope_length+1) )
        eid = expr_id.substr(scope_length+1);

    string tmp = "";
    string tmp_scope = "main";
    int obj_type = ID_TYPE_NUM;

    int id_index = -1;

    vm_asm.push_back("clear_obj");

    for(int i = 0; i < scope_length; i++)
    {
        if(scope.substr(i,1).compare(".")==0 || i == scope_length-1)
        {
            if(i == scope_length-1)
                tmp += scope.substr(i,1);
            //scope_items.push_back(tmp);
            //vm_asm.push_back("solve " + tmp);

            int start_block = -1;
            int end_block = -1;
            int block_scope = 0;

            for(int n = 0; n < tmp.length(); n++)
            {
                if(tmp.substr(n,1).compare("[")==0 && start_block == -1)
                {
                    start_block = n+1;
                    block_scope++;
                }
                else if(tmp.substr(n,1).compare("]")==0)
                {
                    block_scope--;
                    if(block_scope == 0)
                    {
                        end_block = n;
                        break;
                    }
                }
            }

            if(start_block != -1)
            {
                if(end_block > start_block)
                {
                    //cout << "%%%EXP%%% = " << tmp.substr(start_block, (end_block-start_block)) << endl;
                    if(!tokens(tmp.substr(start_block, (end_block-start_block))))
                    {
                        //cout << "ERROR:" << rc_getError() << endl;
                        return false;
                    }

                    //remove comma from evaluation
                    for(int c = 0; c < token.size(); c++) //c++, no pun intended
                    {
                        if(token[c].compare("<comma>")==0)
                            token[c] = "!<comma>";
                    }

                    if(!eval_expression(0,0,true))
                    {
                        //cout << "ERROR:" << rc_getError() << endl;
                    }
                    //cout << endl;
                    //output_tokens();
                    //cout << endl;

                }
            }
            else
            {
                multi_arg_count = 0;
                multi_arg[0] = "";
                multi_arg[1] = "";
                multi_arg[2] = "";
            }

            id_index = getIDInScope_ByIndex(tmp, tmp_scope);
            if(start_block > 0)
                tmp = tmp.substr(0,start_block-1);
            id_index = getIDInScope_ByIndex(tmp, tmp_scope);
            //cout << "--------------------" << endl << tmp_scope << "->" << tmp << " id_index = " << id_index << endl;
            if(id_index >= 0)
            {
                //cout << "id = " << id[id_index].name << endl << "dimensions = " << id[id_index].num_args << endl;
                //cout << "multi_arg_count = " << multi_arg_count << endl;
                if(multi_arg_count != id[id_index].num_args)
                {
                    //cout << "--ERROR: Invalid number of dimensions in " + id[id_index].name << endl;
                    rc_setError("ERROR: Invalid number of dimensions in " + id[id_index].name);
                    return false;
                }

                string emit_out = "";

                if(id[id_index].type == ID_TYPE_USER)
                {
                    emit_out = "obj_usr";
                    obj_type = id[id_index].type;
                }
                else if(id[id_index].type == ID_TYPE_NUM || id[id_index].type == ID_TYPE_ARR_NUM || id[id_index].type == ID_TYPE_ARR_STR)
                {
                    emit_out = "obj_num";
                    obj_type = id[id_index].type;
                }
                else if(id[id_index].type == ID_TYPE_STR)
                {
                    emit_out = "obj_str";
                    obj_type = id[id_index].type;
                }

                if(id[id_index].num_args > 0)
                {
                    if(id[id_index].type == ID_TYPE_ARR_STR)
                    {
                        emit_out = "obj_str";
                        obj_type == ID_TYPE_STR;
                    }

                    emit_out += rc_intToString(id[id_index].num_args);
                }

                vm_asm.push_back(emit_out + " " + rc_intToString(id[id_index].vec_pos) + " " + multi_arg[0] + " " + multi_arg[1] + " " + multi_arg[2]);

            }
            else
            {
                //cout << "ERROR: " << tmp_scope.substr(tmp_scope.find_first_of(".")+1) << "." << tmp << " is not a valid identifier" << endl;
                rc_setError(tmp + " is not a valid identifier");
                return false;
            }
            tmp_scope += "." + tmp;
            tmp = "";
        }
        else
        {
            tmp += scope.substr(i,1);
        }
    }

    if(obj_type == ID_TYPE_NUM || obj_type == ID_TYPE_ARR_NUM || obj_type == ID_TYPE_USER || obj_type == ID_TYPE_ARR_STR)
    {
        rid = "n" + rc_intToString(n_reg);
        vm_asm.push_back("obj_get " + rid);
        inc_n(1);
    }
    else if(obj_type == ID_TYPE_STR)
    {
        rid = "s" + rc_intToString(s_reg);
        vm_asm.push_back("obj_get$ " + rid);
        inc_s(1);
    }


    //cout << endl << "scope = " << scope << endl << "eid = " << eid << endl << endl;
    return true;
}

bool isDelimiter(char c)
{
    switch(c)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case ',':
        case '=':
        case '<':
        case '>':
        case ' ':
            return true;
            break;
    }
    return false;
}

void clearRegs()
{
    n_reg = 0;
    s_reg = 0;
}

bool resolveUserIDs(string& line)
{
    clearRegs();
    string tmp = "";
    string tmp_replace = "";
    int start_tmp = 0;
    int end_tmp = 0;
    bool resolve_pass = false;

    //cout << "RESOLVE[1] = " << line << endl;

    for(int i = 0; i < line.length(); i++)
    {
        if(line.substr(i,1).compare("_")==0 || isalpha(line[i]))
        {
            tmp = "";
            start_tmp = i;
            int scope = 0; //only worried about square bracket
            for(;i < line.length(); i++)
            {
                cout << "li = " << line[i] << endl;
                if(line.substr(i,1).compare("\"")==0)
                {
                    tmp += "\"";
                    i++;
                    for(; line.substr(i,1).compare("\"") != 0 && i < line.length(); i++)
                        tmp += line.substr(i,1);
                }

                if(line.substr(i,1).compare("[")==0)
                    scope++;
                else if(line.substr(i,1).compare("]")==0)
                    scope--;

                if(scope < 0)
                    return false;

                if(scope == 0 && isDelimiter(line[i]))
                {
                    //cout << "!!!!!resolve for: " << tmp << endl;
                    //cout << "delimit: |" << line[i] << "|" << endl;
                    if(resolveID(tmp, tmp_replace, resolve_pass))
                    {
                        if(tmp_replace.compare("")==0)
                            break;
                        //line = tmp_replace;
                        i = start_tmp + 2;
                        //cout << endl << "starting at: " << "0 to " << start_tmp << "; " << end_tmp << endl << endl;
                        line = line.substr(0,start_tmp) + "~" + tmp_replace + line.substr(end_tmp+1);
                        //cout << "line = " << line << endl << endl;
                        //cout << "line[i] = " << line.substr(i) << endl << endl;
                        break;
                    }
                    else if(!resolve_pass)
                    {
                        //cout << "something is wrong up in this piece" << endl;
                        //cout << "line was " << tmp << endl;
                        return false;
                    }

                }
                tmp += line.substr(i,1);
                end_tmp = i;
            }
        }
    }
    clearTokens();

    //cout << "RESOLVE[2]=" << line << endl;

    return true;
}

bool check_rule()
{
    if(token.size()>0)
    {
        if(token[0].compare("<dim>")==0)
        {
            //cout << "DIM RULE FOUND" << endl;  //'DIM' [ID]; '[' #; #; # ']' ; 'AS' [TYPE]; '=' (VALUE)

            string id_name = "";
            int id_type = ID_TYPE_NUM;
            string id_type_name = "";
            int dimensions = 0;

            //check if the next token is a identifier
            if(token.size() > 1)
            {
                if(token[1].substr(0,4).compare("<id>")==0)
                {
                    //if the identifier is not a valid name then return false
                    id_name = token[1].substr(4);
                    id_type = ID_TYPE_NUM;
                    id_type_name = "";
                    dimensions = 0;

                    if(!isValidIDName(id_name))
                    {
                        rc_setError("Invalid Identifier name");
                        return false;
                    }

                    //check if the data type is a string
                    if(id_name.substr(id_name.length()-1).compare("$")==0)
                        id_type = ID_TYPE_STR;

                    //if the identifier already exists and current_block state is not type then return false
                    if(current_block_state != BLOCK_STATE_TYPE && (idExistsInScope(id_name) || idExistsInScope(id_name+"$")) )
                    {
                        rc_setError("Identifier already defined in current scope");
                        return false;
                    }
                    else if(current_block_state == BLOCK_STATE_TYPE && memberExists(id_name))
                    {
                        rc_setError("Type already has member called " + id_name);
                        return false;
                    }

                    //cout << "db1\n";

                    //if there are only two tokens then return here because there is nothing left to check
                    if(token.size()==2)
                    {
                        if(current_block_state == BLOCK_STATE_TYPE)
                        {
                            //cout << "adding type member" << endl;
                            if(!add_type_member(id_name, id_type, "", 0))
                            {
                                //cout << rc_getError() << endl;
                                return false;
                            }
                        }
                        else
                        {
                            if(!create_variable(id_name, id_type))
                            {
                                //cout << rc_getError() << endl;
                                return false;
                            }
                        }

                        //cout << "return true here" << endl;
                        return true;
                    }

                    //cout << "db2\n";

                    //current token
                    int token_index = 2;

                    //check for the next rule; must be [], AS, or =
                    if(token[token_index].compare("<square>")==0 && current_block_state == BLOCK_STATE_TYPE)
                    {
                        token_index++;
                        int end_token = token_index;
                        int sq_scope = 1;
                        for(; end_token < token.size(); end_token++)
                        {
                            if(token[end_token].compare("<square>")==0)
                                sq_scope++;
                            else if(token[end_token].compare("</square>")==0)
                                sq_scope--;

                            if(sq_scope==0)
                                break;
                        }
                        if(sq_scope != 0)
                        {
                            rc_setError("Expected ] in array definition");
                            return false;
                        }
                        if(end_token > token_index)
                            end_token--;
                        else
                        {
                            rc_setError("Expected atleast 1 parameter in member array definition");
                            return false;
                        }
                        if(eval_constantExpression(token_index, end_token))
                        {
                            dimensions = constant_arg_count;
                        }
                        else
                        {
                            rc_setError("Expected constant for type member array");
                            return false;
                        }
                        token_index = end_token+2;

                    }
                    else if(token[token_index].compare("<square>")==0)
                    {
                        int end_token = token_index+1;
                        int sq_scope = 1;
                        for(; end_token < token.size(); end_token++)
                        {
                            if(token[end_token].compare("</square>")==0)
                                sq_scope--;
                            else if(token[end_token].compare("<square>")==0)
                                sq_scope++;

                            if(sq_scope==0)
                                break;
                        }
                        if(sq_scope != 0)
                        {
                            rc_setError("Expected ] in array definition");
                            return false;
                        }
                        if(!eval_expression(token_index, end_token, true))
                        {
                            rc_setError("Could not evaluate expression in array definition");
                            return false;
                        }
                        if(multi_arg_count <= 0 || multi_arg_count > 3)
                        {
                            rc_setError("Expected 1 to 3 Arguments for array definition, Found " + rc_intToString(multi_arg_count));
                            return false;
                        }
                        else
                        {
                            dimensions = multi_arg_count;
                        }
                        token_index = end_token+1;
                        //if(token.size()<token_index)
                        //    return true;
                        //cout << "tok_ind = " << token_index << endl;
                    }
                    if(token.size()>token_index+1)
                    {
                        //cout << "token_size = " << token.size() << endl << "token_index = " << token_index << endl << endl;
                        if(token[token_index].compare("<as>")==0)
                        {
                            token_index++;
                            if(token[token_index].length()>4)
                            {
                                if(token[token_index].substr(0,4).compare("<id>")==0)
                                {
                                    id_type_name = token[token_index].substr(4);
                                }
                            }
                            if(getUType(id_type_name)>=0)
                            {
                                id_type = ID_TYPE_USER;
                            }
                            else
                            {
                                rc_setError(id_type_name + " is not a valid type");
                                return false;
                            }
                        }
                        else
                        {
                            rc_setError("Expected AS TYPE in variable definition");
                            //cout << "FOUND " << token[token_index] << endl;
                            return false;
                        }
                    }
                    else if(token.size()>token_index)
                    {
                        rc_setError("Invalid variable definition");
                        return false;
                    }

                }
                else
                {
                    //if the next token is not an id then the syntax is incorrect and false is returned
                    rc_setError("Expected Identifier name");
                    return false;
                }

                if(current_block_state == BLOCK_STATE_TYPE)
                {
                    if(!add_type_member(id_name, id_type, id_type_name, dimensions, constant_arg[0], constant_arg[1], constant_arg[2]))
                    {
                        //cout << rc_getError() << endl;
                        return false;
                    }
                }
                else
                {
                    //cout << "create variable" << endl;
                    if(dimensions > 0)
                    {
                        switch(id_type)
                        {
                            case ID_TYPE_NUM:
                                id_type = ID_TYPE_ARR_NUM;
                                break;
                            case ID_TYPE_STR:
                                id_type = ID_TYPE_ARR_STR;
                                break;
                        }
                        if(!create_array(id_name, id_type, id_type_name, dimensions))
                        {
                            //cout << rc_getError() << endl;
                            return false;
                        }
                        //cout << "Created Array: " << id_name << " of type " << id_type << endl;
                    }
                    else
                    {
                        if(!create_variable(id_name, id_type, id_type_name))
                        {
                            //cout << rc_getError() << endl;
                            return false;
                        }
                    }
                }

            }
            else
            {
                //if the size of the token vector is not greater than one then the syntax for the line is incomplete so I return false
                rc_setError("Expected Identifier name");
                return false;
            }
        }
        else if(token[0].compare("<type>")==0)
        {
            if(current_block_state != BLOCK_STATE_MAIN)
            {
                rc_setError("Type definition is not allowed in this scope");
                return false;
            }
            if(token.size() != 2)
            {
                rc_setError("invalid type definition");
                return false;
            }
            string id_type_name = "";
            if(token[1].length()>4)
            {
                if(token[1].substr(0,4).compare("<id>")!=0)
                {
                    rc_setError("invalid type name");
                    return false;
                }
                id_type_name = token[1].substr(4);
            }
            if( (!isValidIDName(id_type_name)) || idExistsInScope(id_type_name) || getUType(id_type_name)>=0)
            {
                rc_setError("Invalid type name");
                return false;
            }
            if(!create_type(id_type_name))
            {
                rc_setError("Could not create type: " + id_type_name);
                return false;
            }
            current_block_state = BLOCK_STATE_TYPE;
            return true;
        }
        else if(token[0].compare("<end>")==0 && token.size() == 2)
        {
            if(token[1].compare("<type>")==0)
            {
                current_block_state = BLOCK_STATE_MAIN;
            }
        }
        else if(!eval_expression())
        {
            rc_setError("*Could not evaluate expression");
            return false;
        }
    }
    return true;
}

#endif // PARSER_H_INCLUDED
