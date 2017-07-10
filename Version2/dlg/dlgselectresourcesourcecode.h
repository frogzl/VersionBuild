#ifndef DLGSELECTRESOURCESOURCECODE_H
#define DLGSELECTRESOURCESOURCECODE_H

#include "dlgbase.h"
#include <QTableView>
#include <QPushButton>

class SelectResourceSourceCodeData
{

};

class DlgSelectResourceSourceCode : public DlgBase
{
	Q_OBJECT

public:
	DlgSelectResourceSourceCode(QWidget *parent = 0);
	~DlgSelectResourceSourceCode();
	SelectResourceSourceCodeData Data() { return m_srscd; }
private slots:
	void SlotPBOkClicked();
private:
	void InitData();
	void InitConnect();
private:
	SelectResourceSourceCodeData m_srscd;
	QTableView *m_pTV;
	QPushButton *m_pPBOk;
};

#endif // DLGSELECTRESOURCESOURCECODE_H
