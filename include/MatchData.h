#ifndef MATCHDATA_H
#define MATCHDATA_H

#include "Schedule.h"

class MatchData : public QObject
{
    Q_OBJECT
private:
    Schedule m_schedule = Schedule();
public:
    MatchData();

    Schedule schedule();

public slots:
    void reloadSchedule();
};

#endif // MATCHDATA_H
