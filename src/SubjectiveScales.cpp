#include "SubjectiveScales.h"
#include "ui_SubjectiveScales.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>

SubjectiveScales::SubjectiveScales(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SubjectiveScales)
{
    ui->setupUi(this);

    // #ifdef Q_OS_WASM
    QFile file(":/config");
    // #else
    //     QFile file(QDir::homePath() + "/schedule.json");
    // #endif

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "sad";
    }

    QByteArray data = file.readAll();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    QJsonObject obj = doc.object();
    QJsonObject pages = obj.value("pages").toObject();
    QJsonObject scalesPage = pages.value("scales").toObject();

    QJsonArray values = scalesPage.value("values").toArray();

    for (const QJsonValueRef ref : values) {
        QJsonObject obj = ref.toObject();

        QLabel *title = new QLabel(obj.value("title").toString(""), this);

        QFont tf = title->font();
        tf.setPointSize(17);
        title->setFont(tf);

        QLabel *desc = new QLabel(obj.value("desc").toString(""), this);

        QFont df = desc->font();
        df.setPointSize(11);
        desc->setFont(df);

        Scale *scale = new Scale(this);

        m_scales.append(scale);

        ui->formLayout->addRow(title, scale);
        ui->formLayout->addRow(desc);
    }
}

SubjectiveScales::~SubjectiveScales()
{
    delete ui;
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
