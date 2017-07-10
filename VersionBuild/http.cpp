#include "http.h"

#include <QFileDialog>
#include <WinSock2.h>
#include <Iphlpapi.h>
#include <iostream>
#include <QDir>
#include <QSslConfiguration>
#include <QException>
#include <QJsonObject>
#include <QJsonParseError>
#include <QEventLoop>
#include <QTextCodec>
using namespace std;

Http::Http()
{
	m_baReplyData = "";
    _uploadManager = new QNetworkAccessManager(this);
    connect(_uploadManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
}

bool Http::get(const QUrl &url)
{
	QEventLoop loop;
    QNetworkRequest request(url);
	m_NRReply = _uploadManager->get(request);
	connect(this, SIGNAL(signalQuit()), &loop, SLOT(quit()));
	loop.exec();
	disconnect(this, SIGNAL(signalQuit()), &loop, SLOT(quit()));
	m_nHttpStatus = m_NRReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	m_baReplyData = m_NRReply->readAll();
	return m_nHttpStatus == 200 ? true : false;
}



bool Http::post(const QUrl &url, QString &qsData)
{
	QEventLoop loop;
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
	m_NRReply = _uploadManager->post(request, qsData.toLocal8Bit());
	connect(this, SIGNAL(signalQuit()), &loop, SLOT(quit()));
	loop.exec();
	disconnect(this, SIGNAL(signalQuit()), &loop, SLOT(quit()));
	m_nHttpStatus = m_NRReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	m_baReplyData = m_NRReply->readAll();
	return m_nHttpStatus == 200 ? true : false;
}

bool Http::uploadFile(const QUrl &url, QString &qsFilePath)
{
	QFile file(qsFilePath);
	if (file.open(QFile::ReadOnly))
	{
		QFileInfo fileInfo(qsFilePath);
		const qint64 qn64ReadBlock = 10 * 1024;
		qint64 qn64FileSize = file.size();
		if (qn64FileSize > qn64ReadBlock)
		{
			qint64 qn64Send = 0;
			QString qsFileID = "";
			// 分段上传
			while (qn64Send < qn64FileSize)
			{
				QEventLoop loop;
				QJsonObject jObject;
				jObject["storageid"] = qsFileID;
				jObject["filename"] = QString(QTextCodec::codecForName("utf8")->fromUnicode(fileInfo.completeBaseName() + "." + fileInfo.suffix()));
				QNetworkRequest request(url);
				request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
				if (qn64FileSize - qn64Send < qn64ReadBlock)
				{
					QString qsRange = QString::fromLocal8Bit("bytes %1-%2/%3").arg(qn64Send).arg(qn64FileSize).arg(qn64FileSize);
					request.setRawHeader("Range", qsRange.toLocal8Bit());
					jObject["binary"] = QString(file.read(qn64FileSize - qn64Send).toBase64());
				}
				else
				{
					QString qsRange = QString::fromLocal8Bit("bytes %1-%2/%3").arg(qn64Send).arg(qn64Send + qn64ReadBlock).arg(qn64FileSize);
					request.setRawHeader("Range", qsRange.toLocal8Bit());
					jObject["binary"] = QString(file.read(qn64ReadBlock).toBase64());
				}
				m_NRReply = _uploadManager->post(request, QJsonDocument(jObject).toJson());
				connect(this, SIGNAL(signalQuit()), &loop, SLOT(quit()));
				loop.exec();
				disconnect(this, SIGNAL(signalQuit()), &loop, SLOT(quit()));

				m_nHttpStatus = m_NRReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
				m_baReplyData = m_NRReply->readAll();
				QJsonDocument jsonDoc = QJsonDocument::fromJson(m_baReplyData);
				if (jsonDoc.isNull()) 
				{
					return false;
				}
				QJsonObject jsonRespond = jsonDoc.object();
				qsFileID = jsonRespond["storageid"].toString();
				m_NRReply->deleteLater();
				qn64Send += (qn64ReadBlock + 1);
			}
		}
		else
		{
			// 直接上传
			QEventLoop loop;
			QJsonObject jObject;
			jObject["storageid"] = "";
			jObject["filename"] = QString(QTextCodec::codecForName("utf8")->fromUnicode(fileInfo.completeBaseName() + "." + fileInfo.suffix()));
			jObject["binary"] = QString(file.readAll().toBase64());
			QNetworkRequest request(url);
			request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
			QString qsRange = QString::fromLocal8Bit("bytes 0-");
			request.setRawHeader("Range", qsRange.toLocal8Bit());
			m_NRReply = _uploadManager->post(request, QJsonDocument(jObject).toJson());
			connect(this, SIGNAL(signalQuit()), &loop, SLOT(quit()));
			loop.exec();
			disconnect(this, SIGNAL(signalQuit()), &loop, SLOT(quit()));

			m_nHttpStatus = m_NRReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
			m_baReplyData = m_NRReply->readAll();
			m_NRReply->deleteLater();
		}
	}
	return true;
}

bool Http::downloadFile(const QUrl &url)
{
	return true;
}

QByteArray Http::getReplyData()
{
	return m_baReplyData;
}

void Http::replyFinished(QNetworkReply *reply)
{
	emit signalQuit();
}