#pragma once
#include <json/json.h>
#include "../Common.h"
#include "../Controller/Controller.h"
using namespace std; 
namespace B
{
	class Business
	{
	public:
		Business(Controller::Controller *pController);
		~Business();

		// ҵ��������ÿ��ʵ�������ʵ��
		virtual void process_task() = 0;
		// ��̨������������ʹ�ã����ؼ���
		virtual void background_process() = 0;
		// �ж��Ƿ���Ҫ��ת�������Ҫ������Ŀ��host��port
		virtual bool is_need_redirect(string &sHost, int &nPort);
		// �����Խ��̷�ʽִ������
		virtual bool process_command(string &sBuildCmd, string &sErrorMsg, LPCSTR lpCurrentDirectory = NULL);

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
		Controller::Controller *m_pController;

		bool m_bIsInputHeaderReady;
		bool m_bIsInputDataReady;

		int m_nHttpStatus;			// respond http ״̬��
		Json::Value m_outputData; // respond data
		map<std::string, std::string> m_outputHeaders; // respond custom headers
	};
}

