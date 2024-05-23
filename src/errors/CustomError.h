#ifndef CUSTOMERROR_H
#define CUSTOMERROR_H

#include <QObject>
#include <QNetworkReply>
#include "CustomErrorType.h"

class CustomError: public QObject
{
    Q_OBJECT
public:
    explicit CustomError(QObject *parent = nullptr, ErrorType errorType = ErrorType::NETWORK);

    ErrorType getErrorType();
private:
    ErrorType _errorType;
};

#endif // CAINIAOREQUEST_H
