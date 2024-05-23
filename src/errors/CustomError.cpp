#include "CustomError.h"


CustomError::CustomError(QObject *parent, ErrorType errorType)
{
    _errorType = errorType;
}

ErrorType CustomError::getErrorType()
{
    return _errorType;
}
