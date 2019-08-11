#ifndef RC_STDLIB_H_INCLUDED
#define RC_STDLIB_H_INCLUDED

#define RC_LINUX
//#define RC_WINDOWS
//#define RC_MAC
//#define RC_ANDROID
//#define RC_IOS

#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <stack>
#include <bitset>
#include <sys/stat.h>   //file system stuff
#include <sys/types.h>  //file system stuff
#include <unistd.h>   //file system stuff
#include <dirent.h>
#ifdef RC_ANDROID
	#include "SDL.h"
#else
	#include <SDL2/SDL.h>
#endif
//


#ifdef RC_WINDOWS

#include <tchar.h>
#include <windows.h>

#endif // RC_WINDOWS

using namespace std;

#define RC_MAX_FILES 32

#define RC_FILE_IO_TEXT_INPUT 1
#define RC_FILE_IO_TEXT_OUTPUT 2
#define RC_FILE_IO_TEXT_APPEND 3
#define RC_FILE_IO_TEXT_INPUT_UPDATE 4
#define RC_FILE_IO_TEXT_OUTPUT_UPDATE 5
#define RC_FILE_IO_TEXT_APPEND_UPDATE 6
#define RC_FILE_IO_BINARY_INPUT 7
#define RC_FILE_IO_BINARY_OUTPUT 8
#define RC_FILE_IO_BINARY_APPEND 9
#define RC_FILE_IO_BINARY_INPUT_UPDATE 10
#define RC_FILE_IO_BINARY_OUTPUT_UPDATE 11
#define RC_FILE_IO_BINARY_APPEND_UPDATE 12

#ifndef RC_WINDOWS

struct dirent *rc_entry;
DIR *rc_dir;
string rc_dir_path = "";

#else

struct dirent *rc_entry;
string rc_dir;
string rc_dir_path = "";
HANDLE hfind;

#endif // RC_LINUX


int rc_cmd_count = 0;
string * rc_cmd_args;


SDL_RWops * rc_fstream[RC_MAX_FILES];
bool rc_eof[RC_MAX_FILES];

#define MAX_USER_STACKS 16
int rc_user_active_n_stack = 0;
int rc_user_active_s_stack = 0;

stack<double> rc_user_n_stack[MAX_USER_STACKS];
stack<string> rc_user_s_stack[MAX_USER_STACKS];

void rc_fprint(string txt)
{
    cout << txt;
}

string rc_input(string prompt)
{
    string line = "";
    cout << prompt;
    getline(cin, line);
    return line;
}


inline int rc_intern_asc(string c)
{
    return (int)c[0];
}

inline string rc_intern_chr(int n)
{
    string s = "";
    s += (char) n;
    return s;
}

inline string rc_intern_insert(string src, string tgt, int pos)
{
    return src.substr(0, pos) + tgt + src.substr(pos);
}

inline int rc_intern_instr(string in_string, string in_substring)
{
    //cout << "Cant find " << rc_sid[INSTR_SUBSTR][0] << " in " << rc_sid[INSTR_STR][0] << endl;
    return in_string.find(in_substring);
}

inline string rc_intern_lcase(string lc_string)
{
   for(unsigned int i=0;i<lc_string.length();i++)
   {
      lc_string = tolower(lc_string[i]);
   }
   return lc_string;
}

inline string rc_intern_left(string l_string, int n)
{
    return l_string.substr(0,n);
}

inline int rc_intern_length(string l_string)
{
    //cout << "DBG_LEN" << endl;
    return l_string.length();
}

inline string rc_intern_ltrim(string l_string)
{
    if(l_string.find_first_not_of(" ") != string::npos)
        return l_string.substr(l_string.find_first_not_of(" "));
    return "";
}

inline string rc_intern_mid(string m_string, int m_start, int n)
{
    //cout << "DBG_MID" << endl;
    if(m_string.length() <= m_start)
        return "";
    if( (m_start+n) >= m_string.length())
        return m_string.substr(m_start);
    return m_string.substr(m_start, n);
}

inline string rc_intern_replace(string src, string rpc, int pos)
{
    int rpc_i = 0;
    string n_str = src.substr(0,pos);
    for(int i = pos; i < src.length(); i++)
    {
        if(rpc_i < rpc.length())
            n_str += rpc.substr(rpc_i,1);
        else
            break;
        rpc_i++;
    }
    if((pos+rpc_i) < src.length())
        n_str += src.substr(pos+rpc_i);
    return n_str;
}

