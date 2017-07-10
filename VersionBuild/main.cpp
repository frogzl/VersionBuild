#include "versionbuild.h"
#include <QApplication>
#include <QFile>
#include <QTextCodec>
QString getQssFromFile(QString filename);
int main(int argc, char *argv[])
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
	QApplication a(argc, argv);
	QString qss = getQssFromFile(QString(":/Resources/VersionBuild.qss"));
	a.setStyleSheet(qss);
	VersionBuild w;
	w.show();
	return a.exec();
}

QString getQssFromFile(QString filename)
{
	QFile f(filename);
	QString qss = "";
	if (f.open(QFile::ReadOnly))
	{
		qss = QLatin1String(f.readAll());
		f.close();
	}
	return qss;
}