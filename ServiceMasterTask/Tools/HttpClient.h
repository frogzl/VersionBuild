#pragma once
#include <string>
#include "../Common.h"

using namespace std;
class HttpClient
{
	typedef struct 
	{
		struct event_base* pBase;
		HttpClient *pHttp;
	}Item;
public:
	HttpClient();
	~HttpClient();
public:
	bool download_file(string &sStorageHostList, string sFilePath);
	bool download_file_part(string sAddress, int nPort, char *szBuf, string sRemotePath, long long llStart, long long llEnd, int &nFilePartSize);
	bool download_file_part(string sAddress, int nPort, string sLocalPath, string sRemotePath, long long llStart, long long llEnd);
	
	bool upload_file(string sAddress, int nPort, string sStorageId, string sFileName, string sLocalPath);
	bool upload_file_part(string sAddress, int nPort, string sFileName, string sLocalPath, string sRemotePath, long long llStart, long long llEnd);

	bool get(string &sHost, int &nPort, string &sPath, string &sParam);
	bool post(string &sHost, int &nPort, string &sPath, string &sData);

	bool get_input_headers(struct evhttp_request  *req, map<string, string> &mapHeader);
	char* get_input_buffer(struct evhttp_request  *req);

	void set_http_code(int nCode) { m_nHttpCode = nCode; }
	void set_http_respond_data(Json::Value jsonData) {m_jsonResponseData =  jsonData; }
	string error_code();
	string error_message();
	Json::Value& repsonse_data();

	static void http_request_done(struct evhttp_request *req, void *arg);
private:
	Json::Value m_jsonResponseData;
	int m_nHttpCode;
	string m_sErrorCode;
	string m_sErrorMessage;
	char *m_szBuf;
};

