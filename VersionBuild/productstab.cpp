#include "productstab.h"
#include <QStandardItemModel>
#include <DB.h>
#include <QHeaderView>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include "buttondelegate.h"
#include "http.h"
ProductsTab::ProductsTab(QWidget *parent)
	: QWidget(parent)
{
	QWidget *centerWidget = new QWidget(this);
	m_TableView = new QTableView();
	m_MainLayout = new QVBoxLayout();

	m_MainLayout->addWidget(m_TableView);

	setLayout(m_MainLayout);


	// 属性设置========================================
	QStandardItemModel *sim = new QStandardItemModel();
	sim->setHorizontalHeaderItem(0, new QStandardItem(QString::fromLocal8Bit("产品名称")));
	sim->setHorizontalHeaderItem(1, new QStandardItem(QString::fromLocal8Bit("当前版本号")));
	sim->setHorizontalHeaderItem(2, new QStandardItem(QString::fromLocal8Bit("")));

	m_TableView->setModel(sim);
	m_TableView->setColumnWidth(0, 300);
	m_TableView->setColumnWidth(1, 100);
	m_TableView->setColumnWidth(2, 100);
	m_TableView->setStyleSheet(QString(""));
	ButtonDelegate *bd = new ButtonDelegate(this);
	CollData data;
	data.append(new DataPair(QString::fromLocal8Bit("构建"), ConstructionEvent));
	data.append(new DataPair(QString::fromLocal8Bit("发行"), PublishEvent));
	data.append(new DataPair(QString::fromLocal8Bit("详细"), DetailEvent));
	data.append(new DataPair(QString::fromLocal8Bit("下载"), DownloadEvent));

	bd->setData(data);
	m_TableView->setItemDelegateForColumn(2, bd);
	m_TableView->setSelectionMode(QAbstractItemView::SingleSelection);
	m_TableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_TableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_TableView->horizontalHeader()->setStretchLastSection(true);
	m_TableView->verticalHeader()->setVisible(false);

	// 数据========================================
	DB db;
	db.reloadProducts((QStandardItemModel *)m_TableView->model());
}

ProductsTab::~ProductsTab()
{

}

void ProductsTab::RefreshData()
{
/*	DB db;
	QString qsServerAddres = db.getProtocol() + "://" + db.getServerIp() + ":" + db.getServerPort() + "/";
	QUrl url(qsServerAddres + QString("product/query"));
	Http http;
	http.get(url);
	QString qsReplyData = http.getReplyData();
	QJsonDocument jsonDoc = QJsonDocument::fromJson(qsReplyData.toLocal8Bit());
	if (!jsonDoc.isNull())
	{
		QJsonObject jsonReplyData = jsonDoc.object();
		QString qsCode = jsonReplyData["code"].toString();
		if (qsCode.compare("0") == 0)
		{

		}
	}
	*/
}

bool ProductsTab::ConstructionEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
	return true;
}

bool ProductsTab::DetailEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
	return true;
}

bool ProductsTab::PublishEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
	return true;
}

bool ProductsTab::DownloadEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
	return true;
}