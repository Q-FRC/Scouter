#include "Config.h"

#include <QFile>
#include <QJsonDocument>

ScouterConfig::ScouterConfig(QObject *parent)
    : QObject{parent}
{
    QFile file(":/config");
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "Failed to open config file.";
        std::exit(1);
    }

    QByteArray data = file.readAll();

    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    m_object = doc.object();

    QJsonObject pages = m_object.value("pages").toObject();

    m_autoModel = new PhaseDataModel(pages.value("auto").toArray(), this);
    m_teleModel = new PhaseDataModel(pages.value("tele").toArray(), this);
    m_endModel = new PhaseDataModel(pages.value("end").toArray(), this);
    m_scalesModel = new ScalesModel(pages.value("scales").toArray(), this);
}

QJsonObject ScouterConfig::object() const
{
    return m_object;
}

void ScouterConfig::setObject(const QJsonObject &newObject)
{
    if (m_object == newObject)
        return;
    m_object = newObject;
    emit objectChanged();
}

PhaseDataModel *ScouterConfig::autoModel() const
{
    return m_autoModel;
}

PhaseDataModel *ScouterConfig::teleModel() const
{
    return m_teleModel;
}

PhaseDataModel *ScouterConfig::endModel() const
{
    return m_endModel;
}

ScalesModel *ScouterConfig::scalesModel() const
{
    return m_scalesModel;
}
