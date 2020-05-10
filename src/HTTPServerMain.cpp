/* HTTPServerMain.cpp */

#include<iostream>
#include<string>

#include<stdlib.h>

#include"HTTPServer.h"

#ifdef PLATFORM_WINDOWS
#pragma comment(lib,"ws2_32.lib")
#endif // PLATFORM_WINDOWS


using namespace std;

int main(int argc, char* argv[])
{
	int port;
	HTTPServer* httpServer;
#ifdef PLATFORM_WINDOWS
	// Declare and initialize variables.
	WSADATA wsaData;
	int iResult;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}
#endif


	if(argc == 2){
		port = atoi(argv[1]);
		httpServer = new HTTPServer(port);
	}else{
		httpServer = new HTTPServer();
	}

	if(httpServer->run()){
		cerr<<"Error starting HTTPServer"<<endl;
	}

	delete httpServer;
#ifdef PLATFORM_WINDOWS
	WSACleanup();
#endif
	return 0;
}
