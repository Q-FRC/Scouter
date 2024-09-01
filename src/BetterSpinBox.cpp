#include "BetterSpinBox.h"
#include "ui_BetterSpinBox.h"

BetterSpinBox::BetterSpinBox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BetterSpinBox)
{
    ui->setupUi(this);

    connect(ui->box, &QSpinBox::valueChanged, this, &BetterSpinBox::valueChanged);
}

BetterSpinBox::~BetterSpinBox()
{
    delete ui;
}

void BetterSpinBox::setValue(int value) {
    ui->box->setValue(value);
}

int BetterSpinBox::value() {
    return ui->box->value();
}

void BetterSpinBox::setMaximum(int max) {
    ui->box->setMaximum(max);
}

void BetterSpinBox::setMinimum(int min) {
    ui->box->setMinimum(min);
}

void BetterSpinBox::setWrapping(bool wrap) {
    ui->box->setWrapping(wrap);
}

void BetterSpinBox::setColor(QColor color)
{
    QPalette p = palette();

    p.setColor(QPalette::WindowText, Qt::white);
    p.setColor(QPalette::Button, color);

    setPalette(p);
}

void BetterSpinBox::setTextColor(QColor color)
{
    QPalette p = palette();

    p.setColor(QPalette::ButtonText, color);

    setPalette(p);

}

QString BetterSpinBox::text() const
{
    return m_text;
}

void BetterSpinBox::setText(const QString &newText)
{
    m_text = newText;
}
