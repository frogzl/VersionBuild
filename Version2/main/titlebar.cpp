#include "titlebar.h"
#include <QHBoxLayout>
TitleBar::TitleBar(QWidget *parent)
	: QFrame(parent)
{
	setObjectName(QString::fromLocal8Bit("titlebar"));

	m_pPBLogo = new QPushButton();
	m_pPBLogo->setObjectName(QString::fromLocal8Bit("logo"));

	m_pLBTitle = new QLabel();
	m_pLBTitle->setObjectName(QString::fromLocal8Bit("title"));
	m_pPBClose = new QPushButton();
	m_pPBClose->setObjectName(QString::fromLocal8Bit("close"));
	QHBoxLayout *mainLayout = new QHBoxLayout();
	mainLayout->addWidget(m_pPBLogo);
	mainLayout->addSpacing(5);
	mainLayout->addWidget(m_pLBTitle);
	mainLayout->addStretch();
	mainLayout->addWidget(m_pPBClose);
	mainLayout->setContentsMargins(10, 0, 10, 0);
	setLayout(mainLayout); 

	connect(m_pPBClose, SIGNAL(clicked()), this, SLOT(SlotClose()));
}

TitleBar::~TitleBar()
{

}

void TitleBar::SetTitle(QString qsTitle)
{
	m_pLBTitle->setText(qsTitle);
}

void TitleBar::SlotClose()
{
	emit SignalClose();
}