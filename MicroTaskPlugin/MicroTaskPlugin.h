// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� MICROTASKPLUGIN_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// MICROTASKPLUGIN_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef MICROTASKPLUGIN_EXPORTS
#define MICROTASKPLUGIN_API __declspec(dllexport)
#else
#define MICROTASKPLUGIN_API __declspec(dllimport)
#endif

// �����Ǵ� MicroTaskPlugin.dll ������
class MICROTASKPLUGIN_API CMicroTaskPlugin {
public:
	CMicroTaskPlugin(void);
	// TODO:  �ڴ�������ķ�����
};

extern MICROTASKPLUGIN_API int nMicroTaskPlugin;

MICROTASKPLUGIN_API int fnMicroTaskPlugin(void);
