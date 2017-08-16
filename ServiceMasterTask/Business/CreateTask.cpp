#include "CreateTask.h"
#include "../Common.h"
#include "../Exception/HttpRequestException.h"
#include "../Database/Task_Instance.h"
#include "../Database/Plugin_Deploy.h"
#include "../Database/Plugin_Task.h"
#include "../Database/Plugin.h"

#include <string>
using namespace std;
CreateTask::CreateTask(ServiceData *pD) :m_pD(pD)
{
}

CreateTask::~CreateTask()
{
}

void CreateTask::process_task()
{
	char szBuf[255] = "";
	if (check_input_data())
	{
		// 获取plugin信息
		DB::Conditions conditions;
		conditions.insert(pair<string, string>("unique_id", _sUniqueID));
		conditions.insert(pair<string, string>("version", _sVersion));
		DB::PluginData *pDBPlugin = DB::Plugin().query()->where(conditions)->first();
		if (!pDBPlugin)
		{
			sprintf(szBuf, "plugin %s[%s] is missing.", _sUniqueID.c_str(), _sVersion.c_str());
			m_pD->set_respond_back(499, "1", szBuf, "");
			return;
		}

		// 获取plugin task映射关系
		conditions.clear();
		conditions.insert(pair<string, string>("plugin_id", pDBPlugin->guid));
		conditions.insert(pair<string, string>("task_path", _sTaskPath));
		DB::Plugin_TaskData *pDBPluginTask = DB::Plugin_Task().query()->where(conditions)->first();
		if (!pDBPluginTask)
		{
			sprintf(szBuf, "plugin %s[%s] isn't have task %s.", _sUniqueID.c_str(), _sVersion.c_str(), _sTaskPath.c_str());
			m_pD->set_respond_back(499, "1", szBuf, "");
			delete pDBPlugin;
			return;
		}

		// 获取任务部署位置
		string sPluginDeployID = m_pD->request_data().jData["plugin_deploy_id"].asString();
		if (sPluginDeployID.compare("") == 0)
		{
			// 位置不相关任务
			DB::Task_InstanceData tiData;
			tiData.guid = getGUID();
			tiData.plugin_task_id = pDBPluginTask->guid;
			tiData.plugin_deploy_id = "";
			tiData.status = 0x0001;
			tiData.status_description = "待处理";
			tiData.data = Json::FastWriter().write(m_pD->request_data().jData["data"]);
			tiData.processed_data = "";
			tiData.finish_url = m_pD->request_data().jData["finish_url"].asString();
			if (!DB::Task_Instance().create(tiData)->exec())
			{
				sprintf(szBuf, "create task instance failed %s[%s] %s.", _sUniqueID.c_str(), _sVersion.c_str(), _sTaskPath.c_str());
				m_pD->set_respond_back(499, "1", szBuf, "");
				delete pDBPlugin;
				delete pDBPluginTask;
				return;
			}
			
			string sErrorMsg = "";
			Network::Request_Data rd;
			rd.sData = Json::FastWriter().write(m_pD->request_data().jData);
			sprintf(szBuf, "/task/{%s}/process", tiData.guid.c_str());
			if (!Network::post(Network::enReverseProxy, "cc0e7465-9c6d-4802-8786-2bafd9ef9ff4", "1", szBuf, rd, process_task_callback, &sErrorMsg))
			{
				m_pD->set_respond_back(499, "1", sErrorMsg, "");
				delete pDBPlugin;
				delete pDBPluginTask;
				return;
			}
		}
		else
		{
			// 位置相关业务
		}
	}
}

bool CreateTask::check_input_data()
{
	// 获取任务名称
	_sTaskPath = m_pD->request_data().jData["task_path"].asString();
	if (_sTaskPath.compare("") == 0)
	{
		m_pD->set_respond_back(499, "1", "task_path is null", "");
		return false;
	}

	// 获取插件唯一标识
	_sUniqueID = m_pD->request_data().jData["unique_id"].asString();
	if (_sUniqueID.compare("") == 0)
	{
		m_pD->set_respond_back(499, "1", "unique_id is null", "");
		return false;
	}

	// 获取插件版本
	_sVersion = m_pD->request_data().jData["version"].asString();
	if (_sVersion.compare("") == 0)
	{
		m_pD->set_respond_back(499, "1", "version is null", "");
		return false;
	}
}

bool CreateTask::process_task_callback(Network::Respond_Data *pData, void *pArg)
{
	string &sErrorMsg = *(string*)pArg;
	sErrorMsg = "abc";
	return true;
}