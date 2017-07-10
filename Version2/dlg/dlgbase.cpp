#include "dlgbase.h"
#include <QVBoxLayout>
DlgBase::DlgBase(QWidget *parent)
	: QDialog(parent)
{
	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

	// titlebar
	m_pTitleBar = new DlgTitleBar(this);
	m_pTitleBar->setFixedHeight(26);

	m_pMainLayout = new QVBoxLayout(this);
	m_pMainLayout->addWidget(m_pTitleBar);
	m_pMainLayout->addSpacing(15);
	m_pMainLayout->setContentsMargins(0, 0, 0, 0);
	setLayout(m_pMainLayout);

	connect(m_pTitleBar, SIGNAL(SignalClose()), this, SLOT(close()));
}

DlgBase::~DlgBase()
{

}

QBoxLayout* DlgBase::MainLayout()
{
	return m_pMainLayout;
}

void DlgBase::mouseMoveEvent(QMouseEvent *e)
{
	if (isMaximized())
	{
		e->ignore();
	}
	else
	{

		if (leftbuttonpressed)
		{
			move(e->globalPos() - dragPosition);
			e->accept();
		}
	}

}

void DlgBase::mousePressEvent(QMouseEvent *e)
{
	if (e->button() & Qt::LeftButton)
	{
		if (e->y() > m_pTitleBar->height())
		{
			leftbuttonpressed = false;
		}
		else
		{
			dragPosition = e->globalPos() - frameGeometry().topLeft();
			leftbuttonpressed = true;
		}
	}
	e->accept();
}

void DlgBase::mouseReleaseEvent(QMouseEvent *e)
{
	leftbuttonpressed = false;
	e->accept();
}
