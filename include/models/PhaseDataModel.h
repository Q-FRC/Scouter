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
    int columns;
    QStringList choices;
    int multiplier;
} PhaseData;

class PhaseDataModel : public QAbstractListModel
{
    Q_OBJECT

    int m_columns = 2;

public:
    enum PDMRoleTypes {
        TYPE = Qt::UserRole + 1,
        BUTTON,
        TEXTCOLOR,
        TEXT,
        MIN,
        MAX,
        IDX,
        COLUMNS,
        CHOICES,
        MULT
    };

    explicit PhaseDataModel(const QJsonObject &obj, QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    int columns() const;
    void setColumns(int newColumns);

signals:
    void columnsChanged();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<PhaseData> m_data;
    Q_PROPERTY(int columns READ columns WRITE setColumns NOTIFY columnsChanged FINAL)
};

#endif // PHASEDATAMODEL_H
