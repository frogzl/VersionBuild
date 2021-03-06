﻿#ifndef DLGCREATEBUILDRULE_H
#define DLGCREATEBUILDRULE_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTableView>
#include <QGroupBox>

class DlgCreateBuildRule : public QDialog
{
    Q_OBJECT

public:
	DlgCreateBuildRule(QWidget *parent = 0);
	~DlgCreateBuildRule();

	bool IsAdd();
	QString GetPlatform();
	QString GetScript();
	QString GetOutput();
	QString GetTarget();

private slots:
	void SlotDependsAdd();
	void SlotSelector();
	void SlotAdd();
	void SlotCancle();
private:
	QLabel *m_LBBuildPlatform;
	QLabel *m_LBBuildScript;
	QLabel *m_LBBuildOutput;
	QLabel *m_LBBuildTarget;
	QLabel *m_LBBuildNote;

	QLineEdit *m_LEBuildPlatform;
	QLineEdit *m_LEBuildScript;
	QLineEdit *m_LEBuildOutput;
	QLineEdit *m_LEBuildTarget;

	QTableView *m_TVDepends;

	QGroupBox *m_GBDepends;

	QPushButton *m_BtnDependsAdd;
	QPushButton *m_BtnDependsDelete;
	QPushButton *m_BtnSelector;
	QPushButton *m_BtnAdd;
	QPushButton *m_BtnCancle;

	bool m_bAdd;
};

#endif // DLGCREATEBUILDRULE_H
