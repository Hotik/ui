#ifndef SENSOR_H
#define SENSOR_H

#include <stdlib.h>
#include <QString>

class Sensor
{
public:
    Sensor() {}
    Sensor( QString district, int x, int y, size_t full):district(district), x(x), y(y), full(full) {}
    Sensor(Sensor &s) { this->x = s.x; this->y = s.y; this->full = s.full; this->district = s.district; }
    ~Sensor() {}

    int get_x() { return x; }
    int get_y() { return y; }
    size_t get_full() { return full; }
    QString get_district() { return district; }

    void set_x(int x) { this->x =x; }
    void set_y(int y) { this->y = y; }
    void set_full(size_t full) { this->full = full; }
    void set_district(QString district) { this->district = district; }

private:
    size_t id;
    QString district;
    int x;
    int y;
    size_t full;
};

#endif // SENSOR_H
