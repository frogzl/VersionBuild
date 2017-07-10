#pragma once
#include "Controller.h"
#include "../Common.h"

	namespace Controller
{
	Declare_Controller_Class(BuildResultController, Controller)
		Declare_Controller_Class_Common(BuildResultController)
		Declare_Controller_Class_Function(create)
		Declare_Controller_Class_Function(query)
		Declare_Controller_Class_Function(modify)
		Declare_Controller_Class_Function(delete)
		Declare_Controller_Class_End()
}