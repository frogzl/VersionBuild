#pragma once
#include <json/json.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
class SystemConfig
{
public:
	SystemConfig();
	~SystemConfig();
	static SystemConfig* instance() 
	{
		if (g_Instance == 0)
			g_Instance = new SystemConfig();
		return g_Instance;
	}

	void initConfig();
	string getStoragePath();
	string getStorageTmpPath();
	int m_nWorker;
	int m_nNetworkPort;
	int m_nBacklog;
	string m_sServiceGuid;
	unsigned int m_nServiceType;
	string m_sHost;
	string m_sUser;
	string m_sPassword;
	string m_sName;
	int m_nDBPort;
private:
	static SystemConfig* g_Instance;
};

