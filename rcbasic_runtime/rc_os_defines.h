#ifndef RC_OS_DEFINES_H_INCLUDED
#define RC_OS_DEFINES_H_INCLUDED

#define RC_LINUX
//#define RC_WEB
//#define RC_WINDOWS
//#define RC_ANDROID
//#define RC_MAC
//#define RC_IOS

#ifdef RC_WEB
#define RC_LINUX
#endif

#ifdef RC_ANDROID
#define RC_MOBILE
#endif

#ifdef RC_IOS
#define RC_MOBILE
#endif

#endif // RC_OS_DEFINES_H_INCLUDED
