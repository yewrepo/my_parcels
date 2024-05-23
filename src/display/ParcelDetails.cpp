#include "ParcelDetails.h"


ParcelDetails::ParcelDetails(QObject *parent)
{
    //not use
}

PostService ParcelDetails::postService()
{
    return _postService;
}

void ParcelDetails::setPostService(PostService postService)
{
    _postService = postService;
}

QString ParcelDetails::title()
{
    return _title;
}

void ParcelDetails::setTitle(QString title)
{
    _title = title;
}

QString ParcelDetails::barcode()
{
    return _barcode;
}

void ParcelDetails::setBarcode(QString barcode)
{
    _barcode = barcode;
}

QString ParcelDetails::realBarcode()
{
    return _realBarcode;
}

void ParcelDetails::setRealBarcode(QString realBarcode)
{
    _realBarcode = realBarcode;
}

QString ParcelDetails::sender()
{
    return _sender;
}

void ParcelDetails::setSender(QString sender)
{
    _sender = sender;
}

QString ParcelDetails::recipient()
{
    return _recipient;
}

void ParcelDetails::setRecipient(QString recipient)
{
    _recipient = recipient;
}

QString ParcelDetails::destinationData()
{
    return _destinationData;
}

void ParcelDetails::setDestinationData(QString destinationData)
{
    _destinationData = destinationData;
}

QString ParcelDetails::acceptanceDate()
{
    return _acceptanceDate;
}

void ParcelDetails::setAcceptanceDate(QString acceptanceDate)
{
    _acceptanceDate = acceptanceDate;
}

int ParcelDetails::weight()
{
    return _weight;
}

void ParcelDetails::setWeight(int weight)
{
    _weight = weight;
}

qint64 ParcelDetails::lastUpdate()
{
    return _lastUpdate;
}

void ParcelDetails::setLastUpdate(qint64 timestamp)
{
    _lastUpdate = timestamp;
}

QVariant ParcelDetails::trackingHistory() const
{
    return QVariant::fromValue(_trackingHistoryList);
}

QList<QObject *> ParcelDetails::historyItemList() const
{
    return _trackingHistoryList;
}

void ParcelDetails::addHistoryItem(ParcelHistoryItem *item)
{
    _trackingHistoryList.append(item);
}

QString ParcelDetails::commonStatus()
{
    if(_commonStatus != nullptr) {
        return _commonStatus;
    }
    return "Нет статуса";
}

void ParcelDetails::setCommonStatus(QString commonStatus)
{
    _commonStatus = commonStatus;
}

QString ParcelDetails::getJson()
{
    QJsonObject obj;
    obj.insert("postService", postService());
    obj.insert("sender", sender());
    obj.insert("recipient", recipient());
    obj.insert("destinationData", destinationData());
    obj.insert("weight", weight());
    QJsonArray array;
    for (int index = 0; index < _trackingHistoryList.size(); ++index) {
        QObject *item = _trackingHistoryList.at(index);
        array.append(((ParcelHistoryItem)item).getJson());
    }
    obj.insert("history", array);
    QJsonDocument doc(obj);
    doc.toJson(QJsonDocument::Compact).toStdString().c_str();
    return doc.toJson(QJsonDocument::Compact).toStdString().c_str();
}
