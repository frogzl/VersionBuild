#include "CreateCompilingToolInstance.h"
#include "../Common.h"
#include "../Exception/HttpRequestException.h"
#include "../Database/CompilingTool.h"
#include "../Database/CompilingToolInstance.h"
#include <sstream>
#include <map>
using namespace std;
CreateCompilingToolInstance::CreateCompilingToolInstance(ServiceData *pD) :m_pD(pD)
{
}


CreateCompilingToolInstance::~CreateCompilingToolInstance()
{
}

/*
 range bytes start-end/total

 如果 start = 0, end = total，则使用本地默认分块策略，每块2MB。
 如果 end != total，则以当前范围为一块存储
 */
void CreateCompilingToolInstance::process_task()
{
	char szBuf[255];
	if (check_input_data())
	{
		sprintf(szBuf, "`guid`=\"%s\"", _sCompilingToolID.c_str());
		DB::CompilingToolData *pCTD = DB::CompilingTool().query("compile_cmd_template")->where(szBuf)->first();
		if (pCTD)
		{
			map<int, string> mDataObj;
			Json::Value jData;
			Json::Reader reader;
			if (reader.parse(_sData, jData))
			{
				for (int nIndex = 0; nIndex < jData.size(); nIndex++)
				{
					Json::Value obj = jData[nIndex];
					mDataObj.insert(pair<int, string>(obj["index"].asInt(), obj["value"].asString()));
				}
				string sCmd = pCTD->compile_cmd_template;
				map<int, string>::iterator it = mDataObj.begin();
				while (it != mDataObj.end())
				{
					sprintf(szBuf, "%%%d", it->first);
					replace_all_distinct(sCmd, szBuf, it->second);
					it++;
				}
				
				DB::CompilingToolInstanceData ctid;
				ctid.guid = getGUID();
				ctid.compiling_tool_id = _sCompilingToolID;
				ctid.data = _sData;
				ctid.compile_cmd = sCmd;
				if (DB::CompilingToolInstance().create(ctid)->exec())
				{
					Json::Value jData;
					jData["compile_tool_ins_id"] = pCTD->name;
					Json::Value jRespond;
					jRespond["data"] = jData;
					m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jRespond);
				}
				else
				{
					m_pD->set_respond_back(499, "1", "create CompilingToolInstance failed.", "");
				}
			}
			else
			{
				sprintf(szBuf, "the data of Compiling tool %s is not in json format.", _sCompilingToolID.c_str());
				m_pD->set_respond_back(499, "1", szBuf, "");
			}

			delete pCTD;
		}
		else
		{
			sprintf(szBuf, "Compiling tool %s is not found", _sCompilingToolID.c_str());
			m_pD->set_respond_back(499, "1", szBuf, "");
		}
	}
}

bool CreateCompilingToolInstance::check_input_data()
{	
	// 模板ID
	if (m_pD->request_data().jData["compiling_tool_id"].isString())
		_sCompilingToolID = m_pD->request_data().jData["compiling_tool_id"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "compiling_tool_id is empty.", "");
		return false;
	}

	// 模板数据
	if (m_pD->request_data().jData["data"].isString())
		_sData = m_pD->request_data().jData["data"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "Data is empty.", "");
		return false;
	}

	return true;
}