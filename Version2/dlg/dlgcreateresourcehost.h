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
	// 名称
	DlgSubTitleBar *m_pSTBName;
	DlgLineEdit *m_pDLEName;
	// 描述
	DlgLineEdit *m_pDLEDescription;
	// 地址
	DlgLineEdit *m_pDLEAddress;
	// 类型
	DlgLineEdit *m_pDLEType;
	// 连接服务器
	QPushButton *m_pPBConnect;

	//主机内容
	DlgSubTitleBar *m_pSTBContent;
//	QTreeView *m_pTVContent; 暂时不用，用QPlain暂时代替
	QPlainTextEdit *m_pPTELog;
	QWidget *contentWidget;
	// bottom
	QPushButton *m_pPBCreate;

	QString m_qsHostInfo;
};

#endif // DLGCREATERESOURCEHOST_H
