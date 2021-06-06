#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "tokenizer.h"
#include "identifier.h"
#include "rc_global.h"
#include <inttypes.h>

using namespace std;

int max_for_count = 0;

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

vector<string> n_tmp;
vector<string> s_tmp;

void inc_n(int x)
{
    n_reg += x;
    if( (n_reg+1) > max_n_reg)
        max_n_reg = n_reg + 1;
}

void inc_s(int x)
{
    s_reg += x;
    if( (s_reg+1) > max_s_reg)
        max_s_reg = s_reg + 1;
}

void debug_output_VMASM()
{
    for(int i = 0; i < vm_asm.vm_code.size(); i++)
        cout << vm_asm.vm_code[i] << endl;
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
    if(token[i].compare("!<par>")==0 || token[i].compare("!</par>")==0 ||
       token[i].compare("!<square>")==0 || token[i].compare("!</square>")==0 ||
       token[i].compare("!<curly>")==0 || token[i].compare("!</curly>")==0)
        return true;
    return false;
}

//This function will clear every token from the first operand to the second operand and set the start operand token to solution
void set_op_solution(int start_op, int end_op, string solution)
{
    for(int i = start_op; i <= end_op; i++)
    {
        if(!token_exemption(i))
            token[i] = "";
    }
    token[start_op] = solution;
}

void getRegInfo(string r_reg, int &arg_type, int &arg_utype)
{
    for(int i = 0; i < resolveID_id_reg.size(); i++)
    {
        if(resolveID_id_reg[i].compare(r_reg)==0)
        {
            arg_type = resolveID_id_type[i];
            arg_utype = resolveID_id_ut_index[i];
            return;
        }
    }

    if(r_reg.substr(0,1).compare("s")==0)
    {
        arg_type = ID_TYPE_STR;
        arg_utype = 0;
    }
    else
    {
        arg_type = ID_TYPE_NUM;
        arg_utype = 0;
    }

    return;
}

