#include "presenter.h"
#include "baseview.h"
#include <QFileDialog>
#include <QException>
#include "fileoperations.h"

Presenter::Presenter(BaseView *view, QObject *parent): QObject(parent), view(view), model(new MyModel(0))
{
    QObject *view_obj = dynamic_cast<QObject*>(view);
    QTableView *tmp = view->get_table();
    tmp->setModel(model);
    QObject::connect(view_obj, SIGNAL(openTriggered()),this, SLOT(openAction()));
    QObject::connect(view_obj, SIGNAL(saveTriggered()),this, SLOT(saveAction()));
    QObject::connect(view_obj, SIGNAL(deleteTriggered()),this, SLOT(deleteAction()));
    QObject::connect(view_obj, SIGNAL(addTriggered()),this, SLOT(addAction()));

    timer = new QTimer(this);
    timer->setInterval(700);
    connect(timer, SIGNAL(timeout()) , model, SLOT(timerHit()));
    timer->start();
}

Presenter::~Presenter()
{
    delete timer;
    delete model;
}

void Presenter::openAction()
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

void Presenter::saveAction()
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

void Presenter::deleteAction()
{
    model->delete_sensor(view->get_row());
}

void Presenter::addAction()
{
    QString district = view->get_district();
    int x = view->get_x();
    int y = view->get_y();
    model->add_sensor(district, x, y);
}
