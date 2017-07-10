#include "dlgcreateresourcesourcecode.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QDebug>
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonDocument>
#include "../common/DB.h"
#include "../common/http.h"

QJsonObject SourceCodeData::ToJsonObject()
{
	QJsonObject json;
	json["id"] = m_qsID;
	json["name"] = m_qsName;
	json["description"] = m_qsDescription;
	json["repertoryname"] = m_qsRepertoryName;
	json["branchname"] = m_qsBranchName;
	json["createmethod"] = m_nCreateMethod;
	if (m_nCreateMethod == DlgCreateResourceSourceCode::FromExist)
		json["sourcecodeid"] = m_qsSourceCodeID;
	if (m_nCreateMethod == DlgCreateResourceSourceCode::FromLocal)
		json["localpath"] = m_qsLocalPath;
	json["versionstart"] = m_nVersionStart;

	QJsonArray jsonBuildRules;
	int nInnerid = 1;
	for (int nIndex = 0; nIndex < m_vecBuildRules.size(); nIndex++)
	{
		QJsonObject jsonBuildRule = m_vecBuildRules[nIndex].ToJsonObject();
		jsonBuildRule["innerid"] = nInnerid;
		jsonBuildRules.append(jsonBuildRule);
		nInnerid = (nInnerid << 1);
	}
	json["buildrules"] = jsonBuildRules;
	json["buildstate"] = (-1 << m_vecBuildRules.size()) ^ -1;
	json["buildstatemask"] = (-1 << m_vecBuildRules.size()) ^ -1;
	return json;
}

QString SourceCodeData::ToJsonString()
{
	return QJsonDocument(ToJsonObject()).toJson(QJsonDocument::Compact);
}

