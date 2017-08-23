#include "CreateCompilingToolTemplate.h"
#include "../Common.h"
#include "../Exception/HttpRequestException.h"
#include "../Database/CompilingTool.h"
#include <string>
using namespace std;
CreateCompilingToolTemplate::CreateCompilingToolTemplate(ServiceData *pD) :m_pD(pD)
{
}

CreateCompilingToolTemplate::~CreateCompilingToolTemplate()
{
}

void CreateCompilingToolTemplate::process_task()
{
	char szBuf[255];
	if (check_input_data())
	{
		DB::CompilingToolData ctd;
		ctd.guid = getGUID();
		ctd.name = _sName;
		if (m_pD->request_data().jData["discription"].isString())
			ctd.discription = m_pD->request_data().jData["discription"].asString();
		else
			ctd.discription = "";
		ctd.data_template = _sDataTemplate;
		ctd.compile_cmd_template = _sCompileCmdTemplate;

		if (DB::CompilingTool().create(ctd)->exec())
			m_pD->set_respond_back(499, "1", "add CompilingTool to db failed.", "");
		else
		{
			Json::Value jValue;
			jValue["compiling_tool_id"] = ctd.guid;
			Json::Value jData;
			jData["data"] = jValue;
			m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jData);
		}
	}
}

bool CreateCompilingToolTemplate::check_input_data()
{
	// 名称
	if (m_pD->request_data().jData["name"].isString())
		_sName = m_pD->request_data().jData["name"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "name is empty.", "");
		return false;
	}

	// 数据模板
	if (m_pD->request_data().jData["data_template"].isString())
		_sDataTemplate = m_pD->request_data().jData["data_template"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "data_template is empty.", "");
		return false;
	}

	// 编译命令模板
	if (m_pD->request_data().jData["compile_cmd_template"].isString())
		_sCompileCmdTemplate = m_pD->request_data().jData["compile_cmd_template"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "compile_cmd_template is empty.", "");
		return false;
	}
	return true;
}
