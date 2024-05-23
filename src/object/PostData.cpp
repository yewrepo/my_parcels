#include "PostData.h"

PostData::PostData(QByteArray part, QNetworkRequest request)
{
    _part = part;
    _request = request;
}

QByteArray PostData::getPart()
{
    return _part;
}

QNetworkRequest PostData::getRequest()
{
    return _request;
}
