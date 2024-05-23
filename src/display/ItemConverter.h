#ifndef ITEMCONVERTER_H
#define ITEMCONVERTER_H

#include <QDebug>
#include <QTimeZone>
#include <QDateTime>
#include "ParcelDetails.h"
#include "ParcelHistoryItem.h"
#include "../object/global/GlobalTrackingItem.h"
#include "../object/global/GlobalCainiaoItem.h"
#include "../object/cainiao/CainiaoTrackingItem.h"
#include "../object/cainiao/CainiaoItem.h"
#include "../object/pochta/PochtaTrackingItem.h"
#include "../object/pochta/PochtaItem.h"

class ItemConverter
{
public:
    ItemConverter();

    static ParcelHistoryItem *convertHistoryItem(CainiaoTrackingItem *item);
    static ParcelDetails *convertItem(CainiaoItem *item);

    static ParcelHistoryItem *convertHistoryItem(PochtaTrackingItem *item);
    static ParcelDetails *convertItem(PochtaItem *item);

    static ParcelHistoryItem *convertHistoryItem(GlobalTrackingItem *item);
    static ParcelDetails *convertItem(GlobalCainiaoItem *item);
};

#endif // ITEMCONVERTER_H
