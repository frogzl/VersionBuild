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
		typedef bool(*FUNCNETWORK)(Respond_Data *pData);

		HELPER_API bool __stdcall post(HostType enHT, string sPluginID, string sPluginVersion, string sPath, Request_Data &inData, FUNCNETWORK);
		HELPER_API bool __stdcall get(HostType enHT, string sPluginID, string sPluginVersion, string sPath, Request_Data &inData, FUNCNETWORK);
		HELPER_API bool __stdcall upload(string sPluginID, string sPluginVersion, string sPath, Request_Data &inData, FUNCNETWORK);
		HELPER_API bool __stdcall download(string sPluginID, string sPluginVersion, string sPath, Request_Data &inData, FUNCNETWORK);
	}

}
