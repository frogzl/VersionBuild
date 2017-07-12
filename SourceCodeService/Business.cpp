#include "stdafx.h"
#include "Business.h"

Business::Business()
{
}

Business::~Business()
{
}

Business::Respond_Data Business::do_business(Request_Data &inData)
{
	Respond_Data outData;
	return  outData;
}

int Business::http_status()
{
	return m_nHttpStatus;
}

Json::Value& Business::respond_data()
{
	return m_outputData;
}

map<std::string, std::string>& Business::CustomHeaders()
{
	return m_outputHeaders;
}

map<string, string>& Business::input_headers()
{
	return m_inputHeaders;
}

Json::Value& Business::input_data()
{
	return m_inputData;
}

map<string, string>& Business::input_parameters()
{
	return m_inputParameters;
}

bool Business::is_input_header_ready()
{
	return m_bIsInputHeaderReady;
}

bool Business::is_input_data_ready()
{
	return m_bIsInputDataReady;
}

void Business::set_respond_header(string sKey, string sValue)
{
	m_outputHeaders.insert(pair<string, string>(sKey, sValue));
}

void Business::set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription)
{
	m_nHttpStatus = nHttpStatus;
	m_outputData["code"] = sCode;
	m_outputData["message"] = sMessage;
	m_outputData["discription"] = sDiscription;
}

void Business::set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription, Json::Value &jsonValue)
{
	m_nHttpStatus = nHttpStatus;
	m_outputData["code"] = sCode;
	m_outputData["message"] = sMessage;
	m_outputData["discription"] = sDiscription;
	m_outputData["data"] = jsonValue;
}

void Business::set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription, string &sValue)
{
	m_nHttpStatus = nHttpStatus;
	m_outputData["code"] = sCode;
	m_outputData["message"] = sMessage;
	m_outputData["discription"] = sDiscription;
	m_outputData["data"] = sValue;
}
