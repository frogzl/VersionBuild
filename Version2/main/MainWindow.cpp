#include "MainWindow.h"
#include <QIcon>
#include <QDebug>
#include <QVBoxLayout>
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowFlags(Qt::FramelessWindowHint);
	setFixedSize(QSize(300, 600));
	leftbuttonpressed = false;

	m_pTrayIcon = new QSystemTrayIcon(QIcon(":/Resources/ico/logo.ico"), this);
	m_pTrayIcon->setToolTip(QString::fromLocal8Bit("Moon"));
	m_pTrayIcon->show();

	m_pCentralWidget = new CentralWidget(this);
	setCentralWidget(m_pCentralWidget);

	connect(m_pCentralWidget, SIGNAL(SignalClose()), this, SLOT(close()));
	connect(m_pTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(SlotActivated(QSystemTrayIcon::ActivationReason)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
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

void MainWindow::mousePressEvent(QMouseEvent *e)
{
	if (e->button() & Qt::LeftButton)
	{
		if (e->y() > m_pCentralWidget->GetTitleBar()->height())
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

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
	leftbuttonpressed = false;
	e->accept();
}

void MainWindow::SlotActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
		// µ¥»÷
	case QSystemTrayIcon::Trigger:
		// Ë«»÷
	case QSystemTrayIcon::DoubleClick:
		qDebug() << "DoubleClick";
		break;
		// ÓÒ¼ü
	case QSystemTrayIcon::Context:
		qDebug() << "Context";
		break;
	default:
		break;
	}
}