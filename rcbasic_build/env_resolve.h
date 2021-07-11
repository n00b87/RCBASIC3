#ifndef ENV_RESOLVE_H_INCLUDED
#define ENV_RESOLVE_H_INCLUDED

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
   #define RC_WINDOWS
#elif __APPLE__
    #define RC_MAC
#elif __linux__
    #define RC_LINUX
#endif

#ifdef RC_WINDOWS
#include <winbase.h>
#else
#include <cstdlib>
#endif // RC_WINDOWS

string rc_intern_env(string v)
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

string resolveEnvironmentVariables(string sdata)
{
    string sdata_out = "";
    for(int i = 0; i < sdata.length(); i++)
    {
        if(sdata.substr(i, 2).compare("${")==0)
        {
            int end_index = sdata.substr(i+2).find_first_of("}");
            if(end_index == string::npos)
            {
                cout << "Error: Missing closing } in environment variable" << endl;
                return sdata_out;
            }
            string env_var = sdata.substr(i+2).substr(0, end_index);
            //cout << "env_var is " << env_var << endl;
            string env_value = rc_intern_env(env_var);
            sdata_out += env_value;
            i = (i+2) + end_index;
            continue;
        }
        else
        {
            sdata_out += sdata.substr(i, 1);
        }
    }
    return sdata_out;
}

#endif // ENV_RESOLVE_H_INCLUDED
