#ifndef DLGCREATEPACKAGERULE_H
#define DLGCREATEPACKAGERULE_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTableView>
#include <QGroupBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class DlgCreatePackageNameRule : public QDialog
{
    Q_OBJECT

public:
	DlgCreatePackageNameRule(QWidget *parent = 0);

private slots:
	void SlotCBPrefix(bool checked);
	void SlotCBSuffix(bool checked);
	void SlotCBVersion(bool checked);
	void SlotOk();
private:
	QVBoxLayout *m_MainLayout;

	QLabel *m_LBNoteTop;
	QLabel *m_LBTest;
	QLabel *m_LBStable;
	QLabel *m_LBSignature;
	QLabel *m_LBPublish;
	QLabel *m_LBNoteBottom;

	QLineEdit *m_LEPrefix;
	QLineEdit *m_LESuffix;
	QLineEdit *m_LETest;
	QLineEdit *m_LEStable;
	QLineEdit *m_LESignature;
	QLineEdit *m_LEPublish;

	QCheckBox *m_CBPrefix;
	QCheckBox *m_CBSuffix;
	QCheckBox *m_CBVersion;

	QGroupBox *m_GBGuid;
	QGroupBox *m_GBStage;

	QRadioButton *m_RBIncreasingNumber;
	QRadioButton *m_RBDateAndSelfIncreasingNumber;
	QRadioButton *m_RBRandomNumber;

	QPushButton *m_BtnOk;
	QPushButton *m_BtnCancle;

	bool m_bAdd;
};

#endif // DLGCREATEBUILDRULE_H
