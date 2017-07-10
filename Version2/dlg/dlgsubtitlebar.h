#ifndef DLGSUBTITLEBAR_H
#define DLGSUBTITLEBAR_H

#include <QFrame>
#include <QLabel>
class DlgSubTitleBar : public QFrame
{
	Q_OBJECT

public:
	DlgSubTitleBar(QWidget *parent = 0);
	~DlgSubTitleBar();
	void SetTitle(QString qsTitle);
private:
	QLabel *m_pLBTitle;
};

#endif // DLGSUBTITLEBAR_H
