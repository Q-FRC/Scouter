#ifndef QRCODE_H
#define QRCODE_H

#include <QWidget>

namespace Ui {
class QRCode;
}

class QRCode : public QWidget
{
    Q_OBJECT

public:
    explicit QRCode(QWidget *parent = nullptr);
    ~QRCode();

    void config(const QJsonObject &obj);

    void setQRData(QString data);

private:
    Ui::QRCode *ui;

signals:
    void backButtonPressed();
};

#endif // QRCODE_H
