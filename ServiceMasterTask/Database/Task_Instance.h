#pragma once
#include "Database.h"
namespace DB {
	sql_create_8(Declare_Table_Model_Data(Task_Instance),
		1, 8,
		mysqlpp::sql_varchar, guid,
		mysqlpp::sql_varchar, plugin_task_id,
		mysqlpp::sql_varchar, plugin_deploy_id,
		mysqlpp::sql_int, status,
		mysqlpp::sql_varchar, status_description,
		mysqlpp::sql_varchar, data,
		mysqlpp::sql_varchar, processed_data,
		mysqlpp::sql_varchar, finish_url)

		Declare_Table_Model(Task_Instance)
		Declare_Table_Model_End()
}