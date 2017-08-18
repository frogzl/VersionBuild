#pragma once
#include "Database.h"
namespace DB {
	sql_create_5(Declare_Table_Model_Data(Executable_Role_Deploy),
		1, 5,
		mysqlpp::sql_varchar, guid,
		mysqlpp::sql_varchar, host_id,
		mysqlpp::sql_varchar, executable_role_id,
		mysqlpp::sql_int, port,
		mysqlpp::sql_int, status)

		Declare_Table_Model(Executable_Role_Deploy)
		Declare_Table_Model_End()
}