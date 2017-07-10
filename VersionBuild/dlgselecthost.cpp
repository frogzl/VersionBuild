#include "dlgselecthost.h"
#include <QHBoxLayout>
#include <QStandardItemModel>
#include <QHeaderView>
DlgSelectHost::DlgSelectHost(QWidget *parent)
	: QDialog(parent)
{
	setWindowTitle(QString::fromLocal8Bit("选择部署位置"));
	resize(QSize(200, 500));

	m_LBTitle = new QLabel();

	m_TVHost = new QTableView;

	m_BtnAdd = new QPushButton();
	m_BtnCancle = new QPushButton();
	QHBoxLayout *bottomLayout = new QHBoxLayout();
	bottomLayout->addStretch();
	bottomLayout->addWidget(m_BtnAdd);
	bottomLayout->addWidget(m_BtnCancle);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(m_LBTitle);
	mainLayout->addWidget(m_TVHost);
	mainLayout->addLayout(bottomLayout);
	setLayout(mainLayout);

	// 属性设置========================================
	m_BtnAdd->setFixedSize(QSize(100, 25));
	m_BtnCancle->setFixedSize(QSize(100, 25));

	QStandardItemModel *sim = new QStandardItemModel();
	sim->setHorizontalHeaderItem(0, new QStandardItem(QString::fromLocal8Bit("主机名")));
	sim->setHorizontalHeaderItem(1, new QStandardItem(QString::fromLocal8Bit("可用空间")));

	m_TVHost->setModel(sim);
	m_TVHost->setColumnWidth(0, 80);
	m_TVHost->setColumnWidth(1, 80);

	m_TVHost->setStyleSheet(QString(""));
	m_TVHost->setSelectionMode(QAbstractItemView::SingleSelection);
	m_TVHost->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_TVHost->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_TVHost->horizontalHeader()->setStretchLastSection(true);
	m_TVHost->verticalHeader()->setVisible(false);

	// 数据设置========================================
	m_LBTitle->setText(QString::fromLocal8Bit("请选择部署位置"));

	m_BtnAdd->setText(QString::fromLocal8Bit("选择"));
	m_BtnCancle->setText(QString::fromLocal8Bit("取消"));

	// connect========================================
	connect(m_BtnAdd, SIGNAL(clicked()), this, SLOT(SlotAdd()));
	connect(m_BtnCancle, SIGNAL(clicked()), this, SLOT(SlotCancle()));
}

DlgSelectHost::~DlgSelectHost()
{

}

void DlgSelectHost::SlotAdd()
{
	close();
}


void DlgSelectHost::SlotCancle()
{
	close();
}