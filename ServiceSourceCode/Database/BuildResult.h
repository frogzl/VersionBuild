#pragma once
#include "Database.h"
namespace DB {
	sql_create_6(Declare_Table_Model_Data(BuildResult),
		1, 6,
		mysqlpp::sql_varchar, guid,
		mysqlpp::sql_varchar, build_rule_id,
		mysqlpp::sql_int, version,
		mysqlpp::sql_tinyint, status,
		mysqlpp::sql_text, log,
		mysqlpp::sql_varchar, storage_id)

		Declare_Table_Model(BuildResult)
		Declare_Table_Model_End()
}