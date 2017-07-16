#pragma once
#include "Database.h"
namespace DB {
	sql_create_6(Declare_Table_Model_Data(BuildRule_Depend),
		1, 6,
		mysqlpp::sql_varchar, guid,
		mysqlpp::sql_varchar, buildruleid,
		mysqlpp::sql_varchar, dependsourcecodeid,
		mysqlpp::sql_varchar, dependbuildruleid,
		mysqlpp::sql_varchar, dependbuildresultid,
		mysqlpp::sql_tinyint, dependusagemode)

		Declare_Table_Model(BuildRule_Depend)
		Declare_Table_Model_End()
}