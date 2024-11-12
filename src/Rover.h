#ifndef ROVER_H
#define ROVER_H

#include "MotorDriver.h"
#include "Cortadora.h"

class Rover {
private:
    MotorDriver motorDriver;
    Cortadora cortadora;

public:
    Rover(int pinDerechaA, int pinDerechaB, int pinDerechaPWM, 
          int pinIzquierdaA, int pinIzquierdaB, int pinIzquierdaPWM,
          int pinMedioA, int pinMedioB);

    void inicializar();
    void avanzar(int velocidad);
    void retroceder(int velocidad);
    void girarALaDerecha(int velocidad);
    void girarALaIzquierda(int velocidad);
    void parar();
    void girarCortadora();
};

#endif