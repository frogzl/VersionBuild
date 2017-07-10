#ifndef HTTPUPLOADFILES_H
#define HTTPUPLOADFILES_H

#include <QNetworkAccessManager>
#include <QFileInfoList>
#include <QHttpMultiPart>
#include <QNetworkReply>
#include <QDir>
#include <QMutex>

class Http :public QObject
{
    Q_OBJECT
public:
	Http();
	
    bool get(const QUrl &url);
	bool post(const QUrl &url, QString &qsData);
	bool uploadFile(const QUrl &url, QString &qsFilePath);
	bool downloadFile(const QUrl &url);
	QByteArray getReplyData();
signals:
    void SignalGetArray(QByteArray,int);
    void SignalGetDownFile(QString fileName,QByteArray fileBoby);
	void signalQuit();
private slots:
    void replyFinished(QNetworkReply *reply);
private:
    QNetworkAccessManager *_uploadManager;
    QByteArray m_BARespondData;	
	QNetworkReply *m_NRReply;
	QByteArray m_baReplyData;
	int m_nHttpStatus;
};

#endif // HTTPUPLOADFILES_H
