#ifndef MATCH_H
#define MATCH_H

#include <QMap>
#include <QJsonObject>

enum class AllianceStation {
    Red1 = 1,
    Red2 = 2,
    Red3 = 3,
    Blue1 = 4,
    Blue2 = 5,
    Blue3 = 6,
    Invalid = 0
};

enum class CompLevel {
    Quals = 0,
    Semifinals = 1,
    Finals = 2
};

static const QMap<QString, CompLevel> CompLevelMap = {
    {"qm", CompLevel::Quals},
    {"sf", CompLevel::Semifinals},
    {"f", CompLevel::Finals}
};

class Match
{
    QMap<QString, AllianceStation> m_teamMap;

    int m_matchNumber;
    CompLevel m_compLevel;
public:
    Match() = default;
    Match(QJsonObject object);

    AllianceStation stationForTeam(const QString &team);
    QString teamForStation(const AllianceStation &station);

    void fromTBA(const QJsonObject &object);
    QJsonObject toJson();

    int matchNumber();
    CompLevel compLevel();
};

#endif // MATCH_H
