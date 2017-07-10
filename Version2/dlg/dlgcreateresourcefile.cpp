#include "dlgcreateresourcefile.h"
#include <QVBoxLayout>
DlgCreateResourceFile::DlgCreateResourceFile(QWidget *parent)
	: DlgBase(parent)
{
	QSize szMain = QSize(350, 140);
	setFixedSize(szMain);
	setObjectName(QString::fromLocal8Bit("DlgCreateResourceFile"));

	MainLayout()->addStretch();

}

DlgCreateResourceFile::~DlgCreateResourceFile()
{

}

void DlgCreateResourceFile::InitData()
{
	m_pTitleBar->SetTitle(QString::fromLocal8Bit("´´½¨ÎÄµµ"));

}

void DlgCreateResourceFile::InitConnect()
{
}
