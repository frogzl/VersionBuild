#include "dlgcreatebuildrule.h"
#include <QStandardItemModel>
#include <QHeaderView>

QJsonObject BuildRuleData::ToJsonObject()
{
	QJsonObject json;
	json["compilecmd"] = CompileCmd();
	json["compileplatform"] = CompilePlatform();
	json["autucompile"] = AutuCompile();
	json["compileoutput"] = CompileOutput();
	json["compileoutputtype"] = CompileOutputType();
	json["compileoutputdir"] = CompileOutputDir();
	json["compilelog"] = CompileLog();
	json["compilelogdir"] = CompileLogDir();
	json["deployhost"] = m_hdHost.ToJsonObject();

	QJsonArray jsonDepends;
	for (int nIndex = 0; nIndex < m_vecDepends.size(); nIndex++)
	{
	}
	json["depends"] = jsonDepends;
	return json;
}

QString BuildRuleData::ToJsonString()
{
	return QJsonDocument(ToJsonObject()).toJson(QJsonDocument::Compact);
}

DlgCreateBuildRule::DlgCreateBuildRule(QWidget *parent)
	: DlgBase(parent)
{
	QSize szMain = QSize(700, 600);
	setFixedSize(szMain);
	setObjectName(QString::fromLocal8Bit("DlgCreateResourceCompressedFile"));

	// 资源描述------------------------------------------
	// 编译设置
	m_pSTBCompileSettings = new DlgSubTitleBar();
	//   命令
	m_pDLECompileCmd = new DlgLineEdit();
	//   平台
	m_pDLECompilePlatform = new DlgLineEdit();
	//   自动编译
	m_pCBAutoCompile = new QCheckBox();
	//   输出文件名
	m_pDLECompileOutput = new DlgLineEdit(DlgLineEdit::Label| DlgLineEdit::LineEdit| DlgLineEdit::ComboBox);
	
	//   输出目录
	m_pDLECompileOutputDir = new DlgLineEdit();
	//   日志文件名
	m_pDLECompileLog = new DlgLineEdit();
	//   日志目录
	m_pDLECompileLogDir = new DlgLineEdit();
	// 选择部署位置
	m_pPBDeploy = new QPushButton();
	m_pPBDeploy->setObjectName(QString::fromLocal8Bit("BuildRuleDeploy"));
	m_pLBDeploy = new QLabel();
	m_pLBDeploy->setObjectName(QString::fromLocal8Bit("BuildRuleDeploy"));
	m_pLBDeploy->setAlignment(Qt::AlignHCenter);

	QVBoxLayout *deployLayout = new QVBoxLayout();
	deployLayout->setAlignment(Qt::AlignCenter);
	deployLayout->addWidget(m_pPBDeploy);
	deployLayout->addWidget(m_pLBDeploy);
	deployLayout->addStretch();

	// 集合所有
	QHBoxLayout *platformAutoLayout = new QHBoxLayout();
	platformAutoLayout->addWidget(m_pDLECompilePlatform);
	platformAutoLayout->addWidget(m_pCBAutoCompile);
	platformAutoLayout->setContentsMargins(0, 0, 0, 0);

	QVBoxLayout *compileSettingsContentLayout = new QVBoxLayout();
	compileSettingsContentLayout->addWidget(m_pDLECompileCmd);
	compileSettingsContentLayout->addLayout(platformAutoLayout);
	compileSettingsContentLayout->addWidget(m_pDLECompileOutput);
	compileSettingsContentLayout->addWidget(m_pDLECompileOutputDir);
	compileSettingsContentLayout->addWidget(m_pDLECompileLog);
	compileSettingsContentLayout->addWidget(m_pDLECompileLogDir);
	compileSettingsContentLayout->addLayout(deployLayout);
	compileSettingsContentLayout->setContentsMargins(10, 0, 10, 0);

	QVBoxLayout *compileSettingsLayout = new QVBoxLayout();
	compileSettingsLayout->addWidget(m_pSTBCompileSettings);
	compileSettingsLayout->addSpacing(5);
	compileSettingsLayout->addLayout(compileSettingsContentLayout);
	compileSettingsLayout->setContentsMargins(10, 0, 10, 0);
	QWidget *compileSettingsWidget = new QWidget();
	compileSettingsWidget->setLayout(compileSettingsLayout);

	// 依赖资源------------------------------------------------
	m_pSTBDepends = new DlgSubTitleBar();;
	m_pTVDepends = new QTableView();
	m_pTVDepends->setObjectName(QString::fromLocal8Bit("BuildRuleDepends"));
	QVBoxLayout *dependsContentLayout = new QVBoxLayout();
	dependsContentLayout->addWidget(m_pTVDepends);
	dependsContentLayout->setContentsMargins(10, 0, 10, 0);

	QVBoxLayout *dependsLayout = new QVBoxLayout();
	dependsLayout->addWidget(m_pSTBDepends);
	dependsLayout->addLayout(dependsContentLayout);
	QWidget *dependsWidget = new QWidget();
	dependsWidget->setLayout(dependsLayout);

	// bottom
	m_pPBCreate = new QPushButton();
	m_pPBCreate->setObjectName(QString::fromLocal8Bit("BuildRuleCreate"));
	QHBoxLayout *bottomLayout = new QHBoxLayout();
	bottomLayout->addStretch();
	bottomLayout->addWidget(m_pPBCreate);
	bottomLayout->addSpacing(5);
	bottomLayout->setContentsMargins(0, 0, 0, 10);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(compileSettingsWidget);
	mainLayout->addWidget(dependsWidget);
	mainLayout->addLayout(bottomLayout);
	MainLayout()->addLayout(mainLayout);
	MainLayout()->addStretch();

	InitData();
	InitConnect();
}

