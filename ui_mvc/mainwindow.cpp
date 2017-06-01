#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QException>
#include "fileoperations.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new MyModel(0);
    ui->tableView->setModel(model);

    timer = new QTimer(this);
    timer->setInterval(700);
    connect(timer, SIGNAL(timeout()) , model, SLOT(timerHit()));
    timer->start();
}

MainWindow::~MainWindow()
{
    delete timer;
    delete model;
    delete ui;
}

void MainWindow::on_actionopen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (fileName.contains(".csv"))
    {
        FileOperations<csv_operations> op;
        model->myUpdate();
        model->set_sensors(op.read(fileName));
    }
    else
        throw QException();
}

void MainWindow::on_actionsave_triggered()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (fileName.contains(".csv"))
    {
        FileOperations<csv_operations> op;
        op.write(model->get_sensors(), fileName);
    }
    else
        throw QException();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    model->delete_sensor(index.row());
}

void MainWindow::on_pushButton_clicked()
{
    bool ok;
    QString district = ui->lineEdit->text();
    int x = ui->lineEdit_2->text().toInt(&ok);
    int y = ui->lineEdit_3->text().toInt(&ok);
    if (ok)
        model->add_sensor(district, x, y);
}
