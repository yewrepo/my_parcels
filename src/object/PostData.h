#ifndef POSTDATA_H
#define POSTDATA_H

#include <QObject>
#include <QUrl>
#include <QHttpMultiPart>

class PostData
{
    Q_GADGET
public:
    explicit PostData(QByteArray part, QNetworkRequest request);

    QByteArray getPart();
    QNetworkRequest getRequest();
private:
    QByteArray _part;
    QNetworkRequest _request;
};

#endif // POSTDATA_H
