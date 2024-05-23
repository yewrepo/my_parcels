#include "BarcodeListViewModel.h"

BarcodeListViewModel::BarcodeListViewModel(LocalBase *localBase, Updater* updater, QObject *parent) : QObject(parent)
{
    _localBase = localBase;
    _updater = updater;
    connect(_localBase, &LocalBase::storedTrackNumbers, this, &BarcodeListViewModel::storedTrackNumbers);
    connect(_localBase, &LocalBase::barcodeListChanged, this, &BarcodeListViewModel::barcodeListChanged);
    connect(_updater, &Updater::updateStateCallback, this, &BarcodeListViewModel::updaterCallback);
}

BarcodeListViewModel::~BarcodeListViewModel()
{
    delete _localBase;
}

void BarcodeListViewModel::refreshAll()
{
    _updater->process();
}

void BarcodeListViewModel::fetchAll()
{
    _localBase->fetchAll();
}

void BarcodeListViewModel::removeParcel(QString barcode)
{
    _localBase->removeParcel(barcode);
}

void BarcodeListViewModel::setStatusChecked(QString barcode)
{
    _localBase->setStatusChecked(barcode);
}

void BarcodeListViewModel::storedTrackNumbers(QList<QObject*> list)
{
    emit fetchStoredBarcodes(list);
}

void BarcodeListViewModel::barcodeListChanged()
{
    emit storedListChanged();
}

void BarcodeListViewModel::updaterCallback(LoadingStatus loadingState, UpdaterResult *result)
{
    emit loadingCallback(loadingState, result);
}
