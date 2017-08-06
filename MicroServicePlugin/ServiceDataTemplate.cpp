#include "ServiceDataTemplate.h"

ServiceDataTemplate::ServiceDataTemplate()
{
}

ServiceDataTemplate::~ServiceDataTemplate()
{
}

Request_Data& ServiceDataTemplate::request_data()
{
	return m_rdInData;
}

Respond_Data& ServiceDataTemplate::respond_data()
{
	return m_rdOutData;
}

void ServiceDataTemplate::set_request_data(Request_Data &rd)
{
	m_rdInData = rd;
}

void ServiceDataTemplate::set_request_headers(std::map<std::string, std::string> &mHeaders)
{
	m_rdInData.mHeaders = mHeaders;
}

void ServiceDataTemplate::set_request_parameters(std::map<int, std::string> &mParameters)
{
	m_rdInData.mParameters = mParameters;
}

void ServiceDataTemplate::set_request_conditions(std::map<std::string, std::string> mConditions)
{
	m_rdInData.mConditions = mConditions;
}

void ServiceDataTemplate::set_request_body(Json::Value &jData)
{
	m_rdInData.jData = jData;
}

void ServiceDataTemplate::insert_request_header(const char* szKey, const char* szValue)
{
	m_rdInData.mHeaders.insert(std::pair<std::string, std::string>(szKey, szValue));
}

void ServiceDataTemplate::insert_request_parameter(int &nKey, const char* szValue)
{
	m_rdInData.mParameters.insert(std::pair<int, std::string>(nKey, szValue));
}

void ServiceDataTemplate::insert_request_condition(const char* szKey, const char* szValue)
{
	m_rdInData.mConditions.insert(std::pair<std::string, std::string>(szKey, szValue));
}

void ServiceDataTemplate::set_respond_header(string sKey, string sValue)
{
	m_rdOutData.mHeaders.insert(pair<string, string>(sKey, sValue));
}

void ServiceDataTemplate::set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription)
{
	m_rdOutData.nHttpStatus = nHttpStatus;
	m_rdOutData.jData["code"] = sCode;
	m_rdOutData.jData["message"] = sMessage;
	m_rdOutData.jData["discription"] = sDiscription;
}

void ServiceDataTemplate::set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription, Json::Value &jsonValue)
{
	m_rdOutData.nHttpStatus = nHttpStatus;
	m_rdOutData.jData["code"] = sCode;
	m_rdOutData.jData["message"] = sMessage;
	m_rdOutData.jData["discription"] = sDiscription;
	m_rdOutData.jData["data"] = jsonValue;
}

void ServiceDataTemplate::set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription, string &sValue)
{
	m_rdOutData.nHttpStatus = nHttpStatus;
	m_rdOutData.jData["code"] = sCode;
	m_rdOutData.jData["message"] = sMessage;
	m_rdOutData.jData["discription"] = sDiscription;
	m_rdOutData.jData["data"] = sValue;
}
