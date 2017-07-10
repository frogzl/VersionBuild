#ifndef DLGTITLEBAR_H
#define DLGTITLEBAR_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
class DlgTitleBar : public QFrame
{
	Q_OBJECT

public:
	DlgTitleBar(QWidget *parent = 0);
	~DlgTitleBar();

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

#endif // DLGTITLEBAR_H
