#pragma once
#include "Database.h"
namespace DB {
	sql_create_13(Declare_Table_Model_Data(BuildRule),
		1, 13,
		mysqlpp::sql_varchar, guid,
		mysqlpp::sql_varchar, sourcecodeid,
		mysqlpp::sql_int, innerid,
		mysqlpp::sql_tinyint, autobuild,
		mysqlpp::sql_varchar, platform,
		mysqlpp::sql_varchar, deployid,
		mysqlpp::sql_varchar, buildcmd,
		mysqlpp::sql_int, targetfiletype,
		mysqlpp::sql_varchar, targetfilename,
		mysqlpp::sql_varchar, targetfilepath,
		mysqlpp::sql_varchar, logfilename,
		mysqlpp::sql_varchar, logfilepath,
		mysqlpp::sql_int, status)

		Declare_Table_Model(BuildRule)
		Declare_Table_Model_End()
}