DlgCreateResourceSourceCode::DlgCreateResourceSourceCode(QWidget *parent)
	: DlgBase(parent)
{
	QSize szMain = QSize(500, 700);
	setFixedSize(szMain);
	setObjectName(QString::fromLocal8Bit("DlgCreateResourceSourceCode"));
	// ��Դ����------------------------------------------

	// ����
	m_pDLEName = new DlgLineEdit();

	// ����
	m_pDLEDescription = new DlgLineEdit();

	// �ֿ�����
	m_pDLERepertory = new DlgLineEdit();

	// ��֧����
	m_pDLEBranchName = new DlgLineEdit();

	// ѡ����λ��
	m_pPBSelectVersionControllHost = new QPushButton();
	m_pPBSelectVersionControllHost->setObjectName(QString::fromLocal8Bit("BuildRuleDeploy"));
	m_pLBSelectVersionControllHost = new QLabel();
	m_pLBSelectVersionControllHost->setObjectName(QString::fromLocal8Bit("BuildRuleDeploy"));
	m_pLBSelectVersionControllHost->setAlignment(Qt::AlignHCenter);

	QVBoxLayout *selectVersionControllHostLayout = new QVBoxLayout();
	selectVersionControllHostLayout->setAlignment(Qt::AlignCenter);
	selectVersionControllHostLayout->addWidget(m_pPBSelectVersionControllHost);
	selectVersionControllHostLayout->addWidget(m_pLBSelectVersionControllHost);
	selectVersionControllHostLayout->addStretch();

	// ��������
	QVBoxLayout *resourceDescriptionContentLayout = new QVBoxLayout();
	resourceDescriptionContentLayout->addWidget(m_pDLEName);
	resourceDescriptionContentLayout->addWidget(m_pDLEDescription);
	resourceDescriptionContentLayout->addWidget(m_pDLERepertory);
	resourceDescriptionContentLayout->addWidget(m_pDLEBranchName);
	resourceDescriptionContentLayout->addLayout(selectVersionControllHostLayout); 
	resourceDescriptionContentLayout->setContentsMargins(10, 0, 10, 0);

	m_pSTBName = new DlgSubTitleBar();
	QVBoxLayout *resourceDescriptionLayout = new QVBoxLayout();
	resourceDescriptionLayout->addWidget(m_pSTBName);
	resourceDescriptionLayout->addSpacing(5);
	resourceDescriptionLayout->addLayout(resourceDescriptionContentLayout);
	resourceDescriptionLayout->setContentsMargins(10, 0, 10, 0);
	QWidget *resourceDescriptionWidget = new QWidget();
	resourceDescriptionWidget->setLayout(resourceDescriptionLayout);

	// ������ʽ-----------------------------------------
	m_pSTBCreateMethod = new DlgSubTitleBar();
	m_pRBFromLocal = new QRadioButton();
	m_pRBFromRepertory = new QRadioButton();
	m_pRBFromExist = new QRadioButton();
	QHBoxLayout *rbLayout = new QHBoxLayout();
	rbLayout->addStretch();
	rbLayout->addWidget(m_pRBFromLocal);
	rbLayout->addSpacing(5);
	rbLayout->addWidget(m_pRBFromRepertory);
	rbLayout->addSpacing(5);
	rbLayout->addWidget(m_pRBFromExist);
	rbLayout->addStretch();

	m_pPBSelectExist = new QPushButton();
	m_pPBSelectExist->setObjectName(QString::fromLocal8Bit("SourceCodeSelectExist"));
	m_pLBSelectExist = new QLabel();
	m_pLBSelectExist->setObjectName(QString::fromLocal8Bit("SourceCodeSelectExist"));
	m_pLBSelectExist->setAlignment(Qt::AlignHCenter);

	m_pPBLocalPath = new QPushButton();
	m_pPBLocalPath->setObjectName(QString::fromLocal8Bit("SourceCodeLocalPath"));
	m_pLBLocalPath = new QLabel();
	m_pLBLocalPath->setObjectName(QString::fromLocal8Bit("SourceCodeLocalPath"));
	m_pLBLocalPath->setAlignment(Qt::AlignHCenter);
	QHBoxLayout *pbLocalPathLayout = new QHBoxLayout();
	pbLocalPathLayout->addStretch();
	pbLocalPathLayout->addWidget(m_pPBLocalPath);
	pbLocalPathLayout->addStretch();

	QVBoxLayout *selectExistLayout = new QVBoxLayout();
	selectExistLayout->setAlignment(Qt::AlignCenter);
	selectExistLayout->addWidget(m_pPBSelectExist);
	selectExistLayout->addWidget(m_pLBSelectExist);
	selectExistLayout->addStretch();
	QVBoxLayout *localPathLayout = new QVBoxLayout();
	localPathLayout->setAlignment(Qt::AlignCenter);
	localPathLayout->addLayout(pbLocalPathLayout);
	localPathLayout->addWidget(m_pLBLocalPath);

	//        fromLocal
	QWidget *fromLocalWidget = new QWidget();
	QVBoxLayout *fromLocalLayout = new QVBoxLayout();
	fromLocalLayout->addLayout(localPathLayout);
	fromLocalWidget->setLayout(fromLocalLayout);

	//        fromRepertory
	QWidget *fromRepertoryWidget = new QWidget();
	QVBoxLayout *fromRepertoryLayout = new QVBoxLayout();
	fromRepertoryWidget->setLayout(fromRepertoryLayout);

	//        fromExist
	QWidget *fromExistWidget = new QWidget();
	QVBoxLayout *fromExistLayout = new QVBoxLayout();
	fromExistLayout->addLayout(selectExistLayout);
	fromExistWidget->setLayout(fromExistLayout);

	m_pSWCreateMethod = new QStackedWidget();
	m_pSWCreateMethod->addWidget(fromLocalWidget);
	m_pSWCreateMethod->addWidget(fromRepertoryWidget);
	m_pSWCreateMethod->addWidget(fromExistWidget);
	QVBoxLayout *createMethodContentLyaout = new QVBoxLayout();
	createMethodContentLyaout->addLayout(rbLayout);
	createMethodContentLyaout->addWidget(m_pSWCreateMethod);
	createMethodContentLyaout->setContentsMargins(10, 0, 10, 0);
	QVBoxLayout *createMethodLyaout = new QVBoxLayout();
	createMethodLyaout->addWidget(m_pSTBCreateMethod);
	createMethodLyaout->addLayout(createMethodContentLyaout);
	QWidget *createMethodWidget = new QWidget();
	createMethodWidget->setLayout(createMethodLyaout);

	// �汾�Ź���
	m_pSTBVersionRule = new DlgSubTitleBar();
	m_pDLEVersionRule = new DlgLineEdit();
	QHBoxLayout *vrLayout = new QHBoxLayout();
	vrLayout->addWidget(m_pDLEVersionRule);

	m_pLBVersionRuleNote = new QLabel();
	QVBoxLayout *versionRuleContentLayout = new QVBoxLayout();
	versionRuleContentLayout->addLayout(vrLayout);
	versionRuleContentLayout->addWidget(m_pLBVersionRuleNote);
	versionRuleContentLayout->setContentsMargins(10, 0, 10, 0);
	QVBoxLayout *versionRuleLayout = new QVBoxLayout();
	versionRuleLayout->addWidget(m_pSTBVersionRule);
	versionRuleLayout->addSpacing(5);
	versionRuleLayout->addLayout(versionRuleContentLayout);
	QWidget *versionRuleWidget = new QWidget();
	versionRuleWidget->setLayout(versionRuleLayout);

	// ��������
	m_pSTBBuildRule = new DlgSubTitleBar();
	m_pTVBuildRule = new QTableView();
	m_pTVBuildRule->setObjectName(QString::fromLocal8Bit("SourceCodeBuildRule"));
	QVBoxLayout *buildRuleContentLayout = new QVBoxLayout();
	buildRuleContentLayout->addWidget(m_pTVBuildRule);
	buildRuleContentLayout->setContentsMargins(10, 0, 10, 0);

	QVBoxLayout *buildRuleLayout = new QVBoxLayout();
	buildRuleLayout->addWidget(m_pSTBBuildRule);
	buildRuleLayout->addLayout(buildRuleContentLayout);
	QWidget *buildRuleWidget = new QWidget();
	buildRuleWidget->setLayout(buildRuleLayout);

	// bottom
	m_pPBCreate = new QPushButton();
	m_pPBCreate->setObjectName(QString::fromLocal8Bit("SourceCodeCreate"));
	QHBoxLayout *bottomLayout = new QHBoxLayout();
	bottomLayout->addStretch();
	bottomLayout->addWidget(m_pPBCreate);
	bottomLayout->addSpacing(5);
	bottomLayout->setContentsMargins(0, 0, 0, 10);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(resourceDescriptionWidget);
	mainLayout->addWidget(createMethodWidget);
	mainLayout->addWidget(versionRuleWidget);
	mainLayout->addWidget(buildRuleWidget);
	mainLayout->addLayout(bottomLayout);
	MainLayout()->addLayout(mainLayout);
	InitData();
	InitConnect();
}

