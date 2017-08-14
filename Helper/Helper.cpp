// Helper.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Helper.h"
#include "Http.h"
#include "SystemConfig.h"
namespace Helper
{
	HELPER_API bool __stdcall init_environment()
	{
		SystemConfig::instance()->init_config();
	}

	namespace Network
	{
		HELPER_API bool __stdcall post(HostType enHT, string sPluginID, string sPluginVersion, Request_Data &inData, FUNCNETWORK func)
		{
			Http http;
			if (http.post(enHT, sPluginID, sPluginVersion, inData))
			{
				Respond_Data &rd = http.Respond();
				return func(&rd);
			}
			else
				return false;
		}

		HELPER_API bool __stdcall get(HostType enHT, string sPluginID, string sPluginVersion, Request_Data &inData, FUNCNETWORK func)
		{
			Http http;
			if (http.get(enHT, sPluginID, sPluginVersion, inData))
			{
				Respond_Data &rd = http.Respond();
				return func(&rd);
			}
			else
				return false;
		}

		HELPER_API bool __stdcall upload(string sPluginID, string sPluginVersion, Request_Data &inData, FUNCNETWORK func)
		{
			Http http;
			if (http.upload(sPluginID, sPluginVersion, inData))
			{
				Respond_Data &rd = http.Respond();
				return func(&rd);
			}
			else
				return false;
		}

		HELPER_API bool __stdcall download(string sPluginID, string sPluginVersion, Request_Data &inData, FUNCNETWORK func)
		{
			Http http;
			if (http.download(sPluginID, sPluginVersion, inData))
			{
				Respond_Data &rd = http.Respond();
				return func(&rd);
			}
			else
				return false;
		}
	}

}
