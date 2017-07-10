#include "delegateresourcelist.h"
#include "../model/modelresourcelist.h"
DelegateResourceList::DelegateResourceList(QObject *parent)
	: QItemDelegate(parent)
{

}

DelegateResourceList::~DelegateResourceList()
{

}

void DelegateResourceList::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	const ModelReourceList *pModel = dynamic_cast<const ModelReourceList*>(index.model());
	index.model()->data(index, Qt::UserRole).toBool();
	painter->save();
	QColor color1(86, 163, 243);
	QColor color2(42, 49, 59);
	QColor color3(69, 130, 194);
	QColor color4(255, 255, 255);
	QColor color5(2, 2, 2);
	QColor color6(128, 128, 128);

	QString qsIconSkin = pModel->data(index, ModelReourceList::png).toString();
	if (qsIconSkin.compare("") == 0)
		qsIconSkin = "zip.png";
	QString qsName = pModel->data(index, ModelReourceList::name).toString();
	QString qsDiscription = pModel->data(index, ModelReourceList::discription).toString();
	if (option.state & QStyle::State_MouseOver || option.state & QStyle::State_Selected)
	{
		// »æÖÆ±³¾°
		QBrush b(color1);
		painter->setPen(color1);
		painter->setBrush(b);
		//		painter->drawRect(option.rect);
		// »­Í¼
		QImage sourceImage(QString(":Resources/png/%1").arg(qsIconSkin));
		painter->drawImage(option.rect.width() - sourceImage.width() - 5, option.rect.y(), sourceImage);
		painter->setPen(color6);
		painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
		// Ð´×Ö
		QFont f(QString::fromLocal8Bit("ºÚÌå"), 12, QFont::Bold);
		painter->setFont(f);
		QFontMetrics fm = painter->fontMetrics();
		double tempWidth = fm.width(qsName);
		painter->setPen(color5);
		painter->drawText(10, option.rect.y() + 17, qsName);
		// Ð´ÃèÊö
		QFont fDiscription(QString::fromLocal8Bit("ºÚÌå"), 10, QFont::Normal);
		painter->setFont(fDiscription);
		painter->setPen(color6);
		painter->drawText(10, option.rect.y() + 17 + 12 + 5, qsDiscription);
	}
	else
	{
		// »æÖÆ±³¾°
		QBrush b(color1);
		painter->setPen(color1);
		painter->setBrush(b);
//		painter->drawRect(option.rect);
		// »­Í¼
		QImage sourceImage(QString(":Resources/png/%1").arg(qsIconSkin));
		painter->drawImage(option.rect.width() - sourceImage.width() - 5, option.rect.y(), sourceImage);
		painter->setPen(color6);
		painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
		// Ð´±êÌâ
		QFont f(QString::fromLocal8Bit("ºÚÌå"), 12, QFont::Bold);
		painter->setFont(f);
		QFontMetrics fm = painter->fontMetrics();
		double tempWidth = fm.width(qsName);
		painter->setPen(color5);
		painter->drawText(10, option.rect.y() + 17, qsName);
		// Ð´ÃèÊö
		QFont fDiscription(QString::fromLocal8Bit("ºÚÌå"), 10, QFont::Normal);
		painter->setFont(fDiscription);
		painter->setPen(color6);
		painter->drawText(10, option.rect.y() + 17 + 12 + 5, qsDiscription);
	}
	painter->restore();
}

QSize DelegateResourceList::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	return QSize(option.rect.width(), 80);
}