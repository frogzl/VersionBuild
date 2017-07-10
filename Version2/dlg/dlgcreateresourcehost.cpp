#include "dlgcreateresourcehost.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStandardItemModel>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include "../common/DB.h"
#include "../common/http.h"
DlgCreateResourceHost::DlgCreateResourceHost(QWidget *parent)
	: DlgBase(parent)
{
	QSize szMain = QSize(550, 260);
	setFixedSize(szMain);
	setObjectName(QString::fromLocal8Bit("DlgCreateResourceHost"));
	// 资源描述------------------------------------------
	// 名称
	m_pDLEName = new DlgLineEdit();

	// 描述
	m_pDLEDescription = new DlgLineEdit();

	// 地址
	m_pDLEAddress = new DlgLineEdit();

	// 类型
	m_pDLEType = new DlgLineEdit(DlgLineEdit::Label | DlgLineEdit::ComboBox);
	QHBoxLayout *addresstypeLayout = new QHBoxLayout();
	addresstypeLayout->addWidget(m_pDLEAddress);
	addresstypeLayout->addWidget(m_pDLEType);
	addresstypeLayout->setContentsMargins(0, 0, 0, 0);

	// 连接服务器
	m_pPBConnect = new QPushButton();
	m_pPBConnect->setObjectName(QString::fromLocal8Bit("HostConnect"));

	QVBoxLayout *connectLayout = new QVBoxLayout();
	connectLayout->setAlignment(Qt::AlignCenter);
	connectLayout->addWidget(m_pPBConnect);
	connectLayout->addStretch();

	// 集合所有
	QVBoxLayout *resourceDescriptionContentLayout = new QVBoxLayout();
	resourceDescriptionContentLayout->addWidget(m_pDLEName);
	resourceDescriptionContentLayout->addWidget(m_pDLEDescription);
	resourceDescriptionContentLayout->addLayout(addresstypeLayout);
	resourceDescriptionContentLayout->addLayout(connectLayout);
	resourceDescriptionContentLayout->setContentsMargins(10, 0, 10, 0);

	m_pSTBName = new DlgSubTitleBar();
	QVBoxLayout *resourceDescriptionLayout = new QVBoxLayout();
	resourceDescriptionLayout->addWidget(m_pSTBName);
	resourceDescriptionLayout->addSpacing(5);
	resourceDescriptionLayout->addLayout(resourceDescriptionContentLayout);
	resourceDescriptionLayout->setContentsMargins(10, 0, 10, 0);
	QWidget *resourceDescriptionWidget = new QWidget();
	resourceDescriptionWidget->setLayout(resourceDescriptionLayout);

	//主机内容
//	m_pTVContent = new QTreeView();
	m_pPTELog = new QPlainTextEdit();
	QVBoxLayout *contentContentLayout = new QVBoxLayout();
	contentContentLayout->addWidget(m_pPTELog);
	contentContentLayout->setContentsMargins(10, 0, 10, 0);

	m_pSTBContent = new DlgSubTitleBar();
	QVBoxLayout *contentLayout = new QVBoxLayout();
	contentLayout->addWidget(m_pSTBContent);
	contentLayout->addLayout(contentContentLayout);
	contentWidget = new QWidget();
	contentWidget->setVisible(false);
	contentWidget->setLayout(contentLayout);

	// bottom
	m_pPBCreate = new QPushButton();
	m_pPBCreate->setObjectName(QString::fromLocal8Bit("HostCreate"));
	QHBoxLayout *bottomLayout = new QHBoxLayout();
	bottomLayout->addStretch();
	bottomLayout->addWidget(m_pPBCreate);
	bottomLayout->addSpacing(5);
	bottomLayout->setContentsMargins(0, 0, 0, 10);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(resourceDescriptionWidget);
	mainLayout->addWidget(contentWidget);
	mainLayout->addLayout(bottomLayout);
	MainLayout()->addLayout(mainLayout);
	InitData();
	InitConnect();
}

DlgCreateResourceHost::~DlgCreateResourceHost()
{

}

