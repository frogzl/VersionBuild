#include "dlgcreategit.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QUuid>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include "dlgcreatebuildrule.h"
#include "dlgselecthost.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "Common.h"
#include "DB.h"
#include "http.h"
DlgCreateGit::DlgCreateGit(QWidget *parent)
	: QDialog(parent)
{
	setWindowTitle(QString::fromLocal8Bit("添加Git仓库"));
	resize(QSize(300, 600));

	// 变量初始化
	m_LBName = new QLabel();
	m_LEName = new QLineEdit();
	QHBoxLayout *ruleNameLayout = new QHBoxLayout();
	ruleNameLayout->addWidget(m_LBName);
	ruleNameLayout->addSpacing(10);
	ruleNameLayout->addWidget(m_LEName);

	m_LBRepertoryPath = new QLabel();
	m_LERepertoryPath = new QLineEdit();
	QHBoxLayout *repertoryPathLayout = new QHBoxLayout();
	repertoryPathLayout->addWidget(m_LBRepertoryPath);
	repertoryPathLayout->addSpacing(10);
	repertoryPathLayout->addWidget(m_LERepertoryPath);

	m_LBBranchName = new QLabel();
	m_LEBranchName = new QLineEdit();
	QHBoxLayout *branchNameLayout = new QHBoxLayout();
	branchNameLayout->addWidget(m_LBBranchName);
	branchNameLayout->addSpacing(10);
	branchNameLayout->addWidget(m_LEBranchName);

	m_LBLocation = new QLabel();
	m_LELocation = new QLineEdit();
	m_BtnLocationSel = new QPushButton();
	QHBoxLayout *locationLayout = new QHBoxLayout();
	locationLayout->addWidget(m_LBLocation);
	locationLayout->addSpacing(10);
	locationLayout->addWidget(m_LELocation);
	locationLayout->addWidget(m_BtnLocationSel);

	m_BtnAdd = new QPushButton();
	m_BtnCancle = new QPushButton();
	QHBoxLayout *bottomLayout = new QHBoxLayout();
	bottomLayout->addStretch();
	bottomLayout->addWidget(m_BtnAdd);
	bottomLayout->addWidget(m_BtnCancle);



	//Version group
	m_LBVersionStartNum = new QLabel();
	m_LEVersionStartNum = new QLineEdit();
	QHBoxLayout *versionPatternLayout = new QHBoxLayout();
	versionPatternLayout->addWidget(m_LBVersionStartNum);
	versionPatternLayout->addWidget(m_LEVersionStartNum);
	versionPatternLayout->addStretch();

	m_LBVersionNote = new QLabel();

	QVBoxLayout *versionGroupLayout = new QVBoxLayout();
	versionGroupLayout->addLayout(versionPatternLayout);
	versionGroupLayout->addWidget(m_LBVersionNote);

	m_GBVersion = new QGroupBox();
	m_GBVersion->setLayout(versionGroupLayout);

	// Build group
	m_BtnAddBuildRule = new QPushButton();
	m_BtnDeleteBuildRule = new QPushButton();
	QHBoxLayout *buildRuleLayout = new QHBoxLayout();
	buildRuleLayout->addWidget(m_BtnAddBuildRule);
	buildRuleLayout->addWidget(m_BtnDeleteBuildRule);
	buildRuleLayout->addStretch();

	m_TVBuildRule = new QTableView();

	QVBoxLayout *buildGroupLayout = new QVBoxLayout();
	buildGroupLayout->addLayout(buildRuleLayout);
	buildGroupLayout->addWidget(m_TVBuildRule);

	m_GBBuild = new QGroupBox();
	m_GBBuild->setLayout(buildGroupLayout);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addLayout(ruleNameLayout);
	mainLayout->addSpacing(10);
	mainLayout->addLayout(repertoryPathLayout);
	mainLayout->addSpacing(10);
	mainLayout->addLayout(branchNameLayout);
	mainLayout->addSpacing(10);
	mainLayout->addLayout(locationLayout);
	mainLayout->addSpacing(20);
	mainLayout->addWidget(m_GBVersion);
	mainLayout->addSpacing(20);
	mainLayout->addWidget(m_GBBuild);
	mainLayout->addLayout(bottomLayout);
	setLayout(mainLayout);

	// 属性设置========================================
	m_BtnLocationSel->setFixedWidth(40);
	m_BtnAddBuildRule->setFixedSize(QSize(60, 25));
	m_BtnDeleteBuildRule->setFixedSize(QSize(60, 25));
	m_BtnAdd->setFixedSize(QSize(100, 25));
	m_BtnCancle->setFixedSize(QSize(100, 25));

	m_LEVersionStartNum->setFixedSize(QSize(380, 25));
	m_LBVersionNote->setFixedSize(QSize(420, 50));
	m_LBVersionNote->setWordWrap(true);

	m_LBName->setFixedSize(QSize(50, 25));
	m_LBRepertoryPath->setFixedSize(QSize(50, 25));
	m_LBBranchName->setFixedSize(QSize(50, 25));
	m_LBLocation->setFixedSize(QSize(50, 25));

	QStandardItemModel *sim = new QStandardItemModel();
	sim->setHorizontalHeaderItem(0, new QStandardItem(QString::fromLocal8Bit("平台")));
	sim->setHorizontalHeaderItem(1, new QStandardItem(QString::fromLocal8Bit("输出路径")));
	sim->setHorizontalHeaderItem(2, new QStandardItem(QString::fromLocal8Bit("文件名")));
	sim->setHorizontalHeaderItem(3, new QStandardItem(QString::fromLocal8Bit("脚本路径")));

	m_TVBuildRule->setModel(sim);
	m_TVBuildRule->setColumnWidth(0, 80);
	m_TVBuildRule->setColumnWidth(1, 80);
	m_TVBuildRule->setColumnWidth(2, 80);
	m_TVBuildRule->setColumnWidth(3, 50);
	m_TVBuildRule->setStyleSheet(QString(""));
	m_TVBuildRule->setSelectionMode(QAbstractItemView::SingleSelection);
	m_TVBuildRule->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_TVBuildRule->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_TVBuildRule->horizontalHeader()->setStretchLastSection(true);
	m_TVBuildRule->verticalHeader()->setVisible(false);

	// 数据设置========================================
	m_LBName->setText(QString::fromLocal8Bit("名    称"));
	m_LBRepertoryPath->setText(QString::fromLocal8Bit("仓库路径"));
	m_LBBranchName->setText(QString::fromLocal8Bit("分支名称"));
	m_LBLocation->setText(QString::fromLocal8Bit("部署位置"));

	m_LEName->setPlaceholderText(QString::fromLocal8Bit("本仓库的自定义名称"));
	m_LERepertoryPath->setPlaceholderText(QString::fromLocal8Bit("填写https路径"));
	m_LEBranchName->setPlaceholderText(QString::fromLocal8Bit("填写分支名称"));
	m_LELocation->setPlaceholderText(QString::fromLocal8Bit("请选择要部署的位置"));

	m_LBVersionStartNum->setText(QString::fromLocal8Bit("初始值"));
	m_LEVersionStartNum->setPlaceholderText(QString::fromLocal8Bit("版本号的初始值"));
	QRegExp regx("[0-9]+$");
	m_LEVersionStartNum->setValidator(new QRegExpValidator(regx));
	m_LBVersionNote->setText(QString::fromLocal8Bit("备注：可以填写任意起始整数，会在每次自动构建的时候自增1，"));

	m_GBVersion->setTitle(QString::fromLocal8Bit("版本号规则"));
	m_GBBuild->setTitle(QString::fromLocal8Bit("构建规则"));

	m_BtnLocationSel->setText(QString::fromLocal8Bit("选择"));
	m_BtnAddBuildRule->setText(QString::fromLocal8Bit("添加"));
	m_BtnDeleteBuildRule->setText(QString::fromLocal8Bit("删除"));
	m_BtnAdd->setText(QString::fromLocal8Bit("添加"));
	m_BtnCancle->setText(QString::fromLocal8Bit("取消"));

	// connect========================================
	connect(m_BtnAddBuildRule, SIGNAL(clicked()), this, SLOT(SlotAddBuildRule()));
	connect(m_BtnLocationSel, SIGNAL(clicked()), this, SLOT(SlotLocationSel()));
	connect(m_BtnDeleteBuildRule, SIGNAL(clicked()), this, SLOT(SlotDeleteBuildRule()));
	connect(m_BtnAdd, SIGNAL(clicked()), this, SLOT(SlotAdd()));
	connect(m_BtnCancle, SIGNAL(clicked()), this, SLOT(SlotCancle()));
}

