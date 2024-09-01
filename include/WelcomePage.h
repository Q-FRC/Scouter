#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include <QWidget>

namespace Ui {
class WelcomePage;
}

class WelcomePage : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomePage(QWidget *parent = nullptr);
    ~WelcomePage();
    void config(const QJsonObject &obj);

    void showButton(bool show = true);

signals:
    void backToQRCode();

private:
    Ui::WelcomePage *ui;
};

#endif // WELCOMEPAGE_H
