#ifndef VERSION2_H
#define VERSION2_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMouseEvent>
#include <QPoint>
#include "centralwidget.h"
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
protected:
	void mouseMoveEvent(QMouseEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
private slots:
	void SlotActivated(QSystemTrayIcon::ActivationReason);
private:
	bool leftbuttonpressed;
	QPoint dragPosition;
	QSystemTrayIcon *m_pTrayIcon;
	CentralWidget *m_pCentralWidget;
};

#endif // VERSION2_H
