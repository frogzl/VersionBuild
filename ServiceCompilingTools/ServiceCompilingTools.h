// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� SERVICECOMPILINGTOOLS_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// SERVICECOMPILINGTOOLS_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef SERVICECOMPILINGTOOLS_EXPORTS
#define SERVICECOMPILINGTOOLS_API __declspec(dllexport)
#else
#define SERVICECOMPILINGTOOLS_API __declspec(dllimport)
#endif

// �����Ǵ� ServiceCompilingTools.dll ������
class SERVICECOMPILINGTOOLS_API CServiceCompilingTools {
public:
	CServiceCompilingTools(void);
	// TODO:  �ڴ�������ķ�����
};

extern SERVICECOMPILINGTOOLS_API int nServiceCompilingTools;

SERVICECOMPILINGTOOLS_API int fnServiceCompilingTools(void);
