#pragma once
#include "Controller.h"
#include "../Common.h"

namespace Controller
{
	Declare_Controller_Class(ServerController, Controller)
		Declare_Controller_Class_Common(ServerController)
		Declare_Controller_Class_Function(init)
		Declare_Controller_Class_Function(resource_query)
		Declare_Controller_Class_End()
}