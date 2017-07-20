// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� MICROTASKPLUGIN_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// MICROTASKPLUGIN_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef DLL_EXPORTS
#define DlLL_API __declspec(dllexport)
#else
#define DlLL_API __declspec(dllimport)
#endif
#include "TaskInterface.h"
DlLL_API const char* library_version();

DlLL_API TaskInterface* create_plugin_template();

DlLL_API TaskInterface*  instantiate_plugin_template(TaskInterface *pInterface);