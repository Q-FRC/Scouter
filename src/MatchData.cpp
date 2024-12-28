#include "MatchData.h"
#include <QFile>
#include <QJsonDocument>
#include <QDir>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>

MatchData::MatchData(QObject *parent)
    : QObject(parent) {
    reloadSchedule();
}

Schedule MatchData::schedule() {
    return m_schedule;
}

#ifndef Q_OS_WASM
void MatchData::downloadSchedule(const QString &event) {
    QDir targetDir = QDir::home();

    QNetworkRequest request = QNetworkRequest("https://www.thebluealliance.com/api/v3/event/" + event + "/matches/simple");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-TBA-Auth-Key", TBA_AUTH_KEY);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::readyRead, this, [this, targetDir, reply] {
        QByteArray data = reply->readAll();
        QFile file(targetDir.path() + "/schedule.json");

        if (reply->error() == QNetworkReply::AuthenticationRequiredError) {
            return;
        }

        if (data.contains("Error")) {
            emit invalidCode();
            return;
        }

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qCritical() << "Failed to write schedule to home directory.";
            emit failedWrite();
            return;
        }

        file.write(data);
        file.close();
        reloadSchedule();

        emit successful();
    });

    connect(reply, &QNetworkReply::errorOccurred, this, [this](QNetworkReply::NetworkError e) {
        if (e != QNetworkReply::ContentNotFoundError) {
            qCritical() << "General network error while downloading schedule:" << e;
            emit failed();
        }
    });

    connect(reply, &QNetworkReply::sslErrors, this, [this](QList<QSslError>) {
        qCritical() << "SSL error while downloading schedule";
        emit failed();
    });
}
#endif


int MatchData::getTeam(const QString &stationString, const int match)
{
    CompLevel level;
    AllianceStation station;

    level = CompLevel::Quals;

    std::optional<Match> matchObj;
    matchObj = m_schedule.getMatch(match, level);

    if (matchObj == std::nullopt) {
        return 0;
    }

    int stationNumber = QString(stationString.back()).toInt();
    bool isBlue = stationString.contains("Blue");
    if (isBlue) stationNumber += 3;

    QString team = matchObj.value().teamForStation((AllianceStation) stationNumber);

    return team.toInt();
}

void MatchData::reloadSchedule()
{
#ifdef Q_OS_WASM
    QFile file(":/Schedule");
#else
    QFile file(QDir::homePath() + "/schedule.json");
#endif

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "Failed to read schedule.";
    }

    QByteArray data = file.readAll();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    m_schedule = Schedule(doc.array());
}
