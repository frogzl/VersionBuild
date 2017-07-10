#include "dlgselectdepends.h"
#include <QStandardItemModel>
#include <DB.h>
#include <QHeaderView>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "buttondelegate.h"
#include "http.h"
DlgSelectDepends::DlgSelectDepends(QWidget *parent)
	: QDialog(parent)
{
	setWindowTitle(QString::fromLocal8Bit("选择依赖"));
	resize(QSize(800, 400));

	m_TV = new QTableView();
	m_MainLayout = new QVBoxLayout();

	m_MainLayout->addWidget(m_TV);

	setLayout(m_MainLayout);

	// 属性设置========================================
	QStandardItemModel *sim = new QStandardItemModel();
	sim->setHorizontalHeaderItem(0, new QStandardItem(QString::fromLocal8Bit("状态")));
	sim->setHorizontalHeaderItem(1, new QStandardItem(QString::fromLocal8Bit("项目名称")));
	sim->setHorizontalHeaderItem(2, new QStandardItem(QString::fromLocal8Bit("URL")));
	sim->setHorizontalHeaderItem(3, new QStandardItem(QString::fromLocal8Bit("分支名")));
	sim->setHorizontalHeaderItem(4, new QStandardItem(QString::fromLocal8Bit("当前版本")));
	sim->setHorizontalHeaderItem(5, new QStandardItem(QString::fromLocal8Bit("")));

	m_TV->setModel(sim);
	m_TV->setColumnWidth(0, 40);
	m_TV->setColumnWidth(1, 155);
	m_TV->setColumnWidth(2, 400);
	m_TV->setColumnWidth(3, 60);
	m_TV->setColumnWidth(4, 60);
	m_TV->setColumnWidth(5, 50);
	m_TV->setStyleSheet(QString(""));
	m_TV->setSelectionMode(QAbstractItemView::SingleSelection);
	m_TV->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_TV->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_TV->horizontalHeader()->setStretchLastSection(true);
	m_TV->verticalHeader()->setVisible(false);
	ButtonDelegate *bd = new ButtonDelegate(this);
	CollData data;
	data.append(new DataPair(QString::fromLocal8Bit("选择"), SelectEvent));
	bd->setData(data);
	m_TV->setItemDelegateForColumn(5, bd);
	// 数据========================================
	RefreshData();
}

DlgSelectDepends::~DlgSelectDepends()
{

}

void DlgSelectDepends::RefreshData()
{
	QStandardItemModel *sim = (QStandardItemModel *)m_TV->model();
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

bool DlgSelectDepends::SelectEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
	return true;
}