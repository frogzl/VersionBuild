#ifndef GITTAB_H
#define GITTAB_H
#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>
#include <QVector>
#include "Common.h"
class GitTab : public QWidget
{
	Q_OBJECT
public:
	GitTab(QWidget *parent = 0);
	~GitTab();

	void RefreshData();
	static bool DetailEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

private:
	QVBoxLayout *m_MainLayout;
	QTableView *m_TableView;
	QVector<Common::RepertoryItem> m_vecRTI;
};

#endif // GITTAB_H
