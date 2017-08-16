#pragma once
#include "Database.h"
namespace DB {
	sql_create_5(Declare_Table_Model_Data(Plugin_Deploy),
		1, 5,
		mysqlpp::sql_varchar, guid,
		mysqlpp::sql_varchar, plugin_id,
		mysqlpp::sql_varchar, proxy_host_id,
		mysqlpp::sql_varchar, server_host_id,
		mysqlpp::sql_int, status)

		Declare_Table_Model(Plugin_Deploy)
		Declare_Table_Model_End()
}