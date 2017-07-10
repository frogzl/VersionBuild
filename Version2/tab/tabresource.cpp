#include "tabresource.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonDocument>
#include "../dlg/dlgcreateresourcecompressedfile.h"
#include "../dlg/dlgcreateresourcefile.h"
#include "../dlg/dlgcreateresourcehost.h"
#include "../dlg/dlgcreateresourcesourcecode.h"
#include "../model/modelresourcelist.h"
#include "../delegate/delegateresourcelist.h"
#include "../common/DB.h"
#include "../common/http.h"
TabResource::TabResource(QWidget *parent)
	: QWidget(parent)
{
	m_pMenu = new QMenu();
	m_pMenuBar = new QMenuBar();
	m_pMenuBar->addMenu(m_pMenu);
	m_pLV = new QListView();
	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(m_pMenuBar);
	mainLayout->addWidget(m_pLV);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	setLayout(mainLayout);

	InitData();
	InitConnect();
}

TabResource::~TabResource()
{

}

void TabResource::RefreshData()
{
	ModelReourceList *pModel = dynamic_cast<ModelReourceList *>(m_pLV->model());
	pModel->Clear();
	ResourceData rd;
	DB db;
	QString qsServerAddres = db.getProtocol() + "://" + db.getServerIp() + ":" + db.getServerPort() + "/";
	QUrl url(qsServerAddres + QString("resource/query"));
	Http http;
	http.get(url);
	QString qsReplyData = http.getReplyData();
	QJsonParseError error;
	QJsonDocument jsonDoc = QJsonDocument::fromJson(qsReplyData.toUtf8(), &error);
	if (!jsonDoc.isNull())
	{
		QJsonObject jsonReplyData = jsonDoc.object();
		QString qsCode = jsonReplyData["code"].toString();
		if (qsCode.compare("0") == 0)
		{

			QJsonArray array = jsonReplyData["data"].toArray();
			for (int nIndex = 0; nIndex < array.size(); nIndex++)
			{
				QJsonObject obj = array[nIndex].toObject();
				rd.SetData(obj["guid"].toString(),
					obj["name"].toString(),
					nIndex + 1,
					obj["discription"].toString(),
					obj["resourceid"].toString(),
					TypeConvert(obj["type"].toInt()));
				pModel->Append(rd);

			}
		}
	}
}

void TabResource::SlotTriggered(QAction *action)
{
	if (action->iconText().compare(QString::fromLocal8Bit("源码")) == 0)
	{
		DlgCreateResourceSourceCode dlg(this);
		if (dlg.exec())
		{
			DB db;
			QString qsServerAddres = db.getProtocol() + "://" + db.getServerIp() + ":" + db.getServerPort();
			QUrl url(qsServerAddres + QString("/sourcecode/create"));

			Http http;
			if (http.post(url, dlg.Data().ToJsonString()))
			{

			}
		}
	}
	else if (action->iconText().compare(QString::fromLocal8Bit("压缩文件")) == 0)
	{
		DlgCreateResourceCompressedFile dlg(this);
		dlg.exec();
	}
	else if (action->iconText().compare(QString::fromLocal8Bit("文档")) == 0)
	{
		DlgCreateResourceFile dlg(this);
		dlg.exec();
	}
	else if (action->iconText().compare(QString::fromLocal8Bit("主机")) == 0)
	{
		DlgCreateResourceHost dlg(this);
		dlg.exec();
	}
}

void TabResource::InitData()
{
	m_pMenu->setIcon(QIcon(":Resources/png/appbar.add.black.png"));
	m_pMenu->addAction(new QAction(QString::fromLocal8Bit("源码"), 0));
	m_pMenu->addAction(new QAction(QString::fromLocal8Bit("压缩文件"), 0));
	m_pMenu->addAction(new QAction(QString::fromLocal8Bit("文档"), 0));
	m_pMenu->addAction(new QAction(QString::fromLocal8Bit("主机"), 0));

	m_pLV->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	DelegateResourceList *pDelegate = new DelegateResourceList();
	m_pLV->setItemDelegate(pDelegate);
	ModelReourceList *pModel = new ModelReourceList();
	m_pLV->setModel(pModel);
}

void TabResource::InitConnect()
{
	connect(m_pMenu, SIGNAL(triggered(QAction *)), this, SLOT(SlotTriggered(QAction *)));

}

QString TabResource::TypeConvert(int nType)
{
	switch (nType)
	{
	case 0:
		return "src.png";
	case 1:
		return "tar.png";
	case 2:
		return "Doc.png";
	case 3:
		return "host.png";
	default:
		return "host.png";
	}
}