#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fileoperations.h"
#include <QFileDialog>
#include <QException>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->setInterval(700);
    connect(timer, SIGNAL(timeout()) , this, SLOT(timerHit()));
    timer->start();
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}

void MainWindow::on_actionopen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (fileName.contains(".csv"))
    {
        FileOperations<csv_operations> op;
        sensors = op.read(fileName);
        this->show_table();
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
        op.write(sensors, fileName);
    }
    else
        throw QException();
}

QColor get_color(size_t full)
{
    if (full < 40)
        return Qt::green;
    else if (full < 60)
       return Qt::yellow;
    else if (full < 80)
        return Qt::red;
    else
        return Qt::darkRed;
}
void MainWindow::show_table()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(sensors.size());
    QTableWidgetItem *tmp;
    int row = 0;
    for (auto s : sensors)
    {
        QColor color = get_color(s.data()->get_full());
        tmp = new QTableWidgetItem(s.data()->get_district());
        tmp->setBackgroundColor(color);
        ui->tableWidget->setItem(row, 0, tmp);
        tmp = new QTableWidgetItem(QString::number(s.data()->get_x()));
        tmp->setBackgroundColor(color);
        ui->tableWidget->setItem(row, 1, tmp);
        tmp = new QTableWidgetItem(QString::number(s.data()->get_y()));
        tmp->setBackgroundColor(color);
        ui->tableWidget->setItem(row, 2, tmp);
        tmp = new QTableWidgetItem(QString::number(s.data()->get_full()));
        tmp->setBackgroundColor(color);
        ui->tableWidget->setItem(row, 3, tmp);
        row++;
    }
}

void MainWindow::timerHit()
{
    if (sensors.size())
    {
        int ind = rand() % sensors.size();
        int delta = rand() % 10;
        int num = rand() % sensors.size();
        num = ind + num >= sensors.size() ? sensors.size()-1 : ind + num;
        for (int i = ind; i <= num; i++)
        {
            int full = sensors[i].data()->get_full();
            if (full + delta > 100)
                sensors[i].data()->set_full(0);
            else
                sensors[i].data()->set_full(full + delta);
        }
        this->show_table();
    }
}

void MainWindow::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    sensors.erase(sensors.begin() + item->row());
    this->show_table();
}

void MainWindow::on_pushButton_clicked()
{
    bool ok;
    QString district = ui->lineEdit->text();
    int x = ui->lineEdit_2->text().toInt(&ok);
    int y = ui->lineEdit_3->text().toInt(&ok);
    if (ok)
    {
        QSharedPointer<Sensor> sensor(new Sensor(district, x, y, 0));
        sensors.push_back(sensor);
        this->show_table();
    }
}
