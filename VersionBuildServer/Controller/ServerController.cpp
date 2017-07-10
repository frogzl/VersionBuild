#include "ServerController.h"

namespace Controller
{
	Define_Controller_Class_Common(ServerController, Controller)
		Controller_Class_Function_Filter(init)
		Controller_Class_Function_Filter(resource_query)
		Define_Controller_Class_Common_End()

		Define_Controller_Class_Function(ServerController, init)
	{
		printf("ServerController, init\n");
	}

	Define_Controller_Class_Function(ServerController, resource_query)
	{
		Json::Value replyRoot;
		printf("ServerController, resource_query\n");

		Json::Value replyData;
		char *szEnv = NULL;
		szEnv = getenv("include");
		if (szEnv)
		{
			Json::Value includeData;
			includeData["name"] = "include";
			includeData["value"] = szEnv;
			replyData["environment variable"].append(includeData);
		}
		szEnv = getenv("lib");
		if (szEnv)
		{
			Json::Value libpathData;
			libpathData["name"] = "lib";
			libpathData["value"] = szEnv;
			replyData["environmentvariable"].append(libpathData);
		}
		szEnv = getenv("path");
		if (szEnv)
		{
			Json::Value pathData;
			pathData["name"] = "path";
			pathData["value"] = szEnv;
			replyData["environmentvariable"].append(pathData);
		}

		// 获取磁盘信息
		DWORD dwSize = GetLogicalDriveStringsA(0, NULL);
		char *szDriveStrings = new char[dwSize + 1];
		dwSize = GetLogicalDriveStringsA(dwSize + 1, szDriveStrings);
		char *pszBegin = szDriveStrings;
		char *pszEnd = szDriveStrings + dwSize + 1;
		while (pszBegin != pszEnd)
		{
			ULARGE_INTEGER nFreeBytesAvailable;
			ULARGE_INTEGER nTotalNumberOfBytes;
			ULARGE_INTEGER nTotalNumberOfFreeBytes;
			if (GetDiskFreeSpaceExA(pszBegin, &nFreeBytesAvailable, &nTotalNumberOfBytes, &nTotalNumberOfFreeBytes))
			{
				char szFreeBytesAvailable[256];
				char szTotalNumberOfBytes[256];
				char szTotalNumberOfFreeBytes[256];
				sprintf(szFreeBytesAvailable, "%lld", nFreeBytesAvailable);
				sprintf(szTotalNumberOfBytes, "%lld", nTotalNumberOfBytes);
				sprintf(szTotalNumberOfFreeBytes, "%lld", nTotalNumberOfFreeBytes);

				Json::Value partitionData;
				partitionData["name"] = pszBegin;
				partitionData["freebytesavailable"] = szFreeBytesAvailable;
				partitionData["totalnumberofbytes"] = szTotalNumberOfBytes;
				partitionData["totalnumberoffreebytes"] = szTotalNumberOfFreeBytes;
				replyData["partition"].append(partitionData);
			}
			pszBegin += (strlen(pszBegin) + 1);
		}
		replyRoot["data"] = replyData;

		// 返回数据
		struct evbuffer *evb = evbuffer_new();
		replyRoot["code"] = "0";
		replyRoot["message"] = "successed";
		evhttp_add_header(evhttp_request_get_output_headers(m_req), "Content-Type", "application/json");
		string sReplyData = Json::FastWriter().write(replyRoot);
		evbuffer_add_printf(evb, "%s", sReplyData.c_str());
		evhttp_send_reply(m_req, HTTP_OK, "OK", evb);

		if (evb)
			evbuffer_free(evb);
	}
}