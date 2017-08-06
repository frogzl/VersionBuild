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

void SystemConfig::initConfig()
{
	char szPath[255];
	GetModuleFileNameA(NULL, szPath, 255);
	string sPath(szPath);
	int nPos = (int)sPath.find("VersionBuildServer.exe", 0);
	int nCount = sizeof("VersionBuildServer.exe");
	sPath.erase(nPos, nCount - 1);
	sPath += "config";
	ifstream is;
	is.open(sPath, std::ios::binary);
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(is, root))   ///root保存整个Json对象的value
	{
		if (!root["service"].isNull())
		{
			Json::Value obj = root["service"];
			m_sServiceGuid = obj["guid"].asString();
			m_nServiceType = obj["type"].asInt();
		}
		if (!root["network"].isNull())
		{
			Json::Value obj = root["network"];
			m_nWorker = obj["worker"].asInt();
			m_nBacklog = obj["backlog"].asInt();
			m_nNetworkPort = obj["port"].asInt();
		}
		if (!root["database-connect"].isNull())
		{
			Json::Value obj = root["database-connect"];
			m_sHost = obj["host"].asString();
			m_sUser = obj["user"].asString();
			m_sPassword = obj["password"].asString();
			m_sName = obj["name"].asString();
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
