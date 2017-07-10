#include "Business.h"

namespace B
{
	Business::Business(Controller::Controller *pController)
	{
		m_szBuf = new char [Buffer_Size];
		m_outputHeaders.clear();
		m_pController = pController;
		pController->get_input_parameters(m_inputParameters);
		m_bIsInputHeaderReady = pController->get_input_headers(m_inputHeaders);
		char *szBuf = pController->get_input_buffer();
		if (szBuf == NULL)
			m_bIsInputDataReady = false;
		else
		{
			Json::Reader reader;
			if (reader.parse(szBuf, m_inputData))
			{
				m_bIsInputDataReady = true;
			}
			else
			{
				m_bIsInputDataReady = false;
			}
			delete szBuf;
		}
	}


	Business::~Business()
	{
		delete [] m_szBuf;
	}

	bool Business::is_need_redirect(string &sHost, int &nPort)
	{
		return false;
	}

	bool Business::process_command(string &sBuildCmd, string &sErrorMsg, LPCSTR lpCurrentDirectory)
	{
		STARTUPINFOA si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&pi, sizeof(pi));
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		HANDLE hOpenFile = (HANDLE)CreateFile(L"E:\\a.text", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		si.hStdOutput = hOpenFile;
		if (!CreateProcessA(NULL, (char*)sBuildCmd.c_str(), NULL, NULL, FALSE, 0, NULL, lpCurrentDirectory, &si, &pi))
		{
			// ´´½¨Ê§°Ü
			char szBuf[255];
			sprintf(szBuf,"get last error %d", GetLastError());
			sErrorMsg = szBuf;
			return false;
		}
		CloseHandle(hOpenFile);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		return true;
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
}
