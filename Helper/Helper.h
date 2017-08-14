// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� HELPER_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// HELPER_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef HELPER_EXPORTS
#define HELPER_API extern "C" __declspec(dllexport)
#else
#define HELPER_API __declspec(dllimport)
#endif
#include "HelperTypes.h"
namespace Helper
{
	HELPER_API bool __stdcall init_environment();
	namespace Network 
	{
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
			std::map<string, string> mHeaders;	// respond custom headers
		}Respond_Data;

		typedef struct
		{
			struct event_base* pBase;
			Respond_Data *pData;
		}Item;

		typedef bool(*FUNCNETWORK)(Respond_Data *pData);

		HELPER_API bool __stdcall post(HostType enHT, string sPluginID, string sPluginVersion, Request_Data &inData, FUNCNETWORK);
		HELPER_API bool __stdcall get(HostType enHT, string sPluginID, string sPluginVersion, Request_Data &inData, FUNCNETWORK);
		HELPER_API bool __stdcall upload(string sPluginID, string sPluginVersion, Request_Data &inData, FUNCNETWORK);
		HELPER_API bool __stdcall download(string sPluginID, string sPluginVersion, Request_Data &inData, FUNCNETWORK);
	}

}
