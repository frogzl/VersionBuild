#include "AddBuildRuleResult.h"
#include "../Exception/HttpRequestException.h"
#include "../Tools/HttpClient.h"

AddBuildRuleResult::AddBuildRuleResult(ServiceData *pD) :m_pD(pD)
{
}

AddBuildRuleResult::~AddBuildRuleResult()
{
}

void AddBuildRuleResult::process_task()
{
}