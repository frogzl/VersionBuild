#pragma once
#include <map>
#include <json/json.h>
using namespace std;
class Business
{
public:
	typedef struct
	{
		map<string, string>mParameters; // url�ϵĲ���
		map<string, string> mHeaders;		// ����ͷ��Ϣ
		Json::Value jData;							// ����������
	}Request_Data;

	typedef struct
	{
		int nHttpStatus;							// respond http ״̬��
		Json::Value jData;						// respond data
		map<string, string> mHeaders; // respond custom headers
	}Respond_Data;
public:
	Business();
	~Business();

	Respond_Data do_business(Request_Data &inData);

	// ҵ��������ÿ��ʵ�������ʵ��
	virtual void process_task() = 0;
	// ��̨������������ʹ�ã����ؼ���
	virtual void background_process() = 0;

	int http_status();
	Json::Value& respond_data();
	map<std::string, std::string>& CustomHeaders();
protected:
	map<string, string>& input_headers();
	Json::Value& input_data();
	map<string, string>& input_parameters();

	bool is_input_header_ready();
	bool is_input_data_ready();

	void set_respond_header(string sKey, string sValue);
	void set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription);
	void set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription, Json::Value &jsonValue);
	void set_respond_back(int nHttpStatus, string sCode, string sMessage, string sDiscription, string &sValue);
protected:
	char *m_szBuf;
	map<string, string> m_inputHeaders;
	Json::Value m_inputData;
	map<string, string> m_inputParameters;
private:

	bool m_bIsInputHeaderReady;
	bool m_bIsInputDataReady;

	int m_nHttpStatus;			// respond http ״̬��
	Json::Value m_outputData; // respond data
	map<std::string, std::string> m_outputHeaders; // respond custom headers
};
