#include "HttpClient.h"
#include "../Database/Resource_Host.h"
#include <algorithm>
HttpClient::HttpClient()
{
	m_szBuf = new char[Buffer_Size];
}

HttpClient::~HttpClient()
{
	delete [] m_szBuf;
}

bool HttpClient::download_file(string &sStorageHostList, string sFilePath)
{
	Json::Reader reader;
	Json::Value jsonHosts;
	if (!reader.parse(sStorageHostList, jsonHosts))
	{
		return false;
	}

	// 根据llStart和llEnd下载
	long long llPartStart = 0, llPartEnd = 0;
	long long llFileDataSize = 0; // 此次获取的文件数据大学
	int nCount = jsonHosts.size();
	for (int nIndex = 0; nIndex < nCount; nIndex++)
	{
		Json::Value jsonHost = jsonHosts[nIndex];
		DB::Conditions conditions;
		conditions.insert(pair<string, string>("guid", jsonHost["hostid"].asString()));
		DB::Resource_Host dbHost;
		DB::Resource_HostData *pHostData = dbHost.query()->where(conditions)->first();
		if (!pHostData)
		{
			return false;
		}

		string sRange = jsonHost["range"].asString();
		sscanf(sRange.c_str(), "%ld-%ld", &llPartStart, &llPartEnd);
		HttpClient httpClient;
		if (!httpClient.download_file_part(pHostData->address, pHostData->port, sFilePath, jsonHost["path"].asString(), llPartStart, llPartEnd))
		{
			return false;
		}
	}
	return true;
}

bool HttpClient::download_file_part(string sAddress, int nPort, char *szBuf, string sRemotePath, long long llStart, long long llEnd, int &nFilePartSize)
{
	char szUrl[255] = { 0 };
	sprintf(szUrl, "http://%s:%d/Storage/download/part?path=%s", sAddress.c_str(), nPort, sRemotePath.c_str());

	struct event_base* baseRedirect;
	struct evhttp_connection* connRedirect;
	struct evhttp_request* reqRedirect;

	baseRedirect = event_base_new();
	connRedirect = evhttp_connection_base_new(baseRedirect, NULL, sAddress.c_str(), nPort);
	Item item;
	item.pBase = baseRedirect;
	item.pHttp = this;
	reqRedirect = evhttp_request_new(http_request_done, &item);
	char szRange[255];
	sprintf(szRange, "bytes %ld-%ld", llStart, llEnd);

	evhttp_add_header(evhttp_request_get_output_headers(reqRedirect), "Range", szRange);


	evhttp_make_request(connRedirect, reqRedirect, EVHTTP_REQ_GET, szUrl);
	event_base_dispatch(baseRedirect);

	// 返回数据
	bool bRet = false;
	if (m_nHttpCode == 200)
	{
		size_t stReal = 0;
		nFilePartSize = (int)Base64_Decode(szBuf, m_jsonResponseData["data"].asString().c_str(), m_jsonResponseData["data"].asString().length());
		bRet = true;
	}
	else
	{
		m_sErrorCode = "1";
	}
	evhttp_connection_free(connRedirect);
	event_base_free(baseRedirect);
	return bRet;
}

bool HttpClient::download_file_part(string sAddress, int nPort, string sLocalPath, string sRemotePath, long long llStart, long long llEnd)
{
	char szUrl[255] = { 0 };
	sprintf(szUrl, "http://%s:%d/Storage/download/part?path=%s", sAddress.c_str(), nPort, sRemotePath.c_str());

	struct event_base* baseRedirect;
	struct evhttp_connection* connRedirect;
	struct evhttp_request* reqRedirect;

	baseRedirect = event_base_new();
	connRedirect = evhttp_connection_base_new(baseRedirect, NULL, sAddress.c_str(), nPort);
	Item item;
	item.pBase = baseRedirect;
	item.pHttp = this;
	reqRedirect = evhttp_request_new(http_request_done, &item);
	char szRange[255];
	sprintf(szRange, "bytes %ld-%ld", llStart, llEnd);

	evhttp_add_header(evhttp_request_get_output_headers(reqRedirect), "Range", szRange);


	evhttp_make_request(connRedirect, reqRedirect, EVHTTP_REQ_GET, szUrl);
	event_base_dispatch(baseRedirect);

	// 返回数据
	bool bRet = false;
	if (m_nHttpCode == 200)
	{
		Base64_Decode(sLocalPath.c_str(), "ab", m_jsonResponseData["data"].asString().c_str(), m_jsonResponseData["data"].asString().length());
		bRet = true;
	}
	else
	{
		m_sErrorCode = "1";
	}
	evhttp_connection_free(connRedirect);
	event_base_free(baseRedirect);
	return bRet;
}

