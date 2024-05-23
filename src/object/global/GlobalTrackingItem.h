#ifndef GLOBALTRACKINGITEM_H
#define GLOBALTRACKINGITEM_H

#include <QObject>
#include <QJsonObject>

class GlobalTrackingItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString actionCode READ actionCode CONSTANT)
    Q_PROPERTY(QString desc READ desc CONSTANT)
    Q_PROPERTY(QString date READ date CONSTANT)
    Q_PROPERTY(QString timezone READ timezone CONSTANT)

public:
    explicit GlobalTrackingItem(QObject *parent = nullptr);

    static GlobalTrackingItem *fromJsonObject(QJsonObject object);

    QString actionCode();
    void setActionCode(QString actionCode);

    QString desc();
    void setDesc(QString desc);

    QString date();
    void setDate(QString date);

    QString timezone();
    void setTimezone(QString timezone);

private:
    QString _actionCode;
    QString _desc;
    QString _date;
    QString _timezone;
};

#endif // GLOBALTRACKINGITEM_H
