#include "SystemConfig.h"
#include <Windows.h>
#include <io.h>  
#include <direct.h>

SystemConfig* SystemConfig::g_Instance = 0;
SystemConfig::SystemConfig()
{
	initConfig();
}


SystemConfig::~SystemConfig()
{
}

void SystemConfig::initConfig()
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
		if (!root["server"].isNull())
		{
			Json::Value obj = root["server"];
			m_sGuid = obj["guid"].asString();
			Json::Value objNetwork = root["network"];
			m_nWorker = objNetwork["worker"].asInt();
			m_nBacklog = objNetwork["backlog"].asInt();
			m_nPort = objNetwork["port"].asInt();
			m_sIP = objNetwork["ip"].asString();
		}
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
		if (!root["database-connect"].isNull())
		{
			Json::Value obj = root["database-connect"];
			m_sDBHost = obj["host"].asString();
			m_sDBUser = obj["user"].asString();
			m_sDBPassword = obj["password"].asString();
			m_sDBName = obj["name"].asString();
			m_nDBPort = obj["port"].asInt();
		}
	}
}

string SystemConfig::getStoragePath()
{
	char szPath[255];
	GetModuleFileNameA(NULL, szPath, 255);
	string sPath(szPath);
	int nPos = (int)sPath.find("VersionBuildServer.exe", 0);
	int nCount = sizeof("VersionBuildServer.exe");
	sPath.erase(nPos, nCount - 1);
	sPath += "storage";
	if (_access(sPath.c_str(), 0) != 0)
		_mkdir(sPath.c_str());
	return sPath;
}

string SystemConfig::getStorageTmpPath()
{
	char szPath[255];
	GetModuleFileNameA(NULL, szPath, 255);
	string sPath(szPath);
	int nPos = (int)sPath.find("VersionBuildServer.exe", 0);
	int nCount = sizeof("VersionBuildServer.exe");
	sPath.erase(nPos, nCount - 1);
	sPath += "storage";
	if (_access(sPath.c_str(), 0) != 0)
		_mkdir(sPath.c_str());
	sPath += "\\"; 
	sPath += "tmp";
	if (_access(sPath.c_str(), 0) != 0)
		_mkdir(sPath.c_str());
	return sPath;
}
