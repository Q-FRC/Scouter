#ifndef TELESCOUTING_H
#define TELESCOUTING_H

#include "BetterSpinBox.h"
#include <QWidget>
#include <QCheckBox>

namespace Ui {
class TeleScouting;
}

class TeleScouting : public QWidget
{
    Q_OBJECT

public:
    explicit TeleScouting(QWidget *parent = nullptr);
    ~TeleScouting();

    void clear();
    QStringList tsv();

private:
    Ui::TeleScouting *ui;

    QList<BetterSpinBox *> m_spinBoxes;
    QList<QCheckBox *> m_checkBoxes;
};

#endif // TELESCOUTING_H
