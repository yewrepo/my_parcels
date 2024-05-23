#include "UpdaterResult.h"

UpdaterResult::UpdaterResult(QObject *parent): QObject(parent)
{

}

UpdaterResult *UpdaterResult::create(int summary, int error)
{
    UpdaterResult *result = new UpdaterResult();
    result->_summaryCount = summary;
    result->_errorCount = error;
    return result;
}

int UpdaterResult::getSummaryCount()
{
    return _summaryCount;
}

int UpdaterResult::getErrorCount()
{
    return _errorCount;
}
