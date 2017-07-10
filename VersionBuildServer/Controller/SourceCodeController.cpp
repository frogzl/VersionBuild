#include "SourceCodeController.h"
#include "../Exception/HttpRequestException.h"
#include <algorithm>
#include "../Business/SourceCode/SourceCodeCreate.h"
#include "../Business/SourceCode/SourceCodeQuery.h"
#include "../Business/SourceCode/SourceCodeDeploy.h"
#include "../Business/SourceCode/SourceCodeBuild.h"
namespace Controller
{
	Define_Controller_Class_Common(SourceCodeController, Controller)
		Controller_Class_Function_Filter(create)
		Controller_Class_Function_Filter(query)
		Controller_Class_Function_Filter(modify)
		Controller_Class_Function_Filter(deploy)
		Controller_Class_Function_Filter(build)
		Controller_Class_Function_Filter(delete)
		Define_Controller_Class_Common_End()


	Define_Controller_Class_Function(SourceCodeController, create)
	{
		printf("RepertoryController create call\n");
		do_business(new B::SourceCodeCreate(this));
	}

	Define_Controller_Class_Function(SourceCodeController, query)
	{
		printf("RepertoryController, query call\n");
		do_business(new B::SourceCodeQuery(this));
	}

	Define_Controller_Class_Function(SourceCodeController, modify)
	{
		printf("RepertoryControlle modify call\n");
	}

	Define_Controller_Class_Function(SourceCodeController, deploy)
	{
		printf("RepertoryControlle deploy call\n");
		do_business(new B::SourceCodeDeploy(this));
	}

	Define_Controller_Class_Function(SourceCodeController, build)
	{
		printf("RepertoryControlle deploy call\n");
		do_business(new B::SourceCodeBuild(this));
	}

	Define_Controller_Class_Function(SourceCodeController, delete)
	{
		printf("RepertoryController delete call\n");
	}
}