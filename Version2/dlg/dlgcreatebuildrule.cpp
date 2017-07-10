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

	// ��Դ����------------------------------------------
	// ��������
	m_pSTBCompileSettings = new DlgSubTitleBar();
	//   ����
	m_pDLECompileCmd = new DlgLineEdit();
	//   ƽ̨
	m_pDLECompilePlatform = new DlgLineEdit();
	//   �Զ�����
	m_pCBAutoCompile = new QCheckBox();
	//   ����ļ���
	m_pDLECompileOutput = new DlgLineEdit(DlgLineEdit::Label| DlgLineEdit::LineEdit| DlgLineEdit::ComboBox);
	
	//   ���Ŀ¼
	m_pDLECompileOutputDir = new DlgLineEdit();
	//   ��־�ļ���
	m_pDLECompileLog = new DlgLineEdit();
	//   ��־Ŀ¼
	m_pDLECompileLogDir = new DlgLineEdit();
	// ѡ����λ��
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

	// ��������
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

	// ������Դ------------------------------------------------
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
	m_pTitleBar->SetTitle(QString::fromLocal8Bit("������������"));
	// ��������
	m_pSTBCompileSettings->SetTitle(QString::fromLocal8Bit("��������"));
 	//   ����
	m_pDLECompileCmd->SetTitle(QString::fromLocal8Bit("����"));
	m_pDLECompileCmd->SetPlaceholderText(QString::fromLocal8Bit("�������������"));
	//   ƽ̨
	m_pDLECompilePlatform->SetTitle(QString::fromLocal8Bit("ƽ̨"));
	m_pDLECompilePlatform->SetPlaceholderText(QString::fromLocal8Bit("ƽ̨���ƣ��磺x86"));
	//   �Զ�����
	m_pCBAutoCompile->setText(QString::fromLocal8Bit("�Զ�����"));
	m_pCBAutoCompile->setChecked(true);
	//   ����ļ���
	m_pDLECompileOutput->SetTitle(QString::fromLocal8Bit("����ļ���"));
	m_pDLECompileOutput->SetPlaceholderText(QString::fromLocal8Bit("�������������ļ���"));
	QStringList list;
	list.append(QString::fromLocal8Bit("exe"));
	list.append(QString::fromLocal8Bit("zip"));
	m_pDLECompileOutput->SetList(list);
	//   ���Ŀ¼
	m_pDLECompileOutputDir->SetTitle(QString::fromLocal8Bit("���Ŀ¼"));
	m_pDLECompileOutputDir->SetPlaceholderText(QString::fromLocal8Bit("������������·��"));
	//   ��־�ļ���
	m_pDLECompileLog->SetTitle(QString::fromLocal8Bit("��־�ļ���"));
	m_pDLECompileLog->SetPlaceholderText(QString::fromLocal8Bit("����������������־�ļ���"));
	//   ��־Ŀ¼
	m_pDLECompileLogDir->SetTitle(QString::fromLocal8Bit("��־Ŀ¼"));
	m_pDLECompileLogDir->SetPlaceholderText(QString::fromLocal8Bit("����������������־Ŀ¼"));
	// ѡ����λ��
	m_pPBDeploy->setText(QString::fromLocal8Bit("ѡ����λ��"));
	// ������Դ
	m_pSTBDepends->SetTitle(QString::fromLocal8Bit("������Դ"));
	QStandardItemModel *sim = new QStandardItemModel();
	sim->setHorizontalHeaderItem(0, new QStandardItem(QIcon(":/Resources/png/appbar.add.green.png"), ""));
	sim->setHorizontalHeaderItem(1, new QStandardItem(QString::fromLocal8Bit("����")));
	sim->setHorizontalHeaderItem(2, new QStandardItem(QString::fromLocal8Bit("����")));
	sim->setHorizontalHeaderItem(3, new QStandardItem(QString::fromLocal8Bit("ʹ�÷�ʽ")));
	sim->setHorizontalHeaderItem(4, new QStandardItem(QString::fromLocal8Bit("����")));


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
	m_pPBCreate->setText(QString::fromLocal8Bit("����"));
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
	//   ����
	m_brd.SetCompileCmd(m_pDLECompileCmd->Content());
	//   ƽ̨
	m_brd.SetCompilePlatform(m_pDLECompilePlatform->Content());
	//   �Զ�����
	m_brd.SetAutuCompile(m_pCBAutoCompile->isChecked());
	//   ����ļ���
	m_brd.SetCompileOutput(m_pDLECompileOutput->Content()) ;
	if (m_pDLECompileOutput->Type().compare("exe") == 0)
		m_brd.SetCompileOutputType(0);
	if (m_pDLECompileOutput->Type().compare("zip") == 0)
		m_brd.SetCompileOutputType(1);
	//   ���Ŀ¼
	m_brd.SetCompileOutputDir(m_pDLECompileOutputDir->Content());
	//   ��־�ļ���
	m_brd.SetCompileLog(m_pDLECompileLog->Content());
	//   ��־Ŀ¼
	m_brd.SetCompileLogDir(m_pDLECompileLogDir->Content()) ;
	accept();
}