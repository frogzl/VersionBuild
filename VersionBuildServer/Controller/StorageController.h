#pragma once
#include "Controller.h"

namespace Controller
{
	Declare_Controller_Class(StorageController, Controller)
		Declare_Controller_Class_Common(StorageController)
		Declare_Controller_Class_Function(download)
		Declare_Controller_Class_Function(download_part)
		Declare_Controller_Class_Function(upload)
		Declare_Controller_Class_Function(upload_part)
		Declare_Controller_Class_End()
}