#include "ParcelHistoryItem.h"

ParcelHistoryItem::ParcelHistoryItem(QObject *parent)
{
    //not use
}

QString ParcelHistoryItem::description()
{
    return _description;
}

void ParcelHistoryItem::setDescription(QString description)
{
    _description = description;
}

QString ParcelHistoryItem::time()
{
    return _time;
}

void ParcelHistoryItem::setTime(QString time)
{
    _time = time;
}

QString ParcelHistoryItem::optionalData()
{
    return _optionalData;
}

void ParcelHistoryItem::setOptionalData(QString optionalData)
{
    _optionalData = optionalData;
}

QString ParcelHistoryItem::getJson()
{
    QJsonObject obj;
    obj.insert("description", description());
    obj.insert("time", time());
    obj.insert("optionalData", optionalData());
    QJsonDocument doc(obj);
    doc.toJson(QJsonDocument::Compact).toStdString().c_str();
    return doc.toJson(QJsonDocument::Compact).toStdString().c_str();
}
