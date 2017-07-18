#pragma once
#include "include/Business.h"
#include <map>
#include <string>

using namespace std;
class BusinessFactory
{
public:
	BusinessFactory();
	~BusinessFactory();

	int register_business(const char *szBusinessName, FuncCreate pCallBack);
	bool change_to_fast_mode();

	Business* get_business(int nIndex);
private:
	map<string, int> *pMapIndex;
	vector<FuncCreate> *pVecCreator;

	FuncCreate *creators;
};

