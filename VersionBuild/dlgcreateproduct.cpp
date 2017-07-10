#include "dlgcreateproduct.h"
#include "dlgresourceselector.h"
#include <QStandardItemModel>
#include <QHeaderView>
#include "dlgcreatepackagenamerule.h"

DlgCreateProduct::DlgCreateProduct(QWidget *parent)
	: QDialog(parent)
{
	setWindowTitle(QString::fromLocal8Bit("添加产品"));
	resize(QSize(600, 500));

	m_LBName = new QLabel();
	m_LEName = new QLineEdit();
	QHBoxLayout *nameLayout = new QHBoxLayout();
	nameLayout->addWidget(m_LBName);
	nameLayout->addWidget(m_LEName);

	// 软件包设置
	m_LBPackageName = new QLabel();
	m_LEPackageName = new QLineEdit();
	m_BtnSetPackageNameRule = new QPushButton();
	QHBoxLayout *packageNameLayout = new QHBoxLayout();
	packageNameLayout->addWidget(m_LBPackageName);
	packageNameLayout->addWidget(m_LEPackageName);
	packageNameLayout->addWidget(m_BtnSetPackageNameRule);

	m_LBScriptPath = new QLabel();
	m_LEScriptPath = new QLineEdit();
	m_BtnSetPackageScripts = new QPushButton();
	QHBoxLayout *scriptPathLayout = new QHBoxLayout();
	scriptPathLayout->addWidget(m_LBScriptPath);
	scriptPathLayout->addWidget(m_LEScriptPath);
	scriptPathLayout->addWidget(m_BtnSetPackageScripts);

	m_LBScriptBuildEntrance = new QLabel();
	m_LEScriptBuildEntrance = new QLineEdit();
	QHBoxLayout *scriptBuildEntranceLayout = new QHBoxLayout();
	scriptBuildEntranceLayout->addWidget(m_LBScriptBuildEntrance);
	scriptBuildEntranceLayout->addWidget(m_LEScriptBuildEntrance);

	QVBoxLayout *packageSettingGroupLayout = new QVBoxLayout();
	packageSettingGroupLayout->addSpacing(10);
	packageSettingGroupLayout->addLayout(packageNameLayout);
	packageSettingGroupLayout->addLayout(scriptPathLayout);
	packageSettingGroupLayout->addLayout(scriptBuildEntranceLayout);
	packageSettingGroupLayout->addSpacing(10);

	m_GBPackageSetting = new QGroupBox();
	m_GBPackageSetting->setLayout(packageSettingGroupLayout);

	// 依赖项目
	m_LBdependentItem = new QLabel();
	m_BtnAdd = new QPushButton();
	m_BtnDelete = new QPushButton();
	QHBoxLayout *layBtn = new QHBoxLayout();
	layBtn->addWidget(m_LBdependentItem);
	layBtn->addWidget(m_BtnAdd);
	layBtn->addWidget(m_BtnDelete);
	layBtn->addStretch();

	m_TV = new QTableView();
	QVBoxLayout *dependentItemLayout = new QVBoxLayout();
	dependentItemLayout->addLayout(layBtn);
	dependentItemLayout->addWidget(m_TV);

	m_BtnCreate = new QPushButton();
	m_BtnCancle = new QPushButton();
	QHBoxLayout *bottomLayout = new QHBoxLayout();
	bottomLayout->addStretch();
	bottomLayout->addWidget(m_BtnCreate);
	bottomLayout->addWidget(m_BtnCancle);

	m_MainLayout = new QVBoxLayout();
	m_MainLayout->addLayout(nameLayout);
	m_MainLayout->addSpacing(20);
	m_MainLayout->addWidget(m_GBPackageSetting);
	m_MainLayout->addSpacing(20);
	m_MainLayout->addLayout(dependentItemLayout);
	m_MainLayout->addSpacing(20);
	m_MainLayout->addLayout(bottomLayout);
	setLayout(m_MainLayout);

	// 属性设置========================================
	m_BtnSetPackageNameRule->setText(QString::fromLocal8Bit("设置"));
	m_BtnSetPackageScripts->setText(QString::fromLocal8Bit("..."));
	m_BtnSetPackageNameRule->setFixedSize(QSize(40, 25));
	m_BtnSetPackageScripts->setFixedSize(QSize(40, 25));

	m_LBdependentItem->setText(QString::fromLocal8Bit("依赖项目:"));

	m_LBName->setText(QString::fromLocal8Bit("名称:"));
	m_LEName->setPlaceholderText(QString::fromLocal8Bit("产品名称"));

	m_LBPackageName->setText(QString::fromLocal8Bit("名称规则:"));
	m_LEPackageName->setPlaceholderText(QString::fromLocal8Bit("{前缀}_{版本号}_{后缀}.exe"));

	m_LBScriptPath->setText(QString::fromLocal8Bit("生成脚本:"));
	m_LEScriptPath->setPlaceholderText(QString::fromLocal8Bit("要上传的软件包路径。"));

	m_LBScriptBuildEntrance->setText(QString::fromLocal8Bit("构建入口:"));
	m_LEScriptBuildEntrance->setPlaceholderText(QString::fromLocal8Bit("软件包中的主程序名。"));

	m_GBPackageSetting->setTitle(QString::fromLocal8Bit("软件包设置"));

	m_BtnAdd->setText(QString::fromLocal8Bit("添加"));
	m_BtnDelete->setText(QString::fromLocal8Bit("删除"));
	m_BtnAdd->setFixedSize(QSize(60, 25));
	m_BtnDelete->setFixedSize(QSize(60, 25));

	m_BtnCreate->setText(QString::fromLocal8Bit("创建"));
	m_BtnCancle->setText(QString::fromLocal8Bit("取消"));
	m_BtnCreate->setFixedSize(QSize(100, 25));
	m_BtnCancle->setFixedSize(QSize(100, 25));

	QStandardItemModel *sim = new QStandardItemModel();
	sim->setHorizontalHeaderItem(0, new QStandardItem(QString::fromLocal8Bit("名称")));
	sim->setHorizontalHeaderItem(1, new QStandardItem(QString::fromLocal8Bit("URL")));
	sim->setHorizontalHeaderItem(2, new QStandardItem(QString::fromLocal8Bit("分支名")));

	m_TV->setModel(sim);
	m_TV->setColumnWidth(0, 50);
	m_TV->setColumnWidth(1, 400);
	m_TV->setColumnWidth(2, 50);
	m_TV->setStyleSheet(QString(""));
	m_TV->setSelectionMode(QAbstractItemView::SingleSelection);
	m_TV->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_TV->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_TV->horizontalHeader()->setStretchLastSection(true);
	m_TV->verticalHeader()->setVisible(false);

	// connect========================================
	connect(m_BtnSetPackageNameRule, SIGNAL(clicked()), this, SLOT(SlotSetPackageNameRule()));
	connect(m_BtnSetPackageScripts, SIGNAL(clicked()), this, SLOT(SlotSetPackageScripts()));
}

DlgCreateProduct::~DlgCreateProduct()
{

}

void DlgCreateProduct::SlotSetPackageNameRule()
{
	DlgCreatePackageNameRule dlg(this);
	dlg.exec();
}

void DlgCreateProduct::SlotSetPackageScripts()
{

}