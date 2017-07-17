#include "BusinessFactory.h"
BusinessFactory::BusinessFactory()
{
	creators = NULL;
	pMapIndex = new map<string, int>;
	pVecCreator = new vector<FuncCreate>;
}

BusinessFactory::~BusinessFactory()
{
	if (creators)
		delete [] creators;
	if (pMapIndex)
		delete pMapIndex;
	if (pVecCreator)
		delete pVecCreator;

	creators = NULL;
	pMapIndex = NULL;
	pVecCreator = NULL;
}

int BusinessFactory::register_business(const char *szBusinessName, FuncCreate pCallBack)
{
	map<string, int>::iterator itFind = pMapIndex->find(szBusinessName);
	if (itFind == pMapIndex->end())
	{
		int nIndex = (int)pVecCreator->size();
		pMapIndex->insert(pair<string, int>(szBusinessName, nIndex));
		pVecCreator->push_back(pCallBack);
		return nIndex;
	}
	else
	{
		return itFind->second;
	}
}

bool BusinessFactory::change_to_fast_mode()
{
	int nCount = (int)pVecCreator->size();
	if (nCount > 0)
	{
		creators = new FuncCreate[nCount];
		for (int nIndex = 0; nIndex < nCount; nIndex++)
			creators[nIndex] = (*pVecCreator)[nIndex];
	}
	if (pMapIndex)
		delete pMapIndex;
	if (pVecCreator)
		delete pVecCreator;
	pMapIndex = NULL;
	pVecCreator = NULL;
	return true;
}

Business* BusinessFactory::get_business(int nIndex)
{
	return creators[nIndex]();
}