DlgCreateBuildRule::~DlgCreateBuildRule()
{

}

void DlgCreateBuildRule::InitData()
{
	m_pTitleBar->SetTitle(QString::fromLocal8Bit("创建构建规则"));
	// 编译设置
	m_pSTBCompileSettings->SetTitle(QString::fromLocal8Bit("编译设置"));
 	//   命令
	m_pDLECompileCmd->SetTitle(QString::fromLocal8Bit("命令"));
	m_pDLECompileCmd->SetPlaceholderText(QString::fromLocal8Bit("请填入编译命令"));
	//   平台
	m_pDLECompilePlatform->SetTitle(QString::fromLocal8Bit("平台"));
	m_pDLECompilePlatform->SetPlaceholderText(QString::fromLocal8Bit("平台名称，如：x86"));
	//   自动编译
	m_pCBAutoCompile->setText(QString::fromLocal8Bit("自动编译"));
	m_pCBAutoCompile->setChecked(true);
	//   输出文件名
	m_pDLECompileOutput->SetTitle(QString::fromLocal8Bit("输出文件名"));
	m_pDLECompileOutput->SetPlaceholderText(QString::fromLocal8Bit("请填入编译输出文件名"));
	QStringList list;
	list.append(QString::fromLocal8Bit("exe"));
	list.append(QString::fromLocal8Bit("zip"));
	m_pDLECompileOutput->SetList(list);
	//   输出目录
	m_pDLECompileOutputDir->SetTitle(QString::fromLocal8Bit("输出目录"));
	m_pDLECompileOutputDir->SetPlaceholderText(QString::fromLocal8Bit("请填入编译输出路径"));
	//   日志文件名
	m_pDLECompileLog->SetTitle(QString::fromLocal8Bit("日志文件名"));
	m_pDLECompileLog->SetPlaceholderText(QString::fromLocal8Bit("请填入编译输出的日志文件名"));
	//   日志目录
	m_pDLECompileLogDir->SetTitle(QString::fromLocal8Bit("日志目录"));
	m_pDLECompileLogDir->SetPlaceholderText(QString::fromLocal8Bit("请填入编译输出的日志目录"));
	// 选择部署位置
	m_pPBDeploy->setText(QString::fromLocal8Bit("选择部署位置"));
	// 依赖资源
	m_pSTBDepends->SetTitle(QString::fromLocal8Bit("依赖资源"));
	QStandardItemModel *sim = new QStandardItemModel();
	sim->setHorizontalHeaderItem(0, new QStandardItem(QIcon(":/Resources/png/appbar.add.green.png"), ""));
	sim->setHorizontalHeaderItem(1, new QStandardItem(QString::fromLocal8Bit("名称")));
	sim->setHorizontalHeaderItem(2, new QStandardItem(QString::fromLocal8Bit("类型")));
	sim->setHorizontalHeaderItem(3, new QStandardItem(QString::fromLocal8Bit("使用方式")));
	sim->setHorizontalHeaderItem(4, new QStandardItem(QString::fromLocal8Bit("描述")));


	m_pTVDepends->setModel(sim);
	m_pTVDepends->setColumnWidth(0, 70);
	m_pTVDepends->setColumnWidth(1, 200);
	m_pTVDepends->setColumnWidth(2, 80);
	m_pTVDepends->setColumnWidth(3, 80);

	m_pTVDepends->setStyleSheet(QString(""));
	m_pTVDepends->setSelectionMode(QAbstractItemView::SingleSelection);
	m_pTVDepends->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pTVDepends->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_pTVDepends->horizontalHeader()->setStretchLastSection(true);
	m_pTVDepends->verticalHeader()->setVisible(false);
	m_pTVDepends->verticalHeader()->setDefaultSectionSize(35);
	m_pTVDepends->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pTVDepends->setSelectionMode(QAbstractItemView::NoSelection);

	// bottom
	m_pPBCreate->setText(QString::fromLocal8Bit("创建"));
}

