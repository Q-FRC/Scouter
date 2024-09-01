#include "MatchPage.h"
#include "ui_MatchPage.h"

#include <QJsonArray>
#include <QJsonObject>

MatchPage::MatchPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MatchPage)
{
    ui->setupUi(this);
}

MatchPage::~MatchPage()
{
    delete ui;
}

void MatchPage::config(bool tele, const QJsonObject &obj)
{    
    if (tele) ui->title->setText("Teleop Data");

    QJsonObject pages = obj.value("pages").toObject();
    QJsonArray page = pages.value(tele ? "tele" : "auto").toArray();

    for (const QJsonValueRef ref : page) {
        QJsonObject val = ref.toObject();

        QString type = val.value("type").toString("int");

        if (type == "int") {
            BetterSpinBox *box = new BetterSpinBox(this);
            box->setColor(val.value("color").toString("#000000"));
            box->setTextColor(val.value("textColor").toString("#FFFFFF"));

            box->setMinimum(val.value("min").toInt(0));
            box->setMaximum(val.value("max").toInt(99999));

            box->setText(val.value("text").toString(""));

            QPalette p = box->palette();
            p.setColor(QPalette::Window, val.value("color").toString("#000000"));
            box->setPalette(p);

            m_spinBoxes.append(box);
        } else if (type == "bool") {
            QCheckBox *box = new QCheckBox(this);
            box->setText(val.value("text").toString(""));

            QPalette p = box->palette();
            p.setColor(QPalette::WindowText, obj.value("textColor").toString("#000000"));
            box->setPalette(p);

            m_checkBoxes.append(box);
        }
    }

    for (size_t i = 0; i < m_spinBoxes.length(); ++i) {
        BetterSpinBox *box = m_spinBoxes.at(i);
        QLabel *label = new QLabel(box->text(), this);
        ui->gridLayout->addWidget(label, i + 1, 0, Qt::AlignTop);
        ui->gridLayout->addWidget(box, i + 1, 1, Qt::AlignTop);
    }

    for (size_t i = 0; i < m_checkBoxes.length(); ++i) {
        QCheckBox *box = m_checkBoxes.at(i);
        box->setStyleSheet("QCheckBox::indicator:unchecked { width: 30px; height: 30px; } QCheckBox::indicator:checked { width: 30px; height: 30px; }");
        ui->gridLayout->addWidget(box, i / 2 + m_spinBoxes.length() + 1, i % 2);
    }

    ui->gridLayout->setColumnStretch(1, 1);
}

void MatchPage::clear() {
    for (BetterSpinBox *box : m_spinBoxes) {
        box->setValue(0);
    }

    for (QCheckBox *box : m_checkBoxes) {
        box->setChecked(false);
    }
}

QStringList MatchPage::tsv()
{
    QStringList tsv;

    for (BetterSpinBox *box : m_spinBoxes) {
        tsv << QString::number(box->value());
    }

    for (QCheckBox *box : m_checkBoxes) {
        tsv << QString::number(box->isChecked());
    }

    return tsv;
}
