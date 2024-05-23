#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H

#include <random>
#include <QObject>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkReply>
#include <qnetworkaccessmanager.h>
#include "RuPochtaRequest.h"
#include "CainiaoRequest.h"
#include "GlobalCainiaoRequest.h"
#include "../display/ParcelDetails.h"
#include "../display/ParcelHistoryItem.h"
#include "../display/ItemConverter.h"
#include "../errors/CustomError.h"
#include "../LoadingStateClass.h"
#include "../PostServiceClass.h"

class RequestManager : public QObject
{
    Q_OBJECT
public:

    explicit RequestManager(QObject *parent = 0);
    ~RequestManager();

    Q_INVOKABLE void getBarcodeData(const QString barcode, const PostService postService);

private:
    QList<QByteArray> _userAgentArray;
    QNetworkAccessManager *_manager;
    RuPochtaRequest *_ruPochtaRequest;
    CainiaoRequest *_cainiaoRequest;
    GlobalCainiaoRequest *_globalRequest;
    QByteArray getUserAgent();

public slots:
    void successReply(QNetworkReply *reply);
    void errorReply(QNetworkReply::NetworkError error);

signals:
    void detailsReply(ParcelDetails *details);
    void loadingStateCallback(LoadingStatus loadingState, CustomError *error = nullptr);
};

#endif // REQUESTMANAGER_H
