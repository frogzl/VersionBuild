#pragma once
#include "Controller.h"
#include "../Common.h"

namespace Controller
{
	Declare_Controller_Class(HostController, Controller)
		Declare_Controller_Class_Common(HostController)
		Declare_Controller_Class_Function(create)
		Declare_Controller_Class_Function(query)
		Declare_Controller_Class_Function(query_physical_information)
		Declare_Controller_Class_Function(modify)
		Declare_Controller_Class_Function(delete)
		Declare_Controller_Class_End()
}