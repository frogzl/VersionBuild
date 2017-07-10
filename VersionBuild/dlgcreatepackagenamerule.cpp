#include "dlgcreatepackagenamerule.h"
#include <QStandardItemModel>
#include <QHeaderView>
#include <QRegExp>
#include <QValidator>
#include <QFileDialog>

DlgCreatePackageNameRule::DlgCreatePackageNameRule(QWidget *parent)
	: QDialog(parent)
{
	setWindowTitle(QString::fromLocal8Bit("修改软件包名称规则"));
	resize(QSize(400, 350));

	// 变量初始化======================================
	m_LBNoteTop = new QLabel();

	// 前缀
	m_CBPrefix = new QCheckBox();
	m_LEPrefix = new QLineEdit();
	QHBoxLayout *prefixLayout = new QHBoxLayout();
	prefixLayout->addSpacing(10);
	prefixLayout->addWidget(m_LEPrefix);

	// 后缀
	m_CBSuffix = new QCheckBox();
	m_LESuffix = new QLineEdit();
	QHBoxLayout *suffixLayout = new QHBoxLayout();
	suffixLayout->addSpacing(10);
	suffixLayout->addWidget(m_LESuffix);

	// 版本号
	m_CBVersion = new QCheckBox();

	// 唯一标识
	m_RBIncreasingNumber = new QRadioButton();
	m_RBDateAndSelfIncreasingNumber = new QRadioButton();
	m_RBRandomNumber = new QRadioButton();
	QHBoxLayout *guidLayout = new QHBoxLayout();
	guidLayout->addSpacing(10);
	guidLayout->addWidget(m_RBIncreasingNumber);
	guidLayout->addWidget(m_RBDateAndSelfIncreasingNumber);
	guidLayout->addWidget(m_RBRandomNumber);
	guidLayout->addSpacing(10);

	m_GBGuid = new QGroupBox();
	m_GBGuid->setLayout(guidLayout);

	// 阶段标识
	m_LBTest = new QLabel();
	m_LETest = new QLineEdit();
	QHBoxLayout *testLayout = new QHBoxLayout();
	testLayout->addWidget(m_LBTest);
	testLayout->addWidget(m_LETest);

	m_LBStable = new QLabel();
	m_LEStable = new QLineEdit();
	QHBoxLayout *stableLayout = new QHBoxLayout();
	stableLayout->addWidget(m_LBStable);
	stableLayout->addWidget(m_LEStable);

	m_LBSignature = new QLabel();
	m_LESignature = new QLineEdit();
	QHBoxLayout *signatureLayout = new QHBoxLayout();
	signatureLayout->addWidget(m_LBSignature);
	signatureLayout->addWidget(m_LESignature);

	m_LBPublish = new QLabel();
	m_LEPublish = new QLineEdit();
	QHBoxLayout *publishLayout = new QHBoxLayout();
	publishLayout->addWidget(m_LBPublish);
	publishLayout->addWidget(m_LEPublish);

	QVBoxLayout *packageSettingGroupLayout = new QVBoxLayout();
	packageSettingGroupLayout->addSpacing(10);
	packageSettingGroupLayout->addLayout(testLayout);
	packageSettingGroupLayout->addLayout(stableLayout);
	packageSettingGroupLayout->addLayout(signatureLayout);
	packageSettingGroupLayout->addLayout(publishLayout);
	packageSettingGroupLayout->addSpacing(10);

	m_GBStage = new QGroupBox();
	m_GBStage->setLayout(packageSettingGroupLayout);

	QVBoxLayout *subversionLayout = new QVBoxLayout();
	subversionLayout->addWidget(m_GBGuid);
	subversionLayout->addWidget(m_GBStage);

	QHBoxLayout *versionLayout = new QHBoxLayout();
	versionLayout->addSpacing(10);
	versionLayout->addLayout(subversionLayout);

	m_LBNoteBottom = new QLabel();

	m_BtnOk = new QPushButton();
	m_BtnCancle = new QPushButton();
	QHBoxLayout *bottomLayout = new QHBoxLayout();
	bottomLayout->addStretch();
	bottomLayout->addWidget(m_BtnOk);
	bottomLayout->addWidget(m_BtnCancle);

	m_MainLayout = new QVBoxLayout();
	m_MainLayout->addSpacing(10);
	m_MainLayout->addWidget(m_LBNoteTop);
	m_MainLayout->addSpacing(10);
	m_MainLayout->addWidget(m_CBPrefix);
	m_MainLayout->addLayout(prefixLayout);
	m_MainLayout->addSpacing(10);
	m_MainLayout->addWidget(m_CBSuffix);
	m_MainLayout->addLayout(suffixLayout);
	m_MainLayout->addSpacing(10);
	m_MainLayout->addWidget(m_CBVersion);
	m_MainLayout->addLayout(versionLayout);
	m_MainLayout->addSpacing(10);
	m_MainLayout->addWidget(m_LBNoteBottom);
	m_MainLayout->addSpacing(10);
	m_MainLayout->addLayout(bottomLayout);
	setLayout(m_MainLayout);

	// 属性设置========================================
	m_LBNoteTop->setText(QString::fromLocal8Bit("软件包名称规则：{前缀}_{版本号}_{后缀}.exe"));
	m_CBPrefix->setText(QString::fromLocal8Bit("前缀"));
	m_CBPrefix->setChecked(true);
	m_LEPrefix->setPlaceholderText(QString::fromLocal8Bit("软件包的前缀。"));
	m_CBSuffix->setText(QString::fromLocal8Bit("后缀"));
	m_CBSuffix->setChecked(true);
	m_LESuffix->setPlaceholderText(QString::fromLocal8Bit("软件包的后缀。"));
	m_CBVersion->setText(QString::fromLocal8Bit("版本号"));
	m_CBVersion->setChecked(true);
	m_GBGuid->setTitle(QString::fromLocal8Bit("唯一标识"));
	m_RBIncreasingNumber->setText(QString::fromLocal8Bit("自增数"));
	m_RBDateAndSelfIncreasingNumber->setText(QString::fromLocal8Bit("日期+自增数"));
	m_RBDateAndSelfIncreasingNumber->setChecked(true);
	m_RBRandomNumber->setText(QString::fromLocal8Bit("随机数"));
	m_GBStage->setTitle(QString::fromLocal8Bit("阶段标识"));
	m_LBTest->setText(QString::fromLocal8Bit("测试版:"));
	m_LBStable->setText(QString::fromLocal8Bit("稳定版:"));
	m_LBSignature->setText(QString::fromLocal8Bit("签名版:"));
	m_LBPublish->setText(QString::fromLocal8Bit("发行版:"));
	m_LETest->setPlaceholderText(QString::fromLocal8Bit("测试版标记"));
	m_LEStable->setPlaceholderText(QString::fromLocal8Bit("稳定版标记"));
	m_LESignature->setPlaceholderText(QString::fromLocal8Bit("签名版标记"));
	m_LEPublish->setPlaceholderText(QString::fromLocal8Bit("发行版标记"));
	m_LBNoteBottom->setText(QString::fromLocal8Bit("预览："));
	m_BtnOk->setText(QString::fromLocal8Bit("修改"));
	m_BtnCancle->setText(QString::fromLocal8Bit("取消"));
	m_BtnOk->setFixedSize(QSize(60, 25));
	m_BtnCancle->setFixedSize(QSize(60, 25));

	// connect=========================================
	connect(m_CBPrefix, SIGNAL(clicked(bool)), this, SLOT(SlotCBPrefix(bool)));
	connect(m_CBSuffix, SIGNAL(clicked(bool)), this, SLOT(SlotCBSuffix(bool)));
	connect(m_CBVersion, SIGNAL(clicked(bool)), this, SLOT(SlotCBVersion(bool)));
	connect(m_BtnOk, SIGNAL(clicked()), this, SLOT(SlotOk()));
	connect(m_BtnCancle, SIGNAL(clicked()), this, SLOT(SlotCancle()));

}
void DlgCreatePackageNameRule::SlotCBPrefix(bool checked)
{
	if (checked)
		m_LEPrefix->setDisabled(false);
	else
		m_LEPrefix->setDisabled(true);
}

void DlgCreatePackageNameRule::SlotCBSuffix(bool checked)
{
	if (checked)
		m_LESuffix->setDisabled(false);
	else
		m_LESuffix->setDisabled(true);
}

void DlgCreatePackageNameRule::SlotCBVersion(bool checked)
{
	if (checked)
	{
		m_RBIncreasingNumber->setDisabled(false);
		m_RBDateAndSelfIncreasingNumber->setDisabled(false);
		m_RBRandomNumber->setDisabled(false);
		m_LETest->setDisabled(false);
		m_LEStable->setDisabled(false);
		m_LESignature->setDisabled(false);
		m_LEPublish->setDisabled(false);
	}
	else
	{
		m_RBIncreasingNumber->setDisabled(true);
		m_RBDateAndSelfIncreasingNumber->setDisabled(true);
		m_RBRandomNumber->setDisabled(true);
		m_LETest->setDisabled(true);
		m_LEStable->setDisabled(true);
		m_LESignature->setDisabled(true);
		m_LEPublish->setDisabled(true);
	}
}

void DlgCreatePackageNameRule::SlotOk()
{
	close();
}