#pragma once
#include "ServiceTemplate.h"
class ServicePlugin:public ServiceTemplate
{
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
};

