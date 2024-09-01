#ifndef AUTOSCOUTING_H
#define AUTOSCOUTING_H

#include "BetterSpinBox.h"
#include <QWidget>
#include <qcheckbox.h>

namespace Ui {
class AutoScouting;
}

class AutoScouting : public QWidget
{
    Q_OBJECT

public:
    explicit AutoScouting(QWidget *parent = nullptr);
    ~AutoScouting();

    void clear();
    QStringList tsv();

private:
    Ui::AutoScouting *ui;

    QList<BetterSpinBox *> m_spinBoxes;
    QList<QCheckBox *> m_checkBoxes;
};

#endif // AUTOSCOUTING_H
