#ifndef GLOBALCAINIAOREQUEST_H
#define GLOBALCAINIAOREQUEST_H

#include <QObject>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkReply>
#include "../object/global/GlobalCainiaoItem.h"
#include "../object/global/GlobalTrackingItem.h"

class GlobalCainiaoRequest: public QObject
{
    Q_OBJECT

public:
    explicit GlobalCainiaoRequest(QObject *parent = nullptr);

    QNetworkRequest getDetails(const QString barcode);
    GlobalCainiaoItem* parseReply(QNetworkReply *reply);
private:
    const QString URL = "https://global.cainiao.com/global/detail.json";
    //const QString URL = "https://global.cainiao.com/global/detail.json?mailNos=%1&lang=ru&language=ru";
};

#endif // GLOBALCAINIAOREQUEST_H
