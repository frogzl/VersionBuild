#pragma once
#include "Database.h"
namespace DB {
	sql_create_5(Declare_Table_Model_Data(Storage),
		1, 5,
		mysqlpp::sql_varchar, guid,
		mysqlpp::sql_varchar, file_name,
		mysqlpp::sql_bigint, size,
		mysqlpp::sql_int, status,
		mysqlpp::sql_int, version)

		Declare_Table_Model(Storage)
		Declare_Table_Model_End()
}