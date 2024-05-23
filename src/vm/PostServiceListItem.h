#ifndef POSTSERVICELISTITEM_H
#define POSTSERVICELISTITEM_H

#include <QObject>
#include "../PostServiceClass.h"

class PostServiceListItem: public QObject{
    Q_OBJECT

    Q_PROPERTY(int postService READ postService CONSTANT)
    Q_PROPERTY(QString caption READ caption CONSTANT)

public:
    explicit PostServiceListItem(QObject *parent = nullptr) : QObject(parent){

    }

    int postService(){
        return _postSercvice;
    }

    void setPostService(int postService){
        _postSercvice = postService;
    }

    QString caption(){
        return _caption;
    }

    void setCaption(QString caption){
        _caption = caption;
    }

private:
    int _postSercvice;
    QString _caption;
};

#endif // POSTSERVICELISTITEM_H
