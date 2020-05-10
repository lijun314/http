
#include "HTTPServer.h"
#include<iostream>
#include<fstream>

#define CELL_SIZE 1024
int GetDataInfo(int index,string* date,int* color)
{
	*date = "2019-2-3 4:14:12";
	*color = index;
	return 0;
}
int GetData(int index, char* pData)
{
	memset(pData, index, CELL_SIZE);
	return 0;
}


void DumpGET(map<string, string>* param)
{
	map<string, string>::iterator iter = param->begin();
	cout << "param:" << endl;
	while (iter != param->end())
	{
		cout << iter->first << '=' << iter->second << endl;
		iter++;
	}
	cout<< endl;

}


int CGI_GetPosInfo(HTTPServer* pHTTPserver, map<string, string>* param)
{
	ostringstream os;
	char buff[128];
	string date;
	int color;
	int index = atoi((*param)["index"].c_str());
	GetDataInfo(index, &date, &color);

	string result;
	sprintf(buff, "[\"/%s\",%d]", date.c_str(), color);

	result = buff;
	os << (int)result.size();

	HTTPResponse* pResponse = pHTTPserver->GetHTTPResponse();
	pResponse->setHTTPHeader("Content-Length", os.str());

	pResponse->setStatusCode(200);
	pResponse->setResponseBody(&result);

	pHTTPserver->SetMineType("application/txt;charset=gb2312");
	pHTTPserver->prepareResponse();
	pHTTPserver->sendResponse();
	return 0;
}
int CGI_DownFile(HTTPServer* pHTTPserver, map<string, string>* param)
{
	ostringstream os;
	string fileName;
	char buff[CELL_SIZE];
	DumpGET(param);
	if (param->find("StartPoint") == param->end() || param->find("EndPoint") == param->end())
		fileName = "参数不正确.txt";
	int startCell = atoi((*param)["StartPoint"].c_str());
	int endCell = atoi((*param)["EndPoint"].c_str());

	os << (endCell - startCell + 1) * 1024;

	HTTPResponse* pResponse = pHTTPserver->GetHTTPResponse();
	pResponse->setHTTPHeader("Content-Disposition","attachment;filename=开始日期-结束日期.vdr");//8
	pResponse->setHTTPHeader("Content-Transfer-Encoding","binary"); 

	pResponse->setHTTPHeader("Content-Length", os.str());

	pResponse->setStatusCode(200);
//	pResponse->setResponseBody(&result);
	
	pHTTPserver->SetMineType("application/vdr"); 
	pHTTPserver->prepareResponse();

	//发送头
	pHTTPserver->sendResponse();

	//发送数据
	int index = startCell;
	do {
		GetData(index, buff);
		pHTTPserver->SendResponseData(buff, CELL_SIZE);
		index++;
	} while (index <= endCell);

	return 0;
}
void InitCGIMgr(HTTPServer* pHTTPserver)
{
	pHTTPserver->AddCGIFunc("/GetPosInfo", CGI_GetPosInfo);
	pHTTPserver->AddCGIFunc("/GetFile", CGI_DownFile);
}