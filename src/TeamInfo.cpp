#include "TeamInfo.h"
#include "ui_TeamInfo.h"

#include <QDir>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QMessageBox>

#include <QKeyEvent>

TeamInfo::TeamInfo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TeamInfo)
{
    ui->setupUi(this);

    m_buttonMap.insert(AllianceStation::Red1, ui->red1);
    m_buttonMap.insert(AllianceStation::Red2, ui->red2);
    m_buttonMap.insert(AllianceStation::Red3, ui->red3);
    m_buttonMap.insert(AllianceStation::Blue1, ui->blue1);
    m_buttonMap.insert(AllianceStation::Blue2, ui->blue2);
    m_buttonMap.insert(AllianceStation::Blue3, ui->blue3);
}

TeamInfo::~TeamInfo()
{
    delete ui;
}

int TeamInfo::teamNumber() {
    return ui->teamNumber->value();
}

int TeamInfo::matchNumber() {
    return ui->matchNumber->value();
}

void TeamInfo::downloadSchedule() {
    QString eventCode = ui->event->text();

    QDir targetDir = QDir::home();

    QNetworkRequest request = QNetworkRequest("https://www.thebluealliance.com/api/v3/event/" + eventCode + "/matches/simple");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-TBA-Auth-Key", TBA_AUTH_KEY);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::readyRead, this, [this, targetDir, reply] {
        QByteArray data = reply->readAll();
        QFile file(targetDir.path() + "/schedule.json");

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qCritical() << "badness";
        }

        file.write(data);
        file.close();
        m_matchData.reloadSchedule();
    });

    connect(reply, &QNetworkReply::errorOccurred, this, [this](QNetworkReply::NetworkError) {
        QMessageBox::critical(this, "Network Error", "A critical network error occurred; check to make sure you're connected and the event code is correct.");
    });

    connect(reply, &QNetworkReply::sslErrors, this, [this](QList<QSslError>) {
        QMessageBox::critical(this, "Network Error", "A critical network error occurred; check to make sure you're connected and the event code is correct.");
    });
}

QString TeamInfo::initials() {
    return ui->initials->text();
}

void TeamInfo::setTeam() {
    int matchNumber = ui->matchNumber->value();
    if (matchNumber == 0) return;

    CompLevel level;
    AllianceStation station;

    level = CompLevel::Quals;

    QMapIterator iter(m_buttonMap);
    while (iter.hasNext()) {
        iter.next();
        if (iter.value()->isChecked()) station = iter.key();
    }

    std::optional<Match> match;
    match = m_matchData.schedule().getMatch(matchNumber, level);

    if (match == std::nullopt) {
        return;
    }

    QString team = match.value().teamForStation(station);

    ui->teamNumber->setValue(team.toInt());
}

void TeamInfo::setStation() {
    QString team = ui->teamNumber->text();
    if (team == "0") return;

    int matchNumber = ui->matchNumber->value();
    if (matchNumber == 0) return;

    CompLevel level;

    level = CompLevel::Quals;

    std::optional<Match> match;
    match = m_matchData.schedule().getMatch(matchNumber, level);

    if (match == std::nullopt) {
        return;
    }

    AllianceStation station = match.value().stationForTeam(team);

    if (station == AllianceStation::Invalid) return;
    m_buttonMap.value(station)->setChecked(true);
}

void TeamInfo::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Backspace) {
        qDebug() << "nuhuh";
    }
}
