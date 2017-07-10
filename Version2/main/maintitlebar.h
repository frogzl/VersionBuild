#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
class MainTitleBar : public QFrame
{
	Q_OBJECT
public:
	MainTitleBar(QWidget *parent = 0);
	~MainTitleBar();

	void SetTitle(QString qsTitle);
signals:
	void SignalClose();
private slots:
	void SlotClose();
private:
	QPushButton *m_pPBLogo;
	QLabel *m_pLBTitle;

	QPushButton *m_pPBMinus;
	QPushButton *m_pPBClose;
};

#endif // TITLEBAR_H
