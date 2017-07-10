#include "dlgcreateresourcecompressedfile.h"
#include <QVBoxLayout>
DlgCreateResourceCompressedFile::DlgCreateResourceCompressedFile(QWidget *parent)
	: DlgBase(parent)
{
	QSize szMain = QSize(350, 140);
	setFixedSize(szMain);
	setObjectName(QString::fromLocal8Bit("DlgCreateResourceCompressedFile"));

	QVBoxLayout *pLayout = new QVBoxLayout();
	pLayout->addWidget(new QPushButton());
	pLayout->addWidget(new QPushButton());
	MainLayout()->addLayout(pLayout);
	MainLayout()->addStretch();

}

DlgCreateResourceCompressedFile::~DlgCreateResourceCompressedFile()
{

}

void DlgCreateResourceCompressedFile::InitData()
{
	m_pTitleBar->SetTitle(QString::fromLocal8Bit("创建压缩文件"));

}

void DlgCreateResourceCompressedFile::InitConnect()
{
}
