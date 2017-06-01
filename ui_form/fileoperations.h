#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <QVector>
#include "sensor.h"
#include <QSharedPointer>

class csv_operations
{
public:
    QVector<QSharedPointer<Sensor>> in(QString filename);
    void out(QVector<QSharedPointer<Sensor>> sensors, QString filename);
};

template <class Operation>
class FileOperations: public Operation
{
public:
    QVector<QSharedPointer<Sensor>> read(QString filename)
    {
        return this->in(filename);
    }

    void write(QVector<QSharedPointer<Sensor>> sensors, QString filename)
    {
        this->out(sensors, filename);
    }
};

#endif // FILEOPERATIONS_H
