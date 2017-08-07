#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Download : public QObject
{
    Q_OBJECT
public:
    explicit Download(QObject *parent = 0);
    void makeRequest(QString str);
    QString result;
    QString get_result();
    QString r1= " - ";

signals:



public slots:
    void replyFinished(QNetworkReply *rpl);

private:
    QNetworkAccessManager *mng;

};

#endif // DOWNLOAD_H
