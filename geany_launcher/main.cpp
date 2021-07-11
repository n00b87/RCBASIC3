#include <iostream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
   #define RC_WINDOWS
#elif __APPLE__
    #define RC_MAC
#elif __linux__
    #define RC_LINUX
#endif

#include <windows.h>
#include <winbase.h>
#include <tchar.h>
#include <fstream>
#include <stdio.h>

#include "file_directory.h"

using namespace std;

string env(string v)
{
    #ifdef RC_WINDOWS
    char * val = new char[32767];
    int n = GetEnvironmentVariable(v.c_str(), val, 32767);
    string rtn = "";
    if (n>0)
        rtn = (string)val;
    delete val;
    return rtn;
    #else
    char * c = getenv(v.c_str());
    if(c != NULL)
        return (string) c;
    return "";
    #endif
}

inline int setEnv(string name, string value)
{
    #ifdef RC_WINDOWS
    //string env_cmd = name + "=" + value;
    return SetEnvironmentVariable(name.c_str(), value.c_str()) ? 1 : 0;
    //return _putenv(name.c_str());
    #else
    return setenv(name.c_str(), value.c_str(), 1);
    #endif
}

#ifdef RC_WINDOWS
inline string dir()
{
    TCHAR buf[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, buf);
    string d = buf;

    if(d.compare("")==0)
    {
        cout << "Could not get current directory" << endl;
        return "";
    }
    return d;
}
#else
inline string dir()
{
    string d = get_current_dir_name();
    if(d.compare("")==0)
    {
        cout << "Could not get current directory" << endl;
        return "";
    }
    rc_dir_path = d;
    return d;
}
#endif // RC_WINDOWS

inline string sysReturnOutput(string rc_sys_cmd)
{
    #if defined(RC_ANDROID) || defined(RC_IOS) || defined(RC_WEB)
        return "";
    #else
        const char * cmd = rc_sys_cmd.c_str();
        char buffer[128];
        std::string result = "";
        FILE* pipe = popen(cmd, "r");
        if (!pipe) throw std::runtime_error("popen() failed!");
        try {
            while (fgets(buffer, sizeof buffer, pipe) != NULL) {
                result += buffer;
            }
        } catch (...) {
            pclose(pipe);
            throw;
        }
        pclose(pipe);
        return result;
    #endif
}

bool is64bit()
{
    return (sysReturnOutput("systeminfo").find("x86-based") == string::npos) ? true : false;
}

string str_replace(string src, string tgt, string rpc)
{
    if(tgt.length()==0)
        return src;
    unsigned long found_inc = rpc.length() > 0 ? rpc.length() : 1;
    size_t found = 0;
    found = src.find(tgt);
    while( found != string::npos && found < src.length())
    {
        src = src.substr(0,found) + rpc + src.substr(found + tgt.length());
        found = src.find(tgt,found+found_inc);
    }
    return src;
}

int main(int argc, char *argv[])
{
    int os_bit = is64bit() ? 64 : 32;
    string dp = argv[0];
    int parent_dir_index = dp.find_last_of("\\");
    //cout << "parent dir = " << parent_dir_index << endl;
    dp = (parent_dir_index != string::npos) ? dp.substr(0, parent_dir_index) : ".";
    dp = rc_absFilePath(dp);
    setEnv("RCBASIC_TOOLS", dp + "\\rcbasic\\tools");
    setEnv("RCBASIC_D32", dp + "\\rcbasic\\rcbasic_32");
    setEnv("RCBASIC_D64", dp + "\\rcbasic\\rcbasic_64");

    if(env("RC_PKG_HOME").compare("")==0)
        setEnv("RC_PKG_HOME", dp + "\\rcbasic\\tools\\dist");

    if(env("RC_KEYSTORE_DIR").compare("")==0)
        setEnv("RC_KEYSTORE_DIR", dp + "\\keystore");

    setEnv("RCBASIC_WIN", dp + "\\rcbasic");
    switch(os_bit)
    {
        case 32:
            setEnv("RCBASIC_BIN", dp + "\\rcbasic\\rcbasic_32");
            break;
        case 64:
            setEnv("RCBASIC_BIN", dp + "\\rcbasic\\rcbasic_64");
            break;
    }

    setEnv("PATH", env("PATH")+";"+env("RC_PKG_HOME")+";"+env("RCBASIC_BIN"));
    //cout << "PATH = " << env("PATH") << endl;
    //cout << "dp = " << dp << endl;
    //cout << "os_bit = " << os_bit << endl;

    string line = "";
    string config_file_path = env("RCBASIC_WIN")+"\\geany_files\\geany.conf";
    ifstream config_file(config_file_path.c_str());
    if (config_file.is_open())
    {
        ofstream config_out((dp+"\\Geany\\Data\\settings\\geany.conf").c_str(), ios::out | ios::trunc);
        while ( getline (config_file,line) )
        {
          config_out << str_replace(line, "[RCBASIC_HOME]", str_replace(env("RCBASIC_WIN"), "\\", "\\\\")) << '\n';
        }
        config_file.close();
        config_out.close();
    }
    else
    {
        cout << "could not open: " << config_file_path << endl;
    }

    string cmd = "start " + dp + "\\Geany\\GeanyPortable";
    system(cmd.c_str());
    return 0;
}
