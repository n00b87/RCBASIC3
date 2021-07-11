#ifndef FILE_DIRECTORY_H_INCLUDED
#define FILE_DIRECTORY_H_INCLUDED


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
   #define RC_WINDOWS
#elif __APPLE__
    #define RC_MAC
#elif __linux__
    #define RC_LINUX
#endif


#include <sys/stat.h>   //file system stuff
#include <sys/types.h>  //file system stuff
#include <unistd.h>   //file system stuff
#include <dirent.h>
#include <stdlib.h>


#ifdef RC_MAC
#define RC_GETCWD
#include <sys/param.h>
#endif

#ifdef RC_WINDOWS
#include <tchar.h>
#include <windows.h>
#include <winbase.h>
#endif // RC_WINDOWS


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

inline bool rc_intern_dirExist(string d_path)
{
    struct stat info;

    if(stat( d_path.c_str(), &info ) != 0)
        return false;
    else if(info.st_mode & S_IFDIR)
        return true;
    else
        return false;
}

    #ifdef RC_GETCWD
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

#endif // RC_WINDOWS


string rc_absFilePath(string file_path)
{
    //cout << "file_path: " << file_path << endl;
    string cwd = rc_intern_dir();
    int start_index = 0;
    string::size_type bs_index = file_path.find_last_of("\\");
    string::size_type fs_index = file_path.find_last_of("/");
    int end_index = 0;

    if(bs_index==string::npos && fs_index==string::npos)
    {
        #ifdef RC_WINDOWS
            return cwd + "\\" + file_path;
        #else
            return cwd + "/" + file_path;
        #endif // RC_WINDOWS
    }

    end_index = ( (bs_index > fs_index || fs_index == string::npos) && bs_index != string::npos) ? bs_index : fs_index;


    if(rc_intern_dirExist(file_path.substr(0, end_index)))
    {
        rc_intern_dirChange(file_path.substr(0, end_index));

        #ifdef RC_WINDOWS
            string abs_file_path = rc_intern_dir() + "\\" + file_path.substr(end_index+1);
        #else
            string abs_file_path = rc_intern_dir() + "/" + file_path.substr(end_index+1);
        #endif // RC_WINDOWS

        rc_intern_dirChange(cwd);
        return abs_file_path;
    }

    return file_path;
}


#endif // FILE_DIRECTORY_H_INCLUDED
