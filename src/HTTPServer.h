/* HTTPServer.h */

#ifndef _HTTP_SERVER_H_
#define _HTTP_SERVER_H_

#include "crossPlatform.h"
#include"HTTPRequest.h"
#include"HTTPResponse.h"

#define SVR_ROOT "d:\\repos\\www"

using namespace std;

class HTTPServer{
	public:
		HTTPServer();
		HTTPServer(int );
		~HTTPServer();

		int run(void );
		int setPort(size_t );
		int initSocket(void );

		int handleRequest(void );
		int recvRequest(void );
		int parseRequest(void );
		int prepareResponse(void );
		int sendResponse(void );
		int processRequest(void );
	
	private:
		string getMimeType(string );

		size_t svrPort;
		SOCKET sockfd, newsockfd;
		socklen_t cliLen;
#ifdef USE_IPV6
		struct sockaddr_in6  servAddr, cliAddr;
#else
		struct sockaddr_in servAddr, cliAddr;
#endif
		string m_url;
		string m_mimeType;
		HTTPRequest* m_httpRequest;
		HTTPResponse* m_httpResponse;
		static const int buf_sz = 32;
};

#endif	/* _HTTP_SERVER_H_ */