void DlgCreateResourceHost::SlotPBConnectClicked()
{
	DB db;
	QString qsServerAddres = db.getProtocol() + "://" + m_pDLEAddress->Content() + ":" + db.getServerPort();
	QUrl url(qsServerAddres + QString("/host/query/physical_information"));

	Http http;
	http.get(url);
	m_qsHostInfo = http.getReplyData();

	/*	QStandardItemModel* model = new QStandardItemModel(m_pTVContent);
		model->setHorizontalHeaderLabels(QStringList() << QStringLiteral("项目") << QStringLiteral("信息"));

		QJsonParseError error;
		QJsonDocument jsonDoc = QJsonDocument::fromJson(qsReplyData.toUtf8(), &error);
		if (!jsonDoc.isNull())
		{
			QJsonObject jsonReplyData = jsonDoc.object();
			QJsonObject jsonData = jsonReplyData["data"].toObject();
			// CPU
			QJsonObject jsonCpu = jsonData["cpu"].toObject();
			QStandardItem* itemCpu = new QStandardItem(QStringLiteral("CPU"));
			model->appendRow(itemCpu);
			model->setItem(0, 1, new QStandardItem(QStringLiteral("CPU信息")));
			QStandardItem* itemCpuChild = new QStandardItem(QStringLiteral("文件夹1"));
			itemCpu->appendRow(itemCpuChild);

			// OS
			QJsonObject jsonOS = jsonData["operatingsystem"].toObject();
			QStandardItem* itemOS = new QStandardItem(QStringLiteral("操作系统"));
			model->appendRow(itemOS);
			model->setItem(1, 1, new QStandardItem(QStringLiteral("操作系统信息")));

			// Memory
			QJsonObject jsonMemory = jsonData["memory"].toObject();
			QStandardItem* itemMemory = new QStandardItem(QStringLiteral("memory"));
			model->appendRow(itemMemory);
			model->setItem(2, 1, new QStandardItem(QStringLiteral("内存信息")));
			QStandardItem* itemMemoryPhy = new QStandardItem(QStringLiteral("physicalmemory"));
			itemMemory->appendRow(itemMemoryPhy);
			model->setItem(2, 1, new QStandardItem(jsonMemory["physicalmemory"].toString()));
			QStandardItem* itemMemoryVir = new QStandardItem(QStringLiteral("virtualmemory"));
			itemMemory->appendRow(itemMemoryVir);
			model->setItem(4, 1, new QStandardItem(jsonMemory["virtualmemory"].toString()));

			// Storage
			QJsonObject jsonStorage = jsonData["storage"].toObject();
			// Env
			QJsonObject jsonEnvVar = jsonData["environmentvariable"].toObject();
		}
		m_pTVContent->setModel(model);

		*/
	m_pPTELog->appendPlainText(m_qsHostInfo);
	QSize szMain = QSize(550, 500);
	setFixedSize(szMain);
	contentWidget->setVisible(true);
}

void DlgCreateResourceHost::SlotPBCreateClicked()
{
	// 检查数据

	// 生成url
	DB db;
	QString qsServerAddres = db.getProtocol() + "://" + db.getServerIp() + ":" + db.getServerPort();
	QUrl url(qsServerAddres + QString("/host/create"));

	// 生成创建数据
	QJsonObject jsonRequest;
	jsonRequest["name"] = m_pDLEName->Content();
	jsonRequest["discription"] = m_pDLEDescription->Content();
	jsonRequest["type"] = TypeNameToCode(m_pDLEType->Type());
	jsonRequest["address"] = m_pDLEAddress->Content();
	jsonRequest["port"] = 10001;
	QJsonParseError error;
	QJsonDocument jsonDoc = QJsonDocument::fromJson(m_qsHostInfo.toUtf8(), &error);
	if (!jsonDoc.isNull())
	{
		QJsonObject jsonReplyData = jsonDoc.object();
		QJsonObject jsonData = jsonReplyData["data"].toObject();
		// CPU
		QJsonObject jsonCpu = jsonData["cpu"].toObject();
		jsonRequest["cpu"] = jsonCpu;

		// OS
		QJsonObject jsonOS = jsonData["operatingsystem"].toObject();
		jsonRequest["operatingsystem"] = jsonOS;

		// Memory
		QJsonObject jsonMemory = jsonData["memory"].toObject();
		jsonRequest["memory"] = jsonMemory;

		// Storage
		QJsonArray jsonArrayStorage = jsonData["storage"].toArray();
		QJsonObject jsonStorageTmp;
		QJsonArray jsonArrayPartitionName;
		QJsonArray jsonArrayTotalSpace;
		QJsonArray jsonArrayAvailableSpace;
		for (int nIndex = 0; nIndex < jsonArrayStorage.size(); nIndex++)
		{
			QJsonObject jsonStorageItem = jsonArrayStorage[nIndex].toObject();
			jsonArrayPartitionName.append(jsonStorageItem["name"]);
			jsonArrayTotalSpace.append(jsonStorageItem["totalnumberofbytes"]);
			jsonArrayAvailableSpace.append(jsonStorageItem["totalnumberoffreebytes"]);
		}
		jsonStorageTmp["partitionName"] = jsonArrayPartitionName;
		jsonStorageTmp["totalSpace"] = jsonArrayTotalSpace;
		jsonStorageTmp["availableSpace"] = jsonArrayAvailableSpace;

		jsonRequest["storage"] = jsonStorageTmp;
		// Env
		QJsonArray jsonEnvVar = jsonData["environmentvariable"].toArray();
		jsonRequest["environmentvariable"] = jsonEnvVar;
	}

	Http http;
	if (http.post(url, QString(QJsonDocument(jsonRequest).toJson())))
		accept();
}

