#include "WelcomePage.h"
#include "ui_WelcomePage.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>

WelcomePage::WelcomePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WelcomePage)
{
    ui->setupUi(this);

    connect(ui->qrcode, &QPushButton::clicked, this, &WelcomePage::backToQRCode);
}

WelcomePage::~WelcomePage()
{
    delete ui;
}

void WelcomePage::config(const QJsonObject &obj)
{
    ui->label->setText(obj.value("welcome").toString());
}

void WelcomePage::showButton(bool show)
{
    ui->qrcode->setVisible(show);
}
