#include "TeamInfo.h"
#include <QDir>

#include <QKeyEvent>

#ifndef Q_OS_WASM
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QMessageBox>

#include "ui_TeamInfo.h"
#else
#include "ui_WebTeamInfo.h"
#endif

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

    connect(ui->teamNumber, &QSpinBox::valueChanged, this, &TeamInfo::teamNumberChanged);
}

#ifndef Q_OS_WASM
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
#endif

TeamInfo::~TeamInfo()
{
    delete ui;
}

void TeamInfo::config(const QJsonObject &obj)
{
    QPalette boxPalette = ui->initials->palette();
    boxPalette.setColor(QPalette::Window, obj.value("button").toString("#ff00ff"));
    boxPalette.setColor(QPalette::ButtonText, obj.value("buttonText").toString("#000000"));
    boxPalette.setColor(QPalette::Button, obj.value("button").toString("#ff00ff"));

    ui->initials->setPalette(boxPalette);
    ui->matchNumber->setPalette(boxPalette);
    ui->teamNumber->setPalette(boxPalette);
#ifndef Q_OS_WASM
    ui->event->setPalette(boxPalette);
    ui->pushButton->setPalette(boxPalette);
#endif
}

int TeamInfo::teamNumber() {
    return ui->teamNumber->value();
}

int TeamInfo::matchNumber() {
    return ui->matchNumber->value();
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

    emit stationChanged(station);

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

void TeamInfo::incrementMatch()
{
    ui->matchNumber->setValue(ui->matchNumber->value() + 1);
    setTeam();
}

void TeamInfo::decrementMatch()
{
    ui->matchNumber->setValue(ui->matchNumber->value() - 1);
    setTeam();
}

void TeamInfo::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Backspace) {
    }
}
