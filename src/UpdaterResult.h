#ifndef UPDATERRESULT_H
#define UPDATERRESULT_H

#include <QObject>

class UpdaterResult : public QObject
{
    Q_OBJECT
public:
    explicit UpdaterResult(QObject *parent = nullptr);

    static UpdaterResult *create(int summary, int error);

    Q_INVOKABLE int getSummaryCount();
    Q_INVOKABLE int getErrorCount();
private:
    int _summaryCount;
    int _errorCount;
};

#endif // UPDATERRESULT_H