inline string rc_intern_replaceSubstr(string src, string tgt, string rpc)
{
    if(tgt.length()==0)
        return src;
    int found_inc = rpc.length() > 0 ? rpc.length() : 1;
    int found = 0;
    found = src.find(tgt);
    while( ((int)found) != -1 && found < src.length())
    {
        src = src.substr(0,found) + rpc + src.substr(found + tgt.length());
        found = src.find(tgt,found+found_inc);
    }
    return src;
}

inline string rc_intern_reverse(string rpc_string)
{
    string n_str = "";
    for(int i = rpc_string.length()-1; i >= 0; i--)
        n_str += rpc_string[i];
    return n_str;
}

inline string rc_intern_right(string src, int n)
{
    return src.substr(src.length()-n);
}

inline string rc_intern_rtrim(string src)
{
    int i = 0;
    for(i = src.length()-1; i >= 0; i--)
        if(src.substr(i,1).compare(" ") != 0)
            break;
    return src.substr(0,i+1);
}

inline string rc_intern_stringfill(string f_string, int n)
{
    string f = "";
    for(int i = 0; i < n; i++)
        f += f_string;
    return f;
}

inline string rc_intern_str(double n)
{
    stringstream ss;
    ss << n;
    return ss.str();
}

inline string rc_intern_str_f(double n)
{
    stringstream ss;
    ss << fixed << n;
    return ss.str();
}

inline string rc_intern_str_s(double n)
{
    stringstream ss;
    ss << scientific << n;
    return ss.str();
}

inline unsigned int rc_intern_tally(string t_string, string t_substring)
{
    int found = 0;
    string t_str = t_string;
    string t_substr = t_substring;
    found = t_str.find(t_substr);
    unsigned int tally_count = 0;
    while( ((int)found) != -1)
    {
        tally_count++;
        found = t_str.find(t_substr,found+1);
    }
    return tally_count;
}

inline string rc_intern_trim(string t_string)
{
    return rc_intern_ltrim(rc_intern_rtrim(t_string));
}

inline string rc_intern_ucase(string u_string)
{
    string u_string_out = "";
    for(unsigned int i=0;i<u_string.length();i++)
    {
        u_string_out += toupper(u_string[i]);
    }
   return u_string_out;
}

inline double rc_intern_val(string v_string)
{
    return atof(v_string.c_str());
}

inline double rc_intern_abs(double n)
{
    if(n < 0)
        return (n * -1);
    else
        return n;
}

inline double rc_intern_aCos(double n)
{
    return acos(n);
}

inline double rc_intern_andBit(uint64_t a, uint64_t b)
{
    return (a & b);
}

inline double rc_intern_aSin(double n)
{
    return asin(n);
}

inline double rc_intern_aTan(double n)
{
    return atan(n);
}

#ifdef RC_ANDROID
string Convert(unsigned int val)
{
   unsigned int mask = 1 << (sizeof(int) * 8 - 1);
   string binstr = "";

   for(int i = 0; i < sizeof(int) * 8; i++)
   {
      if( (val & mask) == 0 )
         //cout << '0' ;
           binstr += "0";
      else
         //cout << '1' ;
           binstr += "1";

      mask  >>= 1;
   }
   return binstr;
}

inline string rc_intern_bin(uint64_t n)
{
    //string bin_str = bitset<64>(n).to_string();
    //bin_str = bin_str.substr(bin_str.find_first_not_of("0"));
    string binstr = Convert(n);// bin_str;
    return binstr.substr(binstr.find_first_not_of("0"));
}
#else

inline string rc_intern_bin(uint64_t n)
{
    string bin_str = bitset<64>(n).to_string();
    bin_str = bin_str.substr(bin_str.find_first_not_of("0"));
    return bin_str;
}

#endif // RC_ANDROID

int64_t rc_intern_cint64(int32_t i)
{
    return (int64_t)i;
}

int32_t rc_intern_cint32(int64_t i)
{
    return (int32_t)i;
}

inline double rc_intern_cos(double angle)
{
    return cos(angle);
}

inline double rc_intern_exp(double n)
{
    return exp(n);
}

inline double rc_intern_frac(double n)
{
    return n - floor(n);
}

inline string rc_intern_hex(uint64_t n)
{
    stringstream ss;
    ss << hex << n;
    return ss.str();
}

inline double rc_intern_hexInt(string n)
{
    uint64_t x;
    stringstream ss;
    ss << hex << n;
    ss >> x;
    return (double)x;
}

inline int64_t rc_intern_int(double n)
{
    return (int64_t)n;
}

