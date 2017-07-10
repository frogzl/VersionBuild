#pragma once
#include "Controller.h"
#include "../Common.h"

namespace Controller
{
	Declare_Controller_Class(ResourceController, Controller)
		Declare_Controller_Class_Common(ResourceController)
		Declare_Controller_Class_Function(query)
		Declare_Controller_Class_End()
}