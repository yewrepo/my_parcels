#ifndef POSTSERVICECLASS_H
#define POSTSERVICECLASS_H
#include <QObject>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

class PostServiceClass
{
    Q_GADGET

public:
    enum Value
    {
        RU_POCHTA,
        CAINIAO,
        GLOBAL_CAINIAO
    };
    Q_ENUM(Value)

    static PostServiceClass::Value getByName(QString name)
    {
        if ("RU_POCHTA" == name)
        {
            return RU_POCHTA;
        }
        else if ("GLOBAL_CAINIAO" == name)
        {
            return GLOBAL_CAINIAO;
        }
        else
        {
            return CAINIAO;
        }
    }

private:
    explicit PostServiceClass();
};

typedef PostServiceClass::Value PostService;

#endif // POSTSERVICECLASS_H
