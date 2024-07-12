#include "MatchData.h"
#include <QFile>
#include <QJsonDocument>
#include <QDir>

MatchData::MatchData() {
    QFile file(":/Schedule");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "Bruh";
    }

    QByteArray data = file.readAll();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    m_schedule = Schedule(doc.array());

}

Schedule MatchData::schedule() {
    return m_schedule;
}
