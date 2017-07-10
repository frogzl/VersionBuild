#ifndef DLGSELECTHOST_H
#define DLGSELECTHOST_H

#include <QDialog>
#include <QPushButton>
#include <QTableView>
#include <QLabel>
class DlgSelectHost : public QDialog
{
	Q_OBJECT

public:
	DlgSelectHost(QWidget *parent = 0);
	~DlgSelectHost();
private slots:
	void SlotAdd();
	void SlotCancle();
private:
	QLabel *m_LBTitle;

	QTableView *m_TVHost;

	QPushButton *m_BtnAdd;
	QPushButton *m_BtnCancle;
};

#endif // DLGSELECTHOST_H
