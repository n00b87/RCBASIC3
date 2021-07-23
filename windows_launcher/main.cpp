#include <iostream>
#include <stdio.h>

#include "file_directory.h"

using namespace std;


int main(int argc, char *argv[])
{
    string dp = argv[0];
    int parent_dir_index = dp.find_last_of("\\");
    //cout << "parent dir = " << parent_dir_index << endl;
    dp = (parent_dir_index != string::npos) ? dp.substr(0, parent_dir_index) : ".";
    dp = rc_absFilePath(dp);

    string cmd = "cd \"" + dp + "\\assets\" && " + "\"" + dp + "\\assets\\bin\\rcbasic\" \"" + dp + "\\assets\\main.cbc\"";
    //cout << "command = " << cmd << endl;
    system(cmd.c_str());
    return 0;
}