bool HttpClient::upload_file(string sAddress, int nPort, string sStorageId, string sFileName, string sLocalPath)
{
	char szUrl[255] = { 0 };
	sprintf(szUrl, "http://%s:%d/Storage/upload", sAddress.c_str(), nPort);

	struct event_base* baseRedirect;
	struct evhttp_connection* connRedirect;
	struct evhttp_request* reqRedirect;

	baseRedirect = event_base_new();
	connRedirect = evhttp_connection_base_new(baseRedirect, NULL, sAddress.c_str(), nPort);
	Item item;
	item.pBase = baseRedirect;
	item.pHttp = this;
	reqRedirect = evhttp_request_new(http_request_done, &item);

	// 设置数据
	Json::Value jsonPost;
	jsonPost["filename"] = sFileName;
	jsonPost["storageid"] = sStorageId;

	FILE *fp = fopen(sLocalPath.c_str(), "rb");
	if (!fp)
		return false;
	fseek(fp, 0, SEEK_END);
	long llTotle = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char *szBuf = new char[llTotle + 1];
	szBuf[llTotle] = 0;
	fread(szBuf, llTotle, 1, fp);
	fclose(fp);
	fp = NULL;

	jsonPost["data"] = Base64_Encode(szBuf, llTotle);
	string sData = Json::FastWriter().write(jsonPost);
	evbuffer_add(evhttp_request_get_output_buffer(reqRedirect), (const void *)sData.c_str(), sData.size());

	// 设置Range头
	char szRange[255];
	sprintf(szRange, "bytes %ld-%ld/%ld", 0, llTotle, llTotle);
	evhttp_add_header(evhttp_request_get_output_headers(reqRedirect), "Range", szRange);

	evhttp_make_request(connRedirect, reqRedirect, EVHTTP_REQ_POST, szUrl);
	event_base_dispatch(baseRedirect);

	// 返回数据
	bool bRet = false;
	if (m_nHttpCode == 200)
	{
		bRet = true;
	}
	else
	{
		m_sErrorCode = "1";
	}
	evhttp_connection_free(connRedirect);
	event_base_free(baseRedirect);
	return bRet;
}

bool HttpClient::upload_file_part(string sAddress, int nPort, string sFileName, string sLocalPath, string sRemotePath, long long llStart, long long llEnd)
{
	char szUrl[255] = { 0 };
	sprintf(szUrl, "http://%s:%d/Storage/upload/part", sAddress.c_str(), nPort);

	struct event_base* baseRedirect;
	struct evhttp_connection* connRedirect;
	struct evhttp_request* reqRedirect;

	baseRedirect = event_base_new();
	connRedirect = evhttp_connection_base_new(baseRedirect, NULL, sAddress.c_str(), nPort);
	Item item;
	item.pBase = baseRedirect;
	item.pHttp = this;
	reqRedirect = evhttp_request_new(http_request_done, &item);

	// 设置数据
	Json::Value jsonPost;
	jsonPost["filename"] = sFileName;
	jsonPost["storagepartid"]  = "";
	jsonPost["path"] = sRemotePath;

	FILE *fp = fopen(sLocalPath.c_str(), "rb");
	if (!fp)
		return false;
	long long llTotal = llEnd - llStart + 1;
	fseek(fp, llStart, SEEK_SET);
	char *szBuf = new char[llTotal + 1];
	szBuf[llTotal] = 0;
	fread(szBuf, llTotal, 1, fp);
	fclose(fp);
	fp = NULL;

	jsonPost["data"] = Base64_Encode(szBuf, llTotal);
	string sData = Json::FastWriter().write(jsonPost);
	evbuffer_add(evhttp_request_get_output_buffer(reqRedirect), (const void *)sData.c_str(), sData.size());

	// 设置Range头
	char szRange[255];
	sprintf(szRange, "bytes %ld-%ld/%ld", 0, llTotal, llTotal);
	evhttp_add_header(evhttp_request_get_output_headers(reqRedirect), "Range", szRange);

	evhttp_make_request(connRedirect, reqRedirect, EVHTTP_REQ_POST, szUrl);
	event_base_dispatch(baseRedirect);

	// 返回数据
	bool bRet = false;
	if (m_nHttpCode == 200)
	{
		bRet = true;
	}
	else
	{
		m_sErrorCode = "1";
	}
	evhttp_connection_free(connRedirect);
	event_base_free(baseRedirect);
	return bRet;
}

