#include "AutoScouting.h"
#include "ui_AutoScouting.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>

AutoScouting::AutoScouting(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AutoScouting)
{
    ui->setupUi(this);

// #ifdef Q_OS_WASM
    QFile file(":/config");
// #else
//     QFile file(QDir::homePath() + "/schedule.json");
// #endif

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "auto scouting sad";
    }

    QByteArray data = file.readAll();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    QJsonObject obj = doc.object();
    QJsonObject pages = obj.value("pages").toObject();
    QJsonObject autoPage = pages.value("auto").toObject();

    QJsonArray values = autoPage.value("values").toArray();

    for (const QJsonValueRef ref : values) {
        QJsonObject obj = ref.toObject();

        QString type = obj.value("type").toString("int");

        if (type == "int") {
            BetterSpinBox *box = new BetterSpinBox(this);
            box->setColor(obj.value("color").toString("#000000"));
            box->setTextColor(obj.value("textColor").toString("#FFFFFF"));

            box->setMinimum(obj.value("min").toInt(0));
            box->setMaximum(obj.value("max").toInt(99999));

            box->setText(obj.value("text").toString(""));

            m_spinBoxes.append(box);
        } else if (type == "bool") {
            QCheckBox *box = new QCheckBox(this);
            box->setText(obj.value("text").toString(""));

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

AutoScouting::~AutoScouting()
{
    delete ui;
}

void AutoScouting::clear() {
    for (BetterSpinBox *box : m_spinBoxes) {
        box->setValue(0);
    }

    for (QCheckBox *box : m_checkBoxes) {
        box->setChecked(false);
    }
}

QStringList AutoScouting::tsv()
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
