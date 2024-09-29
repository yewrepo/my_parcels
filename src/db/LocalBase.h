#ifndef LOCALBASE_H
#define LOCALBASE_H

#include "../PostServiceClass.h"
#include "../display/TrackNumberData.h"
#include "../display/ParcelDetails.h"

#include <QDebug>
#include <QObject>
#include <QtSql>

class LocalBase : public QObject
{
    Q_OBJECT

public:
    explicit LocalBase(QObject *parent = nullptr);

    void fetchAll();
    QList<TrackNumberData*> getAll();
    void changeCaption(QString barcode, QString userCaption);
    bool addParcel(ParcelDetails* details);
    bool updateParcel(ParcelDetails* details);
    bool removeParcel(QString barcode);
    bool contains(QString barcode);
    void setStatusChecked(QString barcode);
    int count();

signals:
    void storedTrackNumbers(QList<QObject* > list);
    void barcodeListChanged();

private:
    QString DB_NAME = "yewrepo_parcels";
    QString TABLE_NAME = "parcel_list";
    QString CREATE_TABLE_SQL = "create table "+TABLE_NAME+
            " (id integer primary key autoincrement, "
            "barcode varchar(50), "
            "userCaption varchar(255), "
            "lastStatus varchar(255), "
            "lastUpdate bigint, "
            "isNewStatus integer, "
            "postService varchar(100), "
            "externalId integer "
            ");";
    QString QUERY_ALL = "select * from " + TABLE_NAME + " order by lastUpdate DESC";
    QString COUNT_ALL = "select count(*) FROM " + TABLE_NAME;

    bool execQuery(QString query);
    bool addParcel(QString barcode, QString userCaption, QString lastStatus, qint64 lastUpdate, QString postService);

    QSqlQuery _query;
};

#endif // LOCALBASE_H
