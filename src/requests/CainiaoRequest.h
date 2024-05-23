#ifndef CAINIAOREQUEST_H
#define CAINIAOREQUEST_H

#include <QObject>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include "../object/PostData.h"
#include "../object/cainiao/CainiaoItem.h"
#include "../object/cainiao/CainiaoTrackingItem.h"

QT_BEGIN_NAMESPACE
class QHttpMultiPart;
class QNetworkAccessManager;
class QNetworkReply;
class QJsonValue;
QT_END_NAMESPACE

class CainiaoRequest : public QObject
{
    Q_OBJECT
public:
    explicit CainiaoRequest(QObject *parent = nullptr);

    PostData getDetails(const QString barcode);
    CainiaoItem* parseReply(QNetworkReply *reply);

private:
    const QString URL = "https://cainiao.ru/api/tracking";
    const QString POST_BODY = "{\"mailNos\": [\"%1\"],\"roleType\": \"CUST\"}";
};

#endif // CAINIAOREQUEST_H
