#ifndef DLGSELECTDEPENDS_H
#define DLGSELECTDEPENDS_H

#include <QDialog>
#include <QTableView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "Common.h"
class DlgSelectDepends : public QDialog
{
	Q_OBJECT

public:
	DlgSelectDepends(QWidget *parent = 0);
	~DlgSelectDepends();
	void RefreshData();
	static bool SelectEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

private:
	QVBoxLayout *m_MainLayout;
	QTableView *m_TV;
	QVector<Common::RepertoryItem> m_vecRTI;
};

#endif // DLGSELECTDEPENDS_H
