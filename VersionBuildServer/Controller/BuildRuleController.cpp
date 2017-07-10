#include "BuildRuleController.h"
#include "../SystemConfig.h"
#include "../Common.h"
#include "../Business/BuildRule/BuildRuleBuild.h"
#include "../Business/BuildRule/BuildRuleQuery.h"
#include "../Business/BuildRule/BuildRuleDeploy.h"
namespace Controller
{
	Define_Controller_Class_Common(BuildRuleController, Controller)
		Controller_Class_Function_Filter(create)
		Controller_Class_Function_Filter(query)
		Controller_Class_Function_Filter(modify)
		Controller_Class_Function_Filter(build)
		Controller_Class_Function_Filter(deploy)
		Controller_Class_Function_Filter(delete)
		Define_Controller_Class_Common_End()

		Define_Controller_Class_Function(BuildRuleController, create)
	{
		printf("BuildRuleController, create\n");
	}

	Define_Controller_Class_Function(BuildRuleController, query)
	{
		printf("BuildRuleController, query\n");
		do_business(new B::BuildRuleQuery(this));
	}

	Define_Controller_Class_Function(BuildRuleController, modify)
	{
		printf("BuildRuleController, modify\n");
	}

	Define_Controller_Class_Function(BuildRuleController, build)
	{
		printf("BuildRuleController, build\n");
		do_business(new B::BuildRuleBuild(this));
	}

	Define_Controller_Class_Function(BuildRuleController, deploy)
	{
		printf("BuildRuleController, deploy\n");
		do_business(new B::BuildRuleDeploy(this));
	}

	Define_Controller_Class_Function(BuildRuleController, delete)
	{
		printf("BuildRuleController, delete\n");
	}
}