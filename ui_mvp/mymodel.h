#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractTableModel>
#include <QSharedPointer>
#include "sensor.h"

class MyModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit MyModel(QObject *parent = 0);
    ~MyModel();

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void set_sensors(QVector<QSharedPointer<Sensor>> sensors);
    QVector<QSharedPointer<Sensor>> get_sensors() { return sensors; }
    void myUpdate() {
        this->beginResetModel();
        this->endResetModel();
    }
    void delete_sensor(int id);
    void add_sensor(QString d, int x, int y);

public slots:
    void timerHit();

private:
    QVector<QSharedPointer<Sensor>> sensors;
};

#endif // MYMODEL_H
