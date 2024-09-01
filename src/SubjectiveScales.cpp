#include "SubjectiveScales.h"
#include "ui_SubjectiveScales.h"

#include <QJsonArray>
#include <QJsonObject>

SubjectiveScales::SubjectiveScales(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SubjectiveScales)
{
    ui->setupUi(this);
}

SubjectiveScales::~SubjectiveScales()
{
    delete ui;
}

void SubjectiveScales::config(const QJsonObject &obj)
{
    QJsonObject pages = obj.value("pages").toObject();
    QJsonArray page = pages.value("scales").toArray();

    for (const QJsonValueRef ref : page) {
        QJsonObject val = ref.toObject();

        QLabel *title = new QLabel(val.value("title").toString(""), this);

        QFont tf = title->font();
        tf.setPointSize(17);
        title->setFont(tf);

        QLabel *desc = new QLabel(val.value("desc").toString(""), this);

        QFont df = desc->font();
        df.setPointSize(11);
        desc->setFont(df);

        Scale *scale = new Scale(this);

        // QPalette p = scale->palette();
        // p.setColor(QPalette::WindowText, obj.value("textColor").toString("#ffffff"));
        // scale->setPalette(p);

        m_scales.append(scale);

        ui->formLayout->addRow(title, scale);
        ui->formLayout->addRow(desc);
    }
}

void SubjectiveScales::clear() {
    for (Scale *scale : m_scales) {
        scale->setValue(0);
    }
}

QStringList SubjectiveScales::tsv()
{
    QStringList tsv;

    for (Scale *scale : m_scales) {
        tsv << QString::number(scale->value());
    }

    return tsv;
}
