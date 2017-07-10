#ifndef DLGCREATEPRODUCT_H
#define DLGCREATEPRODUCT_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>

class DlgCreateProduct : public QDialog
{
	Q_OBJECT

public:
	DlgCreateProduct(QWidget *parent = 0);
	~DlgCreateProduct();

private slots:
	void SlotSetPackageNameRule();
	void SlotSetPackageScripts();

private:
	QVBoxLayout *m_MainLayout;

	QLabel *m_LBName;
	QLabel *m_LBPackageName;
	QLabel *m_LBScriptPath;
	QLabel *m_LBScriptBuildEntrance;
	QLabel *m_LBdependentItem;

	QLineEdit *m_LEName;
	QLineEdit *m_LEPackageName;
	QLineEdit *m_LEScriptPath;
	QLineEdit *m_LEScriptBuildEntrance;

	QGroupBox *m_GBPackageSetting;

	QPushButton *m_BtnSetPackageNameRule;
	QPushButton *m_BtnSetPackageScripts;
	QPushButton *m_BtnAdd;
	QPushButton *m_BtnDelete;
	QPushButton *m_BtnCreate;
	QPushButton *m_BtnCancle;

	QTableView *m_TV;
};

#endif // DLGCREATEPRODUCT_H
