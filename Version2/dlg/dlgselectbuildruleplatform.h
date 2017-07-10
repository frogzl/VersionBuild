#ifndef DLGSELECTBUILDRULEPLATFORM_H
#define DLGSELECTBUILDRULEPLATFORM_H

#include "dlgbase.h"
#include <QTableView>
#include <QPushButton>
class DlgSelectBuildRulePlatform : public DlgBase
{
	Q_OBJECT

public:
	DlgSelectBuildRulePlatform(QWidget *parent);
	~DlgSelectBuildRulePlatform();
private:
	void InitData();
	void InitConnect();
private:
	QTableView *m_pTV;
	QPushButton *m_pPBOk;
};

#endif // DLGSELECTBUILDRULEPLATFORM_H
