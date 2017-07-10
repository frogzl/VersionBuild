#ifndef DLGCREATERESOURCEFILE_H
#define DLGCREATERESOURCEFILE_H

#include "dlgbase.h"
class DlgCreateResourceFile : public DlgBase
{
	Q_OBJECT

public:
	DlgCreateResourceFile(QWidget *parent = 0);
	~DlgCreateResourceFile();
private:
	void InitData();
	void InitConnect();
private:
};

#endif // DLGCREATERESOURCEFILE_H
