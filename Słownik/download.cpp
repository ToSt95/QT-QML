#include "download.h"


Download::Download(QObject *parent) : QObject(parent)
{
    mng = new QNetworkAccessManager();

    connect(mng,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
}

void Download::makeRequest(QString str)
{
    mng->get(QNetworkRequest(QUrl(str)));
}

QString Download::get_result()
{

return r1;

}


void Download::replyFinished(QNetworkReply *rpl)
{
    QByteArray myData;
    myData = rpl->readAll();
    result = myData;
    QString s1("<text>");
    QString s2("</text>");
    int p1 = result.indexOf(s1)+6;
    int p2 = result.indexOf(s2);
    QString odp = "Tlumaczenie: \n";
    odp += result.mid(p1,p2-p1);
    r1 = odp;
}


