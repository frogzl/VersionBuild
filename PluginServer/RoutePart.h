#pragma once
#include <vector>
#include <string>
using namespace std;
class RoutePart
{
	enum Type
	{
		Normal = 0,
		Parameter
	};
public:
	RoutePart();
	RoutePart(string sName);
	~RoutePart();
	string Name() { return sPartName; }
	int CreateIndex(){ return nCreateIndex; }
	Type EnType() { return enType; }

	void setName(string sName){ sPartName = sName; }
	void SetType(Type enType) { this->enType = enType; }

	RoutePart* insert(string sName);
	void set_create_index(int nIndex);
	int parse_path(string sPath, vector<string> &vecParameters);
	bool operator==(const RoutePart & obj2) const;
private:
	int nCreateIndex;
	vector<RoutePart> vecChild;
	string sPartName;
	Type enType;
};

