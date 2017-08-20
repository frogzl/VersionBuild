// Helper.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "include/Helper.h"
#include "Http.h"
#include "SystemConfig.h"
namespace Helper
{
	HELPER_API bool __stdcall init_environment()
	{
		SystemConfig::instance()->init_config();
		return true;
	}

	namespace Network
	{
		HELPER_API bool __stdcall post(HostType enHT, string sPluginID, string sPluginVersion, string sPath, Request_Data &inData, FUNCNETWORK func, void*pArg)
		{
			Http http;
			if (http.post(enHT, sPluginID, sPluginVersion, sPath, inData))
			{
				Respond_Data &rd = http.Respond();
				return func(&rd, pArg);
			}
			else
				return false;
		}

		HELPER_API bool __stdcall post2(HostType enHT, string sUrl, Request_Data &inData, FUNCNETWORK func, void*pArg)
		{
			Http http;
			if (http.post(enHT, sUrl, inData))
			{
				Respond_Data &rd = http.Respond();
				return func(&rd, pArg);
			}
			else
				return false;
		}

		HELPER_API bool __stdcall get(HostType enHT, string sPluginID, string sPluginVersion, string sPath, Request_Data &inData, FUNCNETWORK func, void*pArg)
		{
			Http http;
			if (http.get(enHT, sPluginID, sPluginVersion, sPath, inData))
			{
				Respond_Data &rd = http.Respond();
				return func(&rd, pArg);
			}
			else
				return false;
		}

		HELPER_API bool __stdcall get2(HostType enHT, string sUrl, Request_Data &inData, FUNCNETWORK func, void*pArg)
		{
			Http http;
			if (http.get(enHT, sUrl, inData))
			{
				Respond_Data &rd = http.Respond();
				return func(&rd, pArg);
			}
			else
				return false;
		}

		HELPER_API bool __stdcall upload(string sPluginID, string sPluginVersion, string sPath, string sLocalPath)
		{
			Http http;
			if (http.upload(sPluginID, sPluginVersion, sPath, sLocalPath))
				return true;
			else
				return false;
		}

		HELPER_API bool __stdcall download(string sPluginID, string sPluginVersion, string sPath, string sLocalPath)
		{
			Http http;
			if (http.download(sPluginID, sPluginVersion, sPath, sLocalPath))
				return true;
			else
				return false;
		}

		HELPER_API bool __stdcall download_block(string sPluginID, string sPluginVersion, string sPath, int nStart, int nCount, char *szBuf)
		{
			Http http;
			if (http.download_block(sPluginID, sPluginVersion, sPath, , nStart, nCount, szBuf))
				return true;
			else
				return false;
		}
	}

}
