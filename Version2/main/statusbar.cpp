#include "statusbar.h"

StatusBar::StatusBar(QWidget *parent)
	: QFrame(parent)
{
	setObjectName(QString::fromLocal8Bit("statusbar"));
}

StatusBar::~StatusBar()
{

}
