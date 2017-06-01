#include "mymodel.h"
#include <QBrush>
#include <random>

MyModel::MyModel(QObject *parent) : QAbstractTableModel(parent)
{
 }

MyModel::~MyModel()
{
}

int MyModel::rowCount(const QModelIndex & /*parent*/) const
{
   return sensors.size();
}

int MyModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 4;
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

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        switch (index.column()) {
        case 0:
            return this->sensors[index.row()].data()->get_district();
        case 1:
            return QString::number(this->sensors[index.row()].data()->get_x());
        case 2:
            return QString::number(this->sensors[index.row()].data()->get_y());
        case 3:
            return QString::number(this->sensors[index.row()].data()->get_full());
        }

    }
    if (role == Qt::BackgroundRole)
    {
        QColor color = get_color(this->sensors[index.row()].data()->get_full());
        QBrush brush(color);
        return brush;
    }
    return QVariant();
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("District");
            case 1:
                return QString("X");
            case 2:
                return QString("Y");
            case 3:
                return QString("Full %");
            }
        }
        else
            return QString::number(section);
    }
    return QVariant();
}

void MyModel::set_sensors(QVector<QSharedPointer<Sensor>> sensors)
{
    this->sensors = sensors;
    QModelIndex left =  this->index(0, 0, QModelIndex());
    QModelIndex right = this->index(this->rowCount()-1, this->columnCount()-1, QModelIndex());
    emit this->dataChanged(left, right);
}


void MyModel::timerHit()
{
    if (sensors.size())
    {
        this->myUpdate();
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
        QModelIndex left =  this->index(ind, 0, QModelIndex());
        QModelIndex right = this->index(num, this->columnCount()-1, QModelIndex());
        emit this->dataChanged(left, right);
    }
}

void MyModel::delete_sensor(int id)
{
    this->sensors.erase(this->sensors.begin() + id);
    QModelIndex left =  this->index(id, 0, QModelIndex());
    QModelIndex right = this->index(this->rowCount()-1, this->columnCount()-1, QModelIndex());
    this->myUpdate();
    emit this->dataChanged(left, right);
}

void MyModel::add_sensor(QString d, int x, int y)
{
    QSharedPointer<Sensor> sensor(new Sensor(d, x, y, 0));
    this->sensors.push_back(sensor);
    this->myUpdate();
    QModelIndex left =  this->index(this->rowCount()-1, 0, QModelIndex());
    QModelIndex right = this->index(this->rowCount()-1, this->columnCount()-1, QModelIndex());
    emit this->dataChanged(left, right);
}
