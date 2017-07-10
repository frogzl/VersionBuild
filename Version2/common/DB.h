#pragma once
#include "qobject.h"
#include <QStandardItemModel>
#include <QMutex>
#include <QSqlDatabase>

class DB :public QObject
{
	Q_OBJECT
public:
	DB();
	~DB();
private:
	bool openProDb();
	void closeDb();
public:
	QString getProtocol();
	QString getServerIp();
	QString getServerPort();
	bool reloadProducts(QStandardItemModel *sim);
	bool reloadRepertorys(QStandardItemModel *sim);
	bool insertRepertorys(QString qsGuid, QString qsName, QString qsRepertoryPath, QString qsBranchName, int nVersionStartNum);
	bool insertBuildRules(QString qsGuid, QString qsScriptPath, QString qsOutputPath, QString qsTargetFile, QString qsPlatform);
private:
	QMutex m_Mutex;
	QSqlDatabase m_DB;
};


