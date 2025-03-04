#include "models/PhaseDataModel.h"

#include <QJsonObject>

int PhaseDataModel::columns() const
{
    return m_columns;
}

void PhaseDataModel::setColumns(int newColumns)
{
    if (m_columns == newColumns)
        return;
    m_columns = newColumns;
    emit columnsChanged();
}

PhaseDataModel::PhaseDataModel(const QJsonObject &obj, QObject *parent)
    : QAbstractListModel(parent)
{
    m_columns = obj.value("columns").toInt(2);

    QJsonArray array = obj.value("data").toArray();
    for (QJsonValueConstRef ref : array) {
        QJsonObject obj = ref.toObject();

        PhaseData data;

        data.type = obj.value("type").toString("int");
        data.buttonColor = obj.value("color").toString("#aa0000");
        data.textColor = obj.value("textColor").toString("#dedede");
        data.text = obj.value("text").toString("Label");
        data.min = obj.value("min").toInt(0);
        data.max = obj.value("max").toInt(99);
        data.columns = obj.value("columns").toInt(1);
        data.choices = obj.value("choices").toVariant().toStringList();
        data.multiplier = obj.value("multiplier").toInt(1);

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
    case COLUMNS:
        return p.columns;
    case CHOICES:
        return p.choices;
    case MULT:
        return p.multiplier;
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
    rez[COLUMNS] = "columns";
    rez[CHOICES] = "choices";
    rez[MULT] = "multiplier";

    return rez;
}
