#include "PochtaItem.h"

PochtaItem::PochtaItem(QObject *parent) : QObject(parent)
{
    //not use
}

PochtaItem *PochtaItem::fromJsonObject(QJsonObject object)
{
    PochtaItem *details = new PochtaItem();
    details->setPostService(PostService::RU_POCHTA);

    if (object.contains("trackingItem")){
        QJsonObject root = object.value("trackingItem").toObject();
        details->setDestinationCountryName(root.value("destinationCountryName").toString());
        details->setDestinationCityName(root.value("destinationCityName").toString());
        details->setOriginCountryName(root.value("originCountryName").toString());
        details->setSender(root.value("sender").toString());
        details->setRecipient(root.value("recipient").toString());
        details->setWeight(root.value("weight").toInt());
        details->setTitle(root.value("title").toString());
        details->setMailType(root.value("mailType").toString());
        details->setCommonStatus(root.value("commonStatus").toString());
        details->setGlobalStatus(root.value("globalStatus").toString());
        details->setBarcode(root.value("barcode").toString());

        if (root.contains("acceptanceOperationDateTime")){
            QString acceptDateTime = root.value("acceptanceOperationDateTime").toString();
            QDateTime dateTime = QDateTime::fromString(acceptDateTime, Qt::ISODate);
            QDateTime localDateTime = dateTime.toTimeZone(QTimeZone("Europe/Moscow"));
            details->setAcceptanceOperationDateTime(localDateTime.toString("dd.MM.yyyy в hh:mm"));
            qDebug() << "has acceptanceOperationDateTime: " << details->_acceptanceOperationDateTime;
        }

        if (root.contains("trackingHistoryItemList")) {
            QJsonArray historyArray = root.value("trackingHistoryItemList").toArray();
            for (int index = 0; index < historyArray.size(); ++index) {
                details->addHistoryItem(PochtaTrackingItem::fromJsonObject(historyArray.at(index).toObject()));
            }
        }
    }

    return details;
}

PostService PochtaItem::postService()
{
    return _postService;
}

void PochtaItem::setPostService(PostService postService)
{
    _postService = postService;
}

QString PochtaItem::destinationCountryName()
{
    return _destinationCountryName;
}

void PochtaItem::setDestinationCountryName(QString destinationCountryName)
{
    _destinationCountryName = destinationCountryName;
}

QString PochtaItem::destinationCityName()
{
    return _destinationCityName;
}

void PochtaItem::setDestinationCityName(QString destinationCityName)
{
    _destinationCityName = destinationCityName;
}

QString PochtaItem::originCountryName()
{
    return _originCountryName;
}

void PochtaItem::setOriginCountryName(QString originCountryName)
{
    _originCountryName = originCountryName;
}

QString PochtaItem::sender()
{
    return _sender;
}

void PochtaItem::setSender(QString sender)
{
    _sender = sender;
}

QString PochtaItem::recipient()
{
    return _recipient;
}

void PochtaItem::setRecipient(QString recipient)
{
    _recipient = recipient;
}

int PochtaItem::weight()
{
    return _weight;
}

void PochtaItem::setWeight(int weight)
{
    _weight = weight;
}

QString PochtaItem::title()
{
    return _title;
}

void PochtaItem::setTitle(QString title)
{
    _title = title;
}

QString PochtaItem::mailType()
{
    return _mailType;
}

void PochtaItem::setMailType(QString mailType)
{
    _mailType = mailType;
}

QString PochtaItem::commonStatus()
{
    return _commonStatus;
}

void PochtaItem::setCommonStatus(QString commonStatus)
{
    _commonStatus = commonStatus;
}

QString PochtaItem::globalStatus()
{
    return _globalStatus;
}

void PochtaItem::setGlobalStatus(QString globalStatus)
{
    _globalStatus = globalStatus;
}

QString PochtaItem::barcode()
{
    return _barcode;
}

void PochtaItem::setBarcode(QString barcode)
{
    _barcode = barcode;
}

QString PochtaItem::acceptanceOperationDateTime()
{
    return _acceptanceOperationDateTime;
}

void PochtaItem::setAcceptanceOperationDateTime(QString date)
{
    _acceptanceOperationDateTime = date;
}

QVariant PochtaItem::trackingHistory() const
{
    return QVariant::fromValue(_trackingHistoryItemList);
}

QList<QObject *> PochtaItem::historyItemList() const
{
    return _trackingHistoryItemList;
}

void PochtaItem::addHistoryItem(PochtaTrackingItem *item)
{
    _trackingHistoryItemList.append(item);
}
