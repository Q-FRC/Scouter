#include "Config.h"

#include <QDir>
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

    m_autoModel = new PhaseDataModel(pages.value("auto").toObject(), this);
    m_teleModel = new PhaseDataModel(pages.value("tele").toObject(), this);
    m_endModel = new PhaseDataModel(pages.value("end").toObject(), this);
    m_scalesModel = new ScalesModel(pages.value("scales").toArray(), this);

#if !defined(Q_OS_WASM) && !defined(Q_OS_ANDROID)
    saveCsv();
#endif
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

#if !defined(Q_OS_WASM) && !defined(Q_OS_ANDROID)
void ScouterConfig::saveCsv() const
{
    QStringList csv;
    csv << "Scouter Initials"
        << "Match Number"
        << "Team Number";

    QJsonObject pages = m_object.value("pages").toObject();
    QJsonArray autoPage = pages.value("auto").toArray();
    QJsonArray telePage = pages.value("tele").toArray();
    QJsonArray scalesPage = pages.value("scales").toArray();

    for (QJsonValueConstRef ref : autoPage) {
        csv << ("Auto " + ref.toObject().value("text").toString());
    }

    for (QJsonValueConstRef ref : telePage) {
        csv << ("Teleop " + ref.toObject().value("text").toString());
    }

    for (QJsonValueConstRef ref : scalesPage) {
        csv << ref.toObject().value("title").toString();
    }

    // save to home directory for easy access
    QDir home = QDir::home();
    QFile file(home.absoluteFilePath("data.csv"));

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qCritical() << "Failed to write CSV.";
    } else {
        file.write(csv.join(",").toUtf8());
        file.close();
    }
}
#endif

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
