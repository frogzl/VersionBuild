#ifndef HOSTTAB_H
#define HOSTTAB_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>
class HostTab : public QWidget
{
	Q_OBJECT

public:
	HostTab(QWidget *parent = 0);
	~HostTab();

	void RefreshData();
	static bool DetailEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
private:
	QVBoxLayout *m_MainLayout;
	QTableView *m_TableView;
};

#endif // HOSTTAB_H
