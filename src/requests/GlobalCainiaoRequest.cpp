#include "GlobalCainiaoRequest.h"

GlobalCainiaoRequest::GlobalCainiaoRequest(QObject *parent): QObject(parent)
{

}

QNetworkRequest GlobalCainiaoRequest::getDetails(const QString barcode)
{
    QUrlQuery query;
    query.addQueryItem("language", "ru");
    query.addQueryItem("lang", "ru");
    query.addQueryItem("mailNos", barcode);
    QUrl url(URL);
    url.setQuery(query.query());

    qDebug() << "URL: " << url << "\n";

    QNetworkRequest request(url);
    return request;
}

GlobalCainiaoItem *GlobalCainiaoRequest::parseReply(QNetworkReply *reply)
{
    QJsonDocument jDoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jObj = jDoc.object();

    QString strFromObj = QJsonDocument(jObj).toJson(QJsonDocument::Compact).toStdString().c_str();
    qDebug() << "Reply: " << strFromObj << "\n";

    return GlobalCainiaoItem::fromJsonObject(jObj);
}
