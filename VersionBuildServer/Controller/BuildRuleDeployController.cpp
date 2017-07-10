#include "BuildRuleDeployController.h"
#include "../SystemConfig.h"
#include "../Common.h"

namespace Controller
{
	Define_Controller_Class_Common(BuildRuleDeployController, Controller)
		Controller_Class_Function_Filter(create)
		Controller_Class_Function_Filter(query)
		Controller_Class_Function_Filter(modify)
		Controller_Class_Function_Filter(delete)
		Define_Controller_Class_Common_End()

		Define_Controller_Class_Function(BuildRuleDeployController, create)
	{
		printf("BuildRuleDeployController, create\n");
	}

	Define_Controller_Class_Function(BuildRuleDeployController, query)
	{
		printf("BuildRuleDeployController, query\n");
	}

	Define_Controller_Class_Function(BuildRuleDeployController, modify)
	{
		printf("BuildRuleDeployController, modify\n");
	}

	Define_Controller_Class_Function(BuildRuleDeployController, delete)
	{
		printf("BuildRuleDeployController, delete\n");
	}
}