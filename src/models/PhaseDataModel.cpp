#include "models/PhaseDataModel.h"

#include <QJsonObject>

PhaseDataModel::PhaseDataModel(const QJsonArray &array, QObject *parent)
    : QAbstractListModel(parent)
{
    for (QJsonValueConstRef ref : array) {
        QJsonObject obj = ref.toObject();

        PhaseData data;

        data.type = obj.value("type").toString("int");
        data.buttonColor = obj.value("color").toString("#aa0000");
        data.textColor = obj.value("textColor").toString("#dedede");
        data.text = obj.value("text").toString("Label");
        data.min = obj.value("min").toInt(0);
        data.max = obj.value("max").toInt(99);

        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_data << data;
        endInsertRows();
    }
}

int PhaseDataModel::rowCount(const QModelIndex &parent) const
{
    return m_data.count();
}

QVariant PhaseDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    PhaseData p = m_data[index.row()];

    switch (role) {
    case TYPE:
        return p.type;
    case BUTTON:
        return p.buttonColor;
    case TEXTCOLOR:
        return p.textColor;
    case TEXT:
        return p.text;
    case MIN:
        return p.min;
    case MAX:
        return p.max;
    default:
        return index.row();
    }
}

QHash<int, QByteArray> PhaseDataModel::roleNames() const
{
    QHash<int,QByteArray> rez;
    rez[TYPE] = "type";
    rez[BUTTON] = "buttonColor";
    rez[TEXTCOLOR] = "textColor";
    rez[TEXT] = "text";
    rez[MIN] = "min";
    rez[MAX] = "max";
    rez[IDX] = "idx";

    return rez;
}
