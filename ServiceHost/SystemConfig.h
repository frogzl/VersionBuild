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

public:
	// server
	string m_sGuid;
	int m_nWorker;
	int m_nPort;
	int m_nBacklog;
	string m_sIP;

	// reverse-proxy-server
	int m_nRPSPort;
	string m_sRPSIP;

	// guard-server
	int m_nGSPort;
	string m_sGSIP;

	// database-connect
	string m_sDBHost;
	string m_sDBUser;
	string m_sDBPassword;
	string m_sDBName;
	int m_nDBPort;
private:
	static SystemConfig* g_Instance;
};

