#ifndef PARCELHISTORYITEM_H
#define PARCELHISTORYITEM_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>

class ParcelHistoryItem: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString description READ description CONSTANT)
    Q_PROPERTY(QString time READ time CONSTANT)
    Q_PROPERTY(QString optionalData READ optionalData CONSTANT)
public:
    explicit ParcelHistoryItem(QObject *parent = nullptr);

    QString description();
    void setDescription(QString description);

    QString time();
    void setTime(QString time);

    QString optionalData();
    void setOptionalData(QString optionalData);

    Q_INVOKABLE  QString getJson();

private:
    QString _description;
    QString _time;
    QString _optionalData;
};

#endif // PARCELHISTORYITEM_H
