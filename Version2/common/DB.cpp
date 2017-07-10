#include "DB.h"
#include <QFile>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QCoreApplication>
DB::DB()
{
}


DB::~DB()
{
}

bool DB::openProDb()
{
	m_Mutex.lock();
	m_DB = QSqlDatabase::addDatabase("QSQLITE", "first");
	{
		QString qsAppDir = QCoreApplication::applicationDirPath();
		QString dbName = qsAppDir + QString::fromLocal8Bit("/VersionBuild");
		QFile file(dbName);
		if (!file.exists()) {
			QMessageBox::information(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("找不到文件：") + dbName, QMessageBox::Yes);
			return false;
		}

		m_DB.setDatabaseName(dbName);
		bool ok = m_DB.open();
		if (!ok) {
			QMessageBox::information(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("加载数据文件失败：") + dbName, QMessageBox::Yes);
			return false;
		}
	}
	return true;
}

void DB::closeDb()
{
	m_DB.close();
	m_DB.removeDatabase(m_DB.connectionName());
	m_Mutex.unlock();
}

QString DB::getProtocol()
{
	openProDb();
	QString qsProtocol;
	QSqlQuery query(m_DB);
	QString sql = QString("select value from setting where key='protocol'");
	query.exec(sql);
	if (!query.isActive())
	{
		closeDb();
		return QString::fromLocal8Bit("");
	}

	while (query.next())
	{
		qsProtocol = query.value(0).toString();
	}
	query.clear();
	query.finish();
	closeDb();
	return qsProtocol;
}

QString DB::getServerIp()
{
	openProDb();
	QString qsServerIp;
	QSqlQuery query(m_DB);
	QString sql = QString("select value from setting where key='server'");
	query.exec(sql);
	if (!query.isActive())
	{
		closeDb();
		return QString::fromLocal8Bit("");
	}

	while (query.next())
	{
		qsServerIp = query.value(0).toString();
	}
	query.clear();
	query.finish();
	closeDb();
	return qsServerIp;
}

QString DB::getServerPort()
{
	openProDb();
	QString qsPort;
	QSqlQuery query(m_DB);
	QString sql = QString("select value from setting where key='port'");
	query.exec(sql);
	if (!query.isActive())
	{
		closeDb();
		return QString::fromLocal8Bit("");
	}

	while (query.next())
	{
		qsPort = query.value(0).toString();
	}
	query.clear();
	query.finish();
	closeDb();
	return qsPort;
}

bool DB::reloadProducts(QStandardItemModel *sim)
{
	sim->removeRows(0, sim->rowCount());

	// 重新初始化数据
	openProDb();

	QSqlQuery query(m_DB);
	QString sql = QString("select name, version from products");
	query.exec(sql);
	if (!query.isActive())
	{
		closeDb();
		return false;
	}
	int nIndex = 0;
	while (query.next())
	{
		QString qsProductName = query.value(0).toString();
		QString qsVersion = query.value(1).toString();

		sim->setItem(nIndex, 0, new QStandardItem(qsProductName));
		sim->setItem(nIndex, 1, new QStandardItem(qsVersion));
		nIndex++;
	}
	query.clear();
	query.finish();
	closeDb();
	return true;
}

bool DB::reloadRepertorys(QStandardItemModel *sim)
{
	sim->removeRows(0, sim->rowCount());

	// 重新初始化数据
	openProDb();

	QSqlQuery query(m_DB);
	QString sql = QString("select name, url, branch, usable, version_current from repertorys");
	query.exec(sql);
	if (!query.isActive())
	{
		closeDb();
		return false;
	}
	int nIndex = 0;
	while (query.next())
	{
		QString qsStatus = query.value(3).toInt() == 1 ? QString::fromLocal8Bit("使用中") : QString::fromLocal8Bit("空闲");
		QString qsName = query.value(0).toString();
		QString qsUrl = query.value(1).toString();
		QString qsBranch = query.value(2).toString();
		QString qsVersion = QString("%1").arg(query.value(4).toInt());
		sim->setItem(nIndex, 0, new QStandardItem(qsStatus));
		sim->setItem(nIndex, 1, new QStandardItem(qsName));
		sim->setItem(nIndex, 2, new QStandardItem(qsUrl));
		sim->setItem(nIndex, 3, new QStandardItem(qsBranch));
		sim->setItem(nIndex, 4, new QStandardItem(qsVersion));
		nIndex++;
	}
	query.clear();
	query.finish();
	closeDb();
	return true;
}

bool DB::insertRepertorys(QString qsGuid, QString qsName, QString qsRepertoryPath, QString qsBranchName, int nVersionStartNum)
{
	bool bRet = true;
	openProDb();
	QSqlQuery query(m_DB);
	query.prepare(QString("insert into "
		"repertorys (guid, name, url, branch, usable, product_guid, version_start, version_current) "
		"values (:guid, :name, :url, :branch, :usable, :product_guid, :version_start, :version_current);"));

	query.bindValue(":guid", qsGuid);
	query.bindValue(":name", qsName);
	query.bindValue(":url", qsRepertoryPath);
	query.bindValue(":branch", qsBranchName);
	query.bindValue(":usable", nVersionStartNum);
	query.bindValue(":product_guid", "");
	query.bindValue(":version_start", nVersionStartNum);
	query.bindValue(":version_current", nVersionStartNum);

	if (!query.exec()) {
		bRet = false;
		QSqlError se = query.lastError();
		QMessageBox::information(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("insertRepertorys失败：") + query.lastError().text(), QMessageBox::Yes);
	}
	m_DB.commit();
	query.clear();
	query.finish();
	closeDb();
	return bRet;
}

bool DB::insertBuildRules(QString qsGuid, QString qsScriptPath, QString qsOutputPath, QString qsTargetFile, QString qsPlatform)
{
	bool bRet = true;
	openProDb();
	QSqlQuery query(m_DB);
	query.prepare(QString("insert into "
		"build_rules (guid, script_path, output_path, target_file, platform) "
		"values (:guid, :script_path, :output_path, :target_file, :platform);"));

	query.bindValue(":guid", qsGuid);
	query.bindValue(":script_path", qsScriptPath);
	query.bindValue(":output_path", qsOutputPath);
	query.bindValue(":target_file", qsTargetFile);
	query.bindValue(":platform", qsPlatform);

	if (!query.exec()) {
		bRet = false;
		QSqlError se = query.lastError();
		QMessageBox::information(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("insertBuildRules失败：") + query.lastError().text(), QMessageBox::Yes);
	}
	m_DB.commit();
	query.clear();
	query.finish();
	closeDb();
	return bRet;
}