#include "SensorCorriente.h"

SensorCorriente::SensorCorriente(int pin) : pin(pin){}

float SensorCorriente::sensarCorriente(){
    int analogico = analogRead(pin);
    float sensorVoltaje = (analogico / float(ADC_RESOLUTION)) * ADC_VOLTAGE;
    float corriente = -(sensorVoltaje - ACS712_OFFSET) / SENSITIVITY;

    return corriente; // En Ampere
}