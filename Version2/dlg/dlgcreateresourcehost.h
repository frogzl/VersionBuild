#ifndef DLGCREATERESOURCEHOST_H
#define DLGCREATERESOURCEHOST_H

#include "dlgbase.h"
#include "dlgsubtitlebar.h"
#include "dlglineedit.h"
#include <QTreeView>
#include <QPlainTextEdit>
class DlgCreateResourceHost : public DlgBase
{
	Q_OBJECT

public:
	DlgCreateResourceHost(QWidget *parent = 0);
	~DlgCreateResourceHost();
private slots:
	void SlotPBConnectClicked();
	void SlotPBCreateClicked();
private:
	void InitData();
	void InitConnect();
	int TypeNameToCode(QString &qsTypeName);
private:
	// ����
	DlgSubTitleBar *m_pSTBName;
	DlgLineEdit *m_pDLEName;
	// ����
	DlgLineEdit *m_pDLEDescription;
	// ��ַ
	DlgLineEdit *m_pDLEAddress;
	// ����
	DlgLineEdit *m_pDLEType;
	// ���ӷ�����
	QPushButton *m_pPBConnect;

	//��������
	DlgSubTitleBar *m_pSTBContent;
//	QTreeView *m_pTVContent; ��ʱ���ã���QPlain��ʱ����
	QPlainTextEdit *m_pPTELog;
	QWidget *contentWidget;
	// bottom
	QPushButton *m_pPBCreate;

	QString m_qsHostInfo;
};

#endif // DLGCREATERESOURCEHOST_H
