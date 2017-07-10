#pragma once
#include "qobject.h"
class Common :public QObject
{
	Q_OBJECT
public:
	typedef struct
	{
		QString qsGuid;
		QString qsName;
		QString qsUrl;
		QString qsBranch;
		int nVersionStart;
		int nVersionCurrent;
		int nStatus;
	}RepertoryItem;
public:
	Common();
	~Common();
	static QString unicode_utf8(const QString &inStr);
};

