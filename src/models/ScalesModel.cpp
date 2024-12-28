#include "models/ScalesModel.h"

#include <QJsonObject>

ScalesModel::ScalesModel(const QJsonArray &array, QObject *parent)
    : QAbstractListModel(parent)
{
    for (QJsonValueConstRef ref : array) {
        QJsonObject obj = ref.toObject();

        Scale data;

        data.title = obj.value("title").toString("");
        data.desc = obj.value("desc").toString("");

        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_data << data;
        endInsertRows();
    }
}

int ScalesModel::rowCount(const QModelIndex &parent) const
{
    return m_data.count();
}

QVariant ScalesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    Scale s = m_data[index.row()];

    switch (role) {
    case TITLE:
        return s.title;
    case DESC:
        return s.desc;
    default:
        return index.row();
    }
}

QHash<int, QByteArray> ScalesModel::roleNames() const
{
    QHash<int,QByteArray> rez;
    rez[TITLE] = "title";
    rez[DESC] = "desc";
    rez[IDX] = "idx";

    return rez;
}
