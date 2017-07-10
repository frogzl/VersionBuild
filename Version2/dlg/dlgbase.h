#ifndef DLGBASE_H
#define DLGBASE_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPoint>
#include <QMouseEvent>
#include "dlgtitlebar.h"
class DlgBase : public QDialog
{
	Q_OBJECT

public:
	DlgBase(QWidget *parent);
	~DlgBase();
protected:
	void mouseMoveEvent(QMouseEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);

	QBoxLayout* MainLayout();
private:
	bool leftbuttonpressed;
	QPoint dragPosition;
	QVBoxLayout *m_pMainLayout;
protected:
	DlgTitleBar *m_pTitleBar;
};

#endif // DLGBASE_H
