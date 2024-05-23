#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QHttpMultiPart>
#include <QNetworkReply>
#include "RuPochtaRequest.h"

RuPochtaRequest::RuPochtaRequest(QObject *parent) : QObject(parent)
{
    //not use
}

QNetworkRequest RuPochtaRequest::getDetails(const QString barcode)
{
    QUrlQuery query;
    query.addQueryItem("language", "ru");
    query.addQueryItem("track-numbers", barcode);
    QUrl url(URL);
    url.setQuery(query.query());

    qDebug() << "URL: " << url << "\n";

    QNetworkRequest request(url);
    return request;
}

PochtaItem* RuPochtaRequest::parseReply(QNetworkReply *reply)
{
    QJsonDocument jDoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jObj = jDoc.object();

    QString strFromObj = QJsonDocument(jObj).toJson(QJsonDocument::Compact).toStdString().c_str();
    qDebug() << "Reply: " << strFromObj << "\n";

    if (jObj.contains("detailedTrackings")){
        QJsonArray array = jObj.value("detailedTrackings").toArray();
        if (array.size() > 0){
            QJsonObject obj = array.at(0).toObject();
            QJsonObject trackingItem = obj.value("trackingItem").toObject();
            //if (trackingItem.contains("acceptanceOperationDateTime")){
            //    QString trackingItem = obj.value("acceptanceOperationDateTime").toString();
            //    if (trackingItem != ""){
                    reply->deleteLater();
                    return PochtaItem::fromJsonObject(obj);
            //    }
           // }
        }
    }
    reply->deleteLater();
    return nullptr;
}
