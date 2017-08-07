#include "stdafx.h"
#include "RoutePart.h"
#include "Common.h"
RoutePart::RoutePart()
{
	nCreateIndex = -1;
	enType = Normal;
}

RoutePart::RoutePart(string sName) :sPartName(sName)
{
	nCreateIndex = -1;
	enType = Normal;
}

RoutePart::~RoutePart()
{
}


RoutePart* RoutePart::insert(string sName)
{
	ltrim(sName);
	rtrim(sName);
	RoutePart rp(sName);

	if (sName[0] == '{' && sName[sName.length() - 1] == '}')
	{
		rp.setName("Parameter");
		rp.SetType(Parameter);
	}
	vector<RoutePart>::iterator itFind = find(vecChild.begin(), vecChild.end(), rp);
	if (itFind != vecChild.end())
		return &(*itFind);
	else
	{
		vecChild.push_back(rp);
		return &vecChild[vecChild.size() - 1];
	}
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
	if (this->sPartName.compare(obj2.sPartName) == 0)
		return true;
	else
		return false;
}