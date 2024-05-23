#ifndef GLOBALCAINIAOITEM_H
#define GLOBALCAINIAOITEM_H

#include <QObject>
#include <QVariant>
#include <QJsonDocument>
#include <QJsonObject>
#include "GlobalTrackingItem.h"
#include "../../PostServiceClass.h"

class GlobalCainiaoItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString barcode READ barcode CONSTANT)
    Q_PROPERTY(QString realBarcode READ realBarcode CONSTANT)
    Q_PROPERTY(QString commonStatus READ commonStatus CONSTANT)
    Q_PROPERTY(QString destinationCountryName READ destinationCountryName CONSTANT)
    Q_PROPERTY(QString originCountryName READ originCountryName CONSTANT)
    Q_PROPERTY(QList<QObject *> historyItemList READ historyItemList CONSTANT)
public:
    explicit GlobalCainiaoItem(QObject *parent = nullptr);

    static GlobalCainiaoItem* fromJsonObject(QJsonObject object);

    PostService postService();
    void setPostService(PostService postService);

    QString barcode();
    void setBarcode(QString barcode);

    QString realBarcode();
    void setRealBarcode(QString barcode);

    QString commonStatus();
    void setCommonStatus(QString commonStatus);

    QString destinationCountryName();
    void setDestinationCountryName(QString destinationCountryName);

    QString originCountryName();
    void setOriginCountryName(QString originCountryName);

    QVariant trackingHistory() const;
    QList<QObject *> historyItemList() const;
    void addHistoryItem(GlobalTrackingItem *item);

private:
    PostService _postService;
    QString _barcode;
    QString _realBarcode;
    QString _commonStatus;
    QString _destinationCountryName;
    QString _originCountryName;
    QList<QObject*> _trackingHistoryItemList;
};

#endif // GLOBALCAINIAOITEM_H
