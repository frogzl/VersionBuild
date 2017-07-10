#ifndef DLGCREATEGIT_H
#define DLGCREATEGIT_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QTableView>

class DlgCreateGit : public QDialog
{
	Q_OBJECT

public:
	DlgCreateGit(QWidget *parent = 0);
	~DlgCreateGit();

private slots:
	void SlotLocationSel();
	void SlotAddBuildRule();
	void SlotDeleteBuildRule();
	void SlotAdd();
	void SlotCancle();

private:
	QLabel *m_LBName;
	QLabel *m_LBRepertoryPath;
	QLabel *m_LBBranchName;
	QLabel *m_LBLocation;
	QLabel *m_LBVersionStartNum;
	QLabel *m_LBVersionNote;

	QLineEdit *m_LEName;
	QLineEdit *m_LERepertoryPath;
	QLineEdit *m_LEBranchName;
	QLineEdit *m_LELocation;
	QLineEdit *m_LEVersionStartNum;

	QTableView *m_TVBuildRule;
	QGroupBox *m_GBVersion;
	QGroupBox *m_GBBuild;

	QPushButton *m_BtnLocationSel;
	QPushButton *m_BtnAddBuildRule;
	QPushButton *m_BtnDeleteBuildRule;
	QPushButton *m_BtnAdd;
	QPushButton *m_BtnCancle;
};

#endif // DLGCREATEGIT_H
