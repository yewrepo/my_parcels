#ifndef POCHTAITEM_H
#define POCHTAITEM_H

#include <QDebug>
#include <QObject>
#include <QVariant>
#include <QTimeZone>
#include <QDateTime>
#include <QJsonDocument>
#include "PochtaTrackingItem.h"
#include "../../PostServiceClass.h"

class PochtaItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(PostService postService READ postService CONSTANT)
    Q_PROPERTY(QString destinationCountryName READ destinationCountryName CONSTANT)
    Q_PROPERTY(QString destinationCityName READ destinationCityName CONSTANT)
    Q_PROPERTY(QString originCountryName READ originCountryName CONSTANT)
    Q_PROPERTY(QString sender READ sender CONSTANT)
    Q_PROPERTY(QString recipient READ recipient CONSTANT)
    Q_PROPERTY(int weight READ weight CONSTANT)
    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(QString mailType READ mailType CONSTANT)
    Q_PROPERTY(QString commonStatus READ commonStatus CONSTANT)
    Q_PROPERTY(QString globalStatus READ globalStatus CONSTANT)
    Q_PROPERTY(QString barcode READ barcode CONSTANT)
    Q_PROPERTY(QList<QObject *> historyItemList READ historyItemList CONSTANT)
    Q_PROPERTY(QString acceptanceOperationDateTime READ acceptanceOperationDateTime CONSTANT)

public:
    explicit PochtaItem(QObject *parent = nullptr);

    static PochtaItem* fromJsonObject(QJsonObject object);

    PostService postService();
    void setPostService(PostService postService);

    QString destinationCountryName();
    void setDestinationCountryName(QString destinationCountryName);

    QString destinationCityName();
    void setDestinationCityName(QString destinationCityName);

    QString originCountryName();
    void setOriginCountryName(QString originCountryName);

    QString sender();
    void setSender(QString sender);

    QString recipient();
    void setRecipient(QString recipient);

    int weight();
    void setWeight(int weight);

    QString title();
    void setTitle(QString title);

    QString mailType();
    void setMailType(QString mailType);

    QString commonStatus();
    void setCommonStatus(QString commonStatus);

    QString globalStatus();
    void setGlobalStatus(QString globalStatus); // ARCHIVED, IN_PROGRESS

    QString barcode();
    void setBarcode(QString barcode);

    QString acceptanceOperationDateTime();
    void setAcceptanceOperationDateTime(QString date);

    QVariant trackingHistory() const;
    QList<QObject *> historyItemList() const;
    void addHistoryItem(PochtaTrackingItem *item);

private:
    PostService _postService;
    QString _destinationCountryName;
    QString _destinationCityName;
    QString _originCountryName;
    QString _sender;
    QString _recipient;
    int _weight;
    QString _title;
    QString _mailType;
    QString _commonStatus;
    QString _globalStatus;
    QString _barcode;
    QString _acceptanceOperationDateTime;

    QList<QObject*> _trackingHistoryItemList;
};

#endif // POCHTAITEM_H
