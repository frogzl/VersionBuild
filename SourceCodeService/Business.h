#pragma once
#include <map>
#include <json/json.h>

#define HTTP_OK			200	/**< request completed ok */
#define HTTP_NOCONTENT		204	/**< request does not have content */
#define HTTP_MOVEPERM		301	/**< the uri moved permanently */
#define HTTP_MOVETEMP		302	/**< the uri moved temporarily */
#define HTTP_NOTMODIFIED	304	/**< page was not modified from last */
#define HTTP_BADREQUEST		400	/**< invalid http request was made */
#define HTTP_NOTFOUND		404	/**< could not find content for uri */
#define HTTP_BADMETHOD		405 	/**< method not allowed for this uri */
#define HTTP_ENTITYTOOLARGE	413	/**<  */
#define HTTP_EXPECTATIONFAILED	417	/**< we can't handle this expectation */
#define HTTP_INTERNAL           500     /**< internal error */
#define HTTP_NOTIMPLEMENTED     501     /**< not implemented */
#define HTTP_SERVUNAVAIL	503	/**< the server is not available */

using namespace std;
class Business
{
public:
	typedef struct
	{
		map<string, string>mParameters; // url上的参数
		map<string, string> mHeaders;		// 报文头信息
		Json::Value jData;							// 报文体数据
	}Request_Data;

	typedef struct
	{
		int nHttpStatus;							// respond http 状态码
		Json::Value jData;						// respond data
		map<string, string> mHeaders; // respond custom headers
	}Respond_Data;
public:
	Business();
	~Business();

	Respond_Data do_business(Request_Data &inData);

	// 业务处理方法，每个实现类必须实现
	virtual void process_task() = 0;
	// 后台处理方法，如需使用，重载即可
	virtual void background_process() = 0;

protected:
	void set_respond_header(string sKey, string sValue);
	void set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription);
	void set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription, Json::Value &jsonValue);
	void set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription, string &sValue);
protected:
	char *m_szBuf;
	Request_Data m_rdInData;
	Respond_Data m_rdOutData;
};
