#include "main/MainWindow.h"
#include <QApplication>
#include <QFile>

QString getQssFromFile(QString filename);
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QApplication::setWindowIcon(QIcon(":/Resources/ico/logo.ico"));
	a.setStyleSheet(getQssFromFile(":/Resources/qss/default.qss"));
	MainWindow m;
	m.show();
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