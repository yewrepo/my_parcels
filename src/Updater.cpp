#include "Updater.h"

Updater::Updater(LocalBase *localBase, QObject *parent) : QObject(parent)
{
    _localBase = localBase;

    _worker = new UpdaterWorker();
    _worker->moveToThread(&workerThread);
    connectAll();
    workerThread.start();
}

Updater::~Updater()
{
    disconnectAll();
}

void Updater::process()
{
    emit updateStateCallback(LoadingStatus::LOADING, nullptr);
    QList<TrackNumberData*> list = _localBase->getAll();

    qDebug() << "list count: " << list.size();

    emit operate(list);
}

void Updater::handleResults(const QList<ParcelDetails*> &details, int summary, int errors)
{
    qDebug() << "handleResults: " << details.size() << "; summary/errors" << summary <<"/"<<errors;
    for (int index = 0; index < details.size(); ++index) {
        //сделать апдейт
        _localBase->updateParcel(details.at(index));
    }
    emit updateStateCallback(LoadingStatus::SUCCESS, UpdaterResult::create(summary, errors));
}

void Updater::connectAll()
{
    connect(&workerThread, &QThread::finished, _worker, &QObject::deleteLater);
    connect(this, &Updater::operate, _worker, &UpdaterWorker::doWork);
    connect(_worker, &UpdaterWorker::resultReady, this, &Updater::handleResults);
}

void Updater::disconnectAll()
{
    disconnect(&workerThread);
    disconnect(this);
    disconnect(_worker);
    _worker->deleteLater();
    workerThread.quit();
    workerThread.wait();
}
