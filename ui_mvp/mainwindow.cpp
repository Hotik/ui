#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QException>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::get_row()
{
    return ui->tableView->currentIndex().row();
}

QTableView *MainWindow::get_table()
{
    return ui->tableView;
}

int MainWindow::get_x()
{
    return ui->lineEdit_2->text().toInt();
}

int MainWindow::get_y()
{
    return ui->lineEdit_3->text().toInt();
}

QString MainWindow::get_district()
{
    return ui->lineEdit->text();
}

void MainWindow::on_actionopen_triggered()
{
    emit this->openTriggered();
}


void MainWindow::on_actionsave_triggered()
{
    emit this->saveTriggered();
}

void MainWindow::on_tableView_clicked(const QModelIndex &)
{
    emit this->deleteTriggered();
}

void MainWindow::on_pushButton_clicked()
{
    emit this->addTriggered();
}
