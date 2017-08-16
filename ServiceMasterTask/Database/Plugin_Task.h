#pragma once
#include "Database.h"
namespace DB {
	sql_create_3(Declare_Table_Model_Data(Plugin_Task),
		1, 3,
		mysqlpp::sql_varchar, guid,
		mysqlpp::sql_varchar, plugin_id,
		mysqlpp::sql_varchar, task_path)

		Declare_Table_Model(Plugin_Task)
		Declare_Table_Model_End()
}