#pragma once
#include "Database.h"
	namespace DB {
	sql_create_3(Declare_Table_Model_Data(Resource_Document),
		1, 3,
		mysqlpp::sql_varchar, guid,
		mysqlpp::sql_varchar, name,
		mysqlpp::sql_varchar, discription)

		Declare_Table_Model(Resource_Document)
		Declare_Table_Model_End()
}