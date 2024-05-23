#ifndef RUPOCHTAREQUEST_H
#define RUPOCHTAREQUEST_H

#include <QObject>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkReply>
#include "../object/pochta/PochtaItem.h"
#include "../object/pochta/PochtaTrackingItem.h"

QT_BEGIN_NAMESPACE
class QHttpMultiPart;
class QNetworkAccessManager;
class QNetworkReply;
class QJsonValue;
QT_END_NAMESPACE

class RuPochtaRequest : public QObject
{
    Q_OBJECT
public:
    explicit RuPochtaRequest(QObject *parent = nullptr);

    QNetworkRequest getDetails(const QString barcode);
    PochtaItem* parseReply(QNetworkReply *reply);

private:
    const QString URL = "https://www.pochta.ru/api/tracking/api/v1/trackings/by-barcodes";
};

#endif // RUPOCHTAREQUEST_H
