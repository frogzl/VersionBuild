#include "SystemConfig.h"
#include <Windows.h>
#include <io.h>  
#include <direct.h>

SystemConfig* SystemConfig::g_Instance = 0;
SystemConfig::SystemConfig()
{
}


SystemConfig::~SystemConfig()
{
}

void SystemConfig::init_config()
{
	char szPath[255];
	GetModuleFileNameA(NULL, szPath, 255);
	string sPath(szPath);
	int nPos = (int)sPath.find("PluginServer.exe", 0);
	int nCount = sizeof("PluginServer.exe");
	sPath.erase(nPos, nCount - 1);
	sPath += "config";
	ifstream is;
	is.open(sPath, std::ios::binary);
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(is, root))   ///root保存整个Json对象的value
	{
		if (!root["reverse-proxy-server"].isNull())
		{
			Json::Value obj = root["reverse-proxy-server"];
			m_nRPSPort = obj["port"].asInt();
			m_sRPSIP = obj["ip"].asString();
		}
		if (!root["guard-server"].isNull())
		{
			Json::Value obj = root["guard-server"];
			m_nGSPort = obj["port"].asInt();
			m_sGSIP = obj["ip"].asString();
		}
	}
}