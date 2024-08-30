#ifndef BETTERSPINBOX_H
#define BETTERSPINBOX_H

#include <QSpinBox>

namespace Ui {
class BetterSpinBox;
}

class BetterSpinBox : public QWidget
{
    Q_OBJECT

public:
    explicit BetterSpinBox(QWidget *parent = nullptr);
    ~BetterSpinBox();

    void setValue(int value);
    int value();

    void setMaximum(int max);
    void setMinimum(int min);

    void setWrapping(bool wrap);

    void setColor(QColor color);
    void setTextColor(QColor color);

    QString text() const;
    void setText(const QString &newText);

signals:
    void valueChanged(int value);

private:
    Ui::BetterSpinBox *ui;

    QString m_text;
};

#endif // BETTERSPINBOX_H