DlgCreateGit::~DlgCreateGit()
{

}

void DlgCreateGit::SlotLocationSel()
{
	DlgSelectHost dlg(this);
	dlg.exec();
}

void DlgCreateGit::SlotAddBuildRule()
{
	DlgCreateBuildRule dlg(this);
	dlg.exec();
	if (dlg.IsAdd())
	{
		QStandardItemModel *sim = (QStandardItemModel *)m_TVBuildRule->model();
		int nIndex = sim->rowCount();
		sim->setItem(nIndex, 0, new QStandardItem(dlg.GetPlatform()));
		sim->setItem(nIndex, 1, new QStandardItem(dlg.GetOutput()));
		sim->setItem(nIndex, 2, new QStandardItem(dlg.GetTarget()));
		sim->setItem(nIndex, 3, new QStandardItem(dlg.GetScript()));
	}
}

void DlgCreateGit::SlotDeleteBuildRule()
{
	QStandardItemModel *sim = (QStandardItemModel *)m_TVBuildRule->model();
	sim->removeRow(m_TVBuildRule->currentIndex().row());
}

void DlgCreateGit::SlotAdd()
{
	// 获取初始值
	DB db;
	QString qsServerAddres = db.getProtocol() + "://" + db.getServerIp() + ":" + db.getServerPort() + "/";
	QString qsName = m_LEName->text();
	QString qsRepertoryPath = m_LERepertoryPath->text();
	QString qsBranchName = m_LEBranchName->text();
	int nVersionStartNum = m_LEVersionStartNum->text().toInt();
	QString qsGuid = QUuid::createUuid().toString();
	
	QJsonObject root;
	root["name"] = (qsName);
	root["url"] = Common::unicode_utf8(qsRepertoryPath);
	root["branchname"] = Common::unicode_utf8(qsBranchName);
	root["versionstart"] = nVersionStartNum;
	// 获取build rule数据
	QStandardItemModel *sim = (QStandardItemModel *)m_TVBuildRule->model();
	int nRowCnt = sim->rowCount();
	QJsonArray buildrules;
	for (int nIndex = 0; nIndex < nRowCnt; nIndex++)
	{
		QString qsPlatform = sim->data(sim->index(nIndex, 0)).toString();
		QString qsOutput = sim->data(sim->index(nIndex, 1)).toString();
		QString qsTarget = sim->data(sim->index(nIndex, 2)).toString();
		QString qsScript = sim->data(sim->index(nIndex, 3)).toString();
		QString qsScriptName = QUuid::createUuid().toString();

		// 上传脚本文件，并获取其id
		QUrl url(qsServerAddres + QString("file/upload"));
		Http http;
		http.uploadFile(url, qsScript);
		QJsonDocument jsonDoc = QJsonDocument::fromJson(http.getReplyData());
		if (jsonDoc.isNull())
		{
			QString qsMessage = QString::fromLocal8Bit("上传(%1)构件脚本时出现错误 ").arg(qsScript);
			QMessageBox::information(NULL, QString::fromLocal8Bit("错误"), qsMessage);
			return;
		}
		QJsonObject jsonRespond = jsonDoc.object();
		QString qsStorageID = jsonRespond["storageid"].toString();

		QJsonObject buildrule;
		buildrule["platform"] = Common::unicode_utf8(qsPlatform);
		buildrule["outputpath"] = Common::unicode_utf8(qsOutput);
		buildrule["targetfile"] = Common::unicode_utf8(qsTarget);
		buildrule["storageid "] = Common::unicode_utf8(qsStorageID);
		buildrules.insert(nIndex, buildrule);
	}
	root["buildrules"] = buildrules;

	QUrl url(qsServerAddres + QString("repertory/create"));
	Http http;
	if (http.post(url, QString(QJsonDocument(root).toJson())))
		close();
}

void DlgCreateGit::SlotCancle()
{
	close();
}