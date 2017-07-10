#include "ProductController.h"

namespace Controller
{
	Define_Controller_Class_Common(ProductController, Controller)
		Controller_Class_Function_Filter(create)
		Controller_Class_Function_Filter(query)
		Controller_Class_Function_Filter(modify)
		Controller_Class_Function_Filter(delete)
		Controller_Class_Function_Filter(build)
		Controller_Class_Function_Filter(publish)
		Controller_Class_Function_Filter(deploy)
		Define_Controller_Class_Common_End()

	Define_Controller_Class_Function(ProductController, create)
	{
		printf("ProductController, create\n");
	}

	Define_Controller_Class_Function(ProductController, query)
	{
		printf("ProductController, query\n");
	}

	Define_Controller_Class_Function(ProductController, modify)
	{
		printf("ProductController, modify\n");
	}

	Define_Controller_Class_Function(ProductController, delete)
	{
		printf("ProductController, delete\n");
	}

	Define_Controller_Class_Function(ProductController, build)
	{
		printf("ProductController, build\n");
	}

	Define_Controller_Class_Function(ProductController, publish)
	{
		printf("ProductController, publish\n");
	}

	Define_Controller_Class_Function(ProductController, deploy)
	{
		printf("ProductController, deploy\n");
	}
}