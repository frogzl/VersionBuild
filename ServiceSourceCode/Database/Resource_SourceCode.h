#pragma once
#include "Database.h"
	namespace DB {
		sql_create_12(Declare_Table_Model_Data(Resource_SourceCode),
			1, 12,
			mysqlpp::sql_varchar, guid,
			mysqlpp::sql_varchar, clone_url,
			mysqlpp::sql_varchar, repertoryname,
			mysqlpp::sql_varchar, branchname,
			mysqlpp::sql_varchar, name,
			mysqlpp::sql_varchar, discription,
			mysqlpp::sql_varchar, deployid,
			mysqlpp::sql_int, startversion,
			mysqlpp::sql_int, currentversion,
			mysqlpp::sql_int, status,
			mysqlpp::sql_int, buildstate,
			mysqlpp::sql_int, buildstatemask)

		Declare_Table_Model(Resource_SourceCode)
		Declare_Table_Model_End()
}