bool eval_pow(int start_block, int end_block)
{
    int op_flag = 0;
    string operand1 = "";
    string operand2 = "";

    int op1_index = 0;
    int op2_index = 0;

    //cout << "debug_POW " << start_block << " " << end_block << endl;
    //cout << "t_size" << token.size() << endl;

    for(int i = start_block; i <= end_block; i++)
    {
        if(token_exemption(i))
        {
            //op_flag = 0;
            continue;
        }

        if(token[i].compare("")!=0 && token[i].compare("<pow>")!=0 && (op_flag == 0 || op_flag == 2))
        {
            switch(op_flag)
            {
                case 0:
                    operand1 = token[i];
                    //cout << "op1 = " << operand1 << endl;
                    op1_index = i;
                    op_flag = 1;
                    break;
                case 2:
                    operand2 = token[i];
                    //cout << "op2 = " << operand2 << endl;
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
            //cout << "reset -- " << token[i] << endl;
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

    if(op_flag == 2)
    {
        rc_setError("Expected operand for exponent operation");
        return false;
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

    //cout << "debug_MDM " << start_block << " " << end_block << endl;
    //cout << "t_size" << token.size() << endl;

    for(int i = start_block; i <= end_block; i++)
    {
        if(token_exemption(i))
        {
            //op_flag = 0;
            continue;
        }

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
                    //cout << "op1 = " << operand1 << endl;
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

    if(op_flag == 2)
    {
        rc_setError("Expected operand for mul/div operation");
        return false;
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

    //cout << "\ndebug_AS " << start_block << " " << end_block << endl;
    //cout << "t_size" << token.size() << endl;
    //output_tokens();
    //cout << endl << "^^^^^^^^^^^^^^" << endl;

    for(int i = start_block; i <= end_block; i++)
    {
        if(token_exemption(i))
        {
            //cout << "hello: " << token[i] << endl;
            //op_flag = 0;
            continue;
        }

        if(token[i].compare("")!=0 &&
           token[i].compare("<add>")!=0 &&
           token[i].compare("<sub>")!=0 &&
           (op_flag == 0 || op_flag == 2))
        {
            switch(op_flag)
            {
                case 0:
                    operand1 = token[i];
                    //cout << "!!op1 = " << operand1 << endl;
                    op1_index = i;
                    op_flag = 1;
                    break;
                case 2:
                    operand2 = token[i];
                    //cout << "!!op2 = " << operand1 << endl;
                    op2_index = i;
                    op_flag = 3;
                    break;
            }
        }
        else if(token[i].compare("<add>")==0)
        {
            if(op_flag != 1)
            {
                rc_setError("Missing operand for add/sub operation : " + rc_intToString(op_flag) );
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
            switch(operation)
            {
                case 0:
                    if(operand1.substr(0,1).compare("n")==0 && operand2.substr(0,1).compare("n")==0)
                        vm_asm.push_back("add " + operand1 + " " + operand2);
                    else if(operand1.substr(0,1).compare("s")==0 && operand2.substr(0,1).compare("s")==0)
                        vm_asm.push_back("add$ " + operand1 + " " + operand2);
                    else
                    {
                        rc_setError("Incompatible operands for add operation");
                        return false;
                    }
                    break;
                case 1:
                    if(operand1.substr(0,1).compare("n")==0 && operand2.substr(0,1).compare("n")==0)
                        vm_asm.push_back("sub " + operand1 + " " + operand2);
                    else
                    {
                        rc_setError("Incompatible operands for add operation");
                        return false;
                    }
                    break;
            }
            set_op_solution(op1_index, op2_index, operand1);
            op_flag = 0;
            i = start_block-1;
        }
    }

    if(op_flag == 2)
    {
        rc_setError("Expected operand for add/sub operation");
        return false;
    }

    return true;
}

bool eval_bitshift(int start_block, int end_block)
{
    int op_flag = 0;
    string operand1 = "";
    string operand2 = "";

    int op1_index = 0;
    int op2_index = 0;
    int operation = 0; //0 - add, 1 - sub

    //cout << "\ndebug_BS " << start_block << " " << end_block << endl;
    //cout << "t_size" << token.size() << endl;
    //output_tokens();
    //cout << endl << "^^^^^^^^^^^^^^" << endl;

    for(int i = start_block; i <= end_block; i++)
    {
        if(token_exemption(i))
        {
            //cout << "hello: " << token[i] << endl;
            //op_flag = 0;
            continue;
        }

        if(token[i].compare("")!=0 &&
           token[i].compare("<shl>")!=0 &&
           token[i].compare("<shr>")!=0 &&
           (op_flag == 0 || op_flag == 2))
        {
            switch(op_flag)
            {
                case 0:
                    operand1 = token[i];
                    //cout << "!!op1 = " << operand1 << endl;
                    op1_index = i;
                    op_flag = 1;
                    break;
                case 2:
                    operand2 = token[i];
                    //cout << "!!op2 = " << operand1 << endl;
                    op2_index = i;
                    op_flag = 3;
                    break;
            }
        }
        else if(token[i].compare("<shl>")==0)
        {
            if(op_flag != 1)
            {
                rc_setError("Missing operand for add/sub operation : " + rc_intToString(op_flag) );
                return false;
            }
            op_flag = 2;
            operation = 0;

        }
        else if(token[i].compare("<shr>")==0)
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
            switch(operation)
            {
                case 0:
                    if(operand1.substr(0,1).compare("n")==0 && operand2.substr(0,1).compare("n")==0)
                        vm_asm.push_back("shl " + operand1 + " " + operand2);
                    else
                    {
                        rc_setError("Incompatible operands for shl operation");
                        return false;
                    }
                    break;
                case 1:
                    if(operand1.substr(0,1).compare("n")==0 && operand2.substr(0,1).compare("n")==0)
                        vm_asm.push_back("shr " + operand1 + " " + operand2);
                    else
                    {
                        rc_setError("Incompatible operands for shr operation");
                        return false;
                    }
                    break;
            }
            set_op_solution(op1_index, op2_index, operand1);
            op_flag = 0;
            i = start_block-1;
        }
    }

    if(op_flag == 2)
    {
        rc_setError("Expected operand for add/sub operation");
        return false;
    }

    return true;
}

bool eval_cmp(int start_block, int end_block)
{
    int op_flag = 0;
    string operand1 = "";
    string operand2 = "";

    int op1_index = 0;
    int op2_index = 0;
    int operation = 0; //0 - add, 1 - sub

    //cout << "\ndebug_AS " << start_block << " " << end_block << endl;
    //cout << "t_size" << token.size() << endl;
    //output_tokens();
    //cout << endl << "^^^^^^^^^^^^^^" << endl;

    for(int i = start_block; i <= end_block; i++)
    {
        if(token_exemption(i))
        {
            //cout << "hello: " << token[i] << endl;
            //op_flag = 0;
            continue;
        }

        if(token[i].compare("")!=0 &&
           token[i].compare("<less>")!=0 &&
           token[i].compare("<less_equal>")!=0 &&
           token[i].compare("<greater>")!=0 &&
           token[i].compare("<greater_equal>")!=0 &&
           token[i].compare("<equal>")!=0 &&
           token[i].compare("<not_equal>")!=0 &&
           (op_flag == 0 || op_flag == 2))
        {
            switch(op_flag)
            {
                case 0:
                    operand1 = token[i];
                    //cout << "!!op1 = " << operand1 << endl;
                    op1_index = i;
                    op_flag = 1;
                    break;
                case 2:
                    operand2 = token[i];
                    //cout << "!!op2 = " << operand1 << endl;
                    op2_index = i;
                    op_flag = 3;
                    break;
            }
        }
        else if(token[i].compare("<less>")==0)
        {
            if(op_flag != 1)
            {
                rc_setError("Missing operand for less operation : " + rc_intToString(op_flag) );
                return false;
            }
            op_flag = 2;
            operation = 0;

        }
        else if(token[i].compare("<less_equal>")==0)
        {
            if(op_flag != 1)
            {
                rc_setError("Missing operand for less/equal operation");
                return false;
            }
            op_flag = 2;
            operation = 1;
        }
        else if(token[i].compare("<greater>")==0)
        {
            if(op_flag != 1)
            {
                rc_setError("Missing operand for greater operation : " + rc_intToString(op_flag) );
                return false;
            }
            op_flag = 2;
            operation = 2;

        }
        else if(token[i].compare("<greater_equal>")==0)
        {
            if(op_flag != 1)
            {
                rc_setError("Missing operand for greater/equal operation");
                return false;
            }
            op_flag = 2;
            operation = 3;
        }
        else if(token[i].compare("<equal>")==0)
        {
            if(op_flag != 1)
            {
                rc_setError("Missing operand for equal operation : " + rc_intToString(op_flag) );
                return false;
            }
            op_flag = 2;
            operation = 4;

        }
        else if(token[i].compare("<not_equal>")==0)
        {
            if(op_flag != 1)
            {
                rc_setError("Missing operand for not equal operation");
                return false;
            }
            op_flag = 2;
            operation = 5;
        }
        else if(token[i].compare("")!=0)
        {
            op_flag = 0;
        }

        if(op_flag==3)
        {
            if(operand1.substr(0,1).compare("n")==0 && operand2.substr(0,1).compare("n")==0)
                vm_asm.push_back("cmp " + operand1 + " " + operand2);
            else if(operand1.substr(0,1).compare("s")==0 && operand2.substr(0,1).compare("s")==0)
                vm_asm.push_back("cmp$ " + operand1 + " " + operand2);
            else
            {
                rc_setError("Mismatch types in comparison operation");
                return false;
            }
            string solution = "n" + rc_intToString(n_reg);
            inc_n(1);
            switch(operation)
            {
                case 0:
                    vm_asm.push_back("mov " + solution + " %LESS_FLAG");
                    break;
                case 1:
                    vm_asm.push_back("mov " + solution + " %LESS_EQUAL_FLAG");
                    break;
                case 2:
                    vm_asm.push_back("mov " + solution + " %GREATER_FLAG");
                    break;
                case 3:
                    vm_asm.push_back("mov " + solution + " %GREATER_EQUAL_FLAG");
                    break;
                case 4:
                    vm_asm.push_back("mov " + solution + " %EQUAL_FLAG");
                    break;
                case 5:
                    vm_asm.push_back("mov " + solution + " %NOT_EQUAL_FLAG");
                    break;
            }
            set_op_solution(op1_index, op2_index, solution);
            op_flag = 0;
            i = start_block-1;
        }
    }

    if(op_flag == 2)
    {
        rc_setError("Expected operand for add/sub operation");
        return false;
    }

    return true;
}

bool eval_andor(int start_block, int end_block)
{
    int op_flag = 0;
    string operand1 = "";
    string operand2 = "";

    int op1_index = 0;
    int op2_index = 0;
    int operation = 0; //0 - add, 1 - sub

    //cout << "\ndebug_AND " << start_block << " " << end_block << endl;
    //cout << "t_size" << token.size() << endl;
    //output_tokens();
    //cout << endl << "^^^^^^^^^^^^^^" << endl;

    for(int i = start_block; i <= end_block; i++)
    {
        if(token_exemption(i))
        {
            //cout << "hello: " << token[i] << endl;
            //op_flag = 0;
            continue;
        }

        if(token[i].compare("")!=0 &&
           token[i].compare("<and>")!=0 &&
           token[i].compare("<or>")!=0 &&
           token[i].compare("<xor>")!=0 &&
           (op_flag == 0 || op_flag == 2))
        {
            switch(op_flag)
            {
                case 0:
                    operand1 = token[i];
                    //cout << "!!op1 = " << operand1 << endl;
                    op1_index = i;
                    op_flag = 1;
                    break;
                case 2:
                    operand2 = token[i];
                    //cout << "!!op2 = " << operand1 << endl;
                    op2_index = i;
                    op_flag = 3;
                    break;
            }
        }
        else if(token[i].compare("<and>")==0)
        {
            //cout << "AND OPERATION" << endl;
            if(op_flag != 1)
            {
                rc_setError("Missing operand for and operation : " + rc_intToString(op_flag) );
                return false;
            }
            op_flag = 2;
            operation = 0;

        }
        else if(token[i].compare("<or>")==0)
        {
            if(op_flag != 1)
            {
                rc_setError("Missing operand for or operation");
                return false;
            }
            op_flag = 2;
            operation = 1;
        }
        else if(token[i].compare("<xor>")==0)
        {
            if(op_flag != 1)
            {
                rc_setError("Missing operand for xor operation : " + rc_intToString(op_flag) );
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
            switch(operation)
            {
                case 0:
                    if(operand1.substr(0,1).compare("n")==0 && operand2.substr(0,1).compare("n")==0)
                        vm_asm.push_back("and " + operand1 + " " + operand2);
                    else
                    {
                        rc_setError("Incompatible operands for and operation");
                        return false;
                    }
                    break;
                case 1:
                    if(operand1.substr(0,1).compare("n")==0 && operand2.substr(0,1).compare("n")==0)
                        vm_asm.push_back("or " + operand1 + " " + operand2);
                    else
                    {
                        rc_setError("Incompatible operands for or operation");
                        return false;
                    }
                    break;
                case 2:
                    if(operand1.substr(0,1).compare("n")==0 && operand2.substr(0,1).compare("n")==0)
                        vm_asm.push_back("xor " + operand1 + " " + operand2);
                    else
                    {
                        rc_setError("Incompatible operands for xor operation");
                        return false;
                    }
                    break;
            }
            set_op_solution(op1_index, op2_index, operand1);
            op_flag = 0;
            i = start_block-1;
        }
    }

    if(op_flag == 2)
    {
        rc_setError("Expected operand for add/sub operation");
        return false;
    }

    return true;
}

bool eval_not(int start_block, int end_block)
{
    int op_flag = 0;
    string operand1 = "";
    string operand2 = "";

    int op1_index = 0;
    int op2_index = 0;
    int operation = 0; //0 - add, 1 - sub

    //cout << "\ndebug_AS " << start_block << " " << end_block << endl;
    //cout << "t_size" << token.size() << endl;
    //output_tokens();
    //cout << endl << "^^^^^^^^^^^^^^" << endl;

    for(int i = start_block; i <= end_block; i++)
    {
        if(token_exemption(i))
        {
            //cout << "hello: " << token[i] << endl;
            //op_flag = 0;
            continue;
        }

        if(token[i].compare("")!=0 &&
           token[i].compare("<not>")!=0 &&
           op_flag == 1)
        {

            operand1 = token[i];
            //cout << "!!op1 = " << operand1 << endl;
            op2_index = i;
            op_flag = 2;
        }
        else if(token[i].compare("<not>")==0)
        {
            op1_index = i;
            op_flag = 1;
        }
        else if(token[i].compare("")!=0)
        {
            op_flag = 0;
        }

        if(op_flag==2)
        {
            if(operand1.substr(0,1).compare("n")==0)
                vm_asm.push_back("not " + operand1);
            else
            {
                rc_setError("Incompatible operands for and operation");
                return false;
            }
            set_op_solution(op1_index, op2_index, operand1);
            op_flag = 0;
            i = start_block-1;
        }
    }

    if(op_flag == 2)
    {
        rc_setError("Expected operand for add/sub operation");
        return false;
    }

    return true;
}

//still need to store negative numbers properly
#define PP_FLAG_NONE 0
#define PP_FLAG_ARRAY 1

int getArrayObjStart(int arg_id)
{
    string start_arg = "n" + rc_intToString(n_reg);
    inc_n(1);
    vm_asm.push_back("mov " + start_arg + " 0");
    if(id[arg_id].type == ID_TYPE_ARR_NUM)
    {
        switch(id[arg_id].num_args)
        {
            case 1:
                vm_asm.push_back("obj_num1 !" + rc_intToString(id[arg_id].vec_pos) + " " + start_arg);
                break;
            case 2:
                vm_asm.push_back("obj_num2 !" + rc_intToString(id[arg_id].vec_pos) + " " + start_arg + " " + start_arg);
                break;
            case 3:
                vm_asm.push_back("obj_num3 !" + rc_intToString(id[arg_id].vec_pos) + " " + start_arg + " " + start_arg + " " + start_arg);
                break;
        }
        int obj_n = n_reg;
        inc_n(1);
        vm_asm.push_back("obj_get n" + rc_intToString(obj_n));
        return obj_n;
    }
    else if(id[arg_id].type == ID_TYPE_ARR_STR)
    {
        switch(id[arg_id].num_args)
        {
            case 1:
                vm_asm.push_back("obj_str1 !" + rc_intToString(id[arg_id].vec_pos) + " " + start_arg);
                break;
            case 2:
                vm_asm.push_back("obj_str2 !" + rc_intToString(id[arg_id].vec_pos) + " " + start_arg + " " + start_arg);
                break;
            case 3:
                vm_asm.push_back("obj_str3 !" + rc_intToString(id[arg_id].vec_pos) + " " + start_arg + " " + start_arg + " " + start_arg);
                break;
        }
        int obj_s = s_reg;
        inc_s(1);
        vm_asm.push_back("obj_get$ s" + rc_intToString(obj_s));
        return obj_s;
    }

    return 0;

}

bool pre_parse(int start_token = 0, int end_token = -1, int pp_flags)
{

    if(end_token == -1)
    {
        end_token = token.size();
    }

    int n_flag = 0; // id num ] ) } ,
    string n = "";
    string s = "";
    int expr_id = -1;
    string sdata = "";

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
        else if(token[i].substr(0,8).compare("<string>")==0)
        {
            //store strings in data
            sdata = token[i].substr(8);
            int sdata_addr = data_segment.size();
            for(int n = 0; n < sdata.length(); n++)
            {
                data_segment.push_back(sdata[n]);
            }
            data_segment.push_back('\0');
            string token_replace = "s" + rc_intToString(s_reg);
            inc_s(1);
            vm_asm.push_back("mov$ " + token_replace + " @" + rc_intToString(sdata_addr));
            token[i] = token_replace;
        }
        else if(token[i].substr(0,4).compare("<id>")==0)
        {
            //cout << "ID: " << token[i].substr(4) << endl;
            //more needs to be done here
            n = "n" + rc_intToString(n_reg);
            s = "s" + rc_intToString(s_reg);

            expr_id = getIDInScope_ByIndex(token[i].substr(4));

            //cout << "expr = " << expr_id << endl;
            //cout << "TYPE: " << id[expr_id].type << endl << endl;

            if(expr_id < 0)
            {
                rc_setError(token[i].substr(4) + " was not found in this scope-: " + current_scope);
                //output_vars();
                return false;
            }
//            else if(id[expr_id].type == ID_TYPE_BYREF_NUM)
//            {
//                vm_asm.push_back("mov " + n + " !" + rc_intToString(id[expr_id].vec_pos));
//                resolveID_id_reg.push_back(n);
//                resolveID_id_type.push_back(id[expr_id].type);
//                resolveID_id_ut_index.push_back(id[expr_id].type_index);
//                token[i] = n;
//                inc_n(1);
//            }
            else if(id[expr_id].type == ID_TYPE_NUM)
            {
                //cout << endl << "COME ON: " << id[expr_id].name << endl;
                vm_asm.push_back("mov " + n + " !" + rc_intToString(id[expr_id].vec_pos));
                resolveID_id_reg.push_back(n);
                resolveID_id_type.push_back(id[expr_id].type);
                resolveID_id_ut_index.push_back(id[expr_id].type_index);
                token[i] = n;
                inc_n(1);
            }
            else if(id[expr_id].type == ID_TYPE_STR)
            {
                vm_asm.push_back("mov$ " + s + " !" + rc_intToString(id[expr_id].vec_pos));
                resolveID_id_reg.push_back(s);
                resolveID_id_type.push_back(id[expr_id].type);
                resolveID_id_ut_index.push_back(id[expr_id].type_index);
                token[i] = s;
                inc_s(1);
            }
            else if( (id[expr_id].type == ID_TYPE_BYREF_NUM || id[expr_id].type == ID_TYPE_BYREF_STR) && pp_flags == PP_FLAG_ARRAY)
            {
                //cout << "found array: " << id[expr_id].name << endl << endl;
                int s_scope = 0;
                int arr_token_start = i;
                int arr_token_end = i;
                string args[512];
                int num_args = 0;

                int p_scope = 0;

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
                            else if(token[i].compare("!<par>")==0)
                                p_scope++;
                            else if(token[i].compare("!</par>")==0)
                                p_scope--;
                            else if(token[i].compare("")!=0)
                            {
                                rc_setError("Expected number");
                                return false;
                            }
                        }
                        if(p_scope > 0)
                        {
                            rc_setError("Parenthesis Block was not closed");
                            return false;
                        }
                        else if(p_scope < 0)
                        {
                            rc_setError("Parenthesis Block was not opened");
                            return false;
                        }
                        if(s_scope != 0)
                        {
                            rc_setError("Expected closing ]");
                            return false;
                        }
                    }
                }

                if(num_args > 1)
                {
                    rc_setError("..In " + id[expr_id].name + " Expected 0 to 1 dimensions and found " + rc_intToString(num_args));
                    return false;
                }

                if(id[expr_id].type == ID_TYPE_BYREF_NUM && num_args == 0)
                {
                    vm_asm.push_back("mov " + n + " !" + rc_intToString(id[expr_id].vec_pos));
                    resolveID_id_reg.push_back(n);
                    resolveID_id_type.push_back(id[expr_id].type);
                    resolveID_id_ut_index.push_back(id[expr_id].type_index);
                    token[i] = n;
                    inc_n(1);
                    continue;
                }
                else if(id[expr_id].type == ID_TYPE_BYREF_STR && num_args == 0)
                {
                    vm_asm.push_back("mov$ " + s + " !" + rc_intToString(id[expr_id].vec_pos));
                    resolveID_id_reg.push_back(s);
                    resolveID_id_type.push_back(id[expr_id].type);
                    resolveID_id_ut_index.push_back(id[expr_id].type_index);
                    token[i] = s;
                    inc_s(1);
                    continue;
                }



                if(args[0].substr(0,1).compare("n")!=0)
                {
                    rc_setError("Invalid number of args in array");
                    return false;
                }


                string token_replace = "";

                if(id[expr_id].type == ID_TYPE_BYREF_NUM)
                {
                    //vm_asm.push_back("clear_obj");
                    vm_asm.push_back("obj_num1 !" + rc_intToString(id[expr_id].vec_pos) + " " + args[0]);
                    token_replace = "n" + rc_intToString(n_reg);
                    inc_n(1);
                    vm_asm.push_back("obj_get " + token_replace);
                }
                else
                {
                    //vm_asm.push_back("clear_obj");
                    vm_asm.push_back("obj_str1 !" + rc_intToString(id[expr_id].vec_pos) + " " + args[0]);
                    token_replace = "s" + rc_intToString(s_reg);
                    inc_s(1);
                    vm_asm.push_back("obj_get$ " + token_replace);
                }


                resolveID_id_reg.push_back(token_replace);
                resolveID_id_type.push_back(id[expr_id].type);
                resolveID_id_ut_index.push_back(id[expr_id].type_index);

                for(int p = arr_token_start; p <= arr_token_end; p++)
                    token[p] = "";

                if(token_replace.compare("")==0)
                {
                    rc_setError("%%could not resolve array " + id[expr_id].name);
                    return false;
                }

                token[arr_token_start] = token_replace;

                //cout << "the end of array" << endl;

            }
            else if( (id[expr_id].type == ID_TYPE_ARR_NUM || id[expr_id].type == ID_TYPE_ARR_STR) && pp_flags == PP_FLAG_ARRAY)
            {
                //cout << "found array: " << id[expr_id].name << endl << endl;
                int s_scope = 0;
                int arr_token_start = i;
                int arr_token_end = i;
                string args[3];
                int num_args = 0;

                int p_scope = 0;

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
                            else if(token[i].compare("!<par>")==0)
                                p_scope++;
                            else if(token[i].compare("!</par>")==0)
                                p_scope--;
                            else if(token[i].compare("")!=0)
                            {
                                rc_setError("Expected number");
                                return false;
                            }
                        }
                        if(p_scope > 0)
                        {
                            rc_setError("Parenthesis Block was not closed");
                            return false;
                        }
                        else if(p_scope < 0)
                        {
                            rc_setError("Parenthesis Block was not opened");
                            return false;
                        }
                    }
                }
                //cout << endl << "ID_ARRAY: " << id[expr_id].name << endl;
                //cout << "NUM_ARGS_EXPECTED: " << id[expr_id].num_args << endl;
                //cout << "NUM_ARGS_FOUND: " << num_args << endl;

                if(id[expr_id].isArrayArg)
                {
                    //cout << "array arg found" << endl;
                    id[expr_id].isArrayArg = false;
                    string token_replace = "";
                    if(id[expr_id].type == ID_TYPE_ARR_NUM)
                    {
                        token_replace = "n" + rc_intToString(n_reg);
                        inc_n(1);
                        vm_asm.push_back("mov_arr " + token_replace + " !" + rc_intToString(id[expr_id].vec_pos));

                    }
                    else
                    {
                        token_replace = "s" + rc_intToString(s_reg);
                        inc_s(1);
                        vm_asm.push_back("mov_arr$ " + token_replace + " !" + rc_intToString(id[expr_id].vec_pos));
                    }

                    resolveID_id_reg.push_back(token_replace);
                    resolveID_id_type.push_back(id[expr_id].type);
                    resolveID_id_ut_index.push_back(id[expr_id].type_index);

                    for(int p = arr_token_start; p <= arr_token_end; p++)
                        token[p] = "";

                    token[arr_token_start] = token_replace;
                    continue;
                }

                if(id[expr_id].num_args != num_args)
                {
                    if(num_args == 0)
                        continue;

                    rc_setError("7In " + id[expr_id].name + " Expected " + rc_intToString(id[expr_id].num_args) + " dimensions and found " + rc_intToString(num_args));
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
                            //vm_asm.push_back("clear_obj");
                            vm_asm.push_back("obj_num1 !" + rc_intToString(id[expr_id].vec_pos) + " " + args[0]);
                            token_replace = "n" + rc_intToString(n_reg);
                            inc_n(1);
                            vm_asm.push_back("obj_get " + token_replace);
                        }
                        else
                        {
                            //vm_asm.push_back("clear_obj");
                            vm_asm.push_back("obj_str1 !" + rc_intToString(id[expr_id].vec_pos) + " " + args[0]);
                            token_replace = "s" + rc_intToString(s_reg);
                            inc_s(1);
                            vm_asm.push_back("obj_get$ " + token_replace);
                        }
                        break;
                    case 2:
                        if(id[expr_id].type == ID_TYPE_ARR_NUM)
                        {
                            //vm_asm.push_back("clear_obj");
                            vm_asm.push_back("obj_num2 !" + rc_intToString(id[expr_id].vec_pos) + " " + args[0] + " " + args[1]);
                            token_replace = "n" + rc_intToString(n_reg);
                            inc_n(1);
                            vm_asm.push_back("obj_get " + token_replace);
                        }
                        else
                        {
                            //vm_asm.push_back("clear_obj");
                            vm_asm.push_back("obj_str2 !" + rc_intToString(id[expr_id].vec_pos) + " " + args[0] + " " + args[1]);
                            token_replace = "s" + rc_intToString(s_reg);
                            inc_s(1);
                            vm_asm.push_back("obj_get$ " + token_replace);
                        }
                        break;
                    case 3:
                        if(id[expr_id].type == ID_TYPE_ARR_NUM)
                        {
                            //vm_asm.push_back("clear_obj");
                            vm_asm.push_back("obj_num3 !" + rc_intToString(id[expr_id].vec_pos) + " " + args[0] + " " + args[1] + " " + args[2]);
                            token_replace = "n" + rc_intToString(n_reg);
                            inc_n(1);
                            vm_asm.push_back("obj_get " + token_replace);
                        }
                        else
                        {
                            //vm_asm.push_back("clear_obj");
                            vm_asm.push_back("obj_str3 !" + rc_intToString(id[expr_id].vec_pos) + " " + args[0] + " " + args[1] + " " + args[2]);
                            token_replace = "s" + rc_intToString(s_reg);
                            inc_s(1);
                            vm_asm.push_back("obj_get$ " + token_replace);
                        }
                        break;
                    default:
                        rc_setError("Invalid number of dimensions in array");
                        return false;
                }

                resolveID_id_reg.push_back(token_replace);
                resolveID_id_type.push_back(id[expr_id].type);
                resolveID_id_ut_index.push_back(id[expr_id].type_index);

                for(int p = arr_token_start; p <= arr_token_end; p++)
                    token[p] = "";

                if(token_replace.compare("")==0)
                {
                    rc_setError("%%could not resolve array " + id[expr_id].name);
                    return false;
                }

                token[arr_token_start] = token_replace;

                //cout << "the end of array" << endl;

            }
            else if( (id[expr_id].type == ID_TYPE_FN_NUM || id[expr_id].type == ID_TYPE_FN_STR || id[expr_id].type == ID_TYPE_SUB) && pp_flags == PP_FLAG_ARRAY)
            {
                //cout << "FUNCTION: " << id[expr_id].name << endl;

                //output_tokens();
                //cout << "found function: " << id[expr_id].name << " " << current_block_state << endl << endl;
                //cout << "fn ids = " << id[expr_id].fn_var.size() << endl;

                //push all current function ids onto stack before setting them with the expression function values
//                if(isInFunctionScope)
//                {
//                    for(int n = 0; n < id[expr_id].fn_var.size(); n++)
//                    {
//                        cout << "fid[" << n << "] = " << id[expr_id].fn_var[n].vec_str << endl;
//                        if(id[expr_id].fn_var[n].type == ID_TYPE_NUM || id[expr_id].fn_var[n].type == ID_TYPE_BYREF_NUM || id[expr_id].fn_var[n].type == ID_TYPE_ARR_NUM)
//                        {
//                            vm_asm.push_back("push " + id[expr_id].fn_var[n].vec_str);
//                        }
//                        else
//                        {
//                            vm_asm.push_back("push$ " + id[expr_id].fn_var[n].vec_str);
//                        }
//                    }
//
//                }
                //cout << "debug 1" << endl;

                int s_scope = 0;
                int arr_token_start = i;
                int arr_token_end = i;
                string args[1024];
                args[0] = "";
                int num_args = 0;
                int arg_size = 0; //this variable counts the number of tokens in a argument; used to fix multiple tokens in 1 argument (ie. abs(5 7) should not compile)
                if( (i+1) <= end_token)
                {
                    //cout << "DBG #1: " << id[expr_id].name << endl;
                    if(token[i+1].compare("!<par>")==0)
                    {
                        //cout << "DBG #2" <<endl;
                        s_scope = 1;
                        for(i += 2; (i <= end_token) && (s_scope != 0); i++)
                        {
                            //cout << "loop " << i << endl;
                            if(token[i].compare("!</par>")==0)
                            {
                                //cout << "DBG #4: " << s_scope << endl;
                                s_scope--;
                                if(s_scope == 0)
                                {
                                    //num_args++;
                                    if(num_args > 0 || args[0].compare("") != 0)
                                        num_args++;
                                    arr_token_end = i;
                                }
                            }
                            else if(token[i].compare("!<par>")==0)
                                s_scope++;
                            else if(token[i].compare("!<comma>")==0)
                            {
                                num_args++;
                                arg_size = 0;
                            }
                            else if(token[i].substr(0,1).compare("n")==0 || token[i].substr(0,1).compare("s")==0 || token[i].substr(0,4).compare("<id>")==0)
                            {
                                //cout << id[expr_id].name << "->DBG #3:" << num_args << "  " << token[i] << endl;
                                args[num_args] = token[i];

                                arg_size++;
                                if(arg_size > 1)
                                {
                                    cout << "Expected Operator in expression" << endl;
                                    return false;
                                }
                            }
                            else if(token[i].compare("")!=0)
                            {
                                rc_setError("aInvalid argument in function: "+token[i]);
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
                    rc_setError("//In " + id[expr_id].name + " Expected " + rc_intToString(id[expr_id].num_args) + " arguments and found " + rc_intToString(num_args));
                    rc_setError("arg[0]=" + args[0]);
                    //cout <<"TOEK" << endl;
                    output_tokens();
                    return false;
                }

                int resolve_index = -1;
                int arg_index = -1;

                if(StringToLower(id[expr_id].name).compare("arraydim")==0)
                {
                    //cout << "HERES JOHNNY" << endl;
                    resolve_index = getResolveReg(args[0]);
                    if(resolve_index < 0)
                    {
                        rc_setError("Expected Identifier in ArrayDim argument --> " + args[0]);
                        return false;
                    }
                    switch(resolveID_id_type[resolve_index])
                    {
                        case ID_TYPE_ARR_NUM:
                        case ID_TYPE_BYREF_NUM:
                        case ID_TYPE_NUM:
                            expr_id = getIDInScope_ByIndex("NumberArrayDim");
                            break;
                        case ID_TYPE_ARR_STR:
                        case ID_TYPE_BYREF_STR:
                        case ID_TYPE_STR:
                            expr_id = getIDInScope_ByIndex("StringArrayDim");
                            break;
                    }
                    if(expr_id < 0)
                    {
                        rc_setError("Debug ERROR HERE");
                        return false;
                    }
                }
                else if(StringToLower(id[expr_id].name).compare("arraysize")==0)
                {
                    //cout << "HERES JOHNNY" << endl;
                    resolve_index = getResolveReg(args[0]);
                    if(resolve_index < 0)
                    {
                        rc_setError("Expected Identifier in ArraySize argument: " +args[0]);
                        return false;
                    }
                    switch(resolveID_id_type[resolve_index])
                    {
                        case ID_TYPE_ARR_NUM:
                        case ID_TYPE_BYREF_NUM:
                        case ID_TYPE_NUM:
                            expr_id = getIDInScope_ByIndex("NumberArraySize");
                            break;
                        case ID_TYPE_ARR_STR:
                        case ID_TYPE_BYREF_STR:
                        case ID_TYPE_STR:
                            expr_id = getIDInScope_ByIndex("StringArraySize");
                            break;
                    }
                    if(expr_id < 0)
                    {
                        rc_setError("ArraySize Syntax Error");
                        return false;
                    }
                }

                bool local_state_is_pushed = false; //this variable checks will be set to true if the following function call is recursive
                if(block_state.size() > 0)
                {
                    if(current_scope.substr(0, ("main."+id[expr_id].name).length()).compare("main."+id[expr_id].name)==0)
                    {
                        local_state_is_pushed = true;
                        //cout << "DEBUG: local_state_is_pushed=" << (local_state_is_pushed ? "TRUE":"FALSE") << endl;
                        //push all variables that were made in current function
                        for(uint32_t fn_var_id = current_fn_index+1; fn_var_id < id.size(); fn_var_id++)
                        {
                            switch(id[fn_var_id].type)
                            {
                                case ID_TYPE_NUM:
                                    vm_asm.push_back("push !" + rc_intToString(id[fn_var_id].vec_pos));
                                    n_tmp.push_back("!" + rc_intToString(id[fn_var_id].vec_pos) );
                                    //cout << "push -- " << id[fn_var_id].name << endl;
                                    break;
                                case ID_TYPE_STR:
                                    vm_asm.push_back("push$ !" + rc_intToString(id[fn_var_id].vec_pos));
                                    s_tmp.push_back("!" + rc_intToString(id[fn_var_id].vec_pos) );
                                    break;
                            }
                        }
                    }
                }


                for(int n = 0; n < id[expr_id].num_args; n++)
                {
                    if(args[n].substr(0,1).compare("n")!=0 && args[n].substr(0,1).compare("s")!=0 && args[n].substr(0,4).compare("<id>")!=0)
                    {
                        rc_setError("bInvalid number of args in function: " + args[n]);
                        return false;
                    }

                    if(id[expr_id].fn_arg_type[n] == ID_TYPE_BYREF_NUM || id[expr_id].fn_arg_type[n] == ID_TYPE_BYREF_STR)
                    {
                        resolve_index = getResolveReg(args[n]);
                        if(args[n].substr(0,4).compare("<id>")==0)
                        {
                            //cout << "found id: " << args[n] << " in " << id[expr_id].name << endl;
                            string t_replace = "";
                            int arg_id = getIDInScope_ByIndex(args[n].substr(4));
                            if(arg_id < 0)
                            {
                                rc_setError("Identifier was not declared in byref argument");
                                return false;
                            }
                            if(id[arg_id].type == ID_TYPE_ARR_NUM)
                            {
                                t_replace = "n" + rc_intToString( getArrayObjStart(arg_id));
                                //t_replace = "n" + rc_intToString(n_reg);
                                //inc_n(1);
                                //vm_asm.push_back("mov " + t_replace + " !" + rc_intToString(id[arg_id].vec_pos));

                                resolveID_id_reg.push_back(t_replace);
                                resolveID_id_type.push_back(id[arg_id].type);
                                resolve_index = resolveID_id_reg.size()-1;
                            }
                            else if(id[arg_id].type == ID_TYPE_ARR_STR)
                            {
                                t_replace = "s" + rc_intToString( getArrayObjStart(arg_id));
                                //t_replace = "s" + rc_intToString(s_reg);
                                //inc_s(1);
                                //vm_asm.push_back("mov$ " + t_replace + " !" + rc_intToString(id[arg_id].vec_pos));

                                resolveID_id_reg.push_back(t_replace);
                                resolveID_id_type.push_back(id[arg_id].type);
                                resolve_index = resolveID_id_reg.size()-1;
                            }
                            else
                            {
                                rc_setError("Could not resolve Identifier in ByRef argument");
                                return false;
                            }
                        }

                        if(resolve_index < 0)
                        {
                            rc_setError("Expected identifier for ByRef argument");
                            return false;
                        }

                        /*arg_index = getIDInScope_ByIndex(resolveID_id_reg[resolve_index]);

                        if(arg_index < 0)
                        {
                            rc_setError("Identifier " + resolveID_id_reg[resolve_index] + " was not defined in this scope");
                            return false;
                        }*/

                        switch(id[expr_id].fn_arg_type[n])
                        {
                            case ID_TYPE_BYREF_NUM:
                                if(resolveID_id_type[resolve_index] != ID_TYPE_NUM && resolveID_id_type[resolve_index] != ID_TYPE_ARR_NUM && resolveID_id_type[resolve_index] != ID_TYPE_BYREF_NUM)
                                {
                                    rc_setError("Expected number identifier for argument");
                                    return false;
                                }
                                vm_asm.push_back("ptr !" + rc_intToString(id[expr_id].fn_arg_vec[n]) + " " + resolveID_id_reg[resolve_index]);
                                break;
                            case ID_TYPE_BYREF_STR:
                                if(resolveID_id_type[resolve_index] != ID_TYPE_STR && resolveID_id_type[resolve_index] != ID_TYPE_ARR_STR && resolveID_id_type[resolve_index] != ID_TYPE_BYREF_STR)
                                {
                                    rc_setError("Expected string identifier for argument");
                                    return false;
                                }
                                vm_asm.push_back("ptr$ !" + rc_intToString(id[expr_id].fn_arg_vec[n]) + " " + resolveID_id_reg[resolve_index]);
                                break;
                        }
                    }
                    else if(id[expr_id].fn_arg_type[n] == ID_TYPE_NUM)
                    {
                        if(args[n].substr(0,1).compare("n")!=0)
                        {
                            rc_setError("Expected number expression for argument");
                            return false;
                        }
                        //vm_asm.push_back("mov " + id[expr_id].fn_arg[n] + "->" + id[expr_id].fn_reg[n] + " " + args[n]);
                        vm_asm.push_back("mov !" + rc_intToString(id[expr_id].fn_arg_vec[n]) + " " + args[n]);
                    }
                    else if(id[expr_id].fn_arg_type[n] == ID_TYPE_STR)
                    {
                        if(args[n].substr(0,1).compare("s")!=0)
                        {
                            rc_setError("Expected string expression for argument");
                            return false;
                        }
                        //vm_asm.push_back("mov " + id[expr_id].fn_arg[n] + "->" + id[expr_id].fn_reg[n] + " " + args[n]);
                        vm_asm.push_back("mov$ !" + rc_intToString(id[expr_id].fn_arg_vec[n]) + " " + args[n]);
                    }
                }

                string token_replace = "";

                if(id[expr_id].isBuiltin)
                    vm_asm.push_back("func !" + rc_intToString(id[expr_id].vmFunctionIndex));
                else
                {
                    for(int n = 0; n < n_reg; n++)
                    {
                        vm_asm.push_back("push n" + rc_intToString(n));
                        n_tmp.push_back("n"+rc_intToString(n));
                    }
                    for(int n = 0; n < s_reg; n++)
                    {
                        vm_asm.push_back("push$ s" + rc_intToString(n));
                        s_tmp.push_back("s" + rc_intToString(n));
                    }

                    vm_asm.push_back("gosub @" + id[expr_id].name);
                }

                int ptr_count = 0;
                for(int n = 0; n < id[expr_id].fn_arg.size(); n++)
                {
                    if(id[expr_id].fn_arg_type[n] == ID_TYPE_BYREF_NUM || id[expr_id].fn_arg_type[n] == ID_TYPE_BYREF_STR)
                        ptr_count++;
                }

                if(ptr_count > 0)
                {
                    vm_asm.push_back("pop_ptr !" + rc_intToString(ptr_count));
                }

                if(id[expr_id].type == ID_TYPE_FN_NUM)
                {
                    token_replace = "n" + rc_intToString(n_reg);
                    vm_asm.push_back("pop " + token_replace);
                    inc_n(1);
                }
                else if(id[expr_id].type == ID_TYPE_FN_STR)
                {
                    token_replace = "s" + rc_intToString(s_reg);
                    vm_asm.push_back("pop$ " + token_replace);
                    inc_s(1);
                }
                else if(id[expr_id].type == ID_TYPE_SUB)
                {
                    token_replace = "?";
                }

                //cout << "start_dbg" << endl;

                if(!id[expr_id].isBuiltin)
                {
                    for(int n = n_tmp.size()-1; n >= 0; n--)
                    {
                        vm_asm.push_back("pop " + n_tmp[n]);
                    }
                    for(int n = s_tmp.size()-1; n >= 0; n--)
                    {
                        vm_asm.push_back("pop$ " + s_tmp[n]);
                    }
                    n_tmp.clear();
                    s_tmp.clear();
                }

                //cout << "end dbg" << endl;

//                if(isInFunctionScope)
//                {
//                    for(int n = id[expr_id].fn_var.size()-1; n >= 0;  n--)
//                    {
//                        if(id[expr_id].fn_var[n].type == ID_TYPE_NUM || id[expr_id].fn_var[n].type == ID_TYPE_BYREF_NUM || id[expr_id].fn_var[n].type == ID_TYPE_ARR_NUM)
//                        {
//                            vm_asm.push_back("pop " + id[expr_id].fn_var[n].vec_str);
//                        }
//                        else
//                        {
//                            vm_asm.push_back("pop$ " + id[expr_id].fn_var[n].vec_str);
//                        }
//                    }
//                }

                for(int p = arr_token_start; p <= arr_token_end; p++)
                    token[p] = "";

                if(token_replace.compare("")==0)
                {
                    rc_setError("%%could not resolve function " + id[expr_id].name);
                    return false;
                }

                token[arr_token_start] = token_replace;

                //cout << "the end of function" << endl;

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

        //cout << "start pp" << endl;
        if(!pre_parse(start_block, end_block, PP_FLAG_ARRAY))
        {
            return false;
        }
        //cout << "end pp" << endl;

        getArgBlockStuff(start_block, arg_count);

        //cout << "start block = " << start_token << endl << endl; cout << "end block = " << end_token << endl;

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
            //cout << "arg_count = " << arg_count << endl;
            for(int i = 0; i < arg_count; i++)
            {
                getBlockArg(i, arg_start, arg_end);

                if(!eval_not(start_block, end_block))
                    return false;
                if(!eval_pow(arg_start, arg_end))
                    return false;
                if(!eval_muldiv(arg_start, arg_end))
                    return false;
                if(!eval_addsub(arg_start, arg_end))
                    return false;
                if(!eval_bitshift(arg_start, arg_end))
                    return false;
                if(!eval_cmp(arg_start, arg_end))
                    return false;
                if(!eval_andor(arg_start, arg_end))
                    return false;
                arg_result = "";

                for(int n = arg_start; n <= arg_end; n++)
                {
                    if(token[n].size()>0)
                    {
                        if(token[n].substr(0,1).compare("n")==0 || token[n].substr(0,1).compare("s")==0 || token[n].substr(0,4).compare("<id>") == 0)
                           arg_result = token[n];
                    }
                    token[n] = "";
                }
                token[arg_start] = arg_result;
            }
        }
        else
        {
            //cout << "start" << endl;
            if(!eval_not(start_block, end_block))
                return false;
            if(!eval_pow(start_block, end_block))
                return false;
            if(!eval_muldiv(start_block, end_block))
                return false;
            if(!eval_addsub(start_block, end_block))
                return false;
            if(!eval_bitshift(start_block, end_block))
                return false;
            if(!eval_cmp(start_block, end_block))
                return false;
            if(!eval_andor(start_block, end_block))
                return false;
            //cout << "end here" << endl;
        }

        //cout << "start block end = " << start_token << endl;

    }while(!(start_block==start_token && end_block==end_token));

    int result_count = 0;

    for(int i = start_token; i <= end_token; i++)
    {
        if(token[i].length()>0)
        {
            if(token[i].substr(0,1).compare("n")==0 || token[i].substr(0,1).compare("s")==0 || token[i].substr(0,1).compare("?")==0)
            {
                expr_result = token[i];
                multi_arg[multi_arg_count] = token[i];
                multi_arg_count++;
                result_count++;
            }
            else if(token[i].substr(0,1).compare("!")!=0)
            {
                rc_setError("_Could not evaluate expression");
                return false;
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

int findFirstDelimiter(string line)
{
    for(int i = 0; i < line.length(); i++)
    {
        if(line[i] == '.' || line[i] == '[' || line[i] == ']' || line[i] == ' ')
            return i;
    }
    return line.length()-1;
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
    resolveID_id_reg.clear();
    resolveID_id_type.clear();
    resolveID_id_ut_index.clear();
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
                    if(idExistsInScope(id_name))
                    {
                        rc_setError("Identifier already defined in current scope");
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
                        else if(isInFunctionScope)
                        {
                            if(!create_function_variable(id_name, id_type, ""))
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
                        multi_arg[0] = "";
                        multi_arg[1] = "";
                        multi_arg[2] = "";
                        multi_arg_count = 0;
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
                            //cout << "M_ARG[0] = " << multi_arg[0] << endl;
                            //cout << "M_ARG[1] = " << multi_arg[1] << endl;
                            //cout << "M_ARG[2] = " << multi_arg[2] << endl;
                            dimensions = multi_arg_count;
                        }
                        token_index = end_token+1;
                        //if(token.size()<token_index)
                        //    return true;
                        //cout << "tok_ind = " << token_index << endl;
                    }

                    if(token.size()>token_index)
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
                    if(isInFunctionScope)
                    {
                        if(!create_function_array(id_name,id_type, dimensions, multi_arg[0], multi_arg[1], multi_arg[2]))
                        {
                            return false;
                        }
                    }
                    else if(!create_array(id_name, id_type, id_type_name, dimensions, multi_arg[0], multi_arg[1], multi_arg[2]))
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
            else
            {
                //if the size of the token vector is not greater than one then the syntax for the line is incomplete so I return false
                rc_setError("Expected Identifier name");
                return false;
            }
        }
        else if(token[0].compare("<redim>")==0)
        {
            //cout << "REDIM RULE FOUND" << endl;  //'DIM' [ID]; '[' #; #; # ']' ; 'AS' [TYPE]; '=' (VALUE)

            string id_name = "";
            int id_type = ID_TYPE_NUM;
            string id_type_name = "";
            int dimensions = 0;
            int id_index = -1;

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


                    id_index  = getIDInScope_ByIndex(id_name);
                    //cout << "debug 0: " << id_index << " -> " << id[id_index].name << " --- " << id[id_index].vec_pos << endl;

                    //if the identifier already exists and current_block state is not type then return false
                    if(id_index < 0)
                    {
                        rc_setError("Identifier was not defined in current scope");
                        return false;
                    }

                    if(id[id_index].num_args <= 0)
                    {
                        rc_setError("REDIM expected array identifier");
                        return false;
                    }

                    id_type = id[id_index].type;

                    //cout << "db1\n";

                    //if there are only two tokens then return here because there is nothing left to check
                    if(token.size()==2)
                    {
                        rc_setError("Dimensions must be specified for REDIM");
                        //cout << "return true here" << endl;
                        return false;
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
                        multi_arg[0] = "";
                        multi_arg[1] = "";
                        multi_arg[2] = "";
                        multi_arg_count = 0;
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

                        //cout << "debug 1: " << id_index << endl;

                        if(!eval_expression(token_index, end_token, true))
                        {
                            rc_setError("Could not evaluate expression in array definition");
                            return false;
                        }

                        //cout << "debug 2: " << id_index << endl;

                        if(multi_arg_count <= 0 || multi_arg_count > 3)
                        {
                            rc_setError("Expected 1 to 3 Arguments for array re-dimension, Found " + rc_intToString(multi_arg_count));
                            return false;
                        }
                        else
                        {
                            //cout << "M_ARG[0] = " << multi_arg[0] << endl;
                            //cout << "M_ARG[1] = " << multi_arg[1] << endl;
                            //cout << "M_ARG[2] = " << multi_arg[2] << endl;
                            dimensions = multi_arg_count;
                        }
                        token_index = end_token+1;

                        //cout << "debug 3: " << id_index << endl;
                    }
                    else
                    {
                        rc_setError("Expected dimensions for REDIM");
                        return false;
                    }

                    if(token.size()>token_index)
                    {
                        rc_setError("Invalid use of REDIM");
                        return false;
                    }

                    //cout << "debug 4: " << id_index << endl;

                }
                else
                {
                    //if the next token is not an id then the syntax is incorrect and false is returned
                    rc_setError("Expected Identifier name");
                    return false;
                }

                if(dimensions > 0)
                {
                    //cout << "debug 5: " << id_index <<  endl;
                    switch(id_type)
                    {
                        case ID_TYPE_NUM:
                            id_type = ID_TYPE_ARR_NUM;
                            break;
                        case ID_TYPE_STR:
                            id_type = ID_TYPE_ARR_STR;
                            break;
                    }

                    //cout << "debug 6: " << id_index << endl;

                    if(id[id_index].num_args != dimensions)
                    {
                        id[id_index].num_args = dimensions;
                    }

                    //cout << "debug 7: " << id_index << " -- " << id[id_index].type << endl;

                    if(id[id_index].type == ID_TYPE_NUM || id[id_index].type == ID_TYPE_ARR_NUM)
                    {
                        //cout << "debug 8" << endl;
                        switch(dimensions)
                        {
                            case 1:
                                vm_asm.push_back("redim1 !" + rc_intToString(id[id_index].vec_pos) + " " + multi_arg[0]);
                                break;
                            case 2:
                                vm_asm.push_back("redim2 !" + rc_intToString(id[id_index].vec_pos) + " " + multi_arg[0] + " " + multi_arg[1]);
                                break;
                            case 3:
                                vm_asm.push_back("redim3 !" + rc_intToString(id[id_index].vec_pos) + " " + multi_arg[0] + " " + multi_arg[1] + " " + multi_arg[2]);
                                break;
                            default:
                                rc_setError("Invalid number of dimensions in REDIM");
                                return false;
                        }
                    }
                    else if(id[id_index].type == ID_TYPE_STR || id[id_index].type == ID_TYPE_ARR_STR)
                    {
                        switch(dimensions)
                        {
                            case 1:
                                vm_asm.push_back("redim1$ !" + rc_intToString(id[id_index].vec_pos) + " " + multi_arg[0]);
                                break;
                            case 2:
                                vm_asm.push_back("redim2$ !" + rc_intToString(id[id_index].vec_pos) + " " + multi_arg[0] + " " + multi_arg[1]);
                                break;
                            case 3:
                                vm_asm.push_back("redim3$ !" + rc_intToString(id[id_index].vec_pos) + " " + multi_arg[0] + " " + multi_arg[1] + " " + multi_arg[2]);
                                break;
                            default:
                                rc_setError("Invalid number of dimensions in REDIM");
                                return false;
                        }
                    }
                    else
                    {
                        rc_setError("Invalid type for REDIM");
                        return false;
                    }
                    //cout << "balls" << endl;
                    return true;
                }
                else
                {
                    rc_setError("Expected dimensions in REDIM");
                    return false;
                }

            }
            else
            {
                //if the size of the token vector is not greater than one then the syntax for the line is incomplete so I return false
                rc_setError("Expected Identifier name");
                return false;
            }
            //cout << "debug final" << endl;
        }
        else if(token[0].compare("<end>")==0)
        {
            if(token.size()==1)
            {
                vm_asm.push_back("end");
                return true;
            }
            if(token[1].compare("<function>")==0)
            {
                if(token.size()>2)
                {
                    rc_setError("Expected End of Line in END FUNCTION");
                    return false;
                }
                if(current_block_state != BLOCK_STATE_FUNCTION)
                {
                    rc_setError("Cannot exit function from this scope");
                    return false;
                }

                //int ptr_count = 0;
                //for(int n = 0; n < id[current_fn_index].fn_arg.size(); n++)
                //{
                //    if(id[current_fn_index].fn_arg_type[n] == ID_TYPE_BYREF_NUM || id[current_fn_index].fn_arg_type[n] == ID_TYPE_BYREF_STR)
                //    {
                //        ptr_count++;
                //    }
                //}

                //if(ptr_count > 0)
                //    vm_asm.push_back("pop_ptr !" + rc_intToString(ptr_count));
                if(id[current_fn_index].type == ID_TYPE_FN_NUM)
                {
                    vm_asm.push_back("push 0");
                    vm_asm.push_back("return");
                    vm_asm.push_back(".code");
                    vm_asm.n_stack_count = 0;
                }
                else if(id[current_fn_index].type == ID_TYPE_FN_STR)
                {
                    vm_asm.push_back("push_empty$");
                    vm_asm.push_back("return");
                    vm_asm.push_back(".code");
                    vm_asm.s_stack_count = 0;
                }
                block_state.pop();
                current_block_state = BLOCK_STATE_MAIN;
                isInFunctionScope = false;
                current_scope = "main";
                current_fn_index++;
            }
            else if(token[1].compare("<subp>")==0)
            {
                if(token.size()>2)
                {
                    rc_setError("Expected End of Line in END SUB");
                    return false;
                }
                if(current_block_state != BLOCK_STATE_SUB)
                {
                    rc_setError("Cannot exit sub routine from this scope");
                    return false;
                }

                //int ptr_count = 0;
                //for(int n = 0; n < id[current_fn_index].fn_arg.size(); n++)
                //{
                //    if(id[current_fn_index].fn_arg_type[n] == ID_TYPE_BYREF_NUM || id[current_fn_index].fn_arg_type[n] == ID_TYPE_BYREF_STR)
                //    {
                //        ptr_count++;
                //    }
                //}

                //if(ptr_count > 0)
                //    vm_asm.push_back("pop_ptr !" + rc_intToString(ptr_count));

                vm_asm.push_back("return");
                vm_asm.push_back(".code");

                block_state.pop();
                current_block_state = BLOCK_STATE_MAIN;
                isInFunctionScope = false;
                current_scope = "main";
                current_fn_index++;
            }
            else if(token[1].compare("<if>")==0)
            {
                if(token.size() > 2)
                {
                    rc_setError("Expected End of Line in END IF");
                    return false;
                }
                if(current_block_state != BLOCK_STATE_IF)
                {
                    rc_setError("Cannot END IF without starting an IF Block");
                    return false;
                }
                block_state.pop();
                current_block_state = block_state.top();

                vm_asm.push_back("label ELSE:" + rc_intToString(if_block.top().index) + "->CONDITION:" + rc_intToString(if_block.top().condition));
                vm_asm.push_back("label ENDIF:" + rc_intToString(if_block.top().index));
                if_block.pop();
                exit_scope(1);
            }
            else if(token[1].compare("<select>")==0)
            {
                if(token.size() > 2)
                {
                    rc_setError("Expected End of Line in END SELECT");
                    return false;
                }
                if(current_block_state != BLOCK_STATE_SELECT)
                {
                    rc_setError("Cannot END SELECT without starting a SELECT Block");
                    return false;
                }
                block_state.pop();
                current_block_state = block_state.top();


                vm_asm.push_back("label SELECT:" + rc_intToString(select_block.top().index) + "->CASE:" + rc_intToString(select_block.top().case_index));
                vm_asm.push_back("label SELECT:" + rc_intToString(select_block.top().index) + "->END");

                if(select_block.top().case_type==ID_TYPE_STR)
                {
                    string compare_case = "s" + rc_intToString(s_reg);
                    vm_asm.push_back("pop$ " + compare_case);
                    inc_s(1);
                }
                else
                {
                    string compare_case = "n" + rc_intToString(n_reg);
                    vm_asm.push_back("pop " + compare_case);
                    inc_n(1);
                }

                select_block.pop();
                exit_scope(1);
            }
            else
            {
                rc_setError("Invalid use of END");
                return false;
            }
        }
        else if(token[0].compare("<function>")==0)
        {
            if(isInFunctionScope)
            {
                rc_setError("Cannot declare function from this scope");
                return false;
            }
            if(token.size()<2)
            {
                rc_setError("Expected identifier for function declaration");
                return false;
            }

            string fn_name = rc_substr(token[1], 4, token[1].length());
            if(!isValidIDName(fn_name) )
            {
                rc_setError(fn_name + " is not a valid identifier name");
                return false;
            }
            if(idExistsInScope(fn_name))
            {
                rc_setError("Identifier " + fn_name + " already exists in this scope");
                return false;
            }

            int fn_type = ID_TYPE_FN_NUM;
            if(fn_name.substr(fn_name.length()-1,1).compare("$")==0)
                fn_type = ID_TYPE_FN_STR;

            create_function(fn_name, fn_type, "");
            current_block_state = BLOCK_STATE_FUNCTION;
            block_state.push(current_block_state);

            string fn_arg = "";
            int fn_arg_type = ID_TYPE_NUM;
            bool fn_byref = false;

            int end_token = 0;

            for(int i = 3; i < token.size(); i++)
            {
                if(token[i].compare("<byref>")==0)
                {
                    fn_byref = true;
                }
                else if(rc_substr(token[i], 0, 4).compare("<id>")==0)
                {
                    fn_arg += token[i];
                    if(fn_arg.substr(fn_arg.length()-1,1).compare("$")==0)
                        fn_arg_type = ID_TYPE_STR;
                    else
                        fn_arg_type = ID_TYPE_NUM;
                }
                else if(token[i].compare("<comma>")==0)
                {
                    fn_arg = rc_substr(fn_arg, 4, fn_arg.length()-1);
                    if(!isValidIDName(fn_arg))
                    {
                        rc_setError("Function argument is not a valid identifier name");
                        return false;
                    }
                    if(idExistsInScope(fn_arg))
                    {
                        rc_setError("Function argument identifier already exists in current scope");
                        return false;
                    }

                    if(fn_byref)
                    {
                        if(fn_arg_type == ID_TYPE_NUM)
                            fn_arg_type = ID_TYPE_BYREF_NUM;
                        else
                            fn_arg_type = ID_TYPE_BYREF_STR;
                    }

                    add_function_arg(fn_arg, fn_arg_type, "");
                    fn_arg = "";
                    fn_byref = false;
                }
                else if(token[i].compare("</par>")==0)
                {
                    if(fn_arg.compare("")==0)
                    {
                        end_token = i+1;
                        break;
                    }
                    fn_arg = rc_substr(fn_arg, 4, fn_arg.length()-1);
                    if(!isValidIDName(fn_arg))
                    {
                        rc_setError("Function argument is not a valid identifier name");
                        return false;
                    }
                    if(idExistsInScope(fn_arg))
                    {
                        rc_setError("Function argument identifier already exists in current scope");
                        return false;
                    }

                    if(fn_byref)
                    {
                        if(fn_arg_type == ID_TYPE_NUM)
                            fn_arg_type = ID_TYPE_BYREF_NUM;
                        else
                            fn_arg_type = ID_TYPE_BYREF_STR;
                    }

                    add_function_arg(fn_arg, fn_arg_type, "");
                    fn_arg = "";
                    fn_byref = false;
                    end_token = i+1;
                    break;
                }
                else
                {
                    rc_setError("Argument to function must be a valid identifier: " + token[i]);
                }
            }

            if(token.size()>end_token)
            {
                rc_setError("Expected end of function declaration");
                return false;
            }

        }
        else if(token[0].compare("<subp>")==0)
        {
            if(isInFunctionScope)
            {
                rc_setError("Cannot declare function from this scope");
                return false;
            }
            if(token.size()<2)
            {
                rc_setError("Expected identifier for function declaration");
                return false;
            }

            string fn_name = rc_substr(token[1], 4, token[1].length());
            if(!isValidIDName(fn_name) )
            {
                rc_setError(fn_name + " is not a valid identifier name");
                return false;
            }
            if(idExistsInScope(fn_name))
            {
                rc_setError("Identifier " + fn_name + " already exists in this scope");
                return false;
            }

            int fn_type = ID_TYPE_SUB;

            create_function(fn_name, fn_type, "");
            current_block_state = BLOCK_STATE_SUB;
            block_state.push(current_block_state);

            string fn_arg = "";
            int fn_arg_type = ID_TYPE_NUM;
            bool fn_byref = false;

            int end_token = 0;

            for(int i = 3; i < token.size(); i++)
            {
                if(token[i].compare("<byref>")==0)
                {
                    fn_byref = true;
                }
                else if(rc_substr(token[i], 0, 4).compare("<id>")==0)
                {
                    fn_arg += token[i];
                    if(fn_arg.substr(fn_arg.length()-1,1).compare("$")==0)
                        fn_arg_type = ID_TYPE_STR;
                    else
                        fn_arg_type = ID_TYPE_NUM;
                }
                else if(token[i].compare("<comma>")==0)
                {
                    fn_arg = rc_substr(fn_arg, 4, fn_arg.length()-1);
                    if(!isValidIDName(fn_arg))
                    {
                        rc_setError("Function argument is not a valid identifier name");
                        return false;
                    }
                    if(idExistsInScope(fn_arg))
                    {
                        rc_setError("Function argument identifier already exists in current scope");
                        return false;
                    }

                    if(fn_byref)
                    {
                        if(fn_arg_type == ID_TYPE_NUM)
                            fn_arg_type = ID_TYPE_BYREF_NUM;
                        else
                            fn_arg_type = ID_TYPE_BYREF_STR;
                    }

                    add_function_arg(fn_arg, fn_arg_type, "");
                    fn_arg = "";
                    fn_byref = false;
                }
                else if(token[i].compare("</par>")==0)
                {
                    if(fn_arg.compare("")==0)
                    {
                        end_token = i+1;
                        break;
                    }
                    fn_arg = rc_substr(fn_arg, 4, fn_arg.length()-1);
                    if(!isValidIDName(fn_arg))
                    {
                        rc_setError("Function argument is not a valid identifier name");
                        return false;
                    }
                    if(idExistsInScope(fn_arg))
                    {
                        rc_setError("Function argument identifier already exists in current scope");
                        return false;
                    }

                    if(fn_byref)
                    {
                        if(fn_arg_type == ID_TYPE_NUM)
                            fn_arg_type = ID_TYPE_BYREF_NUM;
                        else
                            fn_arg_type = ID_TYPE_BYREF_STR;
                    }

                    add_function_arg(fn_arg, fn_arg_type, "");
                    fn_arg = "";
                    fn_byref = false;
                    end_token = i+1;
                    break;
                }
                else
                {
                    rc_setError("Argument to function must be a valid identifier: " + token[i]);
                }
            }

            if(token.size()>end_token)
            {
                rc_setError("Expected end of function declaration");
                return false;
            }

        }
        else if(token[0].compare("<return>")==0)
        {
            string tmp_scope = current_scope;
            stack<select_data> tmp_select_stack = select_block;
            int fnID = -1;
            if(current_block_state != BLOCK_STATE_FUNCTION && current_block_state != BLOCK_STATE_SUB)
            {
                string scope_type = "";
                int scope_start = current_scope.find_last_of(".");

                while(scope_start > 0)
                {
                    scope_type = current_scope.substr(scope_start+1);

                    //cout << "\nSCOPE_TYPE->" << scope_type << endl << endl;

                    if(rc_substr(scope_type, 0, 5).compare("#FOR:")==0)
                    {
                        vm_asm.push_back("pop_loop_stack");
                    }
                    else if(rc_substr(scope_type, 0, 8).compare("#SELECT:")==0)
                    {
                        if(tmp_select_stack.top().case_type == ID_TYPE_STR)
                        {
                            vm_asm.push_back("pop$ s0"); //doesnt matter which reg I use since EXIT does not allow expressions
                        }
                        else
                        {
                            vm_asm.push_back("pop n0");
                        }
                        tmp_select_stack.pop();
                    }
                    else
                    {
                        fnID = getIDInScope_ByIndex(scope_type);

                        if(fnID < 0)
                        {
                            exit_scope(1);
                            scope_start = current_scope.find_last_of(".");
                            continue;
                        }

                        int ptr_count = 0;
                        for(int n = 0; n < id[fnID].fn_arg.size(); n++)
                        {
                            if(id[fnID].fn_arg_type[n] == ID_TYPE_BYREF_NUM || id[fnID].fn_arg_type[n] == ID_TYPE_BYREF_STR)
                            {
                                ptr_count++;
                            }
                        }

                        //if(ptr_count > 0)
                        //    vm_asm.push_back("pop_ptr !" + rc_intToString(ptr_count));

                        //cout << "\nRETURN FROM FUNCTION" << id[fnID].name << endl << endl;


                        if(id[fnID].type == ID_TYPE_FN_NUM || id[fnID].type == ID_TYPE_FN_STR)
                        {
                            break;
                        }
                        else if(id[fnID].type == ID_TYPE_SUB)
                        {
                            if(token.size() > 1)
                            {
                                rc_setError("Cannot return a value from a SUB ROUTINE, You should use a FUNCTION instead");
                                return false;
                            }
                            else
                            {
                                current_scope = tmp_scope;
                                vm_asm.push_back("return");
                                return true;
                            }
                        }
                        else
                        {
                            rc_setError("Cannot return from this scope");
                            return false;
                        }
                    }

                    exit_scope(1);
                    scope_start = current_scope.find_last_of(".");
                }

                if(fnID < 0)
                {
                    rc_setError("Cannot return outside of a FUNCTION or SUB");
                    return false;
                }

                current_scope = tmp_scope;

                //rc_setError("cannot return from outside of a function of sub routine");
                //return false;
            }

            if(id[current_fn_index].type == ID_TYPE_SUB)
            {
                if(token.size() > 1)
                {
                    rc_setError("Cannot return a value from a SUB Routine, You should use a FUNCTION instead");
                    return false;
                }
                current_scope = tmp_scope;
                vm_asm.push_back("return");
                return true;
            }

            if(!eval_expression(1, token.size()-1))
            {
                rc_setError("Could not evaluate expression");
                return false;
            }
            if(id[current_fn_index].type == ID_TYPE_FN_NUM)
            {
                if(expr_result.substr(0,1).compare("n")!=0)
                {
                    rc_setError("Must return a number");
                    return false;
                }
                vm_asm.push_back("push " + expr_result);
                vm_asm.push_back("return");
            }
            else
            {
                if(expr_result.substr(0,1).compare("s")!=0)
                {
                    rc_setError("Must return a string");
                    return false;
                }
                vm_asm.push_back("push$ " + expr_result);
                vm_asm.push_back("return");
            }
        }
        else if(token[0].compare("<exit>")==0)
        {
            string tmp_scope = current_scope;
            stack<select_data> tmp_select_stack = select_block;
            string scope_type = "";
            string exit_type = "";

            if(token.size()==1)
            {
                rc_setError("Expected {DO | FOR | WHILE} in EXIT statement");
                return false;
            }

            if(token[1].compare("<do>")==0)
                exit_type = "#DO:";
            else if(token[1].compare("<for>")==0)
                exit_type = "#FOR:";
            else if(token[1].compare("<while>")==0)
                exit_type = "#WHILE:";
            else
            {
                rc_setError("Expected {DO | FOR | WHILE} in EXIT statement");
                return false;
            }

            int scope_start = current_scope.find_last_of(".");
            bool canExit = false;

            while(scope_start > 0)
            {
                scope_type = current_scope.substr(scope_start+1);

                if(rc_substr(scope_type, 0, 5).compare("#FOR:")==0)
                {
                    vm_asm.push_back("pop_loop_stack");
                }
                else if(rc_substr(scope_type, 0, 8).compare("#SELECT:")==0)
                {
                    if(tmp_select_stack.top().case_type == ID_TYPE_STR)
                    {
                        vm_asm.push_back("pop$ s0"); //doesnt matter which reg I use since EXIT does not allow expressions
                    }
                    else
                    {
                        vm_asm.push_back("pop n0");
                    }
                    tmp_select_stack.pop();
                }

                if(scope_type.substr(0,4).compare("#DO:")==0 && exit_type.compare("#DO:")==0)
                {
                    canExit = true;
                    vm_asm.push_back("jmp @" + do_end.top());
                    break;
                }
                else if(scope_type.substr(0,5).compare("#FOR:")==0 && exit_type.compare("#FOR:")==0)
                {
                    canExit = true;
                    vm_asm.push_back("jmp @" + for_end.top());
                    break;
                }
                else if(scope_type.substr(0,7).compare("#WHILE:")==0 && exit_type.compare("#WHILE:")==0)
                {
                    canExit = true;
                    vm_asm.push_back("jmp @" + while_end.top());
                    break;
                }

                exit_scope(1);
                scope_start = current_scope.find_last_of(".");
            }

            if(!canExit)
            {
                rc_setError("Cannot EXIT this scope");
                return false;
            }
            current_scope = tmp_scope;
        }
        else if(token[0].compare("<while>")==0)
        {
            if(token.size()<2)
            {
                rc_setError("Expected expression in WHILE");
                return false;
            }
            current_block_state = BLOCK_STATE_WHILE;
            block_state.push(current_block_state);
            string start_label = current_scope + ".#WHILE:" + rc_intToString(current_while_index);
            string end_label = current_scope + ".#WEND:" + rc_intToString(current_while_index);

            current_scope = start_label;
            while_end.push(end_label);

            current_while_index++;

            vm_asm.push_back("label " + start_label);

            if(!eval_expression(1, token.size()-1))
            {
                rc_setError("Could not evaluate expression");
                return false;
            }

            if(expr_result.substr(0,1).compare("n")!=0)
            {
                rc_setError("Expected a boolean expression");
                return false;
            }

            vm_asm.push_back("while " + expr_result + " @" + end_label);

        }
        else if(token[0].compare("<wend>")==0)
        {
            if(token.size() > 1)
            {
                rc_setError("Expected end of line in WEND");
                return false;
            }
            if(current_block_state != BLOCK_STATE_WHILE)
            {
                rc_setError("Cannot use WEND outside of WHILE");
                return false;
            }
            vm_asm.push_back("jmp @" + current_scope);
            vm_asm.push_back("label " + while_end.top());
            while_end.pop();

            block_state.pop();
            current_block_state = block_state.top();
            exit_scope(1);
        }
        else if(token[0].compare("<do>")==0)
        {
            if(token.size() > 1)
            {
                rc_setError("Expected end of line in DO");
                return false;
            }
            current_block_state = BLOCK_STATE_DO;
            block_state.push(current_block_state);
            string start_label = current_scope + ".#DO:" + rc_intToString(current_do_index);
            string end_label = current_scope + ".#LOOP:" + rc_intToString(current_do_index);

            current_scope = start_label;
            do_end.push(end_label);

            current_do_index++;

            vm_asm.push_back("label " + start_label);
        }
        else if(token[0].compare("<loop>")==0)
        {
            if(current_block_state != BLOCK_STATE_DO)
            {
                rc_setError("Cannot use LOOP outside of DO");
                return false;
            }
            if(token.size()==1)
            {
                vm_asm.push_back("loop @" + current_scope);
                vm_asm.push_back("label " + do_end.top());
                do_end.pop();

                block_state.pop();
                current_block_state = block_state.top();
                exit_scope(1);

            }
            else if(token[1].compare("<while>")==0)
            {
                if(!eval_expression(2, token.size()-1))
                {
                    rc_setError("Could not evaluate expression");
                    return false;
                }
                if(expr_result.substr(0,1).compare("n")!=0)
                {
                    rc_setError("Expected boolean expression: " + expr_result);
                    return false;
                }
                vm_asm.push_back("loop_while " + expr_result + " @" + current_scope);
                vm_asm.push_back("label " + do_end.top());
                do_end.pop();

                block_state.pop();
                current_block_state = block_state.top();
                exit_scope(1);
            }
            else if(token[1].compare("<until>")==0)
            {
                if(!eval_expression(2, token.size()-1))
                {
                    rc_setError("Could not evaluate expression");
                    return false;
                }
                if(expr_result.substr(0,1).compare("n")!=0)
                {
                    rc_setError("Expected boolean expression");
                    return false;
                }
                vm_asm.push_back("loop_until " + expr_result + " @" + current_scope);
                vm_asm.push_back("label " + do_end.top());
                do_end.pop();

                block_state.pop();
                current_block_state = block_state.top();
                exit_scope(1);
            }
            else
            {
                rc_setError("Illegal Syntax");
                return false;
            }
        }
        else if(token[0].compare("<for>")==0)
        {
            current_block_state = BLOCK_STATE_FOR;
            block_state.push(BLOCK_STATE_FOR);
            string start_label = current_scope + ".#FOR:" + rc_intToString(current_for_index);
            string end_label = current_scope +".#NEXT:" + rc_intToString(current_for_index);

            current_scope  = start_label;
            for_end.push(end_label);

            current_for_index++;

            for(int i = token.size(); i < 6; i++)
                token.push_back("");

            int counter_id = -1;
            string counter_var = "";
            string start_value = "";
            string end_value = "";
            string step_value = "";
            if(rc_substr(token[1], 0, 4).compare("<id>")==0)
            {
                counter_var = token[1].substr(4);
                counter_id = getIDInScope_ByIndex(counter_var);
                if(counter_id < 0)
                {
                    if(!isValidIDName(counter_var) || rc_substr(counter_var, counter_var.length()-1,1).compare("$")==0)
                    {
                        rc_setError("Invalid identifier name in FOR");
                        return false;
                    }
                    if(isInFunctionScope)
                    {
                        if(!create_function_variable(counter_var, ID_TYPE_NUM,""))
                        {
                            rc_setError("could not create identifier " + counter_var);
                            return false;
                        }
                    }
                    else if(!create_variable(counter_var, ID_TYPE_NUM))
                    {
                        rc_setError("Could not create identifier " + counter_var);
                        return false;
                    }
                }
                else if(id[counter_id].type != ID_TYPE_NUM && id[counter_id].type != ID_TYPE_BYREF_NUM && id[counter_id].type != ID_TYPE_ARR_NUM)
                {
                    rc_setError("Expected number identifier in for");
                    return false;
                }
                else if(id[counter_id].type == ID_TYPE_ARR_NUM && token[2].compare("<square>") != 0)
                {
                    rc_setError("Expected \"[\" in array");
                    return false;
                }
                counter_id = getIDInScope_ByIndex(counter_var);
                for_counter.push(counter_id);

            }
            else
            {
                rc_setError("Expected identifier after FOR");
                return false;
            }

            int for_equal_op_offset = 2;
            int for_counter_args = 0;

            if(id[counter_id].type == ID_TYPE_ARR_NUM || id[counter_id].type == ID_TYPE_BYREF_NUM)
            {
                if(token[2].compare("<square>") == 0)
                {
                    int f_scope = 1;
                    int token_start = 2;
                    int token_end = 3;
                    multi_arg[0] = "";
                    multi_arg[1] = "";
                    multi_arg[2] = "";
                    multi_arg_count = 0;
                    for(int i = 3; i < token.size(); i++)
                    {
                        if(token[i].compare("<square>")==0)
                            f_scope++;
                        else if(token[i].compare("</square>")==0)
                            f_scope--;
                        if(f_scope == 0)
                        {
                            token_end = i;
                            for_equal_op_offset = i+1;
                            if(token[for_equal_op_offset].compare("<equal>")==0)
                                break;
                            else
                            {
                                rc_setError("Expected \"=\" in FOR");
                                return false;
                            }
                        }
                    }
                    if(!eval_expression(token_start, token_end, true))
                    {
                        rc_setError("Error evaluating counter in FOR");
                        return false;
                    }

                    if(id[counter_id].type == ID_TYPE_ARR_NUM && id[counter_id].num_args != multi_arg_count)
                    {
                        rc_setError("Invalid number of dimensions in FOR counter array");
                        return false;
                    }
                    else if(id[counter_id].type == ID_TYPE_BYREF_NUM && multi_arg_count != 1)
                    {
                        rc_setError("Expected 1 argument in FOR counter ByRef array");
                        return false;
                    }

                    switch(multi_arg_count)
                    {
                        case 1:
                            vm_asm.push_back("for_offset_arr1 " + multi_arg[0]);
                            break;
                        case 2:
                            vm_asm.push_back("for_offset_arr2 " + multi_arg[0] + " " + multi_arg[1]);
                            break;
                        case 3:
                            vm_asm.push_back("for_offset_arr3 " + multi_arg[0] + " " + multi_arg[1] + " " + multi_arg[2]);
                            break;
                    }

                    for(int i = token_start; i <= token_end; i++)
                    {
                        //cout << "remove token: " << token[i] << endl;
                        token[i] = "";
                    }

                }
                else
                    vm_asm.push_back("for_offset_0");
            }

            if(token[for_equal_op_offset].compare("<equal>")!=0)
            {
                rc_setError("Expected = in FOR");
                return false;
            }
            int ft_count = 0;
            string ftokens[] = {"", ""};
            for(int i = for_equal_op_offset+1; i < token.size(); i++)
            {
                if(token[i].compare("<to>")==0 || token[i].compare("<step>")==0)
                {
                    if(ft_count >= 2)
                    {
                        rc_setError("Illegal Syntax in FOR");
                        return false;
                    }
                    ftokens[ft_count] = token[i];
                    ft_count++;
                    token[i] = "!<comma>";
                }
            }
            if(ftokens[0].compare("<to>")!=0)
            {
                rc_setError("Expected to after initialize expression");
                return false;
            }
            if(ftokens[1].compare("<step>")!=0 && ftokens[1].compare("") != 0)
            {
                rc_setError("Expected STEP or end of FOR line");
                return false;
            }

            if(!eval_expression(for_equal_op_offset+1, token.size()-1, true))
            {
                rc_setError("Could not evaluate expression");
                return false;
            }

            start_value = multi_arg[0];
            end_value = multi_arg[1];

            if(multi_arg_count == 2)
            {
                step_value = "n" + rc_intToString(n_reg);
                vm_asm.push_back("mov " + step_value + " 1");
            }
            else if(multi_arg_count == 3)
            {
                step_value = multi_arg[2];
            }
            else
            {
                rc_setError("To many arguments in FOR");
                return false;
            }

            if(start_value.substr(0,1).compare("n")!=0 || end_value.substr(0,1).compare("n")!=0 || step_value.substr(0,1).compare("n")!=0)
            {
                rc_setError("Expected number expression in FOR");
                return false;
            }

            //cout << "FOR_RESULT" << endl << "------------------" << endl;
            //cout << "identifier = " << id[counter_id].vec_pos << endl;
            //cout << "start = " << start_value << endl;
            //cout << "end = " << end_value << endl;
            //cout << "step = " << step_value << endl << endl;

            if(for_counter.size() > max_for_count)
                max_for_count = for_counter.size();

            vm_asm.push_back("for !" + rc_intToString(id[counter_id].vec_pos) + " " + start_value + " " + end_value + " " + step_value);
            vm_asm.push_back("label " + start_label);


        }
        else if(token[0].compare("<next>")==0)
        {
            if(current_block_state != BLOCK_STATE_FOR)
            {
                rc_setError("Cannot use NEXT outside of a FOR loop");
                return false;
            }
            if(token.size() > 1)
            {
                rc_setError("Expected end of line in NEXT");
                return false;
            }
            uint64_t counter_id = for_counter.top();
            for_counter.pop();
            string next_label = for_end.top();
            for_end.pop();
            block_state.pop();
            current_block_state = block_state.top();
            vm_asm.push_back("next @" + current_scope);
            vm_asm.push_back("label " + next_label);
            exit_scope(1);
        }
        else if(token[0].compare("<if>")==0)
        {
            current_block_state = BLOCK_STATE_IF;
            block_state.push(current_block_state);

            if_data if_start;

            if_start.index = current_if_index;
            if_start.condition = 0;

            if_block.push(if_start);

            string start_label = current_scope + ".#IF:" + rc_intToString(if_start.index);

            current_scope = start_label;

            int if_then = -1;

            for(int i = 0; i < token.size(); i++)
            {
                if(token[i].compare("<then>")==0)
                {
                    if_then = i;
                    break;
                }
            }


            if(if_then < 0)
            {
                rc_setError("Expected THEN in IF statement");
                return false;
            }

            if(token.size() > (if_then+1))
            {
                rc_setError("Expected End of Line after THEN");
                return false;
            }

            if(if_then < 2)
            {
                rc_setError("Expected expression in IF");
                return false;
            }

            if(!eval_expression(1, if_then-1))
            {
                rc_setError("Could not evaluate expression");
                return false;
            }

            if(expr_result.substr(0,1).compare("n")!=0)
            {
                rc_setError("Expected Boolean expression");
                return false;
            }

            string else_label = "ELSE:" + rc_intToString(if_block.top().index) + "->CONDITION:" + rc_intToString(if_block.top().condition);

            vm_asm.push_back("cmp " + expr_result + " 0");
            vm_asm.push_back("je @" + else_label);
            //vm_asm.push_back("");
            current_if_index++;

        }
        else if(token[0].compare("<elseif>")==0)
        {
            if(if_block.top().else_set)
            {
                rc_setError("Cannot use ELSEIF after ELSE in the same IF Block");
                return false;
            }
            string start_label = "ELSE:" + rc_intToString(if_block.top().index) + "->CONDITION:" + rc_intToString(if_block.top().condition);
            vm_asm.push_back("jmp @ENDIF:" + rc_intToString(if_block.top().index) );
            vm_asm.push_back("label " + start_label);
            if_block.top().condition++;

            exit_scope(1);

            current_scope += ".#" + start_label;

            int if_then = -1;

            for(int i = 0; i < token.size(); i++)
            {
                if(token[i].compare("<then>")==0)
                {
                    if_then = i;
                    break;
                }
            }


            if(if_then < 0)
            {
                rc_setError("Expected THEN in IF statement");
                return false;
            }

            if(token.size() > (if_then+1))
            {
                rc_setError("Expected End of Line after THEN");
                return false;
            }

            if(if_then < 2)
            {
                rc_setError("Expected expression in IF");
                return false;
            }

            if(!eval_expression(1, if_then-1))
            {
                rc_setError("Could not evaluate expression");
                return false;
            }

            if(expr_result.substr(0,1).compare("n")!=0)
            {
                rc_setError("Expected Boolean expression");
                return false;
            }

            string else_label = "ELSE:" + rc_intToString(if_block.top().index) + "->CONDITION:" + rc_intToString(if_block.top().condition);

            vm_asm.push_back("cmp " + expr_result + " 0");
            vm_asm.push_back("je @" + else_label);
            //vm_asm.push_back("");
        }
        else if(token[0].compare("<else>")==0)
        {
            if(token.size()>1)
            {
                rc_setError("Expected end of line in ELSE");
                return false;
            }

            string start_label = "ELSE:" + rc_intToString(if_block.top().index) + "->CONDITION:" + rc_intToString(if_block.top().condition);
            vm_asm.push_back("jmp @ENDIF:" + rc_intToString(if_block.top().index) );
            vm_asm.push_back("label " + start_label);
            //vm_asm.push_back("");
            if_block.top().else_set = true;
            if_block.top().condition++;

            exit_scope(1);

            current_scope += ".#" + start_label;

        }
        else if(token[0].compare("<select>")==0)
        {
            if(token.size() < 3)
            {
                rc_setError("Incomplete SELECT CASE statement");
                return false;
            }
            if(token[1].compare("<case>")!=0)
            {
                rc_setError("Expected CASE in SELECT CASE statement");
                return false;
            }
            if(!eval_expression(2, token.size()-1))
            {
                rc_setError("Could not evaluate expression");
                return false;
            }
            select_data select_start;
            select_start.index = current_select_index;
            select_start.case_index = 0;
            select_start.default_set = false;
            if(expr_result.substr(0,1).compare("s")==0)
            {
                select_start.case_type = ID_TYPE_STR;
                vm_asm.push_back("push$ " + expr_result);
            }
            else
            {
                select_start.case_type = ID_TYPE_NUM;
                vm_asm.push_back("push " + expr_result);
            }

            select_block.push(select_start);
            string select_label = "SELECT:" + rc_intToString(select_block.top().index) + "->CASE:" + rc_intToString(select_block.top().case_index);

            vm_asm.push_back("jmp @" + select_label);

            current_select_index++;
            current_scope += ".#" + select_label;
            current_block_state = BLOCK_STATE_SELECT;
            block_state.push(current_block_state);

            //vm_asm.push_back("");

        }
        else if(token[0].compare("<case>")==0)
        {
            if(token.size()==1)
            {
                rc_setError("Expected expression in CASE");
                return false;
            }
            if(current_block_state != BLOCK_STATE_SELECT)
            {
                rc_setError("Cannot set CASE outside of a SELECT BLOCK");
                return false;
            }


            select_block.top().case_set = true;

            string compare_case = "";

            string case_end = "SELECT:" + rc_intToString(select_block.top().index) + "->END";
            string case_label = "SELECT:" + rc_intToString(select_block.top().index) + "->CASE:" + rc_intToString(select_block.top().case_index);
            exit_scope(1);
            current_scope += ".#" + case_label;

            select_block.top().case_index++;
            string next_case_label = "SELECT:" + rc_intToString(select_block.top().index) + "->CASE:" + rc_intToString(select_block.top().case_index);

            vm_asm.push_back("jmp @" + case_end);
            vm_asm.push_back("label " + case_label);

            if(select_block.top().case_type==ID_TYPE_STR)
            {
                compare_case = "s" + rc_intToString(s_reg);
                vm_asm.push_back("pop$ " + compare_case);
                vm_asm.push_back("push$ " + compare_case);
                inc_s(1);
            }
            else
            {
                compare_case = "n" + rc_intToString(n_reg);
                vm_asm.push_back("pop " + compare_case);
                vm_asm.push_back("push " + compare_case);
                inc_n(1);
            }
            for(int i = 0; i < token.size(); i++)
            {
                if(token[i].compare("<comma>")==0)
                    token[i] = "!<comma>";
            }
            if(!eval_expression(1, token.size()-1, true))
            {
                rc_setError("Could not evaluate expression");
                return false;
            }
            string case_reg_type = "n";
            if(select_block.top().case_type == ID_TYPE_STR)
                case_reg_type = "s";

            string cmp_or_result = "n" + rc_intToString(n_reg);
            inc_n(1);

            string case_flag_result = "n" + rc_intToString(n_reg);
            inc_n(1);

            vm_asm.push_back("mov " + cmp_or_result + " 0");

            for(int i = 0; i < multi_arg_count; i++)
            {
                if(multi_arg[i].substr(0,1).compare(case_reg_type)!=0)
                {
                    rc_setError("Mismatch type in CASE: " + multi_arg[i]);
                    return false;
                }
                if(case_reg_type.compare("s")==0)
                {
                    vm_asm.push_back("cmp$ " + compare_case + " " + multi_arg[i]);
                    vm_asm.push_back("mov " + case_flag_result + " %EQUAL_FLAG");
                    vm_asm.push_back("or " + cmp_or_result + " " + case_flag_result);
                }
                else
                {
                    vm_asm.push_back("cmp " + compare_case + " " + multi_arg[i]);
                    vm_asm.push_back("mov " + case_flag_result + " %EQUAL_FLAG");
                    vm_asm.push_back("or " + cmp_or_result + " " + case_flag_result);
                }
            }
            vm_asm.push_back("cmp " + cmp_or_result + " 0");
            vm_asm.push_back("je @" + next_case_label);
            //vm_asm.push_back("");
        }
        else if(token[0].compare("<default>")==0)
        {
            if(token.size()>1)
            {
                rc_setError("Expected End of Line for default");
                return false;
            }
            if(current_block_state != BLOCK_STATE_SELECT)
            {
                rc_setError("Cannot set DEFAULT outside of a SELECT BLOCK");
                return false;
            }


            select_block.top().case_set = true;

            string compare_case = "";

            string case_end = "SELECT:" + rc_intToString(select_block.top().index) + "->END";
            string case_label = "SELECT:" + rc_intToString(select_block.top().index) + "->CASE:" + rc_intToString(select_block.top().case_index);
            exit_scope(1);
            current_scope += ".#" + case_label;

            select_block.top().case_index++;
            string next_case_label = "SELECT:" + rc_intToString(select_block.top().index) + "->CASE:" + rc_intToString(select_block.top().case_index);

            vm_asm.push_back("jmp @" + case_end);
            vm_asm.push_back("label " + case_label);

            //vm_asm.push_back("");
        }
        else if(token[0].compare("<print>")==0)
        {
            string last_token = token[token.size()-1];
            if(token.size()==1)
            {
                rc_setError("Expected expression for PRINT");
                return false;
            }
            int start_token = 1;
            if(token[token.size()-1].compare("<semi>")!=0)
                token.push_back("<semi>");
            for(int i = 0; i < token.size(); i++)
            {
                if(token[i].compare("<semi>")==0)
                {
                    token[i] = "";
                    if(!eval_expression(start_token, i))
                    {
                        rc_setError("Could not evaluate expression");
                        output_tokens();
                        cout << endl << endl;
                        return false;
                    }
                    if(expr_result.substr(0,1).compare("n")==0)
                        vm_asm.push_back("print " + expr_result);
                    else
                        vm_asm.push_back("print$ " + expr_result);
                    start_token = i;
                }
            }
            if(start_token < (token.size()-1 ) )
            {
                if(!eval_expression(start_token, token.size()-1))
                {
                    rc_setError("Could not evaluate expression");
                    return false;
                }
                if(expr_result.substr(0,1).compare("n")==0)
                    vm_asm.push_back("print " + expr_result);
                else
                    vm_asm.push_back("print$ " + expr_result);
            }
            if(last_token.compare("<semi>")!=0)
                vm_asm.push_back("println");
        }
        else if(token[0].compare("<delete>")==0)
        {
            if(token.size() != 2)
            {
                rc_setError("Expected single identifier in DELETE statement");
                return false;
            }
            if(token[1].substr(0,4).compare("<id>")!=0)
            {
                rc_setError("Expected single identifier in DELETE statement");
                return false;
            }
            int id_index = getIDInScope_ByIndex(token[1].substr(4));
            if(id_index < 0)
            {
                rc_setError("Identifier does not exists in current scope");
                return false;
            }
            if(id[id_index].type == ID_TYPE_ARR_NUM || id[id_index].type == ID_TYPE_NUM)
            {
                vm_asm.push_back("delete !" + rc_intToString(id[id_index].vec_pos));
            }
            else if(id[id_index].type == ID_TYPE_ARR_STR || id[id_index].type == ID_TYPE_STR)
            {
                vm_asm.push_back("delete$ !" + rc_intToString(id[id_index].vec_pos));
            }
            else
            {
                rc_setError("Cannot delete identifier of this type");
                return false;
            }
            id[id_index].name = "";
        }
        else if(token.size() > 2)
        {
            //cout << "token[1] = " << token[1] << endl;
            if(token[1].compare("<equal>")==0)
            {
                string var_id = "";
                int var_type = ID_TYPE_NUM;
                int var_ut_index = -1;
                int var_id_index = -1;

                if(rc_substr(token[0], 0, 1).compare("n")==0 || rc_substr(token[0], 0, 1).compare("s")==0)
                {
                    for(int i = 0; i < resolveID_id_reg.size(); i++)
                    {
                        if(resolveID_id_reg[i].compare(token[0])==0)
                        {
                            var_id = "~" + token[0];
                            if(token[0].substr(0,1).compare("s")==0)
                                var_type = ID_TYPE_STR;
                            else if(resolveID_id_type[i] == ID_TYPE_USER)
                            {
                                var_type = ID_TYPE_USER;
                                var_ut_index = resolveID_id_ut_index[i];
                            }
                            else
                                var_type = resolveID_id_type[i];
                            break;
                        }
                    }
                    if(var_id.compare("")==0)
                    {
                        rc_setError("Expected identifier for variable assignment");
                        return false;
                    }
                }
                else if(rc_substr(token[0], 0, 4).compare("<id>")==0)
                {
                    var_id = token[0].substr(4);
                    var_type = (var_id.substr(var_id.length()-1).compare("$")==0) ? ID_TYPE_STR : ID_TYPE_NUM; //length() will always be atleast 1 so there is no need to check

//                    if(var_id.substr(var_id.length()-1,1).compare("$")==0)
//                    {
//                        //cout << "looking for: " << var_id.substr(0, var_id.length()-1) << endl;
//                        var_id_index = getIDInScope(var_id.substr(0, var_id.length()-1));
//                        if(var_id_index >= 0)
//                            var_type = id[var_id_index].type;
//                        //cout << "var_index = " << var_id_index << endl;
//                    }
                    if(var_id_index < 0)
                    {
                        var_id_index = getIDInScope_ByIndex(var_id);
                        if(var_id_index >= 0)
                            var_type = id[var_id_index].type;
                    }

                    if(var_id_index < 0)
                    {
                        if(!isValidIDName(var_id))
                        {
                            rc_setError(var_id + " is not a valid identifier");
                            return false;
                        }
                        if(isInFunctionScope)
                        {
                            if(!create_function_variable(var_id, var_type, ""))
                            {
                                rc_setError("Could not create " + var_id);
                                return false;
                            }
                        }
                        else if(!create_variable(var_id, var_type))
                        {
                            rc_setError("Could not create " + var_id);
                            return false;
                        }

                        var_id_index = getIDInScope_ByIndex(var_id);

                        if(var_id_index < 0)
                        {
                            rc_setError("Unexpected error");
                            return false;
                        }
                    }
                }

                if(var_type == ID_TYPE_BYREF_NUM)
                    var_type = ID_TYPE_NUM;
                else if(var_type == ID_TYPE_BYREF_STR)
                    var_type = ID_TYPE_STR;

                if(var_type != ID_TYPE_NUM && var_type != ID_TYPE_STR)
                {
                    bool id_type_match = false;
                    if(token.size()!=3)
                    {
                        rc_setError("Expected identifier of same type in assignment");
                        return false;
                    }

                    for(int i = 0; i < resolveID_id_reg.size(); i++)
                    {
                        if(resolveID_id_reg[i].compare(token[2])==0)
                        {
                            if(resolveID_id_type[i] == var_type)
                            {
                                if(var_type == ID_TYPE_USER && var_ut_index == resolveID_id_ut_index[i])
                                {
                                    id_type_match = true;
                                }
                                else if(var_type == ID_TYPE_ARR_NUM || var_type == ID_TYPE_ARR_STR)
                                {
                                    id_type_match = true;
                                }
                            }
                        }
                    }

                    if(!id_type_match)
                    {
                        rc_setError("Expected identifier of same type in assignment");
                        return false;
                    }

                    vm_asm.push_back("mov_type " + var_id.substr(1) + " " + token[2]);

                    return true;
                }

                if(!eval_expression(2))
                {
                    rc_setError("Could not evaluate expression");
                    return false;
                }

                if(var_type == ID_TYPE_NUM && expr_result.substr(0,1).compare("n")!=0 )
                {
                    rc_setError("Must set number variable to number expression");
                    return false;
                }
                else if(var_type == ID_TYPE_STR && expr_result.substr(0,1).compare("s")!=0 )
                {
                    rc_setError("Must set string variable to string expression");
                    return false;
                }

                if(var_id.substr(0,1).compare("~")==0)
                {
                    switch(var_type)
                    {
                        case ID_TYPE_NUM:
                            vm_asm.push_back("mov_r " + var_id.substr(1) + " " + expr_result);
                            break;
                        case ID_TYPE_STR:
                            vm_asm.push_back("mov_r$ " + var_id.substr(1) + " " +expr_result);
                            break;
                        default:
                            //cout << "VAR_TYPE = " << var_type << endl;
                            break;
                    }
                }
                else
                {
                    switch(var_type)
                    {
                        case ID_TYPE_NUM:
                            vm_asm.push_back("mov !" + rc_intToString(id[var_id_index].vec_pos) + " " + expr_result);
                            break;
                        case ID_TYPE_STR:
                            vm_asm.push_back("mov$ !" + rc_intToString(id[var_id_index].vec_pos) + " " + expr_result);
                            break;
                    }
                }

            }
            else if(rc_substr(token[0], 0, 4).compare("<id>")==0 && token.size() > 5)
            {
                //cout << "dbg 1" << endl;
                int expr_id = getIDInScope_ByIndex(token[0].substr(4));

                if(expr_id < 0)
                {
                    rc_setError("Identifier " + token[0].substr(4) + " was not declared in this scope");
                    return false;
                }

                int start_token = 0;
                int end_token = 0;

                int s_scope = 1;

                if(token[1].compare("<square>")==0)
                {
                    for(int i = 2; i < token.size(); i++)
                    {
                        if(token[i].compare("</square>")==0)
                            s_scope--;
                        else if(token[i].compare("<square>")==0)
                            s_scope++;
                        if(s_scope == 0)
                        {
                            end_token = i;

                            //for(int i2 = start_token; i2 <= end_token; i2++)
                            //    cout << "token: " << i2 << token[i2] << endl;

                            break;
                        }
                    }
                    if(s_scope != 0)
                    {
                        rc_setError("Expected ] in array assignment");
                        return false;
                    }
                }
                else
                {
                    //cout << "dbg 2" << endl;
                    if(!eval_expression())
                    {
                        rc_setError("^Could not evaluate expression");
                        return false;
                    }
                }

                if(!eval_expression(start_token, end_token))
                {
                    rc_setError("Could not resolve array identifier");
                    return false;
                }

                string var = expr_result;
                end_token++;
                bool isAssignment = false;

                if(token.size()>end_token)
                {
                    if(token[end_token].compare("<equal>")==0)
                    {
                        isAssignment = true;
                        start_token = end_token+1;
                    }
                }


                string var_result = "";
                if(isAssignment)
                {
                    if(!eval_expression(start_token, token.size()-1))
                    {
                        rc_setError("Could not evaluate expression");
                        return false;
                    }

                    if(var.substr(0,1).compare("n")==0 && expr_result.substr(0,1).compare("n")==0)
                    {
                        vm_asm.push_back("mov_r " + var + " " + expr_result);
                        return true;
                    }
                    else if(var.substr(0,1).compare("s")==0 && expr_result.substr(0,1).compare("s")==0)
                    {
                        vm_asm.push_back("mov_r$ " + var + " " + expr_result);
                        return true;
                    }
                    else
                    {
                        rc_setError("Identifier type does not match assignment type");
                        return false;
                    }

                }
                else
                {
                    if(!eval_expression(start_token, token.size()-1))
                    {
                        rc_setError("Could not evaluate expression");
                        return false;
                    }
                }

            }
            else
            {
                //cout << "debug problem here" << endl;
                //output_tokens();
                if(!eval_expression())
                {
                    rc_setError("-+Could not evaluate expression");
                    return false;
                }
            }
        }
        else
        {
            if(!eval_expression(0, token.size()-1))
            {
                rc_setError("Could not evaluate expression");
                return false;
            }
            //cout <<"THIS IS A TEST" << endl;
        }
    }
    return true;
}

bool check_rule_embedded()
{
    if(token.size() > 0)
    {
        if(token[0].compare("<function>")==0)
        {
            if(token.size()<2)
            {
                rc_setError("Expected identifier for function declaration");
                return false;
            }

            string fn_name = rc_substr(token[1], 4, token[1].length());
            if(!isValidIDName(fn_name) )
            {
                rc_setError(fn_name + " is not a valid identifier name");
                return false;
            }
            if(idExistsInScope(fn_name))
            {
                rc_setError("Identifier " + fn_name + " already exists in this scope");
                return false;
            }

            int fn_type = ID_TYPE_FN_NUM;
            if(fn_name.substr(fn_name.length()-1,1).compare("$")==0)
                fn_type = ID_TYPE_FN_STR;

            embed_function(fn_name, fn_type);
            current_block_state = BLOCK_STATE_FUNCTION;
            block_state.push(current_block_state);

            string fn_arg = "";
            int fn_arg_type = ID_TYPE_NUM;
            bool fn_byref = false;

            int end_token = 0;

            for(int i = 3; i < token.size(); i++)
            {
                if(token[i].compare("<byref>")==0)
                {
                    fn_byref = true;
                }
                else if(rc_substr(token[i], 0, 4).compare("<id>")==0)
                {
                    fn_arg += token[i];
                    if(fn_arg.substr(fn_arg.length()-1,1).compare("$")==0)
                        fn_arg_type = ID_TYPE_STR;
                    else
                        fn_arg_type = ID_TYPE_NUM;
                }
                else if(token[i].compare("<comma>")==0)
                {
                    fn_arg = rc_substr(fn_arg, 4, fn_arg.length()-1);
                    if(!isValidIDName(fn_arg))
                    {
                        rc_setError("Function argument is not a valid identifier name");
                        return false;
                    }
                    if(idExistsInScope(fn_arg))
                    {
                        rc_setError("Function argument identifier already exists in current scope");
                        return false;
                    }

                    if(fn_byref)
                    {
                        if(fn_arg_type == ID_TYPE_NUM)
                            fn_arg_type = ID_TYPE_BYREF_NUM;
                        else
                            fn_arg_type = ID_TYPE_BYREF_STR;
                    }

                    add_embedded_arg(fn_arg, fn_arg_type);
                    fn_arg = "";
                    fn_byref = false;
                }
                else if(token[i].compare("</par>")==0)
                {
                    if(fn_arg.compare("")==0)
                    {
                        end_token = i+1;
                        break;
                    }
                    fn_arg = rc_substr(fn_arg, 4, fn_arg.length()-1);
                    if(!isValidIDName(fn_arg))
                    {
                        rc_setError("Function argument is not a valid identifier name");
                        return false;
                    }
                    if(idExistsInScope(fn_arg))
                    {
                        rc_setError("Function argument identifier already exists in current scope: " + fn_arg + " -> " + current_scope + " ? ");
                        return false;
                    }

                    if(fn_byref)
                    {
                        if(fn_arg_type == ID_TYPE_NUM)
                            fn_arg_type = ID_TYPE_BYREF_NUM;
                        else
                            fn_arg_type = ID_TYPE_BYREF_STR;
                    }

                    add_embedded_arg(fn_arg, fn_arg_type);
                    fn_arg = "";
                    fn_byref = false;
                    end_token = i+1;
                    break;
                }
                else
                {
                    rc_setError("Argument to function must be a valid identifier: " + token[i]);
                    return false;
                }
            }

            current_block_state = BLOCK_STATE_MAIN;
            current_scope = "main";
            block_state.pop();
            isInFunctionScope = false;
            current_fn_index++;

            if(token.size()>end_token)
            {
                rc_setError("Expected end of function declaration");
                return false;
            }

        }
        else if(token[0].compare("<subp>")==0)
        {
            if(token.size()<2)
            {
                rc_setError("Expected identifier for function declaration");
                return false;
            }

            string fn_name = rc_substr(token[1], 4, token[1].length());
            if(!isValidIDName(fn_name) )
            {
                rc_setError(fn_name + " is not a valid identifier name");
                return false;
            }
            if(idExistsInScope(fn_name))
            {
                rc_setError("Identifier " + fn_name + " already exists in this scope");
                return false;
            }

            int fn_type = ID_TYPE_SUB;

            embed_function(fn_name, fn_type);
            current_block_state = BLOCK_STATE_SUB;
            block_state.push(current_block_state);

            string fn_arg = "";
            int fn_arg_type = ID_TYPE_NUM;
            bool fn_byref = false;

            int end_token = 0;

            for(int i = 3; i < token.size(); i++)
            {
                if(token[i].compare("<byref>")==0)
                {
                    fn_byref = true;
                }
                else if(rc_substr(token[i], 0, 4).compare("<id>")==0)
                {
                    fn_arg += token[i];
                    if(fn_arg.substr(fn_arg.length()-1,1).compare("$")==0)
                        fn_arg_type = ID_TYPE_STR;
                    else
                        fn_arg_type = ID_TYPE_NUM;
                }
                else if(token[i].compare("<comma>")==0)
                {
                    fn_arg = rc_substr(fn_arg, 4, fn_arg.length()-1);
                    if(!isValidIDName(fn_arg))
                    {
                        rc_setError("Function argument is not a valid identifier name");
                        return false;
                    }
                    if(idExistsInScope(fn_arg))
                    {
                        rc_setError("Function argument identifier already exists in current scope");
                        return false;
                    }

                    if(fn_byref)
                    {
                        if(fn_arg_type == ID_TYPE_NUM)
                            fn_arg_type = ID_TYPE_BYREF_NUM;
                        else
                            fn_arg_type = ID_TYPE_BYREF_STR;
                    }

                    add_embedded_arg(fn_arg, fn_arg_type);
                    fn_arg = "";
                    fn_byref = false;
                }
                else if(token[i].compare("</par>")==0)
                {
                    if(fn_arg.compare("")==0)
                    {
                        end_token = i+1;
                        break;
                    }
                    fn_arg = rc_substr(fn_arg, 4, fn_arg.length()-1);
                    if(!isValidIDName(fn_arg))
                    {
                        rc_setError("Function argument is not a valid identifier name");
                        return false;
                    }
                    if(idExistsInScope(fn_arg))
                    {
                        rc_setError("Function argument identifier already exists in current scope");
                        return false;
                    }

                    if(fn_byref)
                    {
                        if(fn_arg_type == ID_TYPE_NUM)
                            fn_arg_type = ID_TYPE_BYREF_NUM;
                        else
                            fn_arg_type = ID_TYPE_BYREF_STR;
                    }

                    add_embedded_arg(fn_arg, fn_arg_type);
                    fn_arg = "";
                    fn_byref = false;
                    end_token = i+1;
                    break;
                }
                else
                {
                    rc_setError("Argument to function must be a valid identifier: " + token[i]);
                    return false;
                }
            }

            current_block_state = BLOCK_STATE_MAIN;
            current_scope = "main";
            block_state.pop();
            isInFunctionScope = false;
            current_fn_index++;

            if(token.size()>end_token)
            {
                rc_setError("Expected end of function declaration");
                return false;
            }

        }
    }
    return true;
}

#endif // PARSER_H_INCLUDED
