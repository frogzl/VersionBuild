#pragma once
#include "Database.h"
namespace DB {
	sql_create_3(Declare_Table_Model_Data(BuildRule_Deploy),
		1, 3,
		mysqlpp::sql_varchar, guid,
		mysqlpp::sql_varchar, deployhostid,
		mysqlpp::sql_varchar, deploypath)

		Declare_Table_Model(BuildRule_Deploy)
		Declare_Table_Model_End()
}