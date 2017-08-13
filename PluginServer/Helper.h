#pragma once
#include <string>
#include "Common.h"
using namespace std;
struct Helper::Respond_Data;
typedef bool(*FUNCNETWORK)(Helper::Respond_Data *pData);

class Helper
{
public:
	typedef struct
	{
		std::map<std::string, std::string> mHeaders;	// ����ͷ��Ϣ
		std::vector<std::string> vecParameters; // url�ϵĲ�����vecParameters[0]��һ��������vecParameters[1]�ڶ��������ȵ�
		std::map<std::string, std::string> mConditions; // url�ϡ��������������
		Json::Value jData;				// ����������
	}Request_Data;

	typedef struct
	{
		int nHttpStatus;				// respond http ״̬��
		Json::Value jData;				// respond data
		std::map<std::string, std::string> mHeaders;	// respond custom headers
	}Respond_Data;
	typedef struct
	{
		struct event_base* pBase;
		Respond_Data *pData;
	}Item;
public:
	bool post(string sPluginID, string sPluginVersion, Request_Data &inData, FUNCNETWORK);
	bool get(string sPluginID, string sPluginVersion, Request_Data &inData, FUNCNETWORK);
	bool upload(string sPluginID, string sPluginVersion, Request_Data &inData, FUNCNETWORK);
	bool download(string sPluginID, string sPluginVersion, Request_Data &inData, FUNCNETWORK);
private:
	static void http_request_done(struct evhttp_request *req, void *arg);
private:

};

