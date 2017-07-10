#pragma once
//#include <windows.h>
#include <WinSock2.h>
#include <mysql++.h>
#include <ssqls.h>
#include <stack>
#include <string>
using namespace std;
namespace DB {
#define dd(d) #d
#define mm(d) d
#define m(x) mm(new_)##x

typedef map<string, string> Conditions;

// 声明类结构
#define Declare_Table_Model_Data(TableName) mm(TableName)##mm(Data)
#define Declare_Table_Model_End() };
#define Declare_Table_Model(TableName) \
struct Declare_Table_Model_Data(TableName);\
class TableName : public Database{\
public:\
	TableName();\
	~TableName();\
	TableName* create(Declare_Table_Model_Data(TableName) &pdData);\
	TableName* query(string sNames = "");\
	TableName* remove();\
	TableName* update(set<string> &vecfilter, Declare_Table_Model_Data(TableName) &pdData);\
	TableName* where(string sCondition);\
	TableName* where(map<string, string> mapCondition);\
	TableName* order_by(vector<string> vecCondition);\
	TableName* order_by(string sCondition);\
	string end();\
	Declare_Table_Model_Data(TableName)* first();\
	vector<Declare_Table_Model_Data(TableName)>* all();\
	bool exec();

// 定义创建一条新记录
#define Define_Table_Create_Function_Filter_Begin(TableNamePrefix, TableName) string sQuery = mm("insert into `")##dd(TableNamePrefix)##mm("_")##dd(TableName)##mm("s` values (");
#define Define_Table_Create_Function_Filter_String(Name) sQuery += ("\'" + mm(pdData.)##mm(Name) + "\',");
#define Define_Table_Create_Function_Filter_Number(Name) {char szTmp[255];itoa(mm(pdData.)##mm(Name), szTmp, 10); sQuery += (string(szTmp) + ",");}
#define Define_Table_Create_Function_Filter_Datatime(Name) sQuery += ("\"" + mm(pdData.)##mm(Name)##mm(.str()) + "\",");
#define Define_Table_Create_Function_Filter_End() sQuery.erase(sQuery.length() - 1, 1); sQuery += ")";m_stackQuery.push(sQuery);
#define Define_Table_Create_Function_End() 	return this;}
#define Define_Table_Create_Function(TableName) mm(TableName)* mm(TableName)::create(Declare_Table_Model_Data(TableName) &pdData){

// 定义构造函数
#define Define_Table_Constructor(TableName) mm(TableName)::mm(TableName)():Database(){
#define Define_Table_Constructor_End() }

// 定义析构函数
#define Define_Table_Destructor(TableName) mm(TableName)::~mm(TableName)(){
#define Define_Table_Destructor_End() }

// 定义查询函数
#define Define_Table_Query_Function_End() 	return this;}
#define Define_Table_Query_Function(TableName) mm(TableName)* mm(TableName)::query(string sNames){
#define Define_Table_Query_Function_Body(TableNamePrefix, TableName)	if (sNames.compare("") == 0) m_stackQuery.push(mm("select * from `")##dd(TableNamePrefix)##mm("_")##dd(TableName)##mm("s`"));\
	else{\
		string s = "select ";\
		s += sNames;\
		s += mm(" from `define_")##dd(TableName)##mm("s` ");\
		m_stackQuery.push(s);}

// 定义删除函数
#define Define_Table_Remove_Function_End() 	return this;}
#define Define_Table_Remove_Function(TableName) mm(TableName)* mm(TableName)::remove(){
#define Define_Table_Remove_Function_Body(TableNamePrefix, TableName)	m_stackQuery.push(mm("delete from `")##dd(TableNamePrefix)##mm("_")##dd(TableName)##mm("s` "));

// 定义更新函数
#define Define_Table_Update_Function_Filter_Begin(TableNamePrefix, TableName) bool bIsFirst = true;string sQuery = mm("update `")##dd(TableNamePrefix)##mm("_")##dd(TableName)##mm("s` set ");
#define Define_Table_Update_Function_Filter_String(Name) 	if (vecfilter.count(dd(Name)) != 0){\
		if (!bIsFirst) sQuery += ",";\
		bIsFirst = false;\
		sQuery += (mm("`")##dd(Name)##mm("`=\"") + mm(pdData.)##mm(Name) + "\" ");}
#define Define_Table_Update_Function_Filter_Number(Name) 	if (vecfilter.count(dd(Name)) != 0){\
		if (!bIsFirst) sQuery += ",";\
		bIsFirst = false;\
		char szTmp[255];itoa(mm(pdData.)##mm(Name), szTmp, 10);sQuery += (mm("`")##dd(Name)##mm("`=") + string(szTmp) + " ");}
#define Define_Table_Update_Function_Filter_Datatime(Name) 	if (vecfilter.count(dd(Name)) != 0){\
		if (!bIsFirst) sQuery += ",";\
		bIsFirst = false;\
		sQuery += (mm("`")##dd(Name)##mm("`=\"") + mm(pdData.)##mm(Name)##mm(.str()) + "\" ");}
#define Define_Table_Update_Function_Filter_End() 
#define Define_Table_Update_Function_End() 	m_stackQuery.push(sQuery);return this;}
#define Define_Table_Update_Function(TableName) mm(TableName)* mm(TableName)::update(set<string> &vecfilter, Declare_Table_Model_Data(TableName) &pdData){

// 定义条件函数
#define Define_Table_Where_Function_End() 	m_stackQuery.push(s);return this;}
#define Define_Table_Where_Function_Body() 	string s = m_stackQuery.top();m_stackQuery.pop();s += " where "; s += sCondition;
#define Define_Table_Where_Function(TableName) mm(TableName)* mm(TableName)::where(string sCondition){

#define Define_Table_Where2_Function_End() 	m_stackQuery.push(s);return this;}
#define Define_Table_Where2_Function_Body() map<string, string>::iterator it = mapConition.begin();\
		string sTmp;\
		while (it != mapConition.end()){\
			sTmp += ("`" + it->first + "`");\
			sTmp += " = ";\
			sTmp += ("\"" + it->second + "\"");\
			it++;\
			if (it != mapConition.end())\
				sTmp += " and ";}\
		string s = m_stackQuery.top();\
		m_stackQuery.pop();\
		s += " where ";\
		s += sTmp;
#define Define_Table_Where2_Function(TableName) mm(TableName)* mm(TableName)::where(map<string, string> mapConition){

// 定义排序函数
#define Define_Table_OrderBy_Function_End() m_stackQuery.push(s);return this;}
#define Define_Table_OrderBy_Function_Body() vector<string>::iterator it = vecConition.begin();\
		string sTmp;\
		while (it != vecConition.end()){\
			sTmp += *it ;\
			it++;\
			if (it != vecConition.end())\
				sTmp += ", ";}\
		string s = m_stackQuery.top();\
		m_stackQuery.pop();\
		s += " order by ";\
		s += sTmp;
#define Define_Table_OrderBy_Function(TableName) mm(TableName)* mm(TableName)::order_by(vector<string> vecConition){

#define Define_Table_OrderBy2_Function_End() m_stackQuery.push(s);return this;}
#define Define_Table_OrderBy2_Function_Body() string s = m_stackQuery.top();m_stackQuery.pop();s += " order by "; s += sCondition;
#define Define_Table_OrderBy2_Function(TableName) mm(TableName)* mm(TableName)::order_by(string sCondition){

// 定义结束函数
#define Define_Table_End_Function_End() 	return sQuery;}
#define Define_Table_End_Function_Body() 	string sQuery = m_stackQuery.top();m_stackQuery.pop();
#define Define_Table_End_Function(TableName) string TableName::end(){

// 定义获取第一条数据函数
#define Define_Table_First_Function_End() 	}
#define Define_Table_First_Function_Body(TableName) 		if (m_stackQuery.size() != 1) return NULL;\
		try{\
			string sQuery = m_stackQuery.top();\
			m_stackQuery.pop();\
			if (open_database()){\
				mysqlpp::Query query = con.query(sQuery);\
				vector<Declare_Table_Model_Data(TableName)> res;\
				query.storein(res);\
				if (res.size() > 0){\
					Declare_Table_Model_Data(TableName) *pData = new Declare_Table_Model_Data(TableName)();\
					*pData = res[0];\
					return pData;}}\
			return NULL;} \
		catch (const mysqlpp::BadQuery& er) {\
			cerr << "Query error: " << er.what() << endl;}\
		catch (const mysqlpp::BadConversion& er) {\
			cerr << "Conversion error: " << er.what() << endl <<\
				"\tretrieved data size: " << er.retrieved <<\
				", actual size: " << er.actual_size << endl;}\
		catch (const mysqlpp::Exception& er) {\
			cerr << "Error: " << er.what() << endl;}\
		return NULL;
#define Define_Table_First_Function(TableName) Declare_Table_Model_Data(TableName)* mm(TableName)::first(){

// 定义获取所有数据函数
#define Define_Table_All_Function_End() 	}
#define Define_Table_All_Function_Body(TableName)	if (m_stackQuery.size() != 1) return NULL;\
		try{\
			string sQuery = m_stackQuery.top();\
			m_stackQuery.pop();\
			if (open_database()){\
				mysqlpp::Query query = con.query(sQuery);\
				vector<Declare_Table_Model_Data(TableName)> *res = new vector<Declare_Table_Model_Data(TableName)>();\
				query.storein(*res);\
				return res;}\
			return NULL;}\
		catch (const mysqlpp::BadQuery& er) {\
			cerr << "Query error: " << er.what() << endl;}\
		catch (const mysqlpp::BadConversion& er) {\
			cerr << "Conversion error: " << er.what() << endl <<\
				"\tretrieved data size: " << er.retrieved <<\
				", actual size: " << er.actual_size << endl;}\
		catch (const mysqlpp::Exception& er) {\
			cerr << "Error: " << er.what() << endl;}\
		return NULL;

#define Define_Table_All_Function(TableName) vector<Declare_Table_Model_Data(TableName)>* mm(TableName)::all(){

// 定义执行sql语句函数
#define Define_Table_Exec_Function_End() 	}
#define Define_Table_Exec_Function_Body(TableName)		if (m_stackQuery.size() != 1) return NULL;\
		try{\
			string sQuery = m_stackQuery.top();\
			cout  << sQuery<<endl; \
			m_stackQuery.pop();\
			if (open_database()){\
				mysqlpp::Query query = con.query();\
				return query.exec(sQuery);}\
			return false;}\
		catch (const mysqlpp::BadQuery& er) {\
			cerr << "Query error: " << er.what() << endl;}\
		catch (const mysqlpp::BadConversion& er) {\
			cerr << "Conversion error: " << er.what() << endl <<\
				"\tretrieved data size: " << er.retrieved <<\
				", actual size: " << er.actual_size << endl;}\
		catch (const mysqlpp::Exception& er) {\
			cerr << "Error: " << er.what() << endl;}\
		return false;
#define Define_Table_Exec_Function(TableName) bool mm(TableName)::exec(){

class Database
{
public:
	Database();
	~Database();
	virtual bool open_database();
	virtual void close_database();
protected:
	mysqlpp::Connection con;
	stack<string> m_stackQuery;
};

}