// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� SERVICESLAVESTORAGE_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// SERVICESLAVESTORAGE_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef SERVICESLAVESTORAGE_EXPORTS
#define SERVICESLAVESTORAGE_API __declspec(dllexport)
#else
#define SERVICESLAVESTORAGE_API __declspec(dllimport)
#endif

// �����Ǵ� ServiceSlaveStorage.dll ������
class SERVICESLAVESTORAGE_API CServiceSlaveStorage {
public:
	CServiceSlaveStorage(void);
	// TODO:  �ڴ�������ķ�����
};

extern SERVICESLAVESTORAGE_API int nServiceSlaveStorage;

SERVICESLAVESTORAGE_API int fnServiceSlaveStorage(void);
