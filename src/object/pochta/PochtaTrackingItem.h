#ifndef TRACKINGHISTORYITEM_H
#define TRACKINGHISTORYITEM_H

#include <QObject>
#include <QDateTime>
#include <QJsonArray>
#include <QJsonObject>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QTimeZone>
#include <QDateTime>
#include <QJsonDocument>

class PochtaTrackingItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString date READ date CONSTANT)
    Q_PROPERTY(QString humanStatus READ humanStatus CONSTANT)
    Q_PROPERTY(int countryId READ countryId CONSTANT)
    Q_PROPERTY(int index READ index CONSTANT)
    Q_PROPERTY(QString cityName READ cityName CONSTANT)
    Q_PROPERTY(QString countryName READ countryName CONSTANT)
    Q_PROPERTY(QString countryCustomName READ countryCustomName CONSTANT)
    Q_PROPERTY(QString description READ description CONSTANT)
    Q_PROPERTY(int weight READ weight CONSTANT)
    Q_PROPERTY(bool isInInternationalTracking READ isInInternationalTracking CONSTANT)

public:
    explicit PochtaTrackingItem(QObject *parent = nullptr);

    static PochtaTrackingItem *fromJsonObject(QJsonObject object);

    QString date();
    void setDate(QString date);

    QString humanStatus();
    void setHumanStatus(QString humanStatus);

    int countryId();
    void setCountryId(int countryId);

    int index();
    void setIndex(int index);

    QString cityName();
    void setCityName(QString cityName);

    QString countryName();
    void setCountryName(QString countryName);

    QString countryCustomName();
    void setCountryCustomName(QString countryCustomName);

    QString description();
    void setDescription(QString description);

    int weight();
    void setWeight(int weight);

    bool isInInternationalTracking();
    void setIsInInternationalTracking(bool isInInternationalTracking);

    Q_INVOKABLE  QString getJson();

private:
    QString _date;
    QString _humanStatus;
    int _countryId;
    int _index;
    QString _cityName;
    QString _countryName;
    QString _countryCustomName;
    QString _description;
    int _weight;
    bool _isInInternationalTracking;
};

#endif // TRACKINGHISTORYITEM_H
