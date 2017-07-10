#ifndef DLGSELECTHOST_H
#define DLGSELECTHOST_H

#include "dlgbase.h"
#include <QTableView>
#include <QPushButton>

enum ENHostType
{
	enHostType_Storage = 0x00000001, // 存储服务器
	enHostType_Build = 0x00000002, // 构建服务器
	enHostType_Database = 0x00000004, // 数据库服务器
	enHostType_Business = 0x00000008, // 业务服务器
	enHostType_VersionControll = 0x00000010, // 版本控制服务器
	enHostType_Log = 0x00000020 // 日志服务器
};

class HostData
{
public:
	QJsonObject ToJsonObject();
	QString ToJsonString();
	void	 SetHostID(QString qsData) { m_qsHostID = qsData; }
	void	 SetHostAddress(QString qsData) { m_qsHostAddress = qsData; }
	void	 SetHostOSName(QString qsData) { m_qsOSName = qsData; }
	void	 SetHostOSPlatform(QString qsData) { m_qsOSPlatform = qsData; }
	void	 SetHostType(ENHostType enData) { m_enHostType = enData; }
	void	 SetSelectPath(QString qsData) { m_qsPath = qsData; }
	int SetHostPort(int nPort) { return m_nPort; }

	QString HostID() { return m_qsHostID; }
	QString HostAddress() { return m_qsHostAddress; }
	QString HostOSName() { return m_qsOSName; }
	QString HostOSPlatform() { return m_qsOSPlatform; }
	ENHostType HostType() { return m_enHostType; }
	QString SelectPath() { return m_qsPath; }
	int HostPort() { return m_nPort; }
private:
	QString m_qsHostID;
	QString m_qsHostAddress;
	QString m_qsOSName;
	QString m_qsOSPlatform;
	QString m_qsPath;
	int m_nPort;
	ENHostType m_enHostType;
};

class DlgSelectHost : public DlgBase
{
	Q_OBJECT

public:
	DlgSelectHost(ENHostType ht, QWidget *parent = 0);
	~DlgSelectHost();
	HostData Data() { return m_hd; }
private:
	void InitData();
	void InitConnect();
	private slots:
	void SlotPBOkClicked();
private:
	QTableView *m_pTV;
	QPushButton *m_pPBOk;
	QString m_qsHostInfo;
	HostData m_hd;
};

#endif // DLGSELECTHOST_H
