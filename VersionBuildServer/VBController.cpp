#include "VBController.h"

namespace Controller
{
	map<string, Fun> VBController::m_mapClassCreator;
	VBController::VBController()
	{
	}


	VBController::~VBController()
	{
	}

	bool VBController::call_function(string sFunctionName, struct evhttp_request *req)
	{
		vector<string> vecName;
		split(sFunctionName, "@", vecName);
		if (vecName.size() == 2)
		{
			Controller *pC = NULL;
			map<string, Fun>::iterator it = m_mapClassCreator.find(vecName[0]);
			if (it != m_mapClassCreator.end())
			{
				pC = it->second(req);
				pC->call_function(vecName[1]);
				delete pC;
			}
			return true;
		}
		else
			return false;
	}

	void VBController::register_class(string sClassName, Fun create_function)
	{
		m_mapClassCreator.insert(pair<string, Fun>(sClassName, create_function));
	}
}