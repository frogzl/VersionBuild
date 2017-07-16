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
		return con.connect(SystemConfig::instance()->m_sName.c_str(),
			SystemConfig::instance()->m_sHost.c_str(),
			SystemConfig::instance()->m_sUser.c_str(),
			SystemConfig::instance()->m_sPassword.c_str());
	}

	void Database::close_database()
	{

	}
}