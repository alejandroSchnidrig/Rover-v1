#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include "Ruedas.h" 

class MotorDriver {
private:
    Ruedas ruedasDerecha;
    Ruedas ruedasIzquierda;

public:
    MotorDriver(int pinDerechaA, int pinDerechaB, int pinDerechaPWM, 
          int pinIzquierdaA, int pinIzquierdaB, int pinIzquierdaPWM);

    void inicializar();
    void avanzar(int velocidad);
    void retroceder(int velocidad);
    void girarALaDerecha(int velocidad);
    void girarALaIzquierda(int velocidad);
    void parar();
};

#endif