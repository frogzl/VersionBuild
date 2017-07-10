#include "dlgcreatehost.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "http.h"
#include "DB.h"
DlgCreateHost::DlgCreateHost(QWidget *parent): QDialog(parent)
{
	setWindowTitle(QString::fromLocal8Bit("添加主机"));
	resize(QSize(400, 500));

	m_LBHostIP = new QLabel();
	m_LEHostIP = new QLineEdit();
	QHBoxLayout *hostIPLayout = new QHBoxLayout();
	hostIPLayout->addWidget(m_LBHostIP);
	hostIPLayout->addWidget(m_LEHostIP);

	m_LBHostPort = new QLabel();
	m_LEHostPort = new QLineEdit();
	QHBoxLayout *hostPortLayout = new QHBoxLayout();
	hostPortLayout->addWidget(m_LBHostPort);
	hostPortLayout->addWidget(m_LEHostPort);

	m_LBHostType = new QLabel();
	m_CBHostType = new QComboBox();
	QHBoxLayout *hostTypeLayout = new QHBoxLayout();
	hostTypeLayout->addWidget(m_LBHostType);
	hostTypeLayout->addWidget(m_CBHostType);
	hostTypeLayout->addStretch();

	m_PBTest = new QPushButton();
	QHBoxLayout *testLayout = new QHBoxLayout();
	testLayout->addWidget(m_PBTest);
	testLayout->addStretch();

	m_PTE = new QPlainTextEdit();

	m_PBCreate = new QPushButton();
	m_PBCancel = new QPushButton();
	QHBoxLayout *bottomLayout = new QHBoxLayout();
	bottomLayout->addStretch();
	bottomLayout->addWidget(m_PBCreate);
	bottomLayout->addWidget(m_PBCancel);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addSpacing(10);
	mainLayout->addLayout(hostIPLayout);
	mainLayout->addLayout(hostPortLayout);
	mainLayout->addLayout(hostTypeLayout);
	mainLayout->addLayout(testLayout);
	mainLayout->addSpacing(10);
	mainLayout->addWidget(m_PTE);
	mainLayout->addSpacing(10);
	mainLayout->addLayout(bottomLayout);
	setLayout(mainLayout);
	
	// 属性设置========================================
	m_LBHostIP->setFixedWidth(50);
	m_LBHostIP->setText(QString::fromLocal8Bit("主机IP:"));
	m_LEHostIP->setPlaceholderText(QString::fromLocal8Bit("请输入想添加的主机IP"));

	m_LBHostPort->setFixedWidth(50);
	m_LBHostPort->setText(QString::fromLocal8Bit("主机Port:"));
	m_LEHostPort->setPlaceholderText(QString::fromLocal8Bit("请输入想添加的主机服务所使用的端口"));

	m_LBHostType->setFixedWidth(50);
	m_LBHostType->setText(QString::fromLocal8Bit("主机类型:"));
	m_CBHostType->addItem(QString::fromLocal8Bit("主控服务主机"));
	m_CBHostType->addItem(QString::fromLocal8Bit("部署服务主机"));
	m_CBHostType->addItem(QString::fromLocal8Bit("存储服务主机"));

	m_PBTest->setFixedWidth(100);
	m_PBTest->setText(QString::fromLocal8Bit("测试"));

	m_PBCreate->setFixedWidth(100);
	m_PBCreate->setText(QString::fromLocal8Bit("创建"));
	m_PBCancel->setFixedWidth(100);
	m_PBCancel->setText(QString::fromLocal8Bit("取消"));

	connect(m_PBTest, SIGNAL(clicked()), this, SLOT(SlotTest()));
}

DlgCreateHost::~DlgCreateHost()
{
}

void DlgCreateHost::SlotTest()
{
	m_PTE->clear();

	DB db;
	QString qsServerAddres = db.getProtocol() + "://" + db.getServerIp() + ":" + db.getServerPort() + "/";
	QUrl url(qsServerAddres + QString("server/resource/query"));

	Http http;
	http.get(url);
	QString qsReplyData = http.getReplyData();
	QJsonParseError error;
	QJsonDocument jsonDoc = QJsonDocument::fromJson(qsReplyData.toUtf8(), &error);
	if (!jsonDoc.isNull())
	{
		QJsonObject jsonReplyData = jsonDoc.object();
		QString qsCode = jsonReplyData["code"].toString();
		if (qsCode.compare(QString("0")) == 0)
		{
			QJsonObject arrayData = jsonReplyData["data"].toObject();

			QJsonArray arrayEnv = arrayData["environmentvariable"].toArray();
			for (int nIndexEnv = 0; nIndexEnv < arrayEnv.size(); nIndexEnv++)
			{
				QJsonObject objEnv = arrayEnv[nIndexEnv].toObject();
				m_PTE->appendPlainText(QString::fromLocal8Bit("***********%1***********").arg(objEnv["name"].toString()));
				QString sValue = objEnv["value"].toString();
				QStringList sl = sValue.split(QString(";"));
				for (int nIndexValue = 0; nIndexValue < sl.size(); nIndexValue++)
					m_PTE->appendPlainText(sl.at(nIndexValue));
			}

			QJsonArray arrayPartition = arrayData["partition"].toArray();
			for (int nIndexPartition = 0; nIndexPartition < arrayPartition.size(); nIndexPartition++)
			{
				QJsonObject objEnv = arrayPartition[nIndexPartition].toObject();
				m_PTE->appendPlainText(QString::fromLocal8Bit("***********%1***********").arg(objEnv["name"].toString()));
				QString qsFreeBytesAvailable = objEnv["freebytesavailable"].toString();
				QString qsTotalNumberOfBytes = objEnv["totalnumberofbytes"].toString();
				QString qsTotalNumberOfFreeBytes = objEnv["totalnumberoffreebytes"].toString();

				m_PTE->appendPlainText(QString::fromLocal8Bit("总空间（byte）: %1").arg(qsTotalNumberOfBytes));
				m_PTE->appendPlainText(QString::fromLocal8Bit("总空闲空间（byte）: %1").arg(qsTotalNumberOfFreeBytes));
				m_PTE->appendPlainText(QString::fromLocal8Bit("可用空闲空间（byte）: %1").arg(qsFreeBytesAvailable));
			}

		}
	}
}