inline double rc_intern_log(double n)
{
    return log(n);
}

inline double rc_intern_max(double a, double b)
{
    if(a > b)
        return a;
    else
        return b;
}

inline double rc_intern_min(double a, double b)
{
    if(a < b)
        return a;
    else
        return b;
}

inline double rc_intern_orBit(uint64_t a, uint64_t b)
{
    return (a | b);
}

inline int rc_intern_randomize(double n)
{
    srand(n);
    return 0;
}

inline int rc_intern_rand(int n)
{
    return (int)( (rand() / double(RAND_MAX))*(double(n) + ( n < 0 ? 0.001 : -0.001 )) );
}

inline double rc_intern_round(double n)
{
    return round(n);
}

inline int rc_intern_sign(double n)
{
    if(n == 0)
        return 0;
    else if(n > 0)
        return 1;
    else
        return -1;
}

inline double rc_intern_sin(double angle)
{
    return sin(angle);
}

inline double rc_intern_sqrt(double n)
{
    return sqrt(n);
}

inline double rc_intern_tan(double angle)
{
    return tan(angle);
}

inline double rc_intern_xorbit(uint64_t a, uint64_t b)
{
    return (a ^ b);
}

inline int rc_intern_fileOpen(int fo_stream, string fo_file, int fo_mode)
{
    if(fo_stream >= 0 && fo_stream < RC_MAX_FILES)
    {
        if(rc_fstream[fo_stream] != NULL)
            return 0;

        rc_eof[fo_stream] = false;

        switch(fo_mode)
        {
            case RC_FILE_IO_TEXT_INPUT:
                //rc_fstream[fo_stream].open(fo_file.c_str(), fstream::in);
                rc_fstream[fo_stream] = SDL_RWFromFile(fo_file.c_str(), "r");
                //cout << "RC_DEBUG_TEXT_INPUT" << endl;
                break;
            case RC_FILE_IO_TEXT_OUTPUT:
                rc_fstream[fo_stream] = SDL_RWFromFile(fo_file.c_str(),"w");
                break;
            case RC_FILE_IO_TEXT_APPEND:
                rc_fstream[fo_stream] = SDL_RWFromFile(fo_file.c_str(),"a");
                break;
            case RC_FILE_IO_TEXT_INPUT_UPDATE:
                rc_fstream[fo_stream] = SDL_RWFromFile(fo_file.c_str(),"r+");
                break;
            case RC_FILE_IO_TEXT_OUTPUT_UPDATE:
                rc_fstream[fo_stream] = SDL_RWFromFile(fo_file.c_str(),"w+");
                break;
            case RC_FILE_IO_TEXT_APPEND_UPDATE:
                rc_fstream[fo_stream] = SDL_RWFromFile(fo_file.c_str(),"a+");
                break;
            case RC_FILE_IO_BINARY_INPUT:
                rc_fstream[fo_stream] = SDL_RWFromFile(fo_file.c_str(),"rb");
                break;
            case RC_FILE_IO_BINARY_OUTPUT:
                rc_fstream[fo_stream] = SDL_RWFromFile(fo_file.c_str(),"wb");
                break;
            case RC_FILE_IO_BINARY_APPEND:
                rc_fstream[fo_stream] = SDL_RWFromFile(fo_file.c_str(),"ab");
                break;
            case RC_FILE_IO_BINARY_INPUT_UPDATE:
                rc_fstream[fo_stream] = SDL_RWFromFile(fo_file.c_str(),"rb+");
                break;
            case RC_FILE_IO_BINARY_OUTPUT_UPDATE:
                rc_fstream[fo_stream] = SDL_RWFromFile(fo_file.c_str(),"wb+");
                break;
            case RC_FILE_IO_BINARY_APPEND_UPDATE:
                rc_fstream[fo_stream] = SDL_RWFromFile(fo_file.c_str(),"ab+");
                break;
        }
        if(rc_fstream[fo_stream] == NULL)
        {
            //cout << "RC_DEBUG: FILE NOT OPEN" << endl;
            return 0;
        }
    }
    return 1;
}

inline int rc_intern_fileClose(int fc_stream)
{
    rc_eof[fc_stream] = false;

    if(rc_fstream[fc_stream] != NULL)
    {
        SDL_RWclose(rc_fstream[fc_stream]);
        rc_fstream[fc_stream] = NULL;
        return 1;
    }
    else
        return 0;
}

