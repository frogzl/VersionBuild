#pragma once
#include "include/BusinessInterface.h"
using namespace std;
class BusinessTemplate:public BusinessInterface
{
public:
	BusinessTemplate();
	~BusinessTemplate();

	Request_Data& request_data();
	Respond_Data& respond_data();

	void set_request_data(Request_Data &rd);
	void set_respond_header(string sKey, string sValue);
	void set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription);
	void set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription, Json::Value &jsonValue);
	void set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription, string &sValue);
protected:
	char *m_szBuf;
	Request_Data m_rdInData;
	Respond_Data m_rdOutData;
};