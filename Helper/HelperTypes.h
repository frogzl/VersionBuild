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
			map<string, string> mHeaders;	// ����ͷ��Ϣ
			vector<string> vecParameters; // url�ϵĲ�����vecParameters[0]��һ��������vecParameters[1]�ڶ��������ȵ�
			map<string, string> mConditions; // url�ϡ��������������
			string sData;				// ����������
		}Request_Data;

		typedef struct
		{
			int nHttpStatus;				// respond http ״̬��
			string sData;				// respond data
			map<string, string> mHeaders;	// respond custom headers
		}Respond_Data;
	}
}