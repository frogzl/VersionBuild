#pragma once
#include "Business.h"
#define Http_Operator_Get			"get"		//	�����ȡRequest - URI����ʶ����Դ
#define Http_Operator_Post			"post"		//	��Request - URI����ʶ����Դ�󸽼��µ�����
#define Http_Operator_Head			"head"		//	�����ȡ��Request - URI����ʶ����Դ����Ӧ��Ϣ��ͷ
#define Http_Operator_Put				"put"		//	����������洢һ����Դ������Request - URI��Ϊ���ʶ
#define Http_Operator_Delete		"delete"	//	���������ɾ��Request - URI����ʶ����Դ
#define Http_Operator_Trace			"trace"		// ��������������յ���������Ϣ����Ҫ���ڲ��Ի����
#define Http_Operator_Options		"options"	//	�����ѯ�����������ܣ����߲�ѯ����Դ��ص�ѡ�������

class ServiceInterface
{
public:
	typedef struct
	{
		const char *szPath;					// ·��ģ��
		const char *szoperation;			// http ����
		const char *szBusinessName;	// ���������
		int nIndex;								// ����
	}Route_Info;
	void destory();
	const char* library_version();
public:
	virtual ~ServiceInterface();
	// ���ڻ�ȡ·����Ϣ
	virtual int route_infos(Route_Info *&routeInfos) = 0;
	// ���ڻ�ȡΨһ��ʶ
	virtual const char* unique_id() = 0;
	// ���ڻ�ȡ������
	virtual const char* name() = 0;
	// ���ڻ�ȡ�汾
	virtual const char* version() = 0;
	// ���ڸ���APIִ��
	virtual const char* dispatch_by_route_path(int nIndex, Business::Request_Data &inData, Business::Respond_Data &outData) = 0;
	// ��ʼ��Ҫע���·�ɸ�������Ҫ��register_http_routes�ӿڵ��ʼ����
	virtual bool init_route_count(int nCount) = 0;
	// ע��·��
	virtual bool register_http_route(const char *szPath, const char *szBusinessName, const char *szOperation) = 0;
	// ע�������
	virtual bool register_service_name(const char *szName) = 0;
	// ע�����Ψһ��ʶ
	virtual bool register_service_unique_id(const char *szID) = 0;
	// ע�����汾��
	virtual bool register_service_version(const char *szVersion) = 0;
	// ע��ҵ��
	virtual bool register_service_business(const char *szBusinessName, FuncCreate pCallBack) = 0;
};

