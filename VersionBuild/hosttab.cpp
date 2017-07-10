#include "hosttab.h"
#include <QStandardItemModel>
#include <DB.h>
#include <QHeaderView>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "buttondelegate.h"
#include "http.h"

HostTab::HostTab(QWidget *parent) : QWidget(parent)
{
	QWidget *centerWidget = new QWidget(this);
	m_TableView = new QTableView();
	m_MainLayout = new QVBoxLayout();

	m_MainLayout->addWidget(m_TableView);

	setLayout(m_MainLayout);

	// 属性设置========================================
	QStandardItemModel *sim = new QStandardItemModel();
	sim->setHorizontalHeaderItem(0, new QStandardItem(QString::fromLocal8Bit("主机名")));
	sim->setHorizontalHeaderItem(1, new QStandardItem(QString::fromLocal8Bit("地址")));
	sim->setHorizontalHeaderItem(2, new QStandardItem(QString::fromLocal8Bit("系统类型")));
	sim->setHorizontalHeaderItem(3, new QStandardItem(QString::fromLocal8Bit("")));

	m_TableView->setModel(sim);
	m_TableView->setColumnWidth(0, 250);
	m_TableView->setColumnWidth(1, 200);
	m_TableView->setColumnWidth(2, 200);
	m_TableView->setColumnWidth(3, 60);
	m_TableView->setStyleSheet(QString(""));
	m_TableView->setSelectionMode(QAbstractItemView::SingleSelection);
	m_TableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_TableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_TableView->horizontalHeader()->setStretchLastSection(true);
	m_TableView->verticalHeader()->setVisible(false);
	ButtonDelegate *bd = new ButtonDelegate(this);
	CollData data;
	data.append(new DataPair(QString::fromLocal8Bit("详细"), DetailEvent));
	bd->setData(data);
	m_TableView->setItemDelegateForColumn(3, bd);
	// 数据========================================

}

HostTab::~HostTab()
{

}

void HostTab::RefreshData()
{

}

bool HostTab::DetailEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
	return true;
}