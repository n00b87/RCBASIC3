#include <iostream>
#include "tokenizer.h"
#include "parser.h"

using namespace std;

void rcbasic_init()
{
    create_type("null");
    create_type("tst");
    add_type_member("x", ID_TYPE_NUM, "", 0,0,0,0);
    add_type_member("y", ID_TYPE_NUM, "", 0,3,4,0);
    create_type("t2");
    add_type_member("t", ID_TYPE_USER, "tst", 2, 5, 0, 0);
    create_variable("var", ID_TYPE_USER, "t2");
    create_variable("mc", ID_TYPE_NUM, "");
    create_variable("womp", ID_TYPE_USER, "t2");
}

int main(void)
{
    string line = "";
    rcbasic_init();

    string null_str;
    int null_int;

    //output_vars();
    //return 0;

    //line = "var.t[5,2].y + var.t[0,0].x + 7 ";
    //resolveUserIDs(line);
    //cout << endl << "ASM OUTPUT" << endl;
    //debug_output_VMASM();
    //cout << endl << "Final Line = " << line << endl << endl;

    //clearTokens();
    //tokens(line);
    //output_tokens();

    //eval_expression();

    //cout << "Final ASM" << endl;
    //debug_output_VMASM();

    //return 0;

    while(getline(cin, line))
    {
        if(line.compare("#var")==0)
        {
            output_vars();
            continue;
        }
        if(!resolveUserIDs(line))
        {
            cout << "Error: User ids are fucked up" << endl;
        }
        else
        {
            cout << "@Resolve = " << line << endl;
        }
        if(!tokens(line))
            cout << "Error1: " << rc_getError() << endl;
        if(!check_rule())
            cout << "ERROR:" << rc_getError() << endl;

        //if(!eval_expression())
        //    cout << "Error2: " << rc_getError() << endl;
        cout << endl << endl << "----TOKENS-----" << endl;
        output_tokens();
        cout << endl << endl << "VM CODE" << endl;
        debug_output_VMASM();
        clearTokens();
        //clear_asm();
    }
    return 0;
}
