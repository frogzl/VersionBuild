#pragma once
#include "include/ServiceData.h"
using namespace std;
class ServiceDataTemplate :public ServiceData
{
public:
	ServiceDataTemplate();
	~ServiceDataTemplate();

	Request_Data& request_data();
	Respond_Data& respond_data();

	void set_request_data(Request_Data &rd);
	void set_request_headers(std::map<std::string, std::string> &mHeaders);
	void set_request_parameters(std::vector<std::string> &vecParameters);
	void set_request_conditions(std::map<std::string, std::string> mConditions);
	void set_request_body(Json::Value &jData);
	void insert_request_header(const char* szKey, const char* szValue);
	void insert_request_parameter(const char* szValue);
	void insert_request_condition(const char* szKey, const char* szValue);

	void set_respond_header(string sKey, string sValue);
	void set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription);
	void set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription, Json::Value &jsonValue);
	void set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription, string &sValue);
protected:
	char *m_szBuf;
	Request_Data m_rdInData;
	Respond_Data m_rdOutData;
};