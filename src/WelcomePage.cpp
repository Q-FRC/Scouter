#include "WelcomePage.h"
#include "ui_WelcomePage.h"

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

void WelcomePage::showButton(bool show)
{
    ui->qrcode->setVisible(show);
}
