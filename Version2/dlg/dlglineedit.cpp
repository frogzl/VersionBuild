#include "dlglineedit.h"
#include <QHBoxLayout>
DlgLineEdit::DlgLineEdit(int ee, QWidget *parent)
	: QFrame(parent)
{
	setObjectName(QString::fromLocal8Bit("DlgLineEdit"));
	QHBoxLayout *mainLayout = new QHBoxLayout();
	if ((ee & Label) == Label)
	{
		m_pLBTitle = new QLabel();
		m_pLBTitle->setObjectName(QString::fromLocal8Bit("DlgLineEditTitle"));
		mainLayout->addWidget(m_pLBTitle);
	}
	if ((ee & LineEdit) == LineEdit)
	{
		m_pLEContent = new QLineEdit();
		m_pLEContent->setObjectName(QString::fromLocal8Bit("DlgLineEditContent"));
		mainLayout->addWidget(m_pLEContent);
	}
	if ((ee & ComboBox) == ComboBox)
	{
		m_pCBList = new QComboBox();
		m_pCBList->setObjectName(QString::fromLocal8Bit("DlgLineEditList"));
		mainLayout->addWidget(m_pCBList);
	}
	mainLayout->setContentsMargins(2, 2, 2, 2);

	setLayout(mainLayout);
}

DlgLineEdit::~DlgLineEdit()
{

}

void DlgLineEdit::SetTitle(QString qsTitle)
{
	m_pLBTitle->setText(qsTitle);
}

void DlgLineEdit::SetContent(QString qsContent)
{
	m_pLEContent->setText(qsContent);
}

void DlgLineEdit::SetPlaceholderText(QString qsPlaceholder)
{
	m_pLEContent->setPlaceholderText(qsPlaceholder);
}

void DlgLineEdit::SetList(QStringList qslList)
{
	m_pCBList->clear();
	int nCount = qslList.size();
	for (int nIndex = 0; nIndex < nCount; nIndex++)
	{
		m_pCBList->addItem(qslList.at(nIndex));
	}
}