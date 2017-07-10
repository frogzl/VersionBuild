#ifndef DLGCREATEBUILDRULE_H
#define DLGCREATEBUILDRULE_H

#include "dlgbase.h"
#include "dlgsubtitlebar.h"
#include "dlglineedit.h"
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QTableView>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonDocument>
#include "dlgselecthost.h"
#include "dlgselectresourcesourcecode.h"
class BuildRuleData
{
public:
	QJsonObject ToJsonObject();
	QString ToJsonString();
	QString CompileCmd() { return m_qsCompileCmd; }
	QString CompilePlatform() { return m_qsCompilePlatform; }
	bool AutuCompile() { return m_bAutuCompile; }
	QString CompileOutput() { return m_qsCompileOutput; }
	int CompileOutputType() { return m_nCompileOutputType; }
	QString CompileOutputDir() { return m_qsCompileOutputDir; }
	QString CompileLog() { return m_qsCompileLog; }
	QString CompileLogDir() { return m_qsCompileLogDir; }
	HostData DeployHost() { return m_hdHost; }

	void SetCompileCmd(QString qsData) { m_qsCompileCmd = qsData; }
	void SetCompilePlatform(QString qsData) { m_qsCompilePlatform = qsData; }
	void SetAutuCompile(bool bData) { m_bAutuCompile = bData; }
	void SetCompileOutput(QString qsData) { m_qsCompileOutput = qsData; }
	void SetCompileOutputType(int nData) { m_nCompileOutputType = nData; }
	void SetCompileOutputDir(QString qsData) { m_qsCompileOutputDir = qsData; }
	void SetCompileLog(QString qsData) { m_qsCompileLog = qsData; }
	void SetCompileLogDir(QString qsData) { m_qsCompileLogDir = qsData; }
	void SetDeployHost(HostData hdData) { m_hdHost = hdData; }
protected:
	QString m_qsCompileCmd;
	QString m_qsCompilePlatform;
	bool m_bAutuCompile;
	QString m_qsCompileOutput;
	int m_nCompileOutputType;
	QString m_qsCompileOutputDir;
	QString m_qsCompileLog;
	QString m_qsCompileLogDir;
	HostData m_hdHost;
	QVector<SelectResourceSourceCodeData> m_vecDepends;
};

class DlgCreateBuildRule : public DlgBase
{
	Q_OBJECT
		friend class BuildRuleData;
public:
	DlgCreateBuildRule(QWidget *parent = 0);
	~DlgCreateBuildRule();
	BuildRuleData Data() { return m_brd; }
private slots:
	void SlotPBDeployClicked();
	void SlotAddDepends(int);
	void SlotPBCreate();
private:
	void InitData();
	void InitConnect();
private:
	// 编译设置
	DlgSubTitleBar *m_pSTBCompileSettings;
	//   命令
	DlgLineEdit *m_pDLECompileCmd;
	//   平台
	DlgLineEdit *m_pDLECompilePlatform;
	//   自动编译
	QCheckBox *m_pCBAutoCompile;
	//   输出文件名
	DlgLineEdit *m_pDLECompileOutput;
	//   输出目录
	DlgLineEdit *m_pDLECompileOutputDir;
	//   日志文件名
	DlgLineEdit *m_pDLECompileLog;
	//   日志目录
	DlgLineEdit *m_pDLECompileLogDir;

	// 选择部署位置
	QPushButton *m_pPBDeploy;
	QLabel *m_pLBDeploy;

	// 依赖资源
	DlgSubTitleBar *m_pSTBDepends;
	QTableView *m_pTVDepends;

	// bottom
	QPushButton *m_pPBCreate;
private:
	BuildRuleData m_brd;
};

#endif // DLGCREATEBUILDRULE_H
