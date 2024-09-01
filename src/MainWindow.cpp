#include "MainWindow.h"

#include <QKeyEvent>

#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pages = {
        ui->welcome,
        ui->teamInfo,
        ui->autoScouting,
        ui->teleScouting,
        ui->notes,
        ui->scales,
        ui->qrcode
    };

    QFile file(":/config");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "sad";
    }

    QByteArray data = file.readAll();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    QJsonObject obj = doc.object();

    ui->welcome->config(obj);
    ui->teamInfo->config(obj);
    ui->autoScouting->config(false, obj);
    ui->teleScouting->config(true, obj);
    ui->scales->config(obj);
    ui->qrcode->config(obj);

    QPalette main = this->palette();
    main.setColor(QPalette::Window, obj.value("backgroundColor").toString("#000000"));
    main.setColor(QPalette::Base, obj.value("backgroundColor").toString("#000000"));
    main.setColor(QPalette::Text, obj.value("textColor").toString("#000000"));
    main.setColor(QPalette::WindowText, obj.value("textColor").toString("#000000"));
    main.setColor(QPalette::Button, obj.value("button").toString("#ff00ff"));
    main.setColor(QPalette::ButtonText, obj.value("buttonText").toString("#000000"));

    this->setPalette(main);

    connect(ui->qrcode, &QRCode::backButtonPressed, this, &MainWindow::backToStart);
    connect(ui->teamInfo, &TeamInfo::teamNumberChanged, this, [this](int team) {
        ui->team->setText("Your Team: " + QString::number(team));
    });

    connect(ui->teamInfo, &TeamInfo::stationChanged, this, [this](AllianceStation station) {
        QString text = "";
        QString color = "#ff0000";
        switch (station) {
        case AllianceStation::Red1:
            text = "Red 1";
            break;
        case AllianceStation::Red2:
            text = "Red 2";
            break;
        case AllianceStation::Red3:
            text = "Red 3";
            break;
        case AllianceStation::Blue1:
            text = "Blue 1";
            color = "#0000ff";
            break;
        case AllianceStation::Blue2:
            text = "Blue 2";
            color = "#0000ff";
            break;
        case AllianceStation::Blue3:
            text = "Blue 3";
            color = "#0000ff";
            break;
        case AllianceStation::Invalid:
            text = "";
            break;
        }

        ui->station->setText(text);

        QPalette p = ui->station->palette();
        p.setColor(QPalette::WindowText, color);

        ui->station->setPalette(p);
    });

    connect(ui->welcome, &WelcomePage::backToQRCode, this, &MainWindow::backToQRCode);

    ui->welcome->showButton(false);
    ui->teamInfo->setTeam();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::serializeData() {
    QStringList tsv;
    tsv << QString::number(ui->teamInfo->teamNumber());
    tsv << QString::number(ui->teamInfo->matchNumber());

    tsv << ui->teamInfo->initials();

    tsv << ui->autoScouting->tsv();

    tsv << ui->teleScouting->tsv();

    tsv << ui->scales->tsv();

    tsv << ui->notes->notes();

    return tsv.join("\t");
}

void MainWindow::next() {
    int nextIdx = currentIdx + 1;
    if (nextIdx >= ui->stackedWidget->count()) nextIdx = ui->stackedWidget->count() - 1;
    currentIdx = nextIdx;

    ui->stackedWidget->setCurrentWidget(m_pages.at(nextIdx));

    if (nextIdx == ui->stackedWidget->count() - 1) {
        ui->qrcode->setQRData(serializeData());
    }
}

void MainWindow::back() {
    int nextIdx = currentIdx - 1;
    if (nextIdx < 0) nextIdx = 0;
    currentIdx = nextIdx;

    ui->stackedWidget->setCurrentWidget(m_pages.at(nextIdx));
}

void MainWindow::backToStart() {
    currentIdx = 0;
    ui->welcome->showButton();
    ui->stackedWidget->setCurrentWidget(ui->welcome);
    ui->teamInfo->incrementMatch();

    ui->teleScouting->clear();
    ui->autoScouting->clear();
    ui->notes->clear();
    ui->scales->clear();
}

void MainWindow::backToQRCode()
{
    currentIdx = m_pages.indexOf(ui->qrcode);
    ui->teamInfo->decrementMatch();
    ui->stackedWidget->setCurrentWidget(m_pages.at(currentIdx));
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Back) {
        back();
    } else if (event->key() == Qt::Key_Forward) {
        next();
    }
}
