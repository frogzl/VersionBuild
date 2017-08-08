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
	string Name() { return sName; }
	int CreateIndex(){ return nCreateIndex; }
	Type EnType() { return enType; }

	void setName(string sName){ this->sName = sName; }
	void SetType(Type enType) { this->enType = enType; }

	void insert(string sPath, int &nCreateIndex);
	string get_path_left_part_value(string sPath, string &sValue);
	void set_create_index(int nIndex);
	int parse_path(string sPath, vector<string> &vecParameters);
	bool operator==(const RoutePart & obj2) const;
private:
	int nCreateIndex;
	vector<RoutePart> vecChild;
	string sName;
	Type enType;
};

