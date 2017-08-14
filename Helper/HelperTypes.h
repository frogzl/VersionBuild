#pragma once
#include <map>
#include <vector>
#include <string>
using namespace std;

namespace Helper
{
	namespace Network
	{
		enum HostType
		{
			enReverseProxy,
			enGuard
		};

		typedef struct
		{
			map<string, string> mHeaders;	// 报文头信息
			map<string, string> mConditions; // url上“？”后面的条件
			string sData;				// 报文体数据
		}Request_Data;

		typedef struct
		{
			int nHttpStatus;				// respond http 状态码
			string sData;				// respond data
			map<string, string> mHeaders;	// respond custom headers
		}Respond_Data;
	}
}