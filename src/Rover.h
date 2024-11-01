#ifndef ROVER_H
#define ROVER_H

#include "MotorDriver.h"

class Rover {
private:
    MotorDriver motorDriver;

public:
    Rover(int pinDerechaA, int pinDerechaB, int pinDerechaPWM, 
          int pinIzquierdaA, int pinIzquierdaB, int pinIzquierdaPWM);

    void inicializar();
    void avanzar(int velocidad);
    void retroceder(int velocidad);
    void girarALaDerecha(int velocidad);
    void girarALaIzquierda(int velocidad);
    void parar();
};

#endif