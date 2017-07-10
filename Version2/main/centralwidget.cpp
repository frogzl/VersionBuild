#include "centralwidget.h"
#include <QVBoxLayout>
CentralWidget::CentralWidget(QWidget *parent)
	: QFrame(parent)
{
	setObjectName(QString::fromLocal8Bit("centralwidget"));

	// titlebar
	m_pTitleBar = new MainTitleBar(this);
	m_pTitleBar->SetTitle(QString::fromLocal8Bit("moon"));
	m_pTitleBar->setFixedHeight(70);

	// tagbar
	m_pTabResource = new TabResource();
	m_pTabApplication = new TabApplication();
	m_pTabWidget = new QTabWidget();
	m_pTabWidget->addTab(new QWidget(), QIcon(":Resources/png/appbar.tree.leaf.three.png"), QString::fromLocal8Bit("好友"));
	m_pTabWidget->addTab(m_pTabResource, QIcon(":Resources/png/appbar.tree.leaf.three.png"), QString::fromLocal8Bit("资源"));
	m_pTabWidget->addTab(m_pTabApplication, QIcon(":Resources/png/appbar.app.png"), QString::fromLocal8Bit("应用"));
	m_pTabWidget->addTab(new QWidget(), QIcon(":Resources/png/appbar.app.png"), QString::fromLocal8Bit("消息"));

	// statusbar
	m_pStatusBar = new StatusBar(this);
	m_pStatusBar->setFixedHeight(20);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(m_pTitleBar);
	mainLayout->addWidget(m_pTabWidget);
	mainLayout->addWidget(m_pStatusBar);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	setLayout(mainLayout);

	connect(m_pTitleBar, SIGNAL(SignalClose()), this, SLOT(SlotClose()));
	connect(m_pTabWidget, SIGNAL(tabBarClicked(int)), this, SLOT(SlotTabBarClicked(int)));
}

CentralWidget::~CentralWidget()
{

}

void CentralWidget::SlotClose() 
{ 
	emit SignalClose();
}

void CentralWidget::SlotTabBarClicked(int nIndex)
{
	switch (nIndex)
	{
	case 0:
		break;
	case 1:
	{
		TabResource *pTab = dynamic_cast<TabResource*>(m_pTabWidget->widget(nIndex));
		pTab->RefreshData();
	}
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}
}