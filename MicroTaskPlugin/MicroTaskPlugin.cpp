// MicroTaskPlugin.cpp : ���� DLL Ӧ�ó���ĵ���������
//
#include "MicroTaskPlugin.h"


// ���ǵ���������һ��ʾ��
MICROTASKPLUGIN_API int nMicroTaskPlugin=0;

// ���ǵ���������һ��ʾ����
MICROTASKPLUGIN_API int fnMicroTaskPlugin(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� MicroTaskPlugin.h
CMicroTaskPlugin::CMicroTaskPlugin()
{
	return;
}
