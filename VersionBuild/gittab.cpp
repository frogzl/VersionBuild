#include "gittab.h"
#include <QStandardItemModel>
#include <DB.h>
#include <QHeaderView>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "buttondelegate.h"
#include "http.h"

GitTab::GitTab(QWidget *parent) : QWidget(parent)
{
	m_TableView = new QTableView();
	m_MainLayout = new QVBoxLayout();

	m_MainLayout->addWidget(m_TableView);

	setLayout(m_MainLayout);

	// ��������========================================
	QStandardItemModel *sim = new QStandardItemModel();
	sim->setHorizontalHeaderItem(0, new QStandardItem(QString::fromLocal8Bit("״̬")));
	sim->setHorizontalHeaderItem(1, new QStandardItem(QString::fromLocal8Bit("��Ŀ����")));
	sim->setHorizontalHeaderItem(2, new QStandardItem(QString::fromLocal8Bit("URL")));
	sim->setHorizontalHeaderItem(3, new QStandardItem(QString::fromLocal8Bit("��֧��")));
	sim->setHorizontalHeaderItem(4, new QStandardItem(QString::fromLocal8Bit("��ǰ�汾"))); 
	sim->setHorizontalHeaderItem(5, new QStandardItem(QString::fromLocal8Bit("")));

	m_TableView->setModel(sim);
	m_TableView->setColumnWidth(0, 40);
	m_TableView->setColumnWidth(1, 135);
	m_TableView->setColumnWidth(2, 400);
	m_TableView->setColumnWidth(3, 60);
	m_TableView->setColumnWidth(4, 60);
	m_TableView->setColumnWidth(5, 50);
	m_TableView->setStyleSheet(QString(""));
	m_TableView->setSelectionMode(QAbstractItemView::SingleSelection);
	m_TableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_TableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_TableView->horizontalHeader()->setStretchLastSection(true);
	m_TableView->verticalHeader()->setVisible(false);
	ButtonDelegate *bd = new ButtonDelegate(this);
	CollData data;
	data.append(new DataPair(QString::fromLocal8Bit("��ϸ"), DetailEvent));
	bd->setData(data);
	m_TableView->setItemDelegateForColumn(5, bd);
	// ����========================================
}

GitTab::~GitTab()
{

}

void GitTab::RefreshData()
{
	QStandardItemModel *sim = (QStandardItemModel *)m_TableView->model();
	sim->removeRows(0, sim->rowCount());
	m_vecRTI.clear();

	DB db;
	QString qsServerAddres = db.getProtocol() + "://" + db.getServerIp() + ":" + db.getServerPort() + "/";
	QUrl url(qsServerAddres + QString("repertory/query"));
	Http http;
	http.get(url);
	QString qsReplyData = http.getReplyData();
	QJsonParseError error;
	QJsonDocument jsonDoc = QJsonDocument::fromJson(qsReplyData.toUtf8(), &error);
	if (!jsonDoc.isNull())
	{
		QJsonObject jsonReplyData = jsonDoc.object();
		QString qsCode = jsonReplyData["code"].toString();
		if (qsCode.compare("0") == 0)
		{
			
			QJsonArray array = jsonReplyData["data"].toArray();
			for (int nIndex = 0; nIndex < array.size(); nIndex++)
			{
				QJsonObject obj = array[nIndex].toObject();
				Common::RepertoryItem ri;
				ri.qsGuid = obj["guid"].toString();
				ri.qsName = obj["name"].toString();
				ri.qsUrl = obj["url"].toString();
				ri.qsBranch = obj["branchname"].toString();
				ri.nVersionStart = obj["versionstart"].toInt();
				ri.nVersionCurrent = obj["versioncurrent"].toInt();
				ri.nStatus = obj["status"].toInt();
				m_vecRTI.push_back(ri);
				sim->setItem(nIndex, 0, new QStandardItem(QString("%1").arg(ri.nStatus)));
				sim->setItem(nIndex, 1, new QStandardItem(ri.qsName));
				sim->setItem(nIndex, 2, new QStandardItem(ri.qsUrl));
				sim->setItem(nIndex, 3, new QStandardItem(ri.qsBranch));
				sim->setItem(nIndex, 4, new QStandardItem(QString("%1").arg(ri.nVersionCurrent)));
			}
		}
	}

}

bool GitTab::DetailEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
	return true;
}