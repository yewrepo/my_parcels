#include "GlobalCainiaoItem.h"

GlobalCainiaoItem::GlobalCainiaoItem(QObject *parent) : QObject(parent)
{

}

GlobalCainiaoItem *GlobalCainiaoItem::fromJsonObject(QJsonObject object)
{
    GlobalCainiaoItem *details = new GlobalCainiaoItem();
    details->setPostService(PostService::GLOBAL_CAINIAO);

    if (object.contains("module")){
        QJsonArray array = object.value("module").toArray();
        if (array.count() > 0){
            QJsonObject root = array.at(0).toObject();
            details->setBarcode(root.value("mailNo").toString());
            details->setRealBarcode(root.value("copyRealMailNo").toString());
            details->setCommonStatus(root.value("statusDesc").toString());
            details->setOriginCountryName(root.value("originCountry").toString());
            details->setDestinationCountryName(root.value("destCountry").toString());

            if (root.contains("detailList")) {
                QJsonArray historyArray = root.value("detailList").toArray();
                for (int index = 0; index < historyArray.size(); ++index) {
                    QJsonObject obj = historyArray.at(index).toObject();
                    GlobalTrackingItem *item = GlobalTrackingItem::fromJsonObject(obj);
                    details->addHistoryItem(item);
                }
            }
        }
    }

    return details;
}

PostService GlobalCainiaoItem::postService()
{
    return _postService;
}

void GlobalCainiaoItem::setPostService(PostService postService)
{
    _postService = postService;
}

QString GlobalCainiaoItem::barcode()
{
    return _barcode;
}

void GlobalCainiaoItem::setBarcode(QString barcode)
{
    _barcode = barcode;
}

QString GlobalCainiaoItem::realBarcode()
{
    return _realBarcode;
}

void GlobalCainiaoItem::setRealBarcode(QString barcode)
{
    _realBarcode = barcode;
}

QString GlobalCainiaoItem::commonStatus()
{
    return _commonStatus;
}

void GlobalCainiaoItem::setCommonStatus(QString commonStatus)
{
    _commonStatus=commonStatus;
}

QString GlobalCainiaoItem::destinationCountryName()
{
    return _destinationCountryName;
}

void GlobalCainiaoItem::setDestinationCountryName(QString destinationCountryName)
{
    _destinationCountryName = destinationCountryName;
}

QString GlobalCainiaoItem::originCountryName()
{
    return _originCountryName;
}

void GlobalCainiaoItem::setOriginCountryName(QString originCountryName)
{
    _originCountryName = originCountryName;
}

QVariant GlobalCainiaoItem::trackingHistory() const
{
    return QVariant::fromValue(_trackingHistoryItemList);
}

QList<QObject*> GlobalCainiaoItem::historyItemList() const
{
    return _trackingHistoryItemList;
}

void GlobalCainiaoItem::addHistoryItem(GlobalTrackingItem *item)
{
    _trackingHistoryItemList.append(item);
}
