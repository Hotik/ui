#ifndef PRESENTER_H
#define PRESENTER_H

#include <QObject>
#include "mymodel.h"
#include <QTimer>

class BaseView;

class Presenter : public QObject
{
    Q_OBJECT
public:
    Presenter(BaseView *view,  QObject *parent = 0);
    ~Presenter();

private:
    MyModel *model;
    BaseView *view;
    QTimer *timer;


private slots:
    void openAction();
    void saveAction();
    void deleteAction();
    void addAction();
};

#endif // PRESENTER_H
