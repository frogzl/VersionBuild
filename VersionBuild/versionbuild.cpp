#include "versionbuild.h"
#include "productstab.h"
#include "gittab.h"
#include "hosttab.h"
#include <QAction>
#include <qmenubar.h>
#include <QMenu>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include "dlgcreateproduct.h"
#include "dlgcreategit.h"
#include "dlgcreatehost.h"
#include "http.h"
#include "DB.h"
VersionBuild::VersionBuild(QWidget *parent)
	: QMainWindow(parent)
{
	resize(QSize(800, 600));
	QWidget *centerWidget = new QWidget(this);
	m_TabWidget = new QTabWidget();
	m_MainLayout = new QVBoxLayout();

	m_MainLayout->addWidget(m_TabWidget);
	
	centerWidget->setLayout(m_MainLayout);
	setCentralWidget(centerWidget);

	// 设置菜单
	QAction *createProduct = new QAction(QString::fromLocal8Bit("创建"), this);
	QAction *createGit = new QAction(QString::fromLocal8Bit("创建"), this);
	QAction *createHost = new QAction(QString::fromLocal8Bit("创建"), this);

	QMenu *menuProduct = menuBar()->addMenu(QString::fromLocal8Bit("产品"));
	menuProduct->addAction(createProduct);

	QMenu *menuGit = menuBar()->addMenu(QString::fromLocal8Bit("Git"));
	menuGit->addAction(createGit);

	QMenu *menuHost = menuBar()->addMenu(QString::fromLocal8Bit("Host"));
	menuHost->addAction(createHost);

	//
	m_TabWidget->addTab(new ProductsTab(m_TabWidget), QString::fromLocal8Bit("产品"));
	m_TabWidget->addTab(new GitTab(m_TabWidget), QString::fromLocal8Bit("Git"));
	m_TabWidget->addTab(new HostTab(m_TabWidget), QString::fromLocal8Bit("主机资源"));

	//Connect
	connect(m_TabWidget, SIGNAL(tabBarClicked(int)), this, SLOT(SlotTabBarClicked(int)));
	connect(createProduct, SIGNAL(triggered()), this, SLOT(SlotCreateProduct()));
	connect(createGit, SIGNAL(triggered()), this, SLOT(SlotCreateGit()));
	connect(createHost, SIGNAL(triggered()), this, SLOT(SlotCreateHost()));
}

VersionBuild::~VersionBuild()
{

}

void VersionBuild::SlotTabBarClicked(int nIndex)
{
	if (nIndex == 0)
	{
		ProductsTab *pW = (ProductsTab*)m_TabWidget->widget(nIndex);
		pW->RefreshData();
	}
	if (nIndex == 1)
	{
		GitTab *pW = (GitTab*)m_TabWidget->widget(nIndex);
		pW->RefreshData();
	}
}

void VersionBuild::SlotCreateProduct()
{
	DlgCreateProduct dlg(this);
	dlg.exec();
//	QUrl url(QString("http://127.0.0.1:10001/home"));
//	Http::Instance()->postRepertorys(url);
}

void VersionBuild::SlotCreateGit()
{
	DlgCreateGit dlg(this);
	dlg.exec();
}

void VersionBuild::SlotCreateHost()
{
	DlgCreateHost dlg(this);
	dlg.exec();
}