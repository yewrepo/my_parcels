#ifndef LOADINGSTATECLASS_H
#define LOADINGSTATECLASS_H

#include <QObject>

class LoadingStateClass
{
    Q_GADGET
public:
    enum Value {
        SUCCESS,
        LOADING,
        ERROR
    };
    Q_ENUM(Value)

private:
    explicit LoadingStateClass();
};

typedef LoadingStateClass::Value LoadingStatus;

#endif // LOADINGSTATECLASS_H