DlgCreateResourceSourceCode::~DlgCreateResourceSourceCode()
{

}

void DlgCreateResourceSourceCode::InitData()
{
	m_pTitleBar->SetTitle(QString::fromLocal8Bit("����Դ��"));
	// ����
	m_pSTBName->SetTitle(QString::fromLocal8Bit("��Դ����"));
	m_pDLEName->SetTitle(QString::fromLocal8Bit("��Դ����"));
	m_pDLEName->SetPlaceholderText(QString::fromLocal8Bit("��������Դ����"));
	// ����
	m_pDLEDescription->SetTitle(QString::fromLocal8Bit("��Դ����"));
	m_pDLEDescription->SetPlaceholderText(QString::fromLocal8Bit("���������Դ������"));

	// ������ʽ
	m_pSTBCreateMethod->SetTitle(QString::fromLocal8Bit("������ʽ"));
	m_pRBFromLocal->setText(QString::fromLocal8Bit("�ӱ��ش���"));
	m_pRBFromLocal->setChecked(true);
	m_pRBFromRepertory->setText(QString::fromLocal8Bit("���Ѵ��ڵĲֿⴴ��"));
	m_pRBFromExist->setText(QString::fromLocal8Bit("���Ѵ��ڵ���Դ�п�¡"));

	m_pPBSelectExist->setText(QString::fromLocal8Bit("��Դѡ��"));
	m_pPBLocalPath->setText(QString::fromLocal8Bit("ָ������Ŀ¼"));
	m_pDLERepertory->SetTitle(QString::fromLocal8Bit("�ֿ�����"));
	m_pDLERepertory->SetPlaceholderText(QString::fromLocal8Bit("������ֿ����ƣ����磺Test/master.git"));
	m_pDLEBranchName->SetTitle(QString::fromLocal8Bit("��֧����"));
	m_pDLEBranchName->SetPlaceholderText(QString::fromLocal8Bit("�������֧���ƣ����磺master"));

	m_pPBSelectVersionControllHost->setText(QString::fromLocal8Bit("ѡ����λ��"));
	// �汾�Ź���
	m_pSTBVersionRule->SetTitle(QString::fromLocal8Bit("�汾�Ź���"));
	m_pDLEVersionRule->SetTitle(QString::fromLocal8Bit("��ʼֵ"));
	m_pDLEVersionRule->SetPlaceholderText(QString::fromLocal8Bit("�汾�ŵĳ�ʼֵ"));
	m_pLBVersionRuleNote->setText(QString::fromLocal8Bit("��ע��������д������ʼ����������ÿ���Զ�������ʱ������1"));

	// ��������
	m_pSTBBuildRule->SetTitle(QString::fromLocal8Bit("��������"));
	QStandardItemModel *sim = new QStandardItemModel();
	sim->setHorizontalHeaderItem(0, new QStandardItem(QIcon(":/Resources/png/appbar.add.green.png"), ""));
	sim->setHorizontalHeaderItem(1, new QStandardItem(QString::fromLocal8Bit("ƽ̨")));
	sim->setHorizontalHeaderItem(2, new QStandardItem(QString::fromLocal8Bit("����λ��")));
	sim->setHorizontalHeaderItem(3, new QStandardItem(QString::fromLocal8Bit("������")));


	m_pTVBuildRule->setModel(sim);
	m_pTVBuildRule->setColumnWidth(0, 70);
	m_pTVBuildRule->setColumnWidth(1, 100);
	m_pTVBuildRule->setColumnWidth(2, 160);

	m_pTVBuildRule->setStyleSheet(QString(""));
	m_pTVBuildRule->setSelectionMode(QAbstractItemView::SingleSelection);
	m_pTVBuildRule->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pTVBuildRule->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_pTVBuildRule->horizontalHeader()->setStretchLastSection(true);
	m_pTVBuildRule->verticalHeader()->setVisible(false);
	m_pTVBuildRule->verticalHeader()->setDefaultSectionSize(35);
	m_pTVBuildRule->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pTVBuildRule->setSelectionMode(QAbstractItemView::NoSelection);

	// bottom
	m_pPBCreate->setText(QString::fromLocal8Bit("����"));
}

