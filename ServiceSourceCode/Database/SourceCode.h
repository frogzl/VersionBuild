#pragma once
#include "Database.h"
	namespace DB {
		sql_create_11(Declare_Table_Model_Data(SourceCode),
			1, 11,
			mysqlpp::sql_varchar, guid,
			mysqlpp::sql_varchar, name,
			mysqlpp::sql_varchar, discription,
			mysqlpp::sql_varchar, version_control_ins_id,
			mysqlpp::sql_varchar, source_code_folder,
			mysqlpp::sql_int, start_version,
			mysqlpp::sql_int, current_version,
			mysqlpp::sql_int, status,
			mysqlpp::sql_int, build_state,
			mysqlpp::sql_int, build_state_mask,
			mysqlpp::sql_int, version)

		Declare_Table_Model(SourceCode)
		Declare_Table_Model_End()
}