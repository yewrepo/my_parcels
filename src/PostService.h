#ifndef POSTSERVICE_H
#define POSTSERVICE_H

#include <QObject>

class ModelPostService : public QObject
{
    Q_OBJECT
public:

    explicit ModelPostService(QObject *parent = nullptr);
};

#endif // POSTSERVICE_H
