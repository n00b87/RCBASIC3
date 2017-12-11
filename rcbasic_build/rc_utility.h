#ifndef RC_UTILITY_H_INCLUDED
#define RC_UTILITY_H_INCLUDED
#include <fstream>
#include <sstream>
#include <ctype.h>

using namespace std;

string rc_intToString(int a)
{
    stringstream ss;
    ss << a;
    string str = ss.str();
    ss.clear();
    return str;
}

int rc_stringToInt(string a)
{
    stringstream ss;
    ss << a;
    int i = 0;
    ss >> i;
    ss.clear();
    return i;
}

string StringToUpper(string strToConvert)
{//change each element of the string to upper case
   for(unsigned int i=0;i<strToConvert.length();i++)
   {
      strToConvert[i] = toupper(strToConvert[i]);
   }
   return strToConvert;//return the converted string
}

string StringToLower(string strToConvert)
{//change each element of the string to lower case
   for(unsigned int i=0;i<strToConvert.length();i++)
   {
      strToConvert[i] = tolower(strToConvert[i]);
   }
   return strToConvert;//return the converted string
}

string rc_substr(string s, int start_pos=0, int num_char=0)
{
    if(start_pos < 0)
        return "";
    if(start_pos >= s.length())
        return "";
    if( (start_pos+num_char) >= s.length())
        return s.substr(start_pos);
    return s.substr(start_pos, num_char);
}

bool is_file_exist(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

#endif // RC_UTILITY_H_INCLUDED
