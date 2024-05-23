#include "UpdaterWorker.h"

UpdaterWorker::UpdaterWorker(QObject *parent) : QObject(parent)
{
}

UpdaterWorker::~UpdaterWorker()
{
    disconnectAll();
}

void UpdaterWorker::disconnectAll()
{
    disconnect(_requestManager, &RequestManager::detailsReply, 0, 0);
    disconnect(_requestManager, &RequestManager::loadingStateCallback, 0, 0);
}

void UpdaterWorker::doWork(const QList<TrackNumberData*> &parameter)
{
    qDebug() << "doWork: " << parameter;
    resultList.clear();
    _processCount = 0;
    _errorCount = 0;
    _count = parameter.size();
    _requestManager = new RequestManager(this);
    connect(_requestManager, &RequestManager::detailsReply, this, &UpdaterWorker::detailsReply);
    connect(_requestManager, &RequestManager::loadingStateCallback, this, &UpdaterWorker::loadingStateCallback);
    for (int index = 0; index < parameter.size(); ++index) {
        TrackNumberData* data = parameter.at(index);
        _requestManager->getBarcodeData(data->barcode(), data->postService());
    }
}

void UpdaterWorker::detailsReply(ParcelDetails *details)
{
    _processCount++;
    resultList.append(details);
    qDebug() << "detailsReply: " << details->barcode();
    if (_processCount == _count){
        disconnectAll();
        emit resultReady(resultList, _count, _errorCount);
    }
}

void UpdaterWorker::loadingStateCallback(LoadingStatus loadingState, CustomError *error)
{
    if (loadingState == LoadingStatus::ERROR && error != nullptr){
        _processCount++;
        _errorCount++;
          qDebug() << "loadingStateCallback: ERROR";
        if (_processCount == _count){
            disconnectAll();
            emit resultReady(resultList, _count, _errorCount);
        }
    }
}
