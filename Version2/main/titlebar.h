#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QFrame>
#include <QWidget>
#include <QLabel>
#include <QToolButton>
#include <QPushButton>
class TitleBar : public QFrame
{
	Q_OBJECT

public:
	TitleBar(QWidget *parent = 0);
	~TitleBar();

	void SetTitle(QString qsTitle);
signals:
	void SignalClose();
private slots:
	void SlotClose();
private:
	QPushButton *m_pPBLogo;
	QLabel *m_pLBTitle;

	QPushButton *m_pPBClose;
};

#endif // TITLEBAR_H
