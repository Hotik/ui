#ifndef BASEVIEW_H
#define BASEVIEW_H

#include <QString>
#include <QTableView>

class BaseView
{
public:
    virtual int get_x() = 0;
    virtual int get_y() = 0;
    virtual QString get_district() = 0;
    virtual QTableView *get_table() = 0;
    virtual int get_row() = 0;

public:
    virtual void openTriggered() = 0;
    virtual void saveTriggered() = 0;
    virtual void deleteTriggered() = 0;
    virtual void addTriggered() = 0;
};


#endif // BASEVIEW_H
