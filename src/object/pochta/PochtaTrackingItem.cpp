#include "PochtaTrackingItem.h"

PochtaTrackingItem::PochtaTrackingItem(QObject *parent) : QObject(parent)
{
    //not use
}

PochtaTrackingItem *PochtaTrackingItem::fromJsonObject(QJsonObject object)
{
    QString historyDateTime = object.value("date").toString();
    QDateTime dateTime = QDateTime::fromString(historyDateTime, Qt::ISODate);
    QDateTime localDateTime = dateTime.toTimeZone(QTimeZone("Europe/Moscow"));

    PochtaTrackingItem *item = new PochtaTrackingItem();
    item->setDate(localDateTime.toString("dd.MM.yyyy в hh:mm"));
    item->setHumanStatus(object.value("humanStatus").toString());
    item->setIndex(object.value("index").toInt());
    item->setCityName(object.value("cityName").toString());
    item->setCountryName(object.value("countryName").toString());
    item->setDescription(object.value("description").toString());
    item->setWeight(object.value("weight").toInt());
    return item;
}

QString PochtaTrackingItem::date()
{
    return _date;
}

void PochtaTrackingItem::setDate(QString date)
{
    _date = date;
}

QString PochtaTrackingItem::humanStatus()
{
    return _humanStatus;
}

void PochtaTrackingItem::setHumanStatus(QString humanStatus)
{
    _humanStatus = humanStatus;
}

int PochtaTrackingItem::countryId()
{
    return _countryId;
}

void PochtaTrackingItem::setCountryId(int countryId)
{
    _countryId = countryId;
}

int PochtaTrackingItem::index()
{
    return _index;
}

void PochtaTrackingItem::setIndex(int index)
{
    _index = index;
}

QString PochtaTrackingItem::cityName()
{
    return _cityName;
}

void PochtaTrackingItem::setCityName(QString cityName)
{
    _cityName = cityName;
}

QString PochtaTrackingItem::countryName()
{
    return _countryName;
}

void PochtaTrackingItem::setCountryName(QString countryName)
{
    _countryName = countryName;
}

QString PochtaTrackingItem::countryCustomName()
{
    return _countryCustomName;
}

void PochtaTrackingItem::setCountryCustomName(QString countryCustomName)
{
    _countryCustomName = countryCustomName;
}

QString PochtaTrackingItem::description()
{
    return _description;
}

void PochtaTrackingItem::setDescription(QString description)
{
    _description = description;
}

int PochtaTrackingItem::weight()
{
    return _weight;
}

void PochtaTrackingItem::setWeight(int weight)
{
    _weight = weight;
}

bool PochtaTrackingItem::isInInternationalTracking()
{
    return _isInInternationalTracking;
}

void PochtaTrackingItem::setIsInInternationalTracking(bool isInInternationalTracking)
{
    _isInInternationalTracking = isInInternationalTracking;
}

QString PochtaTrackingItem::getJson()
{
    QJsonObject obj;
    obj.insert("date", date());
    obj.insert("humanStatus", humanStatus());
    if (cityName().isEmpty()){
        obj.insert("point", QString("%1").arg(countryName()));
    }else{
        obj.insert("point", QString("%1, %2").arg(countryName(), cityName()));
    }
    QJsonDocument doc(obj);
    doc.toJson(QJsonDocument::Compact).toStdString().c_str();
    return doc.toJson(QJsonDocument::Compact).toStdString().c_str();
}
