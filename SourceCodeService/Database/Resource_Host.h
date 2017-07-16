#pragma once
#include "Database.h"
	namespace DB {
	sql_create_11(Declare_Table_Model_Data(Resource_Host),
		1, 11,
		mysqlpp::sql_varchar, guid,
		mysqlpp::sql_varchar, name,
		mysqlpp::sql_varchar, discription,
		mysqlpp::sql_int, type,
		mysqlpp::sql_varchar, address,
		mysqlpp::sql_int, port,
		mysqlpp::sql_text, operatingsystem,
		mysqlpp::sql_text, cpu,
		mysqlpp::sql_text, memory,
		mysqlpp::sql_text, storage,
		mysqlpp::sql_text, environmentvariable)

		Declare_Table_Model(Resource_Host)
		Declare_Table_Model_End()
}