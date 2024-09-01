#include "MainWindow.h"

#include <QKeyEvent>

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

    connect(ui->qrcode, &QRCode::backButtonPressed, this, &MainWindow::backToStart);
    connect(ui->teamInfo, &TeamInfo::teamNumberChanged, this, [this](int team) {
        ui->team->setText("Your Team: " + QString::number(team));
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
