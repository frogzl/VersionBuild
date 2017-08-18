#pragma once
#include "Database.h"
namespace DB {
	sql_create_3(Declare_Table_Model_Data(Executable_Role),
		1, 3,
		mysqlpp::sql_varchar, guid,
		mysqlpp::sql_varchar, name,
		mysqlpp::sql_varchar, description)

		Declare_Table_Model(Executable_Role)
		Declare_Table_Model_End()
}