inline int rc_intern_fileReadByte(int f_stream)
{
    unsigned char buf;
    unsigned char rb = SDL_RWread(rc_fstream[f_stream], &buf, 1, 1);
    int t = SDL_RWtell(rc_fstream[f_stream]);
    return (int)buf;
}

inline int rc_intern_fileWriteByte(int f_stream, char wb)
{
    SDL_RWwrite(rc_fstream[f_stream], &wb, 1, 1);
    return 1;
}

inline string rc_intern_fileReadLine(int f_stream)
{
    string rline = "";
    unsigned char buf[5];
    if(SDL_RWread(rc_fstream[f_stream], buf, 1, 1)==0)
    {
        rc_eof[f_stream] = true;
        return "";
    }
    while(buf[0]!='\0' && buf[0]!='\n' && buf[0]!='\r')
    {
        rline.append(1,buf[0]);
        if(SDL_RWread(rc_fstream[f_stream], buf, 1, 1)==0)
        {
            rc_eof[f_stream] = true;
            break;
        }
    }
    if(buf[0]=='\r')
        SDL_RWread(rc_fstream[f_stream], buf, 1, 1);
    return rline;
}

inline int rc_intern_fileWriteLine(int f_stream, string line)
{
    //cout << "DEBUG: WRITELINE" << endl;
    if(rc_fstream[f_stream]!=NULL)
        SDL_RWwrite(rc_fstream[f_stream], line.c_str(), line.length(), 1);
    //cout << "WRITELINE_END" << endl;
    return 1;
}

inline int rc_intern_fileCopy(string src_file, string dst_file)
{
    std::ifstream  src(src_file.c_str(), std::ios::binary);
    std::ofstream  dst(dst_file.c_str(), std::ios::binary);
    if(!(src.is_open() && dst.is_open()))
        return 0;
    dst << src.rdbuf();
    src.close();
    dst.close();
    return 1;
}

inline int rc_intern_fileDelete(string tgt_file)
{
    if(remove(tgt_file.c_str())==0)
        return 1;
    else
        return 0;
}

inline int rc_intern_fileExist(string tgt_file)
{
    std::ifstream infile(tgt_file.c_str());
    bool fx = infile.good();
    infile.close();
    return (int)fx;
}

inline int rc_intern_fileMove(string src, string dst)
{
    int fm = rename(src.c_str(), dst.c_str());
    if(fm == 0)
        return 1;
    else
        return 0;
}

inline int rc_intern_fileRename(string src, string dst)
{
    int fm = rename(src.c_str(), dst.c_str());
    if(fm == 0)
        return 1;
    else
        return 0;
}

inline unsigned long rc_intern_fileLength(string filename)
{
    //struct stat st;
    SDL_RWops * fl_file = SDL_RWFromFile(filename.c_str(), "r");
    int fl_size = SDL_RWsize(fl_file);
    SDL_RWclose(fl_file);
    return fl_size;
}

inline long rc_intern_fileTell(int f_stream)
{
    return SDL_RWtell(rc_fstream[f_stream]);
}

inline unsigned long rc_intern_fileSeek(int f_stream, uint64_t pos)
{
    return SDL_RWseek(rc_fstream[f_stream],pos,RW_SEEK_SET);
}

inline int rc_intern_eof(int f_stream)
{
    //Uint32 current_pos = SDL_RWtell(rc_fstream[(int)rc_nid[EOF_STREAM][0]]);
    //Uint32 current_pos = SDL_RWseek(rc_fstream[(int)rc_nid[EOF_STREAM][0],0,RW_SEEK_CUR);
    //Uint32 file_eof = SDL_RWseek(rc_fstream[(int)rc_nid[EOF_STREAM][0]],0,RW_SEEK_END);
    //SDL_RWseek(rc_fstream[(int)rc_nid[EOF_STREAM][0]],0,current_pos);
    return rc_eof[f_stream];
}

inline int rc_intern_freeFile()
{
    for(int i = 0; i < RC_MAX_FILES; i++)
        if(rc_fstream[i] == NULL)
        return i;
    return -1;
}



#ifndef RC_WINDOWS

#ifdef RC_LINUX
inline int rc_intern_dirChange(string ch_path)
{
    if(chdir(ch_path.c_str())!=0)
    {
        cout << "Error: Could not change directory\n";
        return 2;
    }
    rc_dir_path = get_current_dir_name();
    return 0;
}
#endif // RC_LINUX

inline int rc_intern_dirExist(string d_path)
{
    struct stat info;

    if(stat( d_path.c_str(), &info ) != 0)
        return 0;
    else if(info.st_mode & S_IFDIR)
        return 1;
    else
        return 0;
}

