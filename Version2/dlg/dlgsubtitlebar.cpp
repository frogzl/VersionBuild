#include "dlgsubtitlebar.h"
#include <QHBoxLayout>
DlgSubTitleBar::DlgSubTitleBar(QWidget *parent)
	: QFrame(parent)
{
	setObjectName(QString::fromLocal8Bit("DlgSubTitleBar"));
	m_pLBTitle = new QLabel();
	m_pLBTitle->setObjectName(QString::fromLocal8Bit("DlgSubTitleBarTitle"));
	QHBoxLayout *mainLayout = new QHBoxLayout();
	mainLayout->addWidget(m_pLBTitle);
	mainLayout->addStretch();
	mainLayout->setContentsMargins(0, 0, 0, 0);
	setLayout(mainLayout);
}

DlgSubTitleBar::~DlgSubTitleBar()
{

}

void DlgSubTitleBar::SetTitle(QString qsTitle)
{
	m_pLBTitle->setText(qsTitle);
}