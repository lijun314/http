#ifndef WIN_PLATFORM_H
#define WIN_PLATFORM_H


#ifdef _WIN64
#define PLATFORM_WINDOWS
#endif // _WIN64

#ifdef _WIN32
#define PLATFORM_WINDOWS
#endif // _WIN32



#ifdef PLATFORM_WINDOWS
#include <WinSock2.h>
#define socklen_t int
#define MSG_DONTWAIT 0

#else

#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define closesocket close
typedef SOCKET int

#endif

//#define USE_IPV6
#endif // !WIN_PLATFORM_H
