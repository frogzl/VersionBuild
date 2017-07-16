#include "stdafx.h"
#include "BusinessFactory.h"
#include "Business/SourceCodeBuild.h"
#include "Business/SourceCodeCreate.h"
#include "Business/SourceCodeDelete.h"
#include "Business/SourceCodeDeploy.h"
#include "Business/SourceCodeModify.h"
#include "Business/SourceCodeQuery.h"

BusinessFactory::BusinessFactory()
{
}

BusinessFactory::~BusinessFactory()
{
}

Business* BusinessFactory::get_business(const char *szBusinessName)
{
	if (strcpy("SourceCodeBuild", szBusinessName) == 0)
		return new SourceCodeBuild();

	if (strcpy("SourceCodeCreate", szBusinessName) == 0)
		return new SourceCodeCreate();

	if (strcpy("SourceCodeDelete", szBusinessName) == 0)
		return new SourceCodeDelete();

	if (strcpy("SourceCodeDeploy", szBusinessName) == 0)
		return new SourceCodeDeploy();

	if (strcpy("SourceCodeModify", szBusinessName) == 0)
		return new SourceCodeModify();

	if (strcpy("SourceCodeQuery", szBusinessName) == 0)
		return new SourceCodeQuery();

	return NULL;
}