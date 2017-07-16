#include "Business.h"

Business::Business()
{
}

Business::~Business()
{
}

Business::Respond_Data Business::do_business(Request_Data &inData)
{
	m_rdInData = inData;
	process_task();
	return  m_rdOutData;
}

void Business::set_respond_header(string sKey, string sValue)
{
	m_rdOutData.mHeaders.insert(pair<string, string>(sKey, sValue));
}

void Business::set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription)
{
	m_rdOutData.nHttpStatus = nHttpStatus;
	m_rdOutData.jData["code"] = sCode;
	m_rdOutData.jData["message"] = sMessage;
	m_rdOutData.jData["discription"] = sDiscription;
}

void Business::set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription, Json::Value &jsonValue)
{
	m_rdOutData.nHttpStatus = nHttpStatus;
	m_rdOutData.jData["code"] = sCode;
	m_rdOutData.jData["message"] = sMessage;
	m_rdOutData.jData["discription"] = sDiscription;
	m_rdOutData.jData["data"] = jsonValue;
}

void Business::set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription, string &sValue)
{
	m_rdOutData.nHttpStatus = nHttpStatus;
	m_rdOutData.jData["code"] = sCode;
	m_rdOutData.jData["message"] = sMessage;
	m_rdOutData.jData["discription"] = sDiscription;
	m_rdOutData.jData["data"] = sValue;
}
