#ifndef RC_DEBUG_H_INCLUDED
#define RC_DEBUG_H_INCLUDED

using namespace std;

string ERROR_MSG = "";

void rc_setError(string rc_error)
{
    ERROR_MSG += rc_error + "\n";
}

string rc_getError()
{
    string error_out = ERROR_MSG;
    ERROR_MSG = "";
    return error_out;
}

#endif // RC_DEBUG_H_INCLUDED