void DlgCreateResourceHost::InitData()
{
	m_pTitleBar->SetTitle(QString::fromLocal8Bit("创建主机"));
	// 名称
	m_pSTBName->SetTitle(QString::fromLocal8Bit("资源描述"));
	m_pDLEName->SetTitle(QString::fromLocal8Bit("资源名称"));
	m_pDLEName->SetPlaceholderText(QString::fromLocal8Bit("请填入资源名称"));
	// 描述
	m_pDLEDescription->SetTitle(QString::fromLocal8Bit("资源描述"));
	m_pDLEDescription->SetPlaceholderText(QString::fromLocal8Bit("请填入对资源的描述"));
	// 地址
	m_pDLEAddress->SetTitle(QString::fromLocal8Bit("网络地址"));
	m_pDLEAddress->SetPlaceholderText(QString::fromLocal8Bit("请填入主机的IP地址"));
	// 类型
	m_pDLEType->SetTitle(QString::fromLocal8Bit("主机类型"));
	QStringList list;
	list.append(QString::fromLocal8Bit("存储服务器"));
	list.append(QString::fromLocal8Bit("构建服务器"));
	list.append(QString::fromLocal8Bit("数据库服务器"));
	list.append(QString::fromLocal8Bit("业务服务器"));
	list.append(QString::fromLocal8Bit("版本控制服务器"));
	list.append(QString::fromLocal8Bit("日志服务器"));
	m_pDLEType->SetList(list);
	// 连接服务器
	m_pPBConnect->setText(QString::fromLocal8Bit("连接服务器"));
	m_pSTBContent->SetTitle(QString::fromLocal8Bit("主机内容"));
	// bottom
	m_pPBCreate->setText(QString::fromLocal8Bit("创建"));
}

void DlgCreateResourceHost::InitConnect()
{
	connect(m_pPBConnect, SIGNAL(clicked()), this, SLOT(SlotPBConnectClicked()));
	connect(m_pPBCreate, SIGNAL(clicked()), this, SLOT(SlotPBCreateClicked()));
}

int DlgCreateResourceHost::TypeNameToCode(QString &qsTypeName)
{
	/*
	0x00000001 存储服务器
	0x00000002 构建服务器
	0x00000004 数据库服务器
	0x00000008 业务服务器
	0x00000010 版本控制服务器
	0x00000020 日志服务器
	*/
	if (qsTypeName.compare(QString::fromLocal8Bit("存储服务器")) == 0)
		return 0x00000001;
	if (qsTypeName.compare(QString::fromLocal8Bit("构建服务器")) == 0)
		return 0x00000002;
	if (qsTypeName.compare(QString::fromLocal8Bit("数据库服务器")) == 0)
		return 0x00000004;
	if (qsTypeName.compare(QString::fromLocal8Bit("业务服务器")) == 0)
		return 0x00000008;
	if (qsTypeName.compare(QString::fromLocal8Bit("版本控制服务器")) == 0)
		return 0x00000010;
	if (qsTypeName.compare(QString::fromLocal8Bit("日志服务器")) == 0)
		return 0x00000020;
}