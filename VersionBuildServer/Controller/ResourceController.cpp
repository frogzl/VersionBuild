#include "ResourceController.h"
#include "../Business/Resource/ResourceQuery.h"
namespace Controller
{
	Define_Controller_Class_Common(ResourceController, Controller)
		Controller_Class_Function_Filter(query)
		Define_Controller_Class_Common_End()

	Define_Controller_Class_Function(ResourceController, query)
	{
		printf("ResourceController, query\n");
		do_business(new B::ResourceQuery(this));
	}
}