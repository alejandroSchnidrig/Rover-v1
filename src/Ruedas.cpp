#include <Arduino.h>
#include "Ruedas.h"

    Ruedas::Ruedas(int pinA, int pinB, int pinPWM) {
        this->pinA = pinA;
        this->pinB = pinB;
        this->pinPWM = pinPWM;
    }

    void Ruedas::inicializar(){
        pinMode(pinA, OUTPUT);
        pinMode(pinB, OUTPUT);
        pinMode(pinPWM, OUTPUT);
    }

    void Ruedas::moverAdelante(int velocidad){
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, HIGH);
        analogWrite(pinPWM, velocidad);
    }

    void Ruedas::moverAtras(int velocidad){
        digitalWrite(pinA, HIGH);
        digitalWrite(pinB, LOW);
        analogWrite(pinPWM, velocidad);
    }

    void Ruedas::girarALaDerecha(int velocidad) {
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, HIGH);
        analogWrite(pinPWM, velocidad);
    }

    void Ruedas::girarALaIzquierda(int velocidad) {
        digitalWrite(pinA, HIGH);
        digitalWrite(pinB, LOW);
        analogWrite(pinPWM, velocidad);
    }

    void Ruedas::detener(){
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, LOW);
    }
