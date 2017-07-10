#include "buttondelegate.h"
#include <QApplication>
#include <QMouseEvent>
#include <QMessageBox>
#include <QListIterator>

ButtonDelegate::ButtonDelegate(QObject *parent)
	: QItemDelegate(parent)
{

}

ButtonDelegate::~ButtonDelegate()
{

}

void ButtonDelegate::setData(CollData &data)
{
	m_Datas = data;
}

void ButtonDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	BtnList* buttons = m_Buttons.value(index);
	if (!buttons)
	{
		buttons = new BtnList();
		QListIterator<DataPair*> i(m_Datas);
		while (i.hasNext())
		{
			DataPair* dp = i.next();
			QStyleOptionButton *styleOptBtn = new QStyleOptionButton();
			styleOptBtn->text = dp->first;
			styleOptBtn->state |= QStyle::State_Enabled;
			BtnPair *bp = new BtnPair(styleOptBtn, dp->second);
			buttons->append(bp);
		}
		(const_cast<ButtonDelegate*>(this))->m_Buttons.insert(index, buttons);
	}

	BtnList::iterator it;
	int nIndex = 0;
	int nSize = buttons->size();
//	int nWidth = (option.rect.width() - (nSize + 1) * 4) / nSize;
	int nWidth = 50;

	int nXp1, nXp2;
	for (it = buttons->begin(); it != buttons->end(); it++, nIndex++)
	{
		nXp1 = 4 + (4 + nWidth) * nIndex;
//		nXp2 = 4 + (4 + nWidth) * (nSize - nIndex - 1);
		nXp2 = option.rect.width() - (nXp1 + nWidth);
		(*it)->first->rect = option.rect.adjusted(nXp1, 4, -nXp2, -4);
	}
	painter->save();

	if (option.state & QStyle::State_Selected)
	{
		painter->fillRect(option.rect, option.palette.highlight());
	}
	painter->restore();

	for (it = buttons->begin(); it != buttons->end(); it++)
	{
		QApplication::style()->drawControl(QStyle::CE_PushButton, (*it)->first, painter);
	}
		//=======================================
/*		QStyleOptionButton *firstBtn = new QStyleOptionButton();
		QStyleOptionButton *secondBtn = new QStyleOptionButton();

		firstBtn->text = QString::fromLocal8Bit("构建");
		firstBtn->state |= QStyle::State_Enabled;
		secondBtn->text = QString::fromLocal8Bit("详情");
		secondBtn->state |= QStyle::State_Enabled;

		buttons = new QPair<QStyleOptionButton*, QStyleOptionButton*>(firstBtn, secondBtn);
		(const_cast<ButtonDelegate*>(this))->m_Buttons.insert(index, buttons);
		
	}

	buttons->first->rect = option.rect.adjusted(4, 4, -(option.rect.width() / 2 + 4), -4);
	buttons->second->rect = option.rect.adjusted(buttons->first->rect.width() + 4, 4, -4, -4);
	painter->save();

	if (option.state & QStyle::State_Selected)
	{
		painter->fillRect(option.rect, option.palette.highlight());
	}
	painter->restore();
	QApplication::style()->drawControl(QStyle::CE_PushButton, buttons->first, painter);
	QApplication::style()->drawControl(QStyle::CE_PushButton, buttons->second, painter);*/
}

bool ButtonDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
	if (event->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent *e = (QMouseEvent*)event;
		if (m_Buttons.contains(index))
		{
			BtnList* buttons = m_Buttons.value(index);
			BtnList::iterator it;
			for (it = buttons->begin(); it != buttons->end(); it++)
			{
				if ((*it)->first->rect.contains(e->x(), e->y()))
				{
					(*it)->first->state |= QStyle::State_Sunken;
				}
			}
			
			return true;
		}
	}

	if (event->type() == QEvent::MouseButtonRelease)
	{
		QMouseEvent *e = (QMouseEvent*)event;
		if (m_Buttons.contains(index))
		{
			BtnList* buttons = m_Buttons.value(index);
			BtnList::iterator it;
			for (it = buttons->begin(); it != buttons->end(); it++)
			{
				if ((*it)->first->rect.contains(e->x(), e->y()))
				{
					(*it)->first->state &= (~QStyle::State_Sunken);
					(*it)->second(event, model, option, index);
//					showMsg(QString::fromLocal8Bit("first button column %1").arg(index.column()));
				}
			}

			return true;
		}
	}
	return false;
}

void ButtonDelegate::showMsg(QString str)
{
	QMessageBox msg;
	msg.setText(str);
	msg.exec();
}