#pragma once
#include "Controller.h"
#include "../Common.h"

namespace Controller
{
	Declare_Controller_Class(ProductController, Controller)
		Declare_Controller_Class_Common(ProductController)
		Declare_Controller_Class_Function(create)
		Declare_Controller_Class_Function(query)
		Declare_Controller_Class_Function(modify)
		Declare_Controller_Class_Function(delete)
		Declare_Controller_Class_Function(build)
		Declare_Controller_Class_Function(publish)
		Declare_Controller_Class_Function(deploy)
		Declare_Controller_Class_End()
}