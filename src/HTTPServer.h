/* HTTPServer.h */

#ifndef _HTTP_SERVER_H_
#define _HTTP_SERVER_H_

#include "crossPlatform.h"
#include"HTTPRequest.h"
#include"HTTPResponse.h"

#define SVR_ROOT "d:\\repos\\httpd\\www"

using namespace std;

class HTTPServer;
typedef int (*CGIFunc)(HTTPServer* pHTTPserver, map<string, string>* param);

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
		int SendResponseData(char* pData, unsigned int len);
		int processRequest(void );
		int processCGIRequest(void);
		HTTPRequest* GetHTTPRequest(void) {
			return m_httpRequest;
		};
		HTTPResponse* GetHTTPResponse(void) {
			return m_httpResponse;
		};
		void AddCGIFunc(string strCGIName, CGIFunc func)
		{
			m_CGIFuncMap[strCGIName] = func;
		}
		void SetMineType(string mineType)
		{
			m_mimeType = mineType;
		}
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
		map<string, CGIFunc> m_CGIFuncMap;
		HTTPRequest* m_httpRequest;
		HTTPResponse* m_httpResponse;
		static const int buf_sz = 32;
};

#endif	/* _HTTP_SERVER_H_ */