inline string rc_intern_dirFirst ()
{
    rc_dir = opendir (rc_dir_path.c_str());
    //string s = "";

    if ((rc_entry = readdir (rc_dir)) != NULL)
    {
        //cout << "ERROR: " << rc_entry->d_name;
        return rc_entry->d_name;
    }
    return "";
}

#ifdef RC_ANDROID
string getcwd_str()
{
    char *buffer = new char[MAXPATHLEN];
    getcwd(buffer,MAXPATHLEN);
    if(buffer != NULL)
    {
        string ret(buffer);
        delete[] buffer;
        return ret;
    }
    else
    {
        return string();
    }
}


inline int rc_intern_dirChange(string ch_path)
{
    if(chdir(ch_path.c_str())!=0)
    {
        cout << "Error: Could not change directory\n";
        return 2;
    }
    rc_dir_path = getcwd_str();
    return 0;
}

inline string rc_intern_dir()
{
    string d = getcwd_str();
    //__android_log_print(ANDROID_LOG_ERROR, "RC_DEBUG_DIR", "%s", SDL_GetPrefPath("rcbasic","lucky"));
    if(d.compare("")==0)
    {
        //cout << "Could not get current directory" << endl;
        return "";
    }
    rc_dir_path = d;
    return d;
}

#else

inline string rc_intern_dir()
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

#endif // RC_ANDROID

inline string rc_intern_dirNext()
{
    if( (rc_entry = readdir(rc_dir))!=NULL)
        return rc_entry->d_name;
    return "";
}

inline int rc_intern_dirCreate(string d_path)
{
    if(mkdir(d_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)!=0)
    {
        cout << "ERROR: Could not make directory" << endl;
        return 0;
    }
    return 1;
}

inline int rc_intern_dirDelete(string d_path)
{
    if(rmdir(d_path.c_str())!=0)
    {
        cout << "ERROR: Could not delete directory" << endl;
        return 0;
    }
    return 1;
}

inline string rc_intern_OS()
{
    #ifdef RC_LINUX
        return "LINUX";
    #endif // RC_LINUX

    #ifdef RC_ANDROID
        return "ANDROID";
    #endif // RC_LINUX

    #ifdef RC_MAC
        return "MAC";
    #endif // RC_MAC

    #ifdef RC_IOS
        return "IOS";
    #endif // RC_IOS
}

#else

inline int rc_intern_dirChange(string dpath)
{
    if(SetCurrentDirectory(dpath.c_str())==0)
    {
        cout << "Error: Could not change directory\n";
        return 2;
    }

    DWORD nBufferLength = MAX_PATH;
    char szCurrentDirectory[MAX_PATH + 1];
    GetCurrentDirectory(nBufferLength, szCurrentDirectory);
    szCurrentDirectory[MAX_PATH] = '\0';

    rc_dir_path = (string)szCurrentDirectory;
    return 0;
}

bool dirExists(const std::string& dirName_in)
{
  DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
  if (ftyp == INVALID_FILE_ATTRIBUTES)
    return false;  //something is wrong with your path!

  if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    return true;   // this is a directory!

  return false;    // this is not a directory!
}

inline int rc_intern_dirExist(string dpath)
{
    return dirExists(dpath);
}

HANDLE hFind;
WIN32_FIND_DATA ffd;

string rc_intern_dirFirst()
{
    char* path = (char*)rc_dir_path.c_str();

    cout << "path = " << path << endl;
    if (path[_tcslen(path) - 1] != '\\')
        _tcscat(path, _T("\\"));
    _tcscat(path, _T("*.*"));

    cout << "path2 = " << path << endl;

    hFind = FindFirstFile(path, &ffd);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        cerr << _T("Invalid handle value.") << GetLastError() << endl;
        return "";
    }
    return ffd.cFileName;
}

inline string rc_intern_dir()
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

string rc_intern_dirNext()
{
    if(!FindNextFile(hFind,&ffd))
        return "";
    return ffd.cFileName;
}

inline int rc_intern_dirCreate(string dpath)
{
    if(CreateDirectory(dpath.c_str(),NULL)!=0)
    {
        cout << "ERROR: Could not make directory" << endl;
        return 0;
    }
    return 1;
}

inline int rc_intern_dirDelete(string dpath)
{
    if(RemoveDirectory(dpath.c_str())==0)
    {
        cout << "ERROR: Could not delete directory" << endl;
        return 0;
    }
    return 1;
}

