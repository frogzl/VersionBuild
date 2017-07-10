#include "BuildRuleDependController.h"
#include "../SystemConfig.h"
#include "../Common.h"

namespace Controller
{
	Define_Controller_Class_Common(BuildRuleDependController, Controller)
		Controller_Class_Function_Filter(create)
		Controller_Class_Function_Filter(query)
		Controller_Class_Function_Filter(modify)
		Controller_Class_Function_Filter(delete)
		Define_Controller_Class_Common_End()

		Define_Controller_Class_Function(BuildRuleDependController, create)
	{
		printf("BuildRuleDependController, create\n");
	}

	Define_Controller_Class_Function(BuildRuleDependController, query)
	{
		printf("BuildRuleDependController, query\n");
	}

	Define_Controller_Class_Function(BuildRuleDependController, modify)
	{
		printf("BuildRuleDependController, modify\n");
	}

	Define_Controller_Class_Function(BuildRuleDependController, delete)
	{
		printf("BuildRuleDependController, delete\n");
	}
}