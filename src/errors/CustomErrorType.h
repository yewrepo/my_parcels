#ifndef CUSTOMERRORTYPE_H
#define CUSTOMERRORTYPE_H
#include <QObject>
#include <QtQuick>

class CustomErrorTypeClass
{
    Q_GADGET
public:
    enum Value {
        NONE,
        NETWORK,
        EMPTY_RESPONSE,
        WRONG_SERVICE
    };
    Q_ENUM(Value)

    static void init() {
        qRegisterMetaType<CustomErrorTypeClass::Value>("ErrorType");
        qmlRegisterUncreatableType<CustomErrorTypeClass>("ru.yewrepo.myparcels", 1, 0, "ErrorType", "Enum type");
    }
private:
    explicit CustomErrorTypeClass();

};

typedef CustomErrorTypeClass::Value ErrorType;

#endif // CUSTOMERRORTYPE_H
