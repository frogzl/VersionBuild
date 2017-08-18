#pragma once
#include "Database.h"
namespace DB {
	sql_create_4(Declare_Table_Model_Data(Host),
		1, 4,
		mysqlpp::sql_varchar, guid,
		mysqlpp::sql_varchar, name,
		mysqlpp::sql_varchar, ip,
		mysqlpp::sql_int, status)

		Declare_Table_Model(Host)
		Declare_Table_Model_End()
}