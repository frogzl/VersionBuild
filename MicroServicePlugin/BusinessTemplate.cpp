#include "BusinessTemplate.h"

BusinessTemplate::BusinessTemplate()
{
}

BusinessTemplate::~BusinessTemplate()
{
}

Request_Data& BusinessTemplate::request_data()
{
	return m_rdInData;
}

Respond_Data& BusinessTemplate::respond_data()
{
	return m_rdOutData;
}

void BusinessTemplate::set_request_data(Request_Data &rd)
{
	m_rdInData = rd;
}

void BusinessTemplate::set_respond_header(string sKey, string sValue)
{
	m_rdOutData.mHeaders.insert(pair<string, string>(sKey, sValue));
}

void BusinessTemplate::set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription)
{
	m_rdOutData.nHttpStatus = nHttpStatus;
	m_rdOutData.jData["code"] = sCode;
	m_rdOutData.jData["message"] = sMessage;
	m_rdOutData.jData["discription"] = sDiscription;
}

void BusinessTemplate::set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription, Json::Value &jsonValue)
{
	m_rdOutData.nHttpStatus = nHttpStatus;
	m_rdOutData.jData["code"] = sCode;
	m_rdOutData.jData["message"] = sMessage;
	m_rdOutData.jData["discription"] = sDiscription;
	m_rdOutData.jData["data"] = jsonValue;
}

void BusinessTemplate::set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription, string &sValue)
{
	m_rdOutData.nHttpStatus = nHttpStatus;
	m_rdOutData.jData["code"] = sCode;
	m_rdOutData.jData["message"] = sMessage;
	m_rdOutData.jData["discription"] = sDiscription;
	m_rdOutData.jData["data"] = sValue;
}
