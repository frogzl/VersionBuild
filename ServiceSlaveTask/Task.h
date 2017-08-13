#pragma once
#include "TaskInterface.h"
#include "PluginTask.h"

class Task
{
public:
	Task();
	~Task();

	void setPlugin(PluginTask *pPlugin) { this->pPlugin = pPlugin; }
	void setCreateIndex(int nIndex) { nCreateIndex = nIndex; }
	void setData(TaskData* pData) { this->pData = pData; }
	bool process();
	TaskData* data();
private:
	PluginTask *pPlugin;
	int nCreateIndex;
	TaskData *pData;
};

