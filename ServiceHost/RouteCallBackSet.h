#pragma once
#include "ServiceData.h"
class RouteCallBackSet
{
public:
	// �������
	static void create_host(ServiceData *pD);

	// ��ѯ����
	static void query_host(ServiceData *pD);

	// ɾ������
	static void delete_host(ServiceData *pD);

	// �޸�����
	static void modify_host(ServiceData *pD);

	// ��ѯ��ִ�н�ɫ
	static void query_executable_role(ServiceData *pD);

	// ��ӿ�ִ�н�ɫ�Ĳ�����Ϣ
	static void create_executable_role_deployment_information(ServiceData *pD);

	// ��ѯ��ִ�н�ɫ�Ĳ�����Ϣ
	static void query_executable_role_deployment_information(ServiceData *pD);

	// �޸Ŀ�ִ�н�ɫ�Ĳ�����Ϣ
	static void modify_executable_role_deployment_information(ServiceData *pD);

	// ɾ����ִ�н�ɫ�Ĳ�����Ϣ
	static void delete_executable_role_deployment_information(ServiceData *pD);

};

