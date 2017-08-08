#pragma once
#include "MicroServicePlugin.h"
#include "PluginService.h"
class Service
{
public:
	Service();
	~Service();

	void setPlugin(PluginService *pPlugin) { this->pPlugin = pPlugin; }
	void setCreateIndex(int nIndex) { nCreateIndex = nIndex; }
	void setData(ServiceData* pData) { this->pData = pData; }
	bool process();
	ServiceData* data();
private:
	PluginService *pPlugin;
	int nCreateIndex;
	ServiceData *pData;
};

