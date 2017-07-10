#include "StorageController.h"
#include "../SystemConfig.h"
#include "../Common.h"
#include "../Database/Storage.h"
#include "../Business/Storage/StorageDownloadPart.h"
#include "../Business/Storage/StorageDownload.h"
#include "../Business/Storage/StorageUpload.h"
#include "../Business/Storage/StorageUploadPart.h"
namespace Controller
{
	Define_Controller_Class_Common(StorageController, Controller)
		Controller_Class_Function_Filter(download)
		Controller_Class_Function_Filter(download_part)
		Controller_Class_Function_Filter(upload)
		Controller_Class_Function_Filter(upload_part)
		Define_Controller_Class_Common_End()

	Define_Controller_Class_Function(StorageController, download)
	{
		Json::Value replyRoot;
		printf("FileController, download\n");
		do_business(new B::StorageDownload(this));
	}

	Define_Controller_Class_Function(StorageController, download_part)
	{
		printf("FileController, download_part\n");
		do_business(new B::StorageDownloadPart(this));
	}

	Define_Controller_Class_Function(StorageController, upload)
	{
		Json::Value replyRoot;
		printf("FileController, upload\n");
		do_business(new B::StorageUpload(this));
	}

	Define_Controller_Class_Function(StorageController, upload_part)
	{
		printf("FileController, upload_part\n");
		do_business(new B::StorageUploadPart(this));
	}
}