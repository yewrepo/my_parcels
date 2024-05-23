
#include "TrackNumbersModel.h"

TrackNumbersModel::TrackNumbersModel(QObject *parent): QAbstractListModel(parent)
{
    //not use
}

int TrackNumbersModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) return 0;
    return _data.size();
}

QVariant TrackNumbersModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();

    TrackNumberData *data = _data.at(index.row());

    switch (role) {
    case Barcode:
        return QVariant(data->barcode());
    case LastStatus:
        return QVariant(data->lastStatus());
    case UserCaption:
        return QVariant(data->userCaption());
    case IsNewStatus:
        return QVariant(data->isNewStatus());
    case PostServiceCol:
        return QVariant(data->postService());
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> TrackNumbersModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Barcode] = "barcodeNumber";
    roles[LastStatus] = "lastStatus";
    roles[UserCaption] = "userCaption";
    roles[IsNewStatus] = "isNewStatus";
    roles[PostServiceCol] = "postService";
    return roles;
}

void TrackNumbersModel::removeItem(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    _data.removeAt(index);
    endRemoveRows();
}

void TrackNumbersModel::addItem(TrackNumberData *item)
{
    beginInsertRows(QModelIndex(), _data.size(), _data.size());
    _data.append(item);
    endInsertRows();

    QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
    emit dataChanged(index, index);
}

void TrackNumbersModel::addItem(QString number, QString lastStatus, QString userCaption, bool isNewStatus, PostService postService)
{
    TrackNumberData *data = new TrackNumberData();
    data->setBarcode(number);
    data->setLastStatus(lastStatus);
    data->setUserCaption(userCaption);
    data->setIsNewStatus(isNewStatus);
    data->setPostService(postService);
    addItem(data);
}

int TrackNumbersModel::size() const
{
    return _data.size();
}

void TrackNumbersModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, _data.size());
    _data.clear();
    endRemoveRows();

    QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
    emit dataChanged(index, index);
}
