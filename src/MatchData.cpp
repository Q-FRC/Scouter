#include "MatchData.h"
#include <QFile>
#include <QJsonDocument>
#include <QDir>

MatchData::MatchData() {
    reloadSchedule();
}

Schedule MatchData::schedule() {
    return m_schedule;
}

void MatchData::reloadSchedule()
{
#ifdef Q_OS_WASM
    QFile file(":/Schedule");
#else
    QFile file(QDir::homePath() + "/schedule.json");
#endif

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "Bruh";
    }

    QByteArray data = file.readAll();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    m_schedule = Schedule(doc.array());
}
