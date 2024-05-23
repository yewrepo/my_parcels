#ifndef TRACKNUMBERDATA_H
#define TRACKNUMBERDATA_H

#include <QString>
#include <QObject>
#include "../PostServiceClass.h"

class TrackNumberData : public QObject{

    Q_OBJECT

    Q_PROPERTY(QString barcode READ barcode CONSTANT)
    Q_PROPERTY(QString userCaption READ userCaption CONSTANT)
    Q_PROPERTY(QString lastStatus READ lastStatus CONSTANT)
    Q_PROPERTY(bool isNewStatus READ isNewStatus CONSTANT)
    Q_PROPERTY(PostService postService READ postService CONSTANT)

public:
    explicit TrackNumberData(QObject *parent = 0);

    QString barcode();
    void setBarcode(QString number);

    QString userCaption();
    void setUserCaption(QString userCaption);

    QString lastStatus();
    void setLastStatus(QString lastStatus);

    bool isNewStatus();
    void setIsNewStatus(bool isNewStatus);

    PostService postService();
    void setPostService(PostService postService);

private:
    QString _barcode;
    QString _userCaption;
    QString _lastStatus;
    bool _isNewStatus;
    PostService _postService;
};

#endif
