#ifndef DLGRESOURCESELECTOR_H
#define DLGRESOURCESELECTOR_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableView>
#include <QPushButton>

class DlgResourceSelector : public QDialog
{
    Q_OBJECT

public:
    DlgResourceSelector(QWidget *parent = 0);
    ~DlgResourceSelector();

private:
	QHBoxLayout *m_MainLayout;
	QTableView *m_TV;
	QPushButton *m_BtnAdd;
	QPushButton *m_BtnCancle;
	QWidget *m_RightArea;
};

#endif // DLGRESOURCESELECTOR_H
