#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sensor.h"
#include <QSharedPointer>
#include <QTimer>
#include <QTableWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void show_table();

private slots:
    void on_actionopen_triggered();
    void on_actionsave_triggered();
    void timerHit();
    void on_tableWidget_itemClicked(QTableWidgetItem *item);

    void on_pushButton_clicked();

private:
    QTimer *timer;
    QVector<QSharedPointer<Sensor>> sensors;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
