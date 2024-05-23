#include "CainiaoTrackingItem.h"

CainiaoTrackingItem::CainiaoTrackingItem(QObject *parent) : QObject(parent)
{
    //not use
}

QString CainiaoTrackingItem::actionCode()
{
    return _actionCode;
}

void CainiaoTrackingItem::setActionCode(QString actionCode)
{
    _actionCode = actionCode;
}

QString CainiaoTrackingItem::desc()
{
    return _desc;
}

void CainiaoTrackingItem::setDesc(QString desc)
{
    _desc = desc;
}

double CainiaoTrackingItem::timestamp()
{
    return _timestamp;
}

void CainiaoTrackingItem::setTimestamp(double timestamp)
{
    _timestamp = timestamp;
}
