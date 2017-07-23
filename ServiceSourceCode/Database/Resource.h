#pragma once
#include "Database.h"
	namespace DB {
	sql_create_5(Declare_Table_Model_Data(Resource),
		1, 5,
		mysqlpp::sql_varchar, guid,
		mysqlpp::sql_varchar, name,
		mysqlpp::sql_varchar, discription,
		mysqlpp::sql_int, type,
		mysqlpp::sql_varchar, resourceid)

		Declare_Table_Model(Resource)
		Declare_Table_Model_End()
}