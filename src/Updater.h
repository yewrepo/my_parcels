#ifndef UPDATER_H
#define UPDATER_H

#include <QtConcurrent/QtConcurrent>
#include <QThread>
#include <QObject>
#include <QDebug>
#include "requests/RequestManager.h"
#include "display/TrackNumberData.h"
#include "db/LocalBase.h"
#include "UpdaterWorker.h"
#include "UpdaterResult.h"

class Updater: public QObject
{
    Q_OBJECT
    QThread workerThread;
public:
    explicit Updater(LocalBase *localBase, QObject *parent = nullptr);
    ~Updater();

    void process();

public slots:
    void handleResults(const QList<ParcelDetails*> &details, int summary, int errors);

signals:
    void operate(const QList<TrackNumberData*> &parameter);
    void updateStateCallback(LoadingStatus loadingState, UpdaterResult *result);

private:
    void connectAll();
    void disconnectAll();
    LocalBase* _localBase;
    UpdaterWorker* _worker;
};

#endif // UPDATER_H
