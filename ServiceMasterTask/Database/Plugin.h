#pragma once
#include "Database.h"
namespace DB {
	sql_create_6(Declare_Table_Model_Data(Plugin),
		1, 6,
		mysqlpp::sql_varchar, guid,
		mysqlpp::sql_varchar, name,
		mysqlpp::sql_varchar, discription,
		mysqlpp::sql_varchar, unique_id,
		mysqlpp::sql_varchar, version,
		mysqlpp::sql_varchar, storageid)

		Declare_Table_Model(Plugin)
		Declare_Table_Model_End()
}