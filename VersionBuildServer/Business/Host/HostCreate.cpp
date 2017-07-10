#include "HostCreate.h"
#include "../../Exception/HttpRequestException.h"
#include "../../SystemConfig.h"
#include "../../Database/Resource_Host.h"
namespace B
{
	HostCreate::HostCreate(Controller::Controller *pController) :HostBusiness(pController)
	{
		if (!is_input_data_ready())
			throw HttpRequestException(HTTP_INTERNAL, "1", "read request data failed!");
	}


	HostCreate::~HostCreate()
	{
	}

	void HostCreate::process_task()
	{
		DB::Resource_HostData dbHostData;
		dbHostData.guid = getGUID();
		string sTmp = m_inputData["name"].asString();
		g2u(sTmp.c_str(), sTmp.length(), m_szBuf, Buffer_Size);
		dbHostData.name = m_szBuf;
		sTmp = m_inputData["discription"].asString();
		g2u(sTmp.c_str(), sTmp.length(), m_szBuf, Buffer_Size);
		dbHostData.discription = m_szBuf;
		dbHostData.type = m_inputData["type"].asInt();;
		dbHostData.address = m_inputData["address"].asString();
		dbHostData.port = m_inputData["port"].asInt();;
		
		dbHostData.operatingsystem = Json::FastWriter().write(m_inputData["operatingsystem"]);
		dbHostData.cpu = Json::FastWriter().write(m_inputData["cpu"]);
		dbHostData.memory = Json::FastWriter().write(m_inputData["memory"]);
		dbHostData.storage = Json::FastWriter().write(m_inputData["storage"]);
		dbHostData.environmentvariable = Json::FastWriter().write(m_inputData["environmentvariable"]);

		DB::Resource_Host dbHost;
		if (dbHost.create(dbHostData)->exec())
			set_respond_back(HTTP_OK, "0", "successed", "");
		else
			set_respond_back(HTTP_INTERNAL, "1", "create host failed", "");
	}

	void HostCreate::background_process()
	{

	}
}