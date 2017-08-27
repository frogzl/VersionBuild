#pragma once
#include "Database.h"
namespace DB {
	sql_create_5(Declare_Table_Model_Data(CompilingTool),
		1, 5,
		mysqlpp::sql_varchar, guid,
		mysqlpp::sql_varchar, name,
		mysqlpp::sql_varchar, discription,
		mysqlpp::sql_varchar, data_template,
		mysqlpp::sql_varchar, compile_cmd_template)

		Declare_Table_Model(CompilingTool)
		Declare_Table_Model_End()
}