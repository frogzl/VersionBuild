#pragma once
#include <string>
#include <json/json.h>
#include <map>

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

typedef struct
{
	map<string, string>mParameters; // url上的参数
	map<string, string> mHeaders;	// 报文头信息
	Json::Value jData;				// 报文体数据
}Request_Data;

typedef struct
{
	int nHttpStatus;				// respond http 状态码
	Json::Value jData;				// respond data
	map<string, string> mHeaders;	// respond custom headers
}Respond_Data;

class BusinessInterface
{
public:
	virtual ~BusinessInterface();

	virtual Request_Data& request_data() = 0;
	virtual Respond_Data& respond_data() = 0;

	virtual void set_request_data(Request_Data &rd) = 0;
	virtual void set_respond_header(string sKey, string sValue) = 0;
	virtual void set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription) = 0;
	virtual void set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription, Json::Value &jsonValue) = 0;
	virtual void set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription, string &sValue) = 0;
};

typedef void(*FuncProcess)(BusinessInterface*);