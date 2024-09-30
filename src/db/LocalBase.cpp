#include "LocalBase.h"

LocalBase::LocalBase(QString appFilesPath, QObject *parent) : QObject(parent)
{
    QSqlDatabase  dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName(appFilesPath + "/" + DB_NAME);

    if (!dbase.open()) {
        qDebug() << "open error";
    }else{

        _query = QSqlQuery(dbase);
        qDebug() << "open ok";
        qDebug() << "table number: "+ QString::number(dbase.tables().size());

        if (dbase.tables().contains(TABLE_NAME)){
            qDebug() << "Contains table: " + TABLE_NAME;
        }else{
            bool b = execQuery(CREATE_TABLE_SQL);
            if (!b) {
                qDebug() << "Create table error" << "error: " + _query.lastError().text();
            }
        }
    }
}

void LocalBase::fetchAll()
{
    QList<TrackNumberData*> barcodes = getAll();
    QList<QObject*> list;
    QListIterator<TrackNumberData*> iter(barcodes);

    while (iter.hasNext()){
        list.append(iter.next());
    }
    emit storedTrackNumbers(list);
}

QList<TrackNumberData*> LocalBase::getAll()
{
    QList<TrackNumberData*> list;

    bool selectSuccess = execQuery(QUERY_ALL);
    if (selectSuccess){
        QSqlRecord record = _query.record();
        QString barcode;
        QString userCaption;
        QString lastStatus;
        int isNewStatus;
        QString postServiceStr;

        while (_query.next()) {
            barcode = _query.value(record.indexOf("barcode")).toString();
            userCaption = _query.value(record.indexOf("userCaption")).toString();
            lastStatus = _query.value(record.indexOf("lastStatus")).toString();
            isNewStatus = _query.value(record.indexOf("isNewStatus")).toInt();
            postServiceStr = _query.value(record.indexOf("postService")).toString();

            qDebug() <<"upd " << _query.value(record.indexOf("postService")).toString();

            TrackNumberData *data = new TrackNumberData(this);
            data->setBarcode(barcode);
            data->setUserCaption(userCaption);
            data->setLastStatus(lastStatus);
            data->setIsNewStatus(isNewStatus == 1);
            data->setPostService(PostServiceClass::getByName(postServiceStr));

            list.append(data);
        }
    }
    return list;
}

void LocalBase::changeCaption(QString barcode, QString userCaption)
{
    if (contains(barcode)){
        QString query = QString("update %1 set userCaption = \"%2\" where barcode = \"%3\"").arg(TABLE_NAME, userCaption, barcode);
        bool isSuccess = execQuery(query);
        if (isSuccess){
            emit barcodeListChanged();
        }
    }
}

bool LocalBase::addParcel(QString barcode, QString userCaption, QString lastStatus, qint64 lastUpdate, QString postService)
{
    QString time = QString::number(lastUpdate);
    QString query =
            QString("insert into %1(barcode, userCaption, lastStatus, isNewStatus, lastUpdate, postService) values (\"%2\", \"%3\", \"%4\", 1, %5, \"%6\")")
            .arg(TABLE_NAME, barcode, userCaption, lastStatus, time, postService);
    bool insertSuccess = execQuery(query);
    fetchAll();
    return insertSuccess;
}

bool LocalBase::addParcel(ParcelDetails *details)
{
    QString postServiceName = QVariant::fromValue(details->postService()).toString();
    return addParcel(details->barcode(), details->title(), details->commonStatus(), details->lastUpdate(), postServiceName);
}

bool LocalBase::updateParcel(ParcelDetails *details)
{
    bool selectSuccess = execQuery(QString("select * from %1 where barcode = \"%2\"").arg(TABLE_NAME, details->barcode()));
    if (selectSuccess){
        QSqlRecord record = _query.record();
        QString lastStatus;
        if (_query.first()) {
            lastStatus = _query.value(record.indexOf("lastStatus")).toString();
            bool isNewStatus = lastStatus != details->commonStatus();
            qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
            if (isNewStatus){
                QString updateQuery = QString("update %1 set lastStatus = \"%2\", isNewStatus = %3, lastUpdate = %4 where barcode = \"%4\"")
                        .arg(TABLE_NAME, details->commonStatus(), isNewStatus ? "1" : "0", QString::number(currentTime), details->barcode());
                bool isSuccess = execQuery(updateQuery);
                if (isSuccess){
                    qInfo() << "update record: " << details->barcode();
                }
                return isSuccess;
            }
        }
    }
    return false;
}

bool LocalBase::removeParcel(QString barcode)
{
    QString query = QString("delete from %1 where barcode = \"%2\"").arg(TABLE_NAME, barcode);
    bool removeSuccess = execQuery(query);
    return removeSuccess;
}

bool LocalBase::contains(QString barcode)
{
    QString query = QString("select * from %1 where barcode = \"%2\"").arg(TABLE_NAME, barcode);
    bool selectSuccess = execQuery(query);
    if (selectSuccess){
        QSqlRecord record = _query.record();
        qDebug() << "find records: " + QString::number(record.count());
        return _query.first();
    }
    return false;
}

void LocalBase::setStatusChecked(QString barcode)
{
    if (contains(barcode)){
        QString query = QString("update %1 set isNewStatus = 0 where barcode = \"%2\"").arg(TABLE_NAME, barcode);
        bool isSuccess = execQuery(query);
        if (isSuccess){
            emit barcodeListChanged();
        }
    }
}

int LocalBase::count()
{
    bool isSuccess = execQuery(COUNT_ALL);
    if (isSuccess && _query.first()){
        int count = _query.value(0).toInt();
        return count;
    }
    return 0;
}

bool LocalBase::execQuery(QString query)
{
    bool success = _query.exec(query);
    if (!success){
        qDebug() << "error in: " << query << "message: " + _query.lastError().text();
    }
    return success;
}
