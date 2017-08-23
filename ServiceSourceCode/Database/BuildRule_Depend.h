#pragma once
#include "Database.h"
namespace DB {
	sql_create_6(Declare_Table_Model_Data(BuildRule_Depend),
		1, 6,
		mysqlpp::sql_varchar, guid,
		mysqlpp::sql_varchar, build_rule_id,
		mysqlpp::sql_varchar, depend_source_code_id,
		mysqlpp::sql_varchar, depend_build_rule_id,
		mysqlpp::sql_varchar, depend_build_result_id,
		mysqlpp::sql_tinyint, depend_usage_mode)

		Declare_Table_Model(BuildRule_Depend)
		Declare_Table_Model_End()
}