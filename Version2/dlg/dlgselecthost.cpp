#include "dlgselecthost.h"
#include <QStandardItemModel>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QVBoxLayout>
#include "../common/DB.h"
#include "../common/http.h"
QJsonObject HostData::ToJsonObject()
{
	QJsonObject json;
	json["id"] = m_qsHostID;
	json["address"] = m_qsHostAddress;
	json["osname"] = m_qsOSName;
	json["osplatform"] = m_qsOSPlatform;
	json["path"] = m_qsPath;
	json["type"] = (int)m_enHostType;
	return json;
}

QString HostData::ToJsonString()
{
	return QJsonDocument(ToJsonObject()).toJson(QJsonDocument::Compact);
}

DlgSelectHost::DlgSelectHost(ENHostType ht, QWidget *parent)
	: DlgBase(parent)
{
	QSize szMain = QSize(500, 300);
	setFixedSize(szMain);
	setObjectName(QString::fromLocal8Bit("DlgSelectHost"));

	m_hd.SetHostType(ht);

	m_pTV = new QTableView();
	m_pTV->setObjectName(QString::fromLocal8Bit("DlgSelectHost"));
	QVBoxLayout *buildRuleContentLayout = new QVBoxLayout();
	buildRuleContentLayout->addWidget(m_pTV);
	buildRuleContentLayout->setContentsMargins(10, 0, 10, 0);

	QWidget *buildRuleWidget = new QWidget();
	buildRuleWidget->setLayout(buildRuleContentLayout);

	// bottom
	m_pPBOk = new QPushButton();
	m_pPBOk->setObjectName(QString::fromLocal8Bit("DlgSelectHostOk"));
	QHBoxLayout *bottomLayout = new QHBoxLayout();
	bottomLayout->addStretch();
	bottomLayout->addWidget(m_pPBOk);
	bottomLayout->addSpacing(5);
	bottomLayout->setContentsMargins(0, 0, 0, 10);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(buildRuleWidget);
	mainLayout->addLayout(bottomLayout);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	MainLayout()->addLayout(mainLayout);
	InitData();
	InitConnect();
}

DlgSelectHost::~DlgSelectHost()
{

}

void DlgSelectHost::InitData()
{
	m_pTitleBar->SetTitle(QString::fromLocal8Bit("选择要使用的主机资源"));
	// 主机资源
	QStandardItemModel *sim = new QStandardItemModel();
	sim->setHorizontalHeaderItem(0, new QStandardItem(QString::fromLocal8Bit("名称")));
	sim->setHorizontalHeaderItem(1, new QStandardItem(QString::fromLocal8Bit("地址")));
	sim->setHorizontalHeaderItem(2, new QStandardItem(QString::fromLocal8Bit("操作系统")));
	sim->setHorizontalHeaderItem(3, new QStandardItem(QString::fromLocal8Bit("")));

	m_pTV->setModel(sim);
	m_pTV->setColumnWidth(0,150);
	m_pTV->setColumnWidth(1, 100);
	m_pTV->setColumnWidth(2, 160);

	m_pTV->setStyleSheet(QString(""));
	m_pTV->setSelectionMode(QAbstractItemView::SingleSelection);
	m_pTV->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pTV->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_pTV->horizontalHeader()->setStretchLastSection(true);
	m_pTV->verticalHeader()->setVisible(false);
	m_pTV->verticalHeader()->setDefaultSectionSize(35);
	m_pTV->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pTV->setSelectionMode(QAbstractItemView::NoSelection);
	
	DB db;
	QString qsServerAddres = db.getProtocol() + "://" + db.getServerIp() + ":" + db.getServerPort();
	QUrl url(qsServerAddres + QString::fromLocal8Bit("/host/query?type=%1").arg(m_hd.HostType()));

	Http http;
	http.get(url);
	m_qsHostInfo = http.getReplyData();
	QJsonParseError error;
	QJsonDocument jsonDoc = QJsonDocument::fromJson(m_qsHostInfo.toUtf8(), &error);
	if (!jsonDoc.isNull())
	{
		QJsonObject jsonReplyData = jsonDoc.object();
		QJsonArray jsonData = jsonReplyData["data"].toArray();
		for (int nIndex = 0; nIndex < jsonData.size(); nIndex++)
		{
			QJsonObject jsonHost = jsonData[nIndex].toObject();
			sim->setItem(nIndex, 0, new QStandardItem(jsonHost["name"].toString()));
			sim->setItem(nIndex, 1, new QStandardItem(jsonHost["address"].toString()));
			QString qsOS = jsonHost["operatingsystem"].toString();
			QJsonDocument jsonOSDoc = QJsonDocument::fromJson(qsOS.toUtf8(), &error);
			if (!jsonOSDoc.isNull())
			{
				QJsonObject jsonOS = jsonOSDoc.object();
				QString qsOSName = jsonOS["name"].toString();
				QString qsOSPlatform = jsonOS["platform"].toString();
				QString qsOSContent = QString::fromLocal8Bit("%1 %2").arg(qsOSName).arg(qsOSPlatform);
				sim->setItem(nIndex, 2, new QStandardItem(qsOSContent));
			}
		}
	}
	// bottom
	m_pPBOk->setText(QString::fromLocal8Bit("确定"));
}

void DlgSelectHost::InitConnect()
{
	connect(m_pPBOk, SIGNAL(clicked()), this, SLOT(SlotPBOkClicked()) );
}

void DlgSelectHost::SlotPBOkClicked()
{
	QModelIndex mi = m_pTV->currentIndex();
	if (mi.row() < 0)
		return;
	QJsonParseError error;
	QJsonDocument jsonDoc = QJsonDocument::fromJson(m_qsHostInfo.toUtf8(), &error);
	if (!jsonDoc.isNull())
	{
		QJsonObject jsonReplyData = jsonDoc.object();
		QJsonArray jsonData = jsonReplyData["data"].toArray();
		QJsonObject jsonHost = jsonData[mi.row()].toObject();
		m_hd.SetHostID(jsonHost["guid"].toString());
		m_hd.SetHostAddress(jsonHost["address"].toString());
		m_hd.SetHostPort(jsonHost["port"].toInt());
		QString qsOS = jsonHost["operatingsystem"].toString();
		QJsonDocument jsonOSDoc = QJsonDocument::fromJson(qsOS.toUtf8(), &error);
		if (!jsonOSDoc.isNull())
		{
			QJsonObject jsonOS = jsonOSDoc.object();
			m_hd.SetHostOSName(jsonOS["name"].toString());
			m_hd.SetHostOSPlatform(jsonOS["platform"].toString());
		}
		QString qsStorage = jsonHost["storage"].toString();
		QJsonDocument jsonStorageDoc = QJsonDocument::fromJson(qsStorage.toUtf8(), &error);
		if (!jsonStorageDoc.isNull())
		{
			QJsonObject jsonStorage = jsonStorageDoc.object();
			QJsonArray jsonarrayPN = jsonStorage["partitionName"].toArray();
			m_hd.SetSelectPath(jsonarrayPN[0].toString());
		}
	}
	accept();
}