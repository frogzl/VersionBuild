#include "HostController.h"
#include "../SystemConfig.h"
#include "../Common.h"
#include "../Database/Storage.h"
#include "../Business/Host/HostQueryPhysicalInformation.h"
#include "../Business/Host/HostCreate.h"
#include "../Business/Host/HostQuery.h"
namespace Controller
{
	Define_Controller_Class_Common(HostController, Controller)
		Controller_Class_Function_Filter(create)
		Controller_Class_Function_Filter(query)
		Controller_Class_Function_Filter(query_physical_information)
		Controller_Class_Function_Filter(modify)
		Controller_Class_Function_Filter(delete)
		Define_Controller_Class_Common_End()

		Define_Controller_Class_Function(HostController, create)
	{
		printf("HostController, create\n");
		do_business(new B::HostCreate(this));
	}

	Define_Controller_Class_Function(HostController, query)
	{
		printf("HostController, query\n");
		do_business(new B::HostQuery(this));
	}

	Define_Controller_Class_Function(HostController, query_physical_information)
	{
		printf("HostController, query_physical_information\n");
		do_business(new B::HostQueryPhysicalInformation(this));
	}

	Define_Controller_Class_Function(HostController, modify)
	{
		printf("HostController, modify\n");
	}

	Define_Controller_Class_Function(HostController, delete)
	{
		printf("HostController, delete\n");
	}
}