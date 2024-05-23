#include "ItemConverter.h"

ParcelHistoryItem *ItemConverter::convertHistoryItem(CainiaoTrackingItem *item)
{
    ParcelHistoryItem *result = new ParcelHistoryItem();
    result->setDescription(item->desc());
    result->setOptionalData(item->actionCode());

    qlonglong time = QString::number(item->timestamp(), 'f', 0).toLongLong();
    QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(time);
    result->setTime(dateTime.toString("dd.MM.yyyy в hh:mm"));
    return result;
}

ParcelDetails *ItemConverter::convertItem(CainiaoItem *item)
{
    ParcelDetails *result = new ParcelDetails();
    result->setPostService(PostService::CAINIAO);
    result->setBarcode(item->barcode());
    result->setLastUpdate(QDateTime::currentMSecsSinceEpoch());
    result->setTitle("Отправление Cainiao");
    for (int index = 0; index < item->historyItemList().size(); ++index)
    {
        ParcelHistoryItem *historyItem = convertHistoryItem((CainiaoTrackingItem *)item->historyItemList().at(index));
        result->addHistoryItem(historyItem);
        if (index == 0)
        {
            result->setCommonStatus(historyItem->description());
        }
    }
    return result;
}

ParcelHistoryItem *ItemConverter::convertHistoryItem(PochtaTrackingItem *item)
{
    ParcelHistoryItem *result = new ParcelHistoryItem();
    result->setDescription(item->humanStatus());
    result->setTime(item->date());
    if (item->cityName().isEmpty())
    {
        result->setOptionalData(QString("%1").arg(item->countryName()));
    }
    else
    {
        result->setOptionalData(QString("%1, %2").arg(item->countryName(), item->cityName()));
    }
    return result;
}

ParcelDetails *ItemConverter::convertItem(PochtaItem *item)
{
    ParcelDetails *result = new ParcelDetails();
    result->setPostService(PostService::RU_POCHTA);
    result->setTitle(item->title());
    result->setBarcode(item->barcode());
    result->setLastUpdate(QDateTime::currentMSecsSinceEpoch());
    result->setSender(item->sender());
    result->setRecipient(item->recipient());
    result->setWeight(item->weight());
    result->setDestinationData(
                QString("%1 -> %2, %3").arg(item->originCountryName(), item->destinationCountryName(), item->destinationCityName()));
    result->setAcceptanceDate(item->acceptanceOperationDateTime());
    for (int index = 0; index < item->historyItemList().size(); ++index)
    {
        ParcelHistoryItem *historyItem = convertHistoryItem((PochtaTrackingItem *)item->historyItemList().at(index));
        result->addHistoryItem(historyItem);
        if (index == 0)
        {
            result->setCommonStatus(historyItem->description());
        }
    }
    return result;
}

ParcelHistoryItem *ItemConverter::convertHistoryItem(GlobalTrackingItem *item)
{
    ParcelHistoryItem *result = new ParcelHistoryItem();
    result->setDescription(item->desc());
    result->setOptionalData(item->actionCode());

    QDateTime dateTime = QDateTime::fromString(item->date(), "yyyy-MM-dd hh:mm:ss");
    result->setTime(
                QString("%1 %2").arg(
                    dateTime.toString("dd.MM.yyyy, hh:mm"),
                    item->timezone()));
    return result;
}

ParcelDetails *ItemConverter::convertItem(GlobalCainiaoItem *item)
{
    ParcelDetails *result = new ParcelDetails();
    result->setPostService(PostService::GLOBAL_CAINIAO);
    result->setTitle("Отправление Cainiao");
    result->setBarcode(item->barcode());
    result->setRealBarcode(item->realBarcode());
    result->setLastUpdate(QDateTime::currentMSecsSinceEpoch());
    result->setCommonStatus(item->commonStatus());
    result->setDestinationData(
                QString("%1 -> %2").arg(item->originCountryName(), item->destinationCountryName()));
    for (int index = 0; index < item->historyItemList().size(); ++index)
    {
        ParcelHistoryItem *historyItem = convertHistoryItem((GlobalTrackingItem *)item->historyItemList().at(index));
        result->addHistoryItem(historyItem);
    }
    return result;
}
