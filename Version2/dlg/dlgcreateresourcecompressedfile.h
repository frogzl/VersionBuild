#ifndef DLGCREATERESOURCECOMPRESSEDFILE_H
#define DLGCREATERESOURCECOMPRESSEDFILE_H

#include "dlgbase.h"
class DlgCreateResourceCompressedFile : public DlgBase
{
	Q_OBJECT

public:
	DlgCreateResourceCompressedFile(QWidget *parent = 0);
	~DlgCreateResourceCompressedFile();
private:
	void InitData();
	void InitConnect();
private:

};

#endif // DLGCREATERESOURCECOMPRESSEDFILE_H
