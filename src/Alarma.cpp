#include <Arduino.h>
#include "Alarma.h"

Alarma::Alarma(int pinA){
    this->pinA = pinA;
}

void Alarma::configurar(){
    pinMode(pinA, OUTPUT);
}

void Alarma::encenderAlarma(){
    digitalWrite(pinA, HIGH);
}

void Alarma::apagarAlarma(){
     digitalWrite(pinA, LOW);
}
