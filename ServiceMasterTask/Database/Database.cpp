#include "Database.h"
#include "../SystemConfig.h"

namespace DB {
	Database::Database()
	{
	}


	Database::~Database()
	{
	}

	bool Database::open_database()
	{
		con = mysqlpp::Connection(true);
		con.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
		return con.connect(SystemConfig::instance()->m_sDBName.c_str(),
			SystemConfig::instance()->m_sDBHost.c_str(),
			SystemConfig::instance()->m_sDBUser.c_str(),
			SystemConfig::instance()->m_sDBPassword.c_str());
	}

	void Database::close_database()
	{

	}
}