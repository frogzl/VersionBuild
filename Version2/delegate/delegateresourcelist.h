#ifndef DELEGATESOURCELIST_H
#define DELEGATESOURCELIST_H

#include <QItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
class DelegateResourceList : public QItemDelegate
{
	Q_OBJECT

public:
	DelegateResourceList(QObject *parent=0);
	~DelegateResourceList();
public:
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	QSize sizeHint(const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
private:
	
};

#endif // DELEGATESOURCELIST_H
