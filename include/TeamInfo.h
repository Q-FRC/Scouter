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

    void keyPressEvent(QKeyEvent *event);

public:
    explicit TeamInfo(QWidget *parent = nullptr);
    ~TeamInfo();

    int teamNumber();
    int matchNumber();

    QString initials();

public slots:
    void setTeam();
    void setStation();
    void incrementMatch();
    void decrementMatch();

#ifndef Q_OS_WASM
    void downloadSchedule();

signals:
    void reloadSchedule();
#else
signals:
#endif
    void teamNumberChanged(int team);

private:
    Ui::TeamInfo *ui;

    QMap<AllianceStation, QRadioButton *> m_buttonMap;
};

#endif // TEAMINFO_H
