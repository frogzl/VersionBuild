#include "dlgtitlebar.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
DlgTitleBar::DlgTitleBar(QWidget *parent)
	: QFrame(parent)
{
	setObjectName(QString::fromLocal8Bit("dlgtitlebar"));

	m_pPBLogo = new QPushButton();
	m_pPBLogo->setObjectName(QString::fromLocal8Bit("logo"));

	m_pLBTitle = new QLabel();
	m_pLBTitle->setObjectName(QString::fromLocal8Bit("title"));

	m_pPBClose = new QPushButton();
	m_pPBClose->setObjectName(QString::fromLocal8Bit("close"));

	QHBoxLayout *firstLayout = new QHBoxLayout();
	firstLayout->addWidget(m_pPBLogo);
	firstLayout->addSpacing(3);
	firstLayout->addWidget(m_pLBTitle);
	firstLayout->addStretch();
	firstLayout->addWidget(m_pPBClose);
	firstLayout->setContentsMargins(0, 0, 0, 0);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addLayout(firstLayout);
	mainLayout->addStretch();
	mainLayout->setContentsMargins(5, 0, 3, 0);
	setLayout(mainLayout);

	connect(m_pPBClose, SIGNAL(clicked()), this, SLOT(SlotClose()));
}

DlgTitleBar::~DlgTitleBar()
{

}

void DlgTitleBar::SetTitle(QString qsTitle)
{
	m_pLBTitle->setText(qsTitle);
}

void DlgTitleBar::SlotClose()
{
	emit SignalClose();
}