#pragma once
#include "Database.h"
	namespace DB {
	sql_create_4(Declare_Table_Model_Data(Resource_CompressionPackage),
		1, 4,
		mysqlpp::sql_varchar, guid,
		mysqlpp::sql_varchar, name,
		mysqlpp::sql_varchar, discription,
		mysqlpp::sql_varchar, storageid)

		Declare_Table_Model(Resource_CompressionPackage)
		Declare_Table_Model_End()
}