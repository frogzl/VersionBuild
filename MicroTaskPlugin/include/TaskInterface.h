#pragma once

class TaskInterface
{
public:
	virtual ~TaskInterface();
	// ������
	virtual void destory() = 0;
	// ���ڻ�ȡ·����Ϣ
	virtual int route_infos(Route_Info *&routeInfos) = 0;
	// ���ڻ�ȡΨһ��ʶ
	virtual const char* unique_id() = 0;
	// ���ڻ�ȡ������
	virtual const char* name() = 0;
	// ���ڻ�ȡ�汾
	virtual const char* version() = 0;
	// ���ڸ���APIִ��
	virtual const char* dispatch_by_route_path(int nIndex, BusinessInterface *pB) = 0;
	// ע�������
	virtual bool register_service_name(const char *szName) = 0;
	// ע�����Ψһ��ʶ
	virtual bool register_service_unique_id(const char *szID) = 0;
	// ע�����汾��
	virtual bool register_service_version(const char *szVersion) = 0;
	// ע��·��
	virtual bool register_http_route(const char *szPath, const char *szOperation, FuncProcess pCallBack) = 0;
};

