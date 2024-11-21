#include <Arduino.h>
#include "Cortadora.h"

const int tiempoDeInicio = 1000;
const int valorMaximo = 255;
const int paso = 5;

Cortadora::Cortadora(int pinA, int pinB, int pinPWM){
    this->pinA = pinA;
    this->pinB = pinB;
    this->pinPWM = pinPWM;
}

void Cortadora::inicializar(){
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
}

void Cortadora::cortar(){
    while(valorPWM < valorMaximo){
        valorPWM += paso;
        digitalWrite(pinA, HIGH);
        digitalWrite(pinB, LOW);
        analogWrite(pinPWM, valorPWM);
        delay(5);
    }
}

void Cortadora::parar(){
    valorPWM = 0;
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, LOW);
}