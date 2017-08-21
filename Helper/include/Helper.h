// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� HELPER_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// HELPER_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef HELPER_EXPORTS
#define HELPER_API extern "C" __declspec(dllexport)
#else
#define HELPER_API extern "C" __declspec(dllimport)
#endif
#include "HelperTypes.h"
namespace Helper
{
	HELPER_API bool __stdcall init_environment();
	namespace Network 
	{
		HELPER_API bool __stdcall post(HostType enHT, string sPluginID, string sPluginVersion, string sPath, Request_Data &inData, FUNCNETWORK, void*);
		HELPER_API bool __stdcall post2(HostType enHT, string sUrl, Request_Data &inData, FUNCNETWORK, void*);
		HELPER_API bool __stdcall get(HostType enHT, string sPluginID, string sPluginVersion, string sPath, Request_Data &inData, FUNCNETWORK, void*);
		HELPER_API bool __stdcall get2(HostType enHT, string sUrl, Request_Data &inData, FUNCNETWORK, void*);
		HELPER_API bool __stdcall upload(string sPluginID, string sPluginVersion, string sPath, string sLocalPath);
		HELPER_API bool __stdcall download(string sPluginID, string sPluginVersion, string sPath, string sLocalPath);
		HELPER_API bool __stdcall download_block(string sPluginID, string sPluginVersion, string sPath, Request_Data &inData, char*szData);
	}

}
