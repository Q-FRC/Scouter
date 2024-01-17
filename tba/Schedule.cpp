#include "Schedule.h"
#include "Match.h"

Schedule::Schedule(QJsonArray object) {
    for (QJsonValueRef ref : object) {
        Match match(ref.toObject());
        m_matches.append(match);

        m_numberLevelMap.insert(match.compLevel(), match.matchNumber());
    }
}

QList<Match> Schedule::matches() {
    return m_matches;
}

std::optional<Match> Schedule::getMatch(int matchNumber, CompLevel compLevel) {
    for (Match match : m_matches) {
        if (match.compLevel() == compLevel && match.matchNumber() == matchNumber) {
            return match;
        }
    }

    return std::nullopt;
}

QList<int> Schedule::matchesForLevel(CompLevel level) {
    return m_numberLevelMap.values(level);
}