void DlgCreateResourceSourceCode::InitConnect()
{
	connect(m_pPBSelectVersionControllHost, SIGNAL(clicked()), this, SLOT(SlotPBSelectVersionControllHostClicked()));
	connect(m_pRBFromLocal, SIGNAL(clicked()), this, SLOT(SlotRBFromLocalClicked()));
	connect(m_pRBFromRepertory, SIGNAL(clicked()), this, SLOT(SlotRBFromRepertoryClicked()));
	connect(m_pRBFromExist, SIGNAL(clicked()), this, SLOT(SlotRBFromExistClicked()));
	connect(m_pPBSelectExist, SIGNAL(clicked()), this, SLOT(SlotPBSelectExistClicked()));
	connect(m_pPBLocalPath, SIGNAL(clicked()), this, SLOT(SlotPBLocalPathClicked()));
	connect(m_pPBCreate, SIGNAL(clicked()), this, SLOT(SlotPBCreateClicked()));

	QHeaderView *headers = m_pTVBuildRule->horizontalHeader();
	headers->setSectionsClickable(true);
	connect(headers, SIGNAL(sectionClicked(int)), this, SLOT(SlotAddBuildRule(int)));
}

void DlgCreateResourceSourceCode::SlotPBSelectVersionControllHostClicked()
{
	DlgSelectHost dlg(enHostType_VersionControll, this);
	if (dlg.exec() == 1)
	{
		m_scd.SetHost(dlg.Data());
		QString qsHostInfo = QString::fromLocal8Bit("%1 %2(%3)").arg(m_scd.Host().HostOSName()).arg(m_scd.Host().HostOSPlatform()).arg(m_scd.Host().HostAddress());
		m_pLBSelectVersionControllHost->setText(qsHostInfo);
	}
}

void DlgCreateResourceSourceCode::SlotRBFromLocalClicked()
{
	m_pSWCreateMethod->setCurrentIndex(0);
	m_pSWCreateMethod->setVisible(true);
}

