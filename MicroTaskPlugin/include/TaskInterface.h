#pragma once
#include "TaskData.h"

typedef struct
{
	const char *szPath;					// ·��ģ��
	int nIndex;							// ����
}Task_Route_Info;

class TaskInterface
{
public:
	virtual ~TaskInterface();
	// ������
	virtual void destory() = 0;
	// ���ڻ�ȡ·����Ϣ
	virtual int route_infos(Task_Route_Info *&routeInfos) = 0;
	// ���ڻ�ȡΨһ��ʶ
	virtual const char* unique_id() = 0;
	// ���ڻ�ȡ������
	virtual const char* name() = 0;
	// ���ڻ�ȡ���ʵ�ֿ�İ汾
	virtual const char* version() = 0;
	// ���ڻ�ȡ���������İ汾
	virtual const char* library_version() = 0;
	// �������ݽӿ�
	virtual TaskData* create_data() = 0;
	// ���ڸ���APIִ��
	virtual bool dispatch_by_route_path(int nIndex, TaskData *pTD) = 0;
	// ע�������
	virtual bool register_task_name(const char *szName) = 0;
	// ע�����Ψһ��ʶ
	virtual bool register_task_unique_id(const char *szID) = 0;
	// ע�����汾��
	virtual bool register_task_version(const char *szVersion) = 0;
	// ע��·��
	virtual bool register_task_route(const char *szPath, FuncTaskProcess pCallBack) = 0;
};