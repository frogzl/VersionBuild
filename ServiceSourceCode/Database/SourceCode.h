#pragma once
#include "Database.h"
	namespace DB {
		sql_create_10(Declare_Table_Model_Data(SourceCode),
			1, 10,
			mysqlpp::sql_varchar, guid,
			mysqlpp::sql_varchar, name,
			mysqlpp::sql_varchar, discription,
			mysqlpp::sql_varchar, version_control_id,
			mysqlpp::sql_int, start_version,
			mysqlpp::sql_int, current_version,
			mysqlpp::sql_int, status,
			mysqlpp::sql_int, build_state,
			mysqlpp::sql_int, build_state_mask,
			mysqlpp::sql_int, version)

		Declare_Table_Model(SourceCode)
		Declare_Table_Model_End()
}