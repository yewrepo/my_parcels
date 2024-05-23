#ifndef CAINIAOTRACKINGITEM_H
#define CAINIAOTRACKINGITEM_H

#include <QObject>

class CainiaoTrackingItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString actionCode READ actionCode CONSTANT)
    Q_PROPERTY(QString desc READ desc CONSTANT)
    Q_PROPERTY(double timestamp READ timestamp CONSTANT)

public:

    explicit CainiaoTrackingItem(QObject *parent = nullptr);

    QString actionCode();
    void setActionCode(QString actionCode);

    QString desc();
    void setDesc(QString desc);

    double timestamp();
    void setTimestamp(double timestamp);

private:
    QString _actionCode;
    QString _desc;
    double _timestamp;
};

#endif // CAINIAOTRACKINGITEM_H
