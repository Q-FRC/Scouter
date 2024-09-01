#ifndef MATCHPAGE_H
#define MATCHPAGE_H

#include "BetterSpinBox.h"
#include <QWidget>
#include <qcheckbox.h>

namespace Ui {
class MatchPage;
}

class MatchPage : public QWidget
{
    Q_OBJECT

public:
    explicit MatchPage(QWidget *parent = nullptr);
    ~MatchPage();

    void config(bool tele, const QJsonObject &obj);

    void clear();
    QStringList tsv();

private:
    Ui::MatchPage *ui;

    QList<BetterSpinBox *> m_spinBoxes;
    QList<QCheckBox *> m_checkBoxes;
};

#endif // MATCHPAGE_H
