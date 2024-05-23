
#include "TrackNumberData.h"

TrackNumberData::TrackNumberData(QObject *parent) : QObject(parent){
    //not use
}

QString TrackNumberData::barcode()
{
    return _barcode;
}

void TrackNumberData::setBarcode(QString barcode)
{
    _barcode = barcode;
}

QString TrackNumberData::userCaption()
{
    return _userCaption;
}

void TrackNumberData::setUserCaption(QString userCaption)
{
    _userCaption = userCaption;
}

QString TrackNumberData::lastStatus()
{
    return _lastStatus;
}

void TrackNumberData::setLastStatus(QString lastStatus)
{
    _lastStatus = lastStatus;
}

bool TrackNumberData::isNewStatus()
{
    return _isNewStatus;
}

void TrackNumberData::setIsNewStatus(bool isNewStatus)
{
    _isNewStatus = isNewStatus;
}

PostService TrackNumberData::postService()
{
    return _postService;
}

void TrackNumberData::setPostService(PostService postService)
{
    _postService = postService;
}
