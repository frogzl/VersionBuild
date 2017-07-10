#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QFrame>
#include <QWidget>
#include <QToolButton>
#include <QTabWidget>
#include "maintitlebar.h"
#include "statusbar.h"
#include "tab\tabresource.h"
#include "tab\tabapplication.h"
class CentralWidget : public QFrame
{
	Q_OBJECT

public:
	CentralWidget(QWidget *parent = 0);
	~CentralWidget();

	MainTitleBar* GetTitleBar() { return m_pTitleBar; }
signals:
	void SignalClose();
private slots:
	void SlotClose();
	void SlotTabBarClicked(int nIndex);
private:
	MainTitleBar *m_pTitleBar;
	TabResource *m_pTabResource;
	TabApplication *m_pTabApplication;
	QTabWidget *m_pTabWidget;
	StatusBar *m_pStatusBar;
};

#endif // CENTRALWIDGET_H
