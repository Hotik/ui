#include "fileoperations.h"
#include <QFile>
#include <QException>
#include <QTextStream>

QVector<QSharedPointer<Sensor>> csv_operations::in(QString filename)
{
    QVector<QSharedPointer<Sensor>> sensors;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        throw QException();
    while (!file.atEnd()) {
           QByteArray line = file.readLine();
           QSharedPointer<Sensor> sensor(new Sensor(line.split(';').at(0), line.split(';').at(1).toInt(), line.split(';').at(2).toInt(), line.split(';').at(3).toUInt()));
           sensors.push_back(sensor);
    }
    return sensors;
}

void csv_operations::out(QVector<QSharedPointer<Sensor>> sensors, QString filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly))
        throw QException();
    QTextStream stream( &file );
    for (auto s : sensors)
    {
        stream << s.data()->get_district() << ";";
        stream << s.data()->get_x() << ";";
        stream << s.data()->get_y() << ";";
        stream << s.data()->get_full() << ";" << endl;
    }
    file.close();
}
