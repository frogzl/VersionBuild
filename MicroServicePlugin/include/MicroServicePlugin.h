#pragma once
#include "ServiceInterface.h"
#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

extern "C" DLL_API const char* library_version();
extern "C" DLL_API BusinessInterface* create_business();
extern "C" DLL_API ServiceInterface* create_plugin_template();
extern "C" DLL_API ServiceInterface*  instantiate_plugin_template(ServiceInterface *pInterface)
