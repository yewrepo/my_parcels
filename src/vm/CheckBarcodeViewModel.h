#ifndef CHECKBARCODEVIEWMODEL_H
#define CHECKBARCODEVIEWMODEL_H

#include <QObject>
#include <QDebug>
#include "../requests/RuPochtaRequest.h"
#include "../requests/RequestManager.h"
#include "../display/TrackNumbersModel.h"
#include "../display/TrackNumberData.h"
#include "../db/LocalBase.h"
#include "../errors/CustomError.h"
#include "../LoadingStateClass.h"
#include "../PostServiceClass.h"
#include "PostServiceListItem.h"

class CheckBarcodeViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<QObject *> servicePostList READ servicePostList CONSTANT)
    Q_PROPERTY(ParcelDetails* parcelDetails READ parcelDetails CONSTANT)

public:
    explicit CheckBarcodeViewModel(LocalBase *localBase, QObject *parent = nullptr);

    Q_INVOKABLE void checkBarcode(bool storeIt);
    Q_INVOKABLE void changeCaption(QString newCaption);
    Q_INVOKABLE void setSelectedService(PostService service);
    Q_INVOKABLE void setBarcode(QString barcode);

    Q_INVOKABLE QList<QObject *> servicePostList() const;

private:
    Q_DISABLE_COPY(CheckBarcodeViewModel)

    void checkBarcodeDetails();

    ParcelDetails* parcelDetails();

    QList<QObject*> _servicePostList;
    QString _barcode;
    PostService _selectedPostService = PostService::RU_POCHTA;

    bool _storeIt;
    RequestManager *_requestManager;
    LocalBase *_localBase;
    ParcelDetails *_details;

public slots:
    void detailsReply(ParcelDetails *details);
    void loadingStateCallback(LoadingStatus loadingState, CustomError *error = nullptr);

signals:
    void gotDetails(ParcelDetails *details);
    void gotLoadingState(LoadingStatus loadingState, ErrorType errorType);
    void gotNotification(QString message);
};

#endif // CHECKBARCODEVIEWMODEL_H
