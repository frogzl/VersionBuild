#include "stdafx.h"
#include "Common.h"
#include "RoutePart.h"
#include <algorithm>
#include <string>
RoutePart::RoutePart()
{
	nCreateIndex = -1;
	enType = Normal;
	sName = "";
}

RoutePart::RoutePart(string sName)
{
	nCreateIndex = -1;
	enType = Normal;
	this->sName = sName;
}

RoutePart::~RoutePart()
{
}

void RoutePart::insert(string sPath, int &nCreateIndex)
{
	if (sPath.compare("") == 0)
	{
		set_create_index(nCreateIndex);
		return;
	}
	string sValue = "";
	sPath = get_path_left_part_value(sPath, sValue);
	Type ent = (sValue[0] == '{' && sValue[sValue.length() - 1] == '}') ? Parameter : Normal;
	if (ent == Parameter)
		sValue ="Parameter";

	RoutePart rp(sValue);
	vector<RoutePart>::iterator itFind = find(vecChild.begin(), vecChild.end(), rp);
	if (itFind != vecChild.end())
		return itFind->insert(sPath, nCreateIndex);
	else
	{
		rp.SetType(ent);
		vecChild.push_back(rp);
		return vecChild[vecChild.size() - 1].insert(sPath, nCreateIndex);
	}
}

string RoutePart::get_path_left_part_value(string sPath, string &sValue)
{
	int nPos = sPath.find('/', 1);
	if (nPos == -1)
		sValue = sPath.substr(1);
	else
		sValue = sPath.substr(1, nPos - 1);
	ltrim(sValue);
	rtrim(sValue);
	if (nPos == -1)
		return "";
	else
		return sPath.substr(nPos);
}

void RoutePart::set_create_index(int nIndex)
{
	nCreateIndex = nIndex;
}

int RoutePart::parse_path(string sPath, vector<string> &vecParameters)
{
	if (sPath.compare("") == 0)
		return nCreateIndex;
	else
	{
		string sValue = "";

		int nPos = sPath.find('/', 1);
		if (nPos == -1)
			sValue = sPath.substr(1);
		else
			sValue = sPath.substr(1, nPos - 1);
		ltrim(sValue);
		rtrim(sValue);
		Type enType = Normal;
		if (sValue[0] == '{' && sValue[sValue.length() - 1] == '}')
			enType = Parameter;
		int nChildCnt = vecChild.size();
		for (int nIndexChild = 0; nIndexChild < nChildCnt; nIndexChild++)
		{
			if (vecChild[nIndexChild].EnType() == enType)
			{
				if (enType == Parameter)
				{
					vecParameters.push_back(sValue.substr(1, sValue.length() - 2));
					if (nPos == -1)
						return vecChild[nIndexChild].parse_path("", vecParameters);
					else
						return vecChild[nIndexChild].parse_path(sPath.substr(nPos), vecParameters);
				}
				else
				{
					if (sValue.compare(vecChild[nIndexChild].Name()) == 0)
					{
						if (nPos == -1)
							return vecChild[nIndexChild].parse_path("", vecParameters);
						else
							return vecChild[nIndexChild].parse_path(sPath.substr(nPos), vecParameters);
					}
				}
			}
		}
		return -1;
	}
}

bool RoutePart::operator==(const RoutePart & obj2) const
{
	if (this->sName.compare(obj2.sName) == 0)
		return true;
	else
		return false;
}