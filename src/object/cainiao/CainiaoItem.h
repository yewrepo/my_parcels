#ifndef CAINIAOITEM_H
#define CAINIAOITEM_H

#include <QObject>
#include <QVariant>
#include "CainiaoTrackingItem.h"

class CainiaoItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString barcode READ barcode CONSTANT)
    Q_PROPERTY(QList<QObject *> historyItemList READ historyItemList CONSTANT)
public:
    explicit CainiaoItem(QObject *parent = nullptr);

    QString barcode();
    void setBarcode(QString barcode);

    QVariant trackingHistory() const;
    QList<QObject *> historyItemList() const;
    void addHistoryItem(CainiaoTrackingItem *item);

private:
    QString _barcode;
    QList<QObject*> _trackingHistoryItemList;
};

#endif // CAINIAOITEM_H
