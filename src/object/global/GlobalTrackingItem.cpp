#include "GlobalTrackingItem.h"

GlobalTrackingItem::GlobalTrackingItem(QObject *parent): QObject(parent)
{

}

GlobalTrackingItem *GlobalTrackingItem::fromJsonObject(QJsonObject object)
{
    GlobalTrackingItem *trackingItem = new GlobalTrackingItem();
    trackingItem->setActionCode(object.value("actionCode").toString());
    trackingItem->setDesc(object.value("standerdDesc").toString());
    trackingItem->setDate(object.value("timeStr").toString());
    trackingItem->setTimezone(object.value("timeZone").toString());
    return trackingItem;
}

QString GlobalTrackingItem::actionCode()
{
    return _actionCode;
}

void GlobalTrackingItem::setActionCode(QString actionCode)
{
    _actionCode = actionCode;
}

QString GlobalTrackingItem::desc()
{
    return _desc;
}

void GlobalTrackingItem::setDesc(QString desc)
{
    _desc = desc;
}

QString GlobalTrackingItem::date()
{
    return _date;
}

void GlobalTrackingItem::setDate(QString date)
{
    _date = date;
}

QString GlobalTrackingItem::timezone()
{
    return _timezone;
}

void GlobalTrackingItem::setTimezone(QString timezone)
{
    _timezone = timezone;
}
