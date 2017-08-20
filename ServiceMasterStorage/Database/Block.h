#pragma once
#include "Database.h"
namespace DB {
	sql_create_7(Declare_Table_Model_Data(Block),
		1, 7,
		mysqlpp::sql_varchar, guid,
		mysqlpp::sql_varchar, storage_id,
		mysqlpp::sql_bigint, start,
		mysqlpp::sql_bigint, end,
		mysqlpp::sql_varchar, proxy_host_id,
		mysqlpp::sql_varchar, server_host_id,
		mysqlpp::sql_varchar, path)

		Declare_Table_Model(Block)
		Declare_Table_Model_End()
}