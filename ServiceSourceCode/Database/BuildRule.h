#pragma once
#include "Database.h"
namespace DB {
	sql_create_12(Declare_Table_Model_Data(BuildRule),
		1, 12,
		mysqlpp::sql_varchar, guid,
		mysqlpp::sql_varchar, source_code_id,
		mysqlpp::sql_int, inner_id,
		mysqlpp::sql_int, status,
		mysqlpp::sql_tinyint, auto_build,
		mysqlpp::sql_varchar, proxy_host_id,
		mysqlpp::sql_varchar, server_host_id,
		mysqlpp::sql_varchar, task_id,
		mysqlpp::sql_varchar, target_file_name,
		mysqlpp::sql_varchar, target_file_path,
		mysqlpp::sql_varchar, compile_tool_ins_id,
		mysqlpp::sql_varchar, output_directory_template)

		Declare_Table_Model(BuildRule)
		Declare_Table_Model_End()
}