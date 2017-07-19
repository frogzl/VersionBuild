#pragma once
#include "BusinessInterface.h"
#include "ServiceInterface.h"
#ifdef DLL_EXPORTS
#define DlLL_API __declspec(dllexport)
#else
#define DlLL_API __declspec(dllimport)
#endif

extern "C" DlLL_API const char* library_version();
extern "C" DlLL_API BusinessInterface* create_business();
extern "C" DlLL_API ServiceInterface* create_plugin_template();
extern "C" DlLL_API ServiceInterface*  instantiate_plugin_template(ServiceInterface *pInterface)
