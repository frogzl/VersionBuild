#include "BuildResultController.h"
#include "../SystemConfig.h"
#include "../Common.h"

namespace Controller
{
	Define_Controller_Class_Common(BuildResultController, Controller)
		Controller_Class_Function_Filter(create)
		Controller_Class_Function_Filter(query)
		Controller_Class_Function_Filter(modify)
		Controller_Class_Function_Filter(delete)
		Define_Controller_Class_Common_End()

		Define_Controller_Class_Function(BuildResultController, create)
	{
		printf("BuildRuleDependController, create\n");
	}

	Define_Controller_Class_Function(BuildResultController, query)
	{
		printf("BuildRuleDependController, query\n");
	}

	Define_Controller_Class_Function(BuildResultController, modify)
	{
		printf("BuildRuleDependController, modify\n");
	}

	Define_Controller_Class_Function(BuildResultController, delete)
	{
		printf("BuildRuleDependController, delete\n");
	}
}