// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� SLAVETASKSERVICE_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// SLAVETASKSERVICE_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef SLAVETASKSERVICE_EXPORTS
#define SLAVETASKSERVICE_API __declspec(dllexport)
#else
#define SLAVETASKSERVICE_API __declspec(dllimport)
#endif

// �����Ǵ� SlaveTaskService.dll ������
class SLAVETASKSERVICE_API CSlaveTaskService {
public:
	CSlaveTaskService(void);
	// TODO:  �ڴ�������ķ�����
};

extern SLAVETASKSERVICE_API int nSlaveTaskService;

SLAVETASKSERVICE_API int fnSlaveTaskService(void);
