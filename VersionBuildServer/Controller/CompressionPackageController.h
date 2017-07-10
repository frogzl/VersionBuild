#pragma once
#include "Controller.h"
#include "../Common.h"

namespace Controller
{
	Declare_Controller_Class(CompressionPackageController, Controller)
		Declare_Controller_Class_Common(CompressionPackageController)
		Declare_Controller_Class_Function(create)
		Declare_Controller_Class_Function(query)
		Declare_Controller_Class_Function(modify)
		Declare_Controller_Class_Function(delete)
		Declare_Controller_Class_Function(query_by_repertory)
		Declare_Controller_Class_End()
}