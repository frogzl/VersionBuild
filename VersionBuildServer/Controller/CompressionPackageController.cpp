#include "CompressionPackageController.h"
#include "../SystemConfig.h"
#include "../Common.h"

namespace Controller
{
	Define_Controller_Class_Common(CompressionPackageController, Controller)
		Controller_Class_Function_Filter(create)
		Controller_Class_Function_Filter(query)
		Controller_Class_Function_Filter(modify)
		Controller_Class_Function_Filter(delete)
		Define_Controller_Class_Common_End()

		Define_Controller_Class_Function(CompressionPackageController, create)
	{
		printf("CompressionPackageController, create\n");
	}

	Define_Controller_Class_Function(CompressionPackageController, query)
	{
		printf("CompressionPackageController, query\n");
	}

	Define_Controller_Class_Function(CompressionPackageController, modify)
	{
		printf("CompressionPackageController, modify\n");
	}

	Define_Controller_Class_Function(CompressionPackageController, delete)
	{
		printf("CompressionPackageController, delete\n");
	}

	Define_Controller_Class_Function(CompressionPackageController, query_by_repertory)
	{
		printf("CompressionPackageController, query_by_repertory\n");
	}
}