inline string rc_intern_OS()
{
    return "WINDOWS";
}

#endif // RC_WINDOWS


inline string rc_intern_date()
{
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    stringstream d;
    if( now->tm_mon+1 < 10)
        d << "0" << now->tm_mon + 1 << "-";
    else
        d << now->tm_mon+1 << "-";
    if(now->tm_mday < 10)
        d << "0" << now->tm_mday << "-";
    else
        d<< now->tm_mday << "-";
    d << (now->tm_year + 1900);
    return d.str();
}

string ZeroPadNumber(int num)
{
    stringstream ss;
    // the number is converted to string with the help of stringstream
    ss << num;
    string ret;
    ss >> ret;
    // Append zero chars
    int str_length = ret.length();
    for (int i = 0; i < 2 - str_length; i++)
        ret = "0" + ret;
    return ret;
}

string rc_intern_easter(int X)
{
    stringstream ss;                             // X = year to compute
    int K, M, S, A, D, R, OG, SZ, OE;
    K  = X / 100;                                   // Secular number
    M  = 15 + (3 * K + 3) / 4 - (8 * K + 13) / 25;  // Secular Moon shift
    S  = 2 - (3 * K + 3) / 4;                       // Secular sun shift
    A  = X % 19;                                    // Moon parameter
    D  = (19 * A + M) % 30;                         // Seed for 1st full Moon in spring
    R  = D / 29 + (D / 28 - D / 29) * (A / 11);     // Calendarian correction quantity
    OG = 21 + D - R;                                // Easter limit
    SZ = 7 - (X + X / 4 + S) % 7;                   // 1st sunday in March
    OE = 7 - (OG - SZ) % 7;                         // Distance Easter sunday from Easter limit in days
    //Easter = DateSerial(X, 3, OG + OE);           // Result: Easter sunday as number of days in March
    ss << ZeroPadNumber(((OG + OE)>31)?4:3) << "-" << ZeroPadNumber((((OG + OE)%31)==0)?31:((OG + OE)%31)) << "-" << X;
    return ss.str();
}

inline unsigned long rc_intern_ticks()
{
    return clock();
}

inline string rc_intern_time()
{
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    stringstream d;
    if( now->tm_hour < 10)
        d << "0" << now->tm_hour << ":";
    else
        d << now->tm_hour << ":";

    if(now->tm_min < 10)
        d << "0" << now->tm_min << ":";
    else
        d<< now->tm_min << ":";

    if(now->tm_sec < 10)
        d << "0" << now->tm_sec;
    else
        d << now->tm_sec;
    return d.str();
}

inline double rc_intern_timer()
{
    return SDL_GetTicks();
    //return clock() / (double)(CLOCKS_PER_SEC / 1000);
}

inline void rc_intern_wait(double m_sec)
{
    SDL_Delay(m_sec);
}

inline int rc_intern_system(string rc_sys_cmd)
{
    return system(rc_sys_cmd.c_str());
}

inline string rc_intern_command(int num)
{
    if(num < rc_cmd_count)
    {
        return rc_cmd_args[num];
    }
    return "";
}

inline int rc_intern_numCommands()
{
    return rc_cmd_count;
}

inline string rc_intern_env(string v)
{
    char * c = getenv(v.c_str());
    if(c != NULL)
        return (string) c;
    return "";
}

inline int rc_intern_setEnv(string v)
{
    return putenv((char *)v.c_str());
}

inline string rc_intern_prefPath(string org_name, string app_name)
{
    return (string) SDL_GetPrefPath(org_name.c_str(), app_name.c_str());
}

inline int rc_intern_push_n(double n)
{
    rc_user_n_stack[rc_user_active_n_stack].push(n);
    return 1;
}

inline int rc_intern_push_s(string s)
{
    rc_user_s_stack[rc_user_active_s_stack].push(s);
    return 1;
}

inline double rc_intern_pop_n()
{
    double n = rc_user_n_stack[rc_user_active_n_stack].top();
    rc_user_n_stack[rc_user_active_n_stack].pop();
    return n;
}

inline string rc_intern_pop_s()
{
    string s = rc_user_s_stack[rc_user_active_s_stack].top();
    rc_user_s_stack[rc_user_active_s_stack].pop();
    return s;
}

inline int rc_intern_n_stack_size()
{
    return rc_user_n_stack[rc_user_active_n_stack].size();
}

inline int rc_intern_s_stack_size()
{
    return rc_user_s_stack[rc_user_active_s_stack].size();
}


#endif // RC_STDLIB_H_INCLUDED
