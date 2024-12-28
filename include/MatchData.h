#ifndef MATCHDATA_H
#define MATCHDATA_H

#include "Schedule.h"

class MatchData : public QObject
{
    Q_OBJECT
private:
    Schedule m_schedule = Schedule();
public:
    MatchData(QObject *parent);

    Schedule schedule();

    Q_INVOKABLE int getTeam(const QString &station, const int match);

#ifndef Q_OS_WASM
    Q_INVOKABLE void downloadSchedule(const QString &event);
signals:
    void successful();
    void failed();
    void failedWrite();
    void invalidCode();
#endif
public slots:
    void reloadSchedule();
};

#endif // MATCHDATA_H
