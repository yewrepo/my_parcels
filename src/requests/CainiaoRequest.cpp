#include "CainiaoRequest.h"

CainiaoRequest::CainiaoRequest(QObject *parent) : QObject(parent)
{
    // not use
}

PostData CainiaoRequest::getDetails(const QString barcode)
{
    QUrl url(URL);

    qDebug() << "URL: " << url << "\n";

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json;charset=UTF-8");
    return PostData(POST_BODY.arg(barcode).toUtf8(), request);
}

CainiaoItem *CainiaoRequest::parseReply(QNetworkReply *reply)
{
    QJsonDocument jDoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jObj = jDoc.object();

    QString strFromObj = QJsonDocument(jObj).toJson(QJsonDocument::Compact).toStdString().c_str();
    qDebug() << "Reply: " << strFromObj << "\n";

    if (jObj.contains("success"))
    {
        if (jObj.value("success").toBool() == true)
        {
            CainiaoItem *item = new CainiaoItem();
            QJsonObject data = jObj.value("data").toArray().at(0).toObject();
            item->setBarcode(data.value("mailNo").toString());

            QJsonArray array = data.value("details").toArray();
            for (int index = 0; index < array.size(); ++index)
            {
                QJsonObject obj = array.at(index).toObject();
                CainiaoTrackingItem *trackingItem = new CainiaoTrackingItem();
                trackingItem->setActionCode(obj.value("actionCode").toString());
                trackingItem->setDesc(obj.value("desc").toString());
                trackingItem->setTimestamp(obj.value("time").toDouble());
                item->addHistoryItem(trackingItem);
            }
            return item;
        }
    }
    return nullptr;
}
