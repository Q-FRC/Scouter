#ifndef CONFIG_H
#define CONFIG_H

#include "models/PhaseDataModel.h"
#include "models/ScalesModel.h"
#include <QJsonObject>
#include <QObject>
#include <QQmlEngine>

class ScouterConfig : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QJsonObject object READ object WRITE setObject NOTIFY objectChanged FINAL)
public:
    explicit ScouterConfig(QObject *parent = nullptr);

    QJsonObject object() const;
    void setObject(const QJsonObject &newObject);

    PhaseDataModel *autoModel() const;

    PhaseDataModel *teleModel() const;

    PhaseDataModel *endModel() const;

    ScalesModel *scalesModel() const;

signals:
    void objectChanged();

private:
    QJsonObject m_object;

    PhaseDataModel *m_autoModel;
    PhaseDataModel *m_teleModel;
    PhaseDataModel *m_endModel;
    ScalesModel *m_scalesModel;
};

#endif // CONFIG_H
