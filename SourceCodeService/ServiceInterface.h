#pragma once
#include "Business.h"
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
};

