#pragma once
#include "ServiceData.h"
class RouteCallBackSet
{
public:
	// ��ѯ�洢��Ϣ
	void query_file_info(ServiceData *pD);

	// �������
	static void upload(ServiceData *pD);

	// ��ѯ����
	static void download(ServiceData *pD);
};

