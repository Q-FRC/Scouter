#include "QRCode.h"
#include "ui_QRCode.h"

#include "QrCodeGenerator.h"
#include <QJsonObject>

QRCode::QRCode(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QRCode)
{
    ui->setupUi(this);
    connect(ui->nextMatch, &QPushButton::clicked, this, &QRCode::backButtonPressed);
}

QRCode::~QRCode()
{
    delete ui;
}

void QRCode::config(const QJsonObject &obj)
{

}

void QRCode::setQRData(QString data) {
    QrCodeGenerator gen;
    QImage image = gen.generateQr(data);
    ui->qr->setPixmap(QPixmap::fromImage(image).scaled(ui->qr->width(), ui->qr->height(), Qt::KeepAspectRatio));
    update();
}
