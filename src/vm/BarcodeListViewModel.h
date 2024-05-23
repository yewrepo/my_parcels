#ifndef BARCODELISTVIEWMODEL_H
#define BARCODELISTVIEWMODEL_H

#include <QObject>
#include "../db/LocalBase.h"
#include "../Updater.h"
#include "../UpdaterResult.h"

class BarcodeListViewModel : public QObject
{
    Q_OBJECT
public:
    explicit BarcodeListViewModel(LocalBase *localBase, Updater* updater, QObject *parent = nullptr);
    ~BarcodeListViewModel();

    Q_INVOKABLE void refreshAll();
    Q_INVOKABLE void fetchAll();
    Q_INVOKABLE void removeParcel(QString barcode);
    Q_INVOKABLE void setStatusChecked(QString barcode);

public slots:
    void storedTrackNumbers(QList<QObject*> list);
    void barcodeListChanged();
    void updaterCallback(LoadingStatus loadingState, UpdaterResult *result);

signals:
    void fetchStoredBarcodes(QList<QObject*> list);
    void storedListChanged();
    void loadingCallback(LoadingStatus loadingState, UpdaterResult *result);
private:
    LocalBase* _localBase;
    Updater* _updater;

};

#endif // BARCODELISTVIEWMODEL_H
