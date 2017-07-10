#include "dlgselectbuildruleplatform.h"
#include <QStandardItemModel>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QVBoxLayout>
DlgSelectBuildRulePlatform::DlgSelectBuildRulePlatform(QWidget *parent)
	: DlgBase(parent)
{
	QSize szMain = QSize(220, 350);
	setFixedSize(szMain);
	setObjectName(QString::fromLocal8Bit("DlgSelectBuildRulePlatform"));

	m_pTV = new QTableView();
	m_pTV->setObjectName(QString::fromLocal8Bit("DlgSelectBuildRulePlatform"));
	QVBoxLayout *buildRuleContentLayout = new QVBoxLayout();
	buildRuleContentLayout->addWidget(m_pTV);
	buildRuleContentLayout->setContentsMargins(10, 0, 10, 0);

	QWidget *buildRuleWidget = new QWidget();
	buildRuleWidget->setLayout(buildRuleContentLayout);

	// bottom
	m_pPBOk = new QPushButton();
	m_pPBOk->setObjectName(QString::fromLocal8Bit("DlgSelectBuildRulePlatformOk"));
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

DlgSelectBuildRulePlatform::~DlgSelectBuildRulePlatform()
{

}

void DlgSelectBuildRulePlatform::InitData()
{
	m_pTitleBar->SetTitle(QString::fromLocal8Bit("选择构建规则的平台"));
	// 主机资源
	QStandardItemModel *sim = new QStandardItemModel();
	sim->setHorizontalHeaderItem(0, new QStandardItem(QString::fromLocal8Bit("平台名")));

	m_pTV->setModel(sim);
	m_pTV->setColumnWidth(0, 250);

	m_pTV->setStyleSheet(QString(""));
	m_pTV->setSelectionMode(QAbstractItemView::SingleSelection);
	m_pTV->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pTV->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_pTV->horizontalHeader()->setStretchLastSection(true);
	m_pTV->verticalHeader()->setVisible(false);
	m_pTV->verticalHeader()->setDefaultSectionSize(35);
	m_pTV->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pTV->setSelectionMode(QAbstractItemView::NoSelection);

	// bottom
	m_pPBOk->setText(QString::fromLocal8Bit("确定"));
}

void DlgSelectBuildRulePlatform::InitConnect()
{

}