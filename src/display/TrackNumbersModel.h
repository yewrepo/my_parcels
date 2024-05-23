#ifndef TASKNUMBERMODEL_H
#define TASKNUMBERMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <QList>
#include "../display/TrackNumberData.h"
#include "../PostServiceClass.h"

class TrackNumbersModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int size READ size CONSTANT)

public:
    enum Roles {
        Barcode = Qt::UserRole + 1,
        LastStatus,
        UserCaption,
        IsNewStatus,
        PostServiceCol
    };

    explicit TrackNumbersModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void removeItem(int index);
    Q_INVOKABLE void addItem(TrackNumberData *item);
    Q_INVOKABLE void addItem(QString number, QString lastStatus, QString userCaption, bool isNewStatus, PostService postService);
    Q_INVOKABLE void clear();

    int size() const;

private:
    QList<TrackNumberData*> _data;
};

#endif
