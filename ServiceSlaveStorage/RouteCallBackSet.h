#pragma once
#include "ServiceData.h"
class RouteCallBackSet
{
public:
	// �������
	static void upload_block(ServiceData *pD);

	// ��ѯ����
	static void download_block(ServiceData *pD);
};

