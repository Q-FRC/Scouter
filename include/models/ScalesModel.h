#ifndef SCALESMODEL_H
#define SCALESMODEL_H

#include <QAbstractListModel>
#include <QJsonArray>
#include <qqmlintegration.h>

typedef struct Scale {
    QString title;
    QString desc;
} Scale;

class ScalesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum SMRoleTypes {
        TITLE = Qt::UserRole + 1,
        DESC,
        IDX
    };

    explicit ScalesModel(const QJsonArray &array, QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Scale> m_data;
};
#endif // SCALESMODEL_H
