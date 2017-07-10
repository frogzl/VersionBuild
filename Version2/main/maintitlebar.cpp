#include "maintitlebar.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
MainTitleBar::MainTitleBar(QWidget *parent)
	: QFrame(parent)
{
	setObjectName(QString::fromLocal8Bit("titlebar"));

	m_pPBLogo = new QPushButton();
	m_pPBLogo->setObjectName(QString::fromLocal8Bit("logo"));

	m_pLBTitle = new QLabel();
	m_pLBTitle->setObjectName(QString::fromLocal8Bit("title"));

	m_pPBMinus = new QPushButton();
	m_pPBMinus->setObjectName(QString::fromLocal8Bit("minus"));

	m_pPBClose = new QPushButton();
	m_pPBClose->setObjectName(QString::fromLocal8Bit("close"));

	QHBoxLayout *firstLayout = new QHBoxLayout();
	firstLayout->addWidget(m_pPBLogo);
	firstLayout->addSpacing(3);
	firstLayout->addWidget(m_pLBTitle);
	firstLayout->addStretch();
	firstLayout->addWidget(m_pPBMinus);
	firstLayout->addWidget(m_pPBClose);
	firstLayout->setContentsMargins(0, 0, 0, 0);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addLayout(firstLayout);
	mainLayout->addStretch();
	mainLayout->setContentsMargins(5, 0, 3, 0);
	setLayout(mainLayout); 

	connect(m_pPBClose, SIGNAL(clicked()), this, SLOT(SlotClose()));
}

MainTitleBar::~MainTitleBar()
{

}

void MainTitleBar::SetTitle(QString qsTitle)
{
	m_pLBTitle->setText(qsTitle);
}

void MainTitleBar::SlotClose()
{
	emit SignalClose();
}