#pragma once
#include "ServiceInterface.h"
#include <json/json.h>
#include "BusinessFactoryTpl.h"
class ServiceTemplate : public ServiceInterface
{
public:
	ServiceTemplate();
	~ServiceTemplate();
		
	// ���ڻ�ȡ·����Ϣ
	int route_infos(Route_Info *&routeInfos);
	// ���ڻ�ȡΨһ��ʶ
	const char* unique_id();
	// ���ڻ�ȡ������
	const char* name();
	// ���ڻ�ȡ�汾
	const char* version();
	// ���ڸ���APIִ��
	const char* dispatch_by_route_path(int nIndex, Business::Request_Data &inData, Business::Respond_Data &outData);

protected:
	/*
	 * ��ʼ��Ҫע���·�ɸ�������Ҫ��register_http_routes�ӿڵ��ʼ����
	 */
	bool init_route_count(int nCount);

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
	bool register_http_post(const char *szPath, const char *szBusinessName);
	bool register_http_head(const char *szPath, const char *szBusinessName);
	bool register_http_put(const char *szPath, const char *szBusinessName);
	bool register_http_delete(const char *szPath, const char *szBusinessName);
	bool register_http_trace(const char *szPath, const char *szBusinessName);
	bool register_http_options(const char *szPath, const char *szBusinessName);

	/*
	 * ע�������
	 */
	bool register_service_name(const char *szName);

	/*
	 * ע�����Ψһ��ʶ
	 */
	bool register_service_unique_id(const char *szID);

	/*
	 * ע�����汾��
	 */
	bool register_service_version(const char *szVersion);

	/*
	* ע��ҵ�񹤳�
	*/
	bool register_service_business_factory(BusinessFactoryTpl *pFactory);

private:
	bool register_http_route(const char *szPath, const char *szBusinessName, const char *szOperation);

private:
	BusinessFactoryTpl *bft;
	Route_Info *riRouteInfos;
	int nRouteInfoCnt;
	int nRouteInfoIndex;
	const char *szServiceName;
	const char *szServiceUniqueId;
	const char *szServiceVersion;
};

