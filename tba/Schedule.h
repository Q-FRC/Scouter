#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QJsonArray>
#include <QList>

#include "Match.h"

class Schedule
{
private:
    QList<Match> m_matches;
    QMultiMap<CompLevel, int> m_numberLevelMap;
public:
    Schedule() = default;
    Schedule(QJsonArray object);

    QList<Match> matches();

    void fromTBA(const QJsonDocument &doc);

    QJsonDocument toJson();

    std::optional<Match> getMatch(int matchNumber, CompLevel compLevel);

    QList<int> matchesForLevel(CompLevel level);
};

#endif // SCHEDULE_H
