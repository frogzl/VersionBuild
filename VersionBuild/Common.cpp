#include "Common.h"
#include <QTextCodec>
Common::Common()
{
}


Common::~Common()
{
}

QString Common::unicode_utf8(const QString &inStr)
{
	QTextCodec *utf8 = QTextCodec::codecForName("UTF8");
	return utf8->toUnicode(utf8->fromUnicode(inStr));
}