bool HttpClient::get(string &sHost, int &nPort, string &sPath, string &sParam)
{
	bool bRet = false;
	struct event_base* pBase = event_base_new();
	struct evhttp_connection* pConnection = evhttp_connection_base_new(pBase, NULL, sHost.c_str(), nPort);
	Item item;
	item.pBase = pBase;
	item.pHttp = this;
	struct evhttp_request* pRequest = evhttp_request_new(http_request_done, &item);

	// 初始化头
	evhttp_add_header(evhttp_request_get_output_headers(pRequest), "Host", sHost.c_str());
	evhttp_add_header(evhttp_request_get_output_headers(pRequest), "Content-Type", "application/json");

	// 初始化请求路径
	char szUrl[255] = { 0 };
	if (sParam.compare("") != 0)
		sprintf(szUrl, "http://%s:%d%s?%s", sHost.c_str(), nPort, sPath.c_str(), sParam.c_str());
	else
		sprintf(szUrl, "http://%s:%d%s", sHost.c_str(), nPort, sPath.c_str());

	// 发起请求
	evhttp_make_request(pConnection, pRequest, EVHTTP_REQ_GET, szUrl);
	event_base_dispatch(pBase);

	// 返回数据
	if (m_nHttpCode == 200)
	{
			bRet = true;
	}
	else
	{
		m_sErrorCode = "1";
	}

	evhttp_request_free(pRequest);
	evhttp_connection_free(pConnection);
	event_base_free(pBase);
	return bRet;
}

bool HttpClient::post(string &sHost, int &nPort, string &sPath, string &sData)
{
	bool bRet = false;
	struct event_base* pBase = event_base_new();
	struct evhttp_connection* pConnection = evhttp_connection_base_new(pBase, NULL, sHost.c_str(), nPort);
	Item item;
	item.pBase = pBase;
	item.pHttp = this;
	struct evhttp_request* pRequest = evhttp_request_new(http_request_done, &item);

	// 初始化头
	evhttp_add_header(evhttp_request_get_output_headers(pRequest), "Host", sHost.c_str());
	evhttp_add_header(evhttp_request_get_output_headers(pRequest), "Content-Type", "application/json");

	// 初始化请求路径
	char szUrl[255] = { 0 };
	sprintf(szUrl, "http://%s:%d%s", sHost.c_str(), nPort, sPath.c_str());

	// 设置数据
	evbuffer_add(evhttp_request_get_output_buffer(pRequest), (const void *)sData.c_str(), sData.size());

	// 发起请求
	evhttp_make_request(pConnection, pRequest, EVHTTP_REQ_POST, sPath.c_str());
	event_base_dispatch(pBase);

	// 返回数据
	if (m_nHttpCode == 200)
	{
			bRet = true;
	}
	else
	{
		m_sErrorCode = "1";
	}

	evhttp_request_free(pRequest);
	evhttp_connection_free(pConnection);
	event_base_free(pBase);
	return bRet;
}

bool HttpClient::get_input_headers(struct evhttp_request  *req, map<string, string> &mapHeader)
{
	struct evkeyvalq *headers;
	struct evkeyval *header;
	headers = evhttp_request_get_input_headers(req);
	for (header = headers->tqh_first; header; header = header->next.tqe_next)
		mapHeader.insert(pair<string, string>(header->key, header->value));

	if (mapHeader.size() > 0)
		return true;
	else
		return false;
}

char* HttpClient::get_input_buffer(struct evhttp_request  *req)
{
	char *szBuf = NULL;
	struct evbuffer *buf = evhttp_request_get_input_buffer(req);
	puts("Input data: <<<");
	if (evbuffer_get_length(buf))
	{
		int n;
		szBuf = new char[evbuffer_get_length(buf) + 1];
		n = evbuffer_remove(buf, szBuf, evbuffer_get_length(buf) + 1);
		if (n > 0)
			(void) fwrite(szBuf, 1, n, stdout);
		else
		{
			if (szBuf)
			{
				delete[] szBuf;
				szBuf = NULL;
			}
		}
	}
	puts(">>>");
	return szBuf;
}

string HttpClient::error_code()
{
	return m_sErrorCode;
}

string HttpClient::error_message()
{
	return m_sErrorMessage;
}

Json::Value& HttpClient::repsonse_data()
{
	return m_jsonResponseData;
}

void HttpClient::http_request_done(struct evhttp_request *req, void *arg)
{
	printf("send m_request ok...\n");
	Item*pItem = (Item*)arg;
	if (req == NULL)
	{
		pItem->pHttp->set_http_code(0);
		return;
	}
	pItem->pHttp->set_http_code(evhttp_request_get_response_code(req));
	size_t len = evbuffer_get_length(evhttp_request_get_input_buffer(req));
	unsigned char * str = evbuffer_pullup(evhttp_request_get_input_buffer(req), len);
	if (str == NULL)
	{
		printf("len = %d, str == NULL\n", len);
	}
	else
	{
		char *szBuf = new char[len + 1];
		memset(szBuf, 0, len + 1);
		memcpy(szBuf, str, len);
		Json::Value m_inputData;
		Json::Reader reader;
		if (reader.parse(szBuf, m_inputData))
			pItem->pHttp->set_http_respond_data(m_inputData);
		printf("len = %d, str = %s\n", len, szBuf);
		delete[] szBuf;
	}

	event_base_loopbreak((struct event_base*)pItem->pBase);
}