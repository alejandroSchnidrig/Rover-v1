#include <Arduino.h>
#include "Cortadora.h"

Cortadora::Cortadora(int pinA, int pinB){
    this->pinA = pinA;
    this->pinB = pinB;
}

void Cortadora::cortar(){
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, LOW);
}