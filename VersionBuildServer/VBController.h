#pragma once
#include "Common.h"
#include "Controller/Controller.h"
namespace Controller
{
	class VBController
	{
	public:
		VBController();
		~VBController();
	public:
		static bool call_function(string sFunctionName, struct evhttp_request *req);
		static void register_class(string sClassName, Fun create_function);
	private:
		static map<string, Fun> m_mapClassCreator;
	};
}