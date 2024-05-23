#include "CheckBarcodeViewModel.h"

CheckBarcodeViewModel::CheckBarcodeViewModel(LocalBase *localBase, QObject *parent) : QObject(parent)
{

    PostServiceListItem *item = new PostServiceListItem(parent);
    item->setPostService(PostService::RU_POCHTA);
    item->setCaption("Почта России");

    PostServiceListItem *item2 = new PostServiceListItem(parent);
    item2->setPostService(PostService::CAINIAO);
    item2->setCaption("Cainiao");

    PostServiceListItem *item3 = new PostServiceListItem(parent);
    item3->setPostService(PostService::GLOBAL_CAINIAO);
    item3->setCaption("Cainiao Global");

    _servicePostList.append(item);
    _servicePostList.append(item2);
    _servicePostList.append(item3);

    _requestManager = new RequestManager(this);
    _localBase = localBase;

    connect(_requestManager, &RequestManager::detailsReply, this, &CheckBarcodeViewModel::detailsReply);
    connect(_requestManager, &RequestManager::loadingStateCallback, this, &CheckBarcodeViewModel::loadingStateCallback);
}

void CheckBarcodeViewModel::checkBarcodeDetails()
{
    if (_details != nullptr && _storeIt){
        if (!_localBase->contains(_details->barcode())){
            if (_localBase->addParcel(_details)){
                emit gotNotification("Посылка добавлена для отслеживания");
            }else{
                emit gotNotification("Ошибка добавления посылки");
            }
        }else{
            emit gotNotification("Посылка уже добавлена");
        }
    }
}

ParcelDetails *CheckBarcodeViewModel::parcelDetails()
{
    return _details;
}

void CheckBarcodeViewModel::checkBarcode(bool storeIt)
{
    _storeIt = storeIt;
    _requestManager->getBarcodeData(_barcode, _selectedPostService);
}

void CheckBarcodeViewModel::changeCaption(QString newCaption)
{
    _localBase->changeCaption(_barcode, newCaption);
}

QList<QObject *> CheckBarcodeViewModel::servicePostList() const
{
    return _servicePostList;
}

void CheckBarcodeViewModel::setSelectedService(PostService service)
{
    _selectedPostService = service;
    QString serviceStr = QVariant::fromValue(_selectedPostService).toString();
    qDebug() << "setSelectedService: " << serviceStr;
}

void CheckBarcodeViewModel::setBarcode(QString barcode)
{
    _barcode = barcode;
}

void CheckBarcodeViewModel::detailsReply(ParcelDetails *details)
{
    _details = details;
    checkBarcodeDetails();
    emit gotDetails(details);
}

void CheckBarcodeViewModel::loadingStateCallback(LoadingStatus loadingState, CustomError *error)
{
    if (error == nullptr){
        emit gotLoadingState(loadingState, ErrorType::NONE);
    }else{
        emit gotLoadingState(loadingState, error->getErrorType());
    }
}
