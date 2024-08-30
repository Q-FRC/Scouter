#ifndef SUBJECTIVESCALES_H
#define SUBJECTIVESCALES_H

#include "Scale.h"
#include <QWidget>

namespace Ui {
class SubjectiveScales;
}

class SubjectiveScales : public QWidget
{
    Q_OBJECT

public:
    explicit SubjectiveScales(QWidget *parent = nullptr);
    ~SubjectiveScales();

    void clear();
    QStringList tsv();
private:
    Ui::SubjectiveScales *ui;

    QList<Scale *> m_scales;
};

#endif // SUBJECTIVESCALES_H
