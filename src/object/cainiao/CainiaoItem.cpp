#include "CainiaoItem.h"

CainiaoItem::CainiaoItem(QObject *parent) : QObject(parent)
{
    //not use
}

QString CainiaoItem::barcode()
{
    return _barcode;
}

void CainiaoItem::setBarcode(QString barcode)
{
    _barcode = barcode;
}

QVariant CainiaoItem::trackingHistory() const
{
    return QVariant::fromValue(_trackingHistoryItemList);
}

QList<QObject *> CainiaoItem::historyItemList() const
{
    return _trackingHistoryItemList;
}

void CainiaoItem::addHistoryItem(CainiaoTrackingItem *item)
{
    _trackingHistoryItemList.append(item);
}
