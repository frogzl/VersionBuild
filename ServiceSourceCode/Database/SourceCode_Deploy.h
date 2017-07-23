#pragma once
#include "Database.h"
	namespace DB {
	sql_create_2(Declare_Table_Model_Data(SourceCode_Deploy),
		1,2,
		mysqlpp::sql_varchar, guid,
		mysqlpp::sql_varchar, deployhostid)

		Declare_Table_Model(SourceCode_Deploy)
		Declare_Table_Model_End()
}