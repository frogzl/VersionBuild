#pragma once
#include "Database.h"
namespace DB {
	sql_create_4(Declare_Table_Model_Data(CompilingToolInstance),
		1, 4,
		mysqlpp::sql_varchar, guid,
		mysqlpp::sql_varchar, compiling_tool_id,
		mysqlpp::sql_varchar, data,
		mysqlpp::sql_varchar, compile_cmd)

		Declare_Table_Model(CompilingToolInstance)
		Declare_Table_Model_End()
}