void DlgCreateBuildRule::InitConnect()
{
	connect(m_pPBDeploy, SIGNAL(clicked()), this, SLOT(SlotPBDeployClicked()));
	connect(m_pPBCreate, SIGNAL(clicked()), this, SLOT(SlotPBCreate()));
	QHeaderView *headers = m_pTVDepends->horizontalHeader();
	headers->setSectionsClickable(true);
	connect(headers, SIGNAL(sectionClicked(int)), this, SLOT(SlotAddDepends(int)));
}

void DlgCreateBuildRule::SlotPBDeployClicked()
{
	DlgSelectHost dlg(enHostType_Build, this);
	if (dlg.exec() == 1)
	{
		m_brd.SetDeployHost(dlg.Data());
		QString qsHostInfo = QString::fromLocal8Bit("%1 %2(%3)").arg(m_brd.DeployHost().HostOSName()).arg(m_brd.DeployHost().HostOSPlatform()).arg(m_brd.DeployHost().HostAddress());
		m_pLBDeploy->setText(qsHostInfo);
	}
}

void DlgCreateBuildRule::SlotAddDepends(int nIndex)
{
	if (nIndex == 0)
	{
		DlgSelectResourceSourceCode dlg(this);
		dlg.exec();
	}
}

void DlgCreateBuildRule::SlotPBCreate()
{
	//   命令
	m_brd.SetCompileCmd(m_pDLECompileCmd->Content());
	//   平台
	m_brd.SetCompilePlatform(m_pDLECompilePlatform->Content());
	//   自动编译
	m_brd.SetAutuCompile(m_pCBAutoCompile->isChecked());
	//   输出文件名
	m_brd.SetCompileOutput(m_pDLECompileOutput->Content()) ;
	if (m_pDLECompileOutput->Type().compare("exe") == 0)
		m_brd.SetCompileOutputType(0);
	if (m_pDLECompileOutput->Type().compare("zip") == 0)
		m_brd.SetCompileOutputType(1);
	//   输出目录
	m_brd.SetCompileOutputDir(m_pDLECompileOutputDir->Content());
	//   日志文件名
	m_brd.SetCompileLog(m_pDLECompileLog->Content());
	//   日志目录
	m_brd.SetCompileLogDir(m_pDLECompileLogDir->Content()) ;
	accept();
}