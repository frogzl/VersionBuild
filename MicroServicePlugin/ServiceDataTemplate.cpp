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
