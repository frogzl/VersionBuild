#include "SoftwarePackageController.h"
#include "../SystemConfig.h"
#include "../Common.h"
#include "../Database/Storage.h"

namespace Controller
{
	Define_Controller_Class_Common(SoftwarePackageController, Controller)
		Controller_Class_Function_Filter(create)
		Controller_Class_Function_Filter(query)
		Controller_Class_Function_Filter(modify)
		Controller_Class_Function_Filter(delete)
		Define_Controller_Class_Common_End()

		Define_Controller_Class_Function(SoftwarePackageController, create)
	{
		printf("SoftwarePackageController, create\n");
	}

	Define_Controller_Class_Function(SoftwarePackageController, query)
	{
		printf("SoftwarePackageController, query\n");
	}

	Define_Controller_Class_Function(SoftwarePackageController, modify)
	{
		printf("SoftwarePackageController, modify\n");
	}

	Define_Controller_Class_Function(SoftwarePackageController, delete)
	{
		printf("SoftwarePackageController, delete\n");
	}
}