#ifndef PRODUCTSTAB_H
#define PRODUCTSTAB_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>

class ProductsTab : public QWidget
{
	Q_OBJECT

public:
	ProductsTab(QWidget *parent = 0);
	~ProductsTab();

	void RefreshData();

	static bool ConstructionEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
	static bool DetailEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
	static bool PublishEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
	static bool DownloadEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
private:
	QVBoxLayout *m_MainLayout;
	QTableView *m_TableView;
};

#endif // PRODUCTSTAB_H
