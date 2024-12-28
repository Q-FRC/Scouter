#ifndef PHASEDATAMODEL_H
#define PHASEDATAMODEL_H

#include <QAbstractListModel>
#include <QJsonArray>
#include <qqmlintegration.h>

typedef struct PhaseData {
    QString type;
    QString buttonColor;
    QString textColor;
    QString text;
    int min;
    int max;
} PhaseData;

class PhaseDataModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum PDMRoleTypes {
        TYPE = Qt::UserRole + 1,
        BUTTON,
        TEXTCOLOR,
        TEXT,
        MIN,
        MAX,
        IDX
    };

    explicit PhaseDataModel(const QJsonArray &array, QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<PhaseData> m_data;
};

#endif // PHASEDATAMODEL_H
