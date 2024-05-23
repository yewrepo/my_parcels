#ifndef PARCELDETAILS_H
#define PARCELDETAILS_H

#include <QObject>
#include <QVariant>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "ParcelHistoryItem.h"
#include "../PostServiceClass.h"

class ParcelDetails: public QObject
{
    Q_OBJECT
    Q_PROPERTY(PostService postService READ postService CONSTANT)
    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(QString barcode READ barcode CONSTANT)
    Q_PROPERTY(QString realBarcode READ realBarcode CONSTANT)
    Q_PROPERTY(QString commonStatus READ commonStatus CONSTANT)
    Q_PROPERTY(QString sender READ sender CONSTANT)
    Q_PROPERTY(QString recipient READ recipient CONSTANT)
    Q_PROPERTY(QString destinationData READ destinationData CONSTANT)
    Q_PROPERTY(QString acceptanceDate READ acceptanceDate CONSTANT)
    Q_PROPERTY(int weight READ weight CONSTANT)
    Q_PROPERTY(qint64 lastUpdate READ lastUpdate CONSTANT)
    Q_PROPERTY(QList<QObject *> historyItemList READ historyItemList CONSTANT)

public:
    explicit ParcelDetails(QObject *parent = nullptr);

    PostService postService();
    void setPostService(PostService postService);

    QString title();
    void setTitle(QString title);

    QString barcode();
    void setBarcode(QString barcode);

    QString realBarcode();
    void setRealBarcode(QString realBarcode);

    QString sender();
    void setSender(QString sender);

    QString recipient();
    void setRecipient(QString recipient);

    QString destinationData();
    void setDestinationData(QString destinationData);

    QString acceptanceDate();
    void setAcceptanceDate(QString acceptanceDate);

    int weight();
    void setWeight(int weight);

    qint64 lastUpdate();
    void setLastUpdate(qint64 timestamp);

    QVariant trackingHistory() const;
    QList<QObject *> historyItemList() const;
    void addHistoryItem(ParcelHistoryItem *item);

    QString commonStatus();
    void setCommonStatus(QString commonStatus);

    Q_INVOKABLE  QString getJson();
private:
    PostService _postService;
    QString _title;
    QString _barcode;
    QString _realBarcode;
    QString _sender;
    QString _recipient;
    QString _destinationData;
    QString _acceptanceDate;
    QString _commonStatus;
    qint64 _lastUpdate;
    int _weight;
    QList<QObject*> _trackingHistoryList;
};

#endif // PARCELDETAILS_H
