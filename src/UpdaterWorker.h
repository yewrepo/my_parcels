#ifndef UPDATERWORKER_H
#define UPDATERWORKER_H

#include <QObject>
#include <QDebug>
#include "db/LocalBase.h"
#include "requests/RequestManager.h"
#include "display/TrackNumberData.h"
#include "errors/CustomError.h"

class UpdaterWorker : public QObject
{
    Q_OBJECT
public:
    explicit UpdaterWorker(QObject *parent = nullptr);
    ~UpdaterWorker();

private:
    void disconnectAll();

    QList<ParcelDetails*> resultList;
    int _processCount;
    int _errorCount;
    int _count;
    RequestManager* _requestManager;

public slots:
    void doWork(const QList<TrackNumberData*> &parameter);
    void detailsReply(ParcelDetails *details);
    void loadingStateCallback(LoadingStatus loadingState, CustomError *error = nullptr);
signals:
    void resultReady(const QList<ParcelDetails*> &list, int summary, int errors);
};

#endif // UPDATERWORKER_H
