#pragma once
#include "Database.h"
	namespace DB {
	sql_create_5(Declare_Table_Model_Data(Storage),
		1, 5,
		mysqlpp::sql_varchar, guid,
		mysqlpp::sql_text, storagehostlist,
		mysqlpp::sql_varchar, name,
		mysqlpp::sql_int, size,
		mysqlpp::sql_varchar, md5)

		Declare_Table_Model(Storage)
		Declare_Table_Model_End()
}