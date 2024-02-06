#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow, Ui::MainWindow
{
    Q_OBJECT

    QList<QWidget *> m_pages;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString serializeData();

public slots:
    void next();
    void back();
    void backToStart();

private:
    int currentIdx = 0;

    void keyReleaseEvent(QKeyEvent *event) override;
};
#endif // MAINWINDOW_H
