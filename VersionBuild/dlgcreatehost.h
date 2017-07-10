#ifndef DLGCREATEHOST_H
#define DLGCREATEHOST_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableView>
#include <QComboBox>
#include <QPlainTextEdit>
class DlgCreateHost : public QDialog
{
	Q_OBJECT

public:
	DlgCreateHost(QWidget *parent = 0);
	~DlgCreateHost();
private slots:
	void SlotTest();
private:
	QLabel *m_LBHostIP;
	QLabel *m_LBHostPort;
	QLabel *m_LBHostType;

	QLineEdit *m_LEHostIP;
	QLineEdit *m_LEHostPort;

	QComboBox *m_CBHostType;
	
	QPlainTextEdit *m_PTE;

	QPushButton *m_PBTest;
	QPushButton *m_PBCreate;
	QPushButton *m_PBCancel;
};

#endif // DLGCREATEHOST_H
