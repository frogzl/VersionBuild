#include "dlgcreatebuildrule.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QRegExp>
#include <QValidator>
#include <QFileDialog>
#include "dlgselectdepends.h"

DlgCreateBuildRule::DlgCreateBuildRule(QWidget *parent)
	: QDialog(parent)
{
	setWindowTitle(QString::fromLocal8Bit("创建构建规则"));
	resize(QSize(400, 400));

	// 变量初始化======================================

	// Build group
	m_LBBuildPlatform = new QLabel();
	m_LEBuildPlatform = new QLineEdit();
	QHBoxLayout *buildPlatformLayout = new QHBoxLayout();
	buildPlatformLayout->addWidget(m_LBBuildPlatform);
	buildPlatformLayout->addWidget(m_LEBuildPlatform);
	buildPlatformLayout->addStretch();

	m_LBBuildScript = new QLabel(); 
	m_LEBuildScript = new QLineEdit();
	m_BtnSelector = new QPushButton();
	QHBoxLayout *buildScriptLayout = new QHBoxLayout();
	buildScriptLayout->addWidget(m_LBBuildScript);
	buildScriptLayout->addWidget(m_LEBuildScript);
	buildScriptLayout->addWidget(m_BtnSelector);
	buildScriptLayout->addStretch();

	m_LBBuildOutput = new QLabel();
	m_LEBuildOutput = new QLineEdit();
	QHBoxLayout *buildOutputLayout = new QHBoxLayout();
	buildOutputLayout->addWidget(m_LBBuildOutput);
	buildOutputLayout->addWidget(m_LEBuildOutput);
	buildOutputLayout->addStretch();

	m_LBBuildTarget = new QLabel();
	m_LEBuildTarget = new QLineEdit();
	QHBoxLayout *buildTargetLayout = new QHBoxLayout();
	buildTargetLayout->addWidget(m_LBBuildTarget);
	buildTargetLayout->addWidget(m_LEBuildTarget);
	buildTargetLayout->addStretch();
	m_LBBuildNote = new QLabel();

	QVBoxLayout *buildGroupLayout = new QVBoxLayout();
	buildGroupLayout->addLayout(buildPlatformLayout);
	buildGroupLayout->addLayout(buildScriptLayout);
	buildGroupLayout->addLayout(buildOutputLayout);
	buildGroupLayout->addLayout(buildTargetLayout);
	buildGroupLayout->addWidget(m_LBBuildNote);

	// depends
	m_BtnDependsAdd = new QPushButton();
	m_BtnDependsDelete = new QPushButton();
	QHBoxLayout *buildRuleLayout = new QHBoxLayout();
	buildRuleLayout->addWidget(m_BtnDependsAdd);
	buildRuleLayout->addWidget(m_BtnDependsDelete);
	buildRuleLayout->addStretch();

	m_TVDepends = new QTableView();

	QVBoxLayout *dependsLayout = new QVBoxLayout();
	dependsLayout->addLayout(buildRuleLayout);
	dependsLayout->addWidget(m_TVDepends);

	m_GBDepends = new QGroupBox();
	m_GBDepends->setLayout(dependsLayout);

	// bottom
	m_BtnAdd = new QPushButton();
	m_BtnCancle = new QPushButton();
	QHBoxLayout *bottomLayout = new QHBoxLayout();
	bottomLayout->addStretch();
	bottomLayout->addWidget(m_BtnAdd);
	bottomLayout->addWidget(m_BtnCancle);
	// main
	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addLayout(buildGroupLayout);
	mainLayout->addWidget(m_GBDepends);
	mainLayout->addLayout(bottomLayout);
	mainLayout->addStretch();
	setLayout(mainLayout);

	// 属性设置========================================
	m_BtnDependsAdd->setFixedSize(QSize(60, 25));
	m_BtnDependsDelete->setFixedSize(QSize(60, 25));
	m_BtnSelector->setFixedSize(QSize(25, 25));
	m_BtnAdd->setFixedSize(QSize(90, 25));
	m_BtnCancle->setFixedSize(QSize(90, 25));

	m_LEBuildScript->setFixedSize(QSize(325, 25));
	m_LEBuildOutput->setFixedSize(QSize(355, 25));
	m_LEBuildTarget->setFixedSize(QSize(355, 25));
	m_LBBuildNote->setFixedSize(QSize(420, 40));
	m_LBBuildNote->setWordWrap(true);

	QStandardItemModel *sim = new QStandardItemModel();
	sim->setHorizontalHeaderItem(0, new QStandardItem(QString::fromLocal8Bit("名称")));
	sim->setHorizontalHeaderItem(1, new QStandardItem(QString::fromLocal8Bit("平台")));
	sim->setHorizontalHeaderItem(2, new QStandardItem(QString::fromLocal8Bit("当前版本")));
	sim->setHorizontalHeaderItem(3, new QStandardItem(QString::fromLocal8Bit("位置（相对）")));

	m_TVDepends->setModel(sim);
	m_TVDepends->setColumnWidth(0, 80);
	m_TVDepends->setColumnWidth(1, 80);
	m_TVDepends->setColumnWidth(2, 80);
	m_TVDepends->setColumnWidth(3, 50);
	m_TVDepends->setStyleSheet(QString(""));
	m_TVDepends->setSelectionMode(QAbstractItemView::SingleSelection);
	m_TVDepends->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_TVDepends->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_TVDepends->horizontalHeader()->setStretchLastSection(true);
	m_TVDepends->verticalHeader()->setVisible(false);
	// 数据设置========================================
	m_LBBuildPlatform->setText(QString::fromLocal8Bit("平    台"));
	m_LEBuildPlatform->setPlaceholderText(QString::fromLocal8Bit("支持的平台类型，如：x64"));

	m_LBBuildScript->setText(QString::fromLocal8Bit("编译脚本"));
	m_LEBuildScript->setPlaceholderText(QString::fromLocal8Bit("编辑脚本的上传路径"));

	m_LBBuildOutput->setText(QString::fromLocal8Bit("输出路径"));
	m_LEBuildOutput->setPlaceholderText(QString::fromLocal8Bit("编译脚本的输出路径"));
	
	m_LBBuildTarget->setText(QString::fromLocal8Bit("目标文件"));
	m_LEBuildTarget->setPlaceholderText(QString::fromLocal8Bit("目标文件的文件名（包含扩展名）"));

	m_LBBuildNote->setText(QString::fromLocal8Bit("备注：输出路径的根目录是本地仓库的更目录"));

	m_GBDepends->setTitle(QString::fromLocal8Bit("依赖"));
	m_BtnDependsAdd->setText(QString::fromLocal8Bit("添加"));
	m_BtnDependsDelete->setText(QString::fromLocal8Bit("删除"));
	m_BtnSelector->setText(QString::fromLocal8Bit("..."));
	m_BtnAdd->setText(QString::fromLocal8Bit("添加"));
	m_BtnCancle->setText(QString::fromLocal8Bit("取消"));

	// connect=========================================
	connect(m_BtnDependsAdd, SIGNAL(clicked()), this, SLOT(SlotDependsAdd()));
	connect(m_BtnAdd, SIGNAL(clicked()), this, SLOT(SlotAdd()));
	connect(m_BtnCancle, SIGNAL(clicked()), this, SLOT(SlotCancle()));
	connect(m_BtnSelector, SIGNAL(clicked()), this, SLOT(SlotSelector()));
	m_bAdd = false;
}

DlgCreateBuildRule::~DlgCreateBuildRule()
{

}

bool DlgCreateBuildRule::IsAdd()
{
	return m_bAdd;
}

QString DlgCreateBuildRule::GetPlatform()
{
	return m_LEBuildPlatform->text();
}

QString DlgCreateBuildRule::GetScript()
{
	return m_LEBuildScript->text();
}

QString DlgCreateBuildRule::GetOutput()
{
	return m_LEBuildOutput->text();
}

QString DlgCreateBuildRule::GetTarget()
{
	return m_LEBuildTarget->text();
}

void DlgCreateBuildRule::SlotDependsAdd()
{
	DlgSelectDepends dlg(this);
	dlg.exec();
}

void DlgCreateBuildRule::SlotSelector()
{
	QString qsName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("获取脚本文件"));
	m_LEBuildScript->setText(qsName);
}

void DlgCreateBuildRule::SlotAdd()
{
	m_bAdd = true;
	close();
}

void DlgCreateBuildRule::SlotCancle()
{
	close();
}