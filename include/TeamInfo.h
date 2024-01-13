#ifndef TEAMINFO_H
#define TEAMINFO_H

#include <QWidget>
#include <QRadioButton>

#include "MatchData.h"

namespace Ui {
class TeamInfo;
}

class TeamInfo : public QWidget
{
    Q_OBJECT

private:
    MatchData m_matchData{};

public:
    explicit TeamInfo(QWidget *parent = nullptr);
    ~TeamInfo();

    int teamNumber();
    int matchNumber();

public slots:
    void setTeam();
    void setStation();

private:
    Ui::TeamInfo *ui;
    QMap<AllianceStation, QRadioButton *> m_buttonMap;
};

#endif // TEAMINFO_H
