#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <NewPing.h>

class Sensor {
private:
    NewPing sensor;
    unsigned int distanciaObstaculo;
    bool obstaculoDetectado;

public:
    Sensor(int triggerPin, int echoPin, int maxDistance, unsigned int distanciaObstaculo);

    unsigned int getDistancia();
    bool detectarObstaculo();
    bool actualizarEstado();
};

#endif