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
	// ��������
	DlgSubTitleBar *m_pSTBCompileSettings;
	//   ����
	DlgLineEdit *m_pDLECompileCmd;
	//   ƽ̨
	DlgLineEdit *m_pDLECompilePlatform;
	//   �Զ�����
	QCheckBox *m_pCBAutoCompile;
	//   ����ļ���
	DlgLineEdit *m_pDLECompileOutput;
	//   ���Ŀ¼
	DlgLineEdit *m_pDLECompileOutputDir;
	//   ��־�ļ���
	DlgLineEdit *m_pDLECompileLog;
	//   ��־Ŀ¼
	DlgLineEdit *m_pDLECompileLogDir;

	// ѡ����λ��
	QPushButton *m_pPBDeploy;
	QLabel *m_pLBDeploy;

	// ������Դ
	DlgSubTitleBar *m_pSTBDepends;
	QTableView *m_pTVDepends;

	// bottom
	QPushButton *m_pPBCreate;
private:
	BuildRuleData m_brd;
};

#endif // DLGCREATEBUILDRULE_H
