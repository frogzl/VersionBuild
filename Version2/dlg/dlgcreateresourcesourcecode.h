#ifndef DLGCREATERESOURCESOURCECODE_H
#define DLGCREATERESOURCESOURCECODE_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QStackedWidget>
#include <QTableView>
#include "dlgbase.h"
#include "dlgsubtitlebar.h"
#include "dlglineedit.h"
#include "dlgcreatebuildrule.h"
#include "dlgselectresourcesourcecode.h"
#include "dlgselecthost.h"
class SourceCodeData
{
public:
	QJsonObject ToJsonObject();
	QString ToJsonString();
	QString ID() { return m_qsID; }
	QString Name() { return m_qsName; }
	QString Description() { return m_qsDescription; }
	QString RepertoryName() { return m_qsRepertoryName; }
	QString BranchName() { return m_qsBranchName; }
	HostData Host() { return m_hdHost; }
	int CreateMethod() { return m_nCreateMethod; }
	QString LocalPath() { return m_qsLocalPath; }
	QString SourceCodeID() { return m_qsSourceCodeID; }
	int VersionStart() { return m_nVersionStart; }
	QVector<BuildRuleData>& BuildRules() { return m_vecBuildRules; }

	void SetID(QString qsData) { m_qsID = qsData; }
	void SetName(QString qsData) { m_qsName = qsData; }
	void SetDescription(QString qsData) { m_qsDescription = qsData; }
	void SetRepertoryName(QString qsData) { m_qsRepertoryName = qsData; }
	void SetBranchName(QString qsData) { m_qsBranchName = qsData; }
	void SetHost(HostData hdData) { m_hdHost = hdData; }
	void SetCreateMethod(int nData) { m_nCreateMethod = nData; }
	void SetLocalPath(QString qsData) { m_qsLocalPath = qsData; }
	void SetSourceCodeID(QString qsData) { m_qsSourceCodeID = qsData; }
	void SetVersionStart(int nData) { m_nVersionStart = nData; }
private:
	QString m_qsID;
	QString m_qsName;
	QString m_qsDescription;
	QString m_qsRepertoryName;
	QString m_qsBranchName;
	HostData m_hdHost;
	int m_nCreateMethod;
	QString m_qsLocalPath;
	QString m_qsSourceCodeID;
	int m_nVersionStart;
	QVector<BuildRuleData> m_vecBuildRules;
};

class DlgCreateResourceSourceCode : public DlgBase
{
	Q_OBJECT
public:
	enum CreateMethod{
		FromLocal = 0,
		FromRepertory,
		FromExist
	};
public:
	DlgCreateResourceSourceCode(QWidget *parent = 0);
	~DlgCreateResourceSourceCode();
	SourceCodeData Data() { return m_scd; }
private slots:
	void SlotPBSelectVersionControllHostClicked();
	void SlotRBFromLocalClicked();
	void SlotRBFromRepertoryClicked();
	void SlotRBFromExistClicked();
	void SlotAddBuildRule(int nIndex);
	void SlotPBSelectExistClicked();
	void SlotPBLocalPathClicked();
	void SlotPBCreateClicked();
private:
	void InitData();
	void InitConnect();
private:
	// 名称
	DlgSubTitleBar *m_pSTBName;
	DlgLineEdit *m_pDLEName;
	// 描述
	DlgLineEdit *m_pDLEDescription;
	// 仓库名称
	DlgLineEdit *m_pDLERepertory;
	// 分支名称
	DlgLineEdit *m_pDLEBranchName;
	// 选择版本控制服务器
	QPushButton *m_pPBSelectVersionControllHost;
	QLabel *m_pLBSelectVersionControllHost;

	// 创建方式
	DlgSubTitleBar *m_pSTBCreateMethod;
	QRadioButton *m_pRBFromLocal;
	QRadioButton *m_pRBFromRepertory;
	QRadioButton *m_pRBFromExist;
	
	QStackedWidget *m_pSWCreateMethod;
	QPushButton *m_pPBSelectExist;
	QLabel *m_pLBSelectExist;
	QPushButton *m_pPBLocalPath;
	QLabel *m_pLBLocalPath;

	// 版本号规则
	DlgSubTitleBar *m_pSTBVersionRule;
	DlgLineEdit *m_pDLEVersionRule;
	QLabel *m_pLBVersionRuleNote;

	// 构建规则
	DlgSubTitleBar *m_pSTBBuildRule;
	QTableView *m_pTVBuildRule;

	// bottom
	QPushButton *m_pPBCreate;
private:
	SourceCodeData m_scd;
};

#endif // DLGCREATERESOURCESOURCECODE_H
