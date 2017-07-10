#ifndef TABRESOURCE_H
#define TABRESOURCE_H

#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QListView>
class TabResource : public QWidget
{
	Q_OBJECT

public:
	TabResource(QWidget *parent = 0);
	~TabResource();
	void RefreshData();
private slots:
	void SlotTriggered(QAction *action);
private:
	void InitData();
	void InitConnect();
	QString TypeConvert(int nType);
private:
	QMenuBar *m_pMenuBar;
	QMenu *m_pMenu;
	QListView *m_pLV;
};

#endif // TABRESOURCE_H
