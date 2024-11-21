#ifndef SENSOR_CORRIENTE_H
#define SENSOR_CORRIENTE_H

#include <Arduino.h>

class SensorCorriente {
private:
    int pin;
    const float ACS712_OFFSET = 2.5;
    const float SENSITIVITY = 0.185;

    const int ADC_RESOLUTION = 4095;
    const float ADC_VOLTAGE = 3.3;

public:
    SensorCorriente(int pin);

    float sensarCorriente();
};

#endif