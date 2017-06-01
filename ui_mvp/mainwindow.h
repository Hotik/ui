#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <presenter.h>
#include "baseview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public BaseView
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int get_x();
    int get_y();
    QString get_district();
    QTableView *get_table();
    int get_row();

signals:
    void openTriggered();
    void saveTriggered();
    void deleteTriggered();
    void addTriggered();

private slots:
    void on_actionopen_triggered();

    void on_actionsave_triggered();

    void on_tableView_clicked(const QModelIndex &);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
