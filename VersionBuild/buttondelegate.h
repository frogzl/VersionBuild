#ifndef BUTTONDELEGATE_H
#define BUTTONDELEGATE_H

#include <QItemDelegate>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QStyleOptionButton>
#include <QPainter>
#include <QPair>
#include <QMap>
#include <QList>

typedef bool (*FunEditorEvent)(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
typedef QPair<QStyleOptionButton*, FunEditorEvent> BtnPair;
typedef QPair<QString, FunEditorEvent> DataPair;

typedef QList<BtnPair* > BtnList;
typedef QList<DataPair* > CollData;
typedef QMap<QModelIndex, BtnList* > CollButtons;

class ButtonDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	ButtonDelegate(QObject *parent = 0);
	~ButtonDelegate();
public:
	void setData(CollData &data);
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

signals:
public slots:

private:
	void showMsg(QString str);

private:

	CollData m_Datas;
	CollButtons m_Buttons;
};

#endif // BUTTONDELEGATE_H
