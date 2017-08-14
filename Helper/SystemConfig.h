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
	void init_config();

public:
	// reverse-proxy-server
	int _nRPSPort;
	string _sRPSIP;

	// guard-server
	int _nGSPort;
	string _sGSIP;
private:
	static SystemConfig* g_Instance;
};