void DlgCreateResourceSourceCode::SlotRBFromRepertoryClicked()
{
	m_pSWCreateMethod->setCurrentIndex(1);
	m_pSWCreateMethod->setVisible(false);
}

void DlgCreateResourceSourceCode::SlotRBFromExistClicked()
{
	m_pSWCreateMethod->setCurrentIndex(2);
	m_pSWCreateMethod->setVisible(true);
}

void DlgCreateResourceSourceCode::SlotAddBuildRule(int nIndex)
{
	if (nIndex == 0)
	{
		DlgCreateBuildRule dlg(this);
		if (dlg.exec())
		{
			m_scd.BuildRules().push_back(dlg.Data());
			QStandardItemModel *sim = (QStandardItemModel *)m_pTVBuildRule->model();
			int nRowCount = sim->rowCount();
			sim->setItem(nRowCount, 1, new QStandardItem(dlg.Data().CompilePlatform()));
			sim->setItem(nRowCount,2, new QStandardItem(dlg.Data().DeployHost().HostID()));
			sim->setItem(nRowCount, 3, new QStandardItem("0"));
		}
	}
}

void DlgCreateResourceSourceCode::SlotPBSelectExistClicked()
{
	DlgSelectResourceSourceCode dlg(this);
	dlg.exec();
}

void DlgCreateResourceSourceCode::SlotPBLocalPathClicked()
{
	QUrl url = QFileDialog::getExistingDirectoryUrl(this, QString::fromLocal8Bit("ѡ��Ҫ���浽�������Ĵ���·��"));
	m_pLBLocalPath->setText(url.toLocalFile());
}

void DlgCreateResourceSourceCode::SlotPBCreateClicked()
{
/*	// ����
	m_scd.SetName(m_pDLEName->Content());
	// ����
	m_scd.SetDescription(m_pDLEDescription->Content());
	// �ֿ�����
	m_scd.SetRepertoryName(m_pDLERepertory->Content());
	// ��֧����
	m_scd.SetBranchName(m_pDLEBranchName->Content());
	// ������ʽ
	if (m_pRBFromLocal->isChecked())
	{
		m_scd.SetCreateMethod((int)FromLocal);
		m_scd.SetLocalPath(m_pLBLocalPath->text());
	}
	if (m_pRBFromRepertory->isChecked())
		m_scd.SetCreateMethod((int)FromRepertory);
	if (m_pRBFromExist->isChecked())
	{
		m_scd.SetCreateMethod((int)FromExist);
		m_scd.SetSourceCodeID(m_pLBSelectExist->text());
	}

	// �汾�Ź���
	m_scd.SetVersionStart(m_pDLEVersionRule->Content().toInt());

	// �ύ������
	// 1 �����ֿ��¼
	// 2 �ֱ𴴽�BuildRule
	// 3 �ֱ���BuildRule
	DB db;
	QString qsServerAddres = db.getProtocol() + "://" + db.getServerIp() + ":" + db.getServerPort();
	QUrl url(qsServerAddres + QString::fromLocal8Bit("/sourcecode/create"));

	Http http;
	if (http.post(url, m_scd.ToJsonString()))
	{
		QString qsRespond = http.getReplyData();
		QJsonParseError error;
		QJsonDocument jsonDoc = QJsonDocument::fromJson(qsRespond.toUtf8(), &error);
		if (!jsonDoc.isNull())
		{
			QJsonObject jsonReplyData = jsonDoc.object();
			m_scd.SetID(jsonReplyData["data"].toString());
		}
	}
	else
		return;
		*/
	DB db;
	QString qsServerAddres = db.getProtocol() + "://" + db.getServerIp() + ":" + db.getServerPort();
	Http http;
	m_scd.SetID("{30025023-B184-4453-B1B8-5A88E043D48B}");
	QUrl url2(qsServerAddres + QString::fromLocal8Bit("/sourcecode/deploy"));
	if (http.post(url2, m_scd.ToJsonString()))
	{
		QString qsRespond = http.getReplyData();
		QJsonParseError error;
		QJsonDocument jsonDoc = QJsonDocument::fromJson(qsRespond.toUtf8(), &error);
		if (!jsonDoc.isNull())
		{
//			accept();
		}
	}
}