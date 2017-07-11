#pragma once
#include <string>
using namespace std;
class ServiceController
{
public:
	typedef struct
	{
		const char *szPath;					// ·��ģ��
		const char *szoperation;			// http ����
		const char *szBusinessName;	// ���������
		int nIndex;						// ����
	}Route_Info;

	typedef struct 
	{
	}Request_Data;

	typedef struct
	{
	}Respond_Data;

public:
	ServiceController();
	~ServiceController();

	int route_infos(Route_Info *&routeInfos);
protected:
	/*
	 * ֧��ע���http��������
	 * GET				�����ȡRequest-URI����ʶ����Դ
	 * POST			��Request-URI����ʶ����Դ�󸽼��µ�����
	 * HEAD			�����ȡ��Request-URI����ʶ����Դ����Ӧ��Ϣ��ͷ
	 * PUT				����������洢һ����Դ������Request-URI��Ϊ���ʶ
	 * DELETE			���������ɾ��Request-URI����ʶ����Դ
	 * TRACE			��������������յ���������Ϣ����Ҫ���ڲ��Ի����
	 * OPTIONS		�����ѯ�����������ܣ����߲�ѯ����Դ��ص�ѡ�������
	 */
	bool register_http_get(const char *szPath, const char *szBusinessName);
	bool register_http_http_post(const char *szPath, const char *szBusinessName);
	bool register_http_head(const char *szPath, const char *szBusinessName);
	bool register_http_put(const char *szPath, const char *szBusinessName);
	bool register_http_delete(const char *szPath, const char *szBusinessName);
	bool register_http_trace(const char *szPath, const char *szBusinessName);
	bool register_http_options(const char *szPath, const char *szBusinessName);

	/*
	 * ��ʼ��Ҫע���·�ɸ�������Ҫ��register_http_routes�ӿڵ��ʼ����
	 */
	bool init_route_count(int nCount);

protected: // interface
	virtual void register_http_routes() = 0;
	virtual string unique_id() = 0;
	virtual string name() = 0;
	virtual string version() = 0;
	virtual string dispatch_by_route_path(char *szRoutePath, char *sz, Request_Data &inData, Respond_Data &outData) = 0;

private:
	bool register_http_route(const char *szPath, const char *szBusinessName, const char *szOperation);

private:
	Route_Info *riRouteInfos;
	int nRouteInfoCnt;
	int nRouteInfoIndex;
};

