#ifndef ROVER_H
#define ROVER_H

#include "MotorDriver.h"
#include "Cortadora.h"
#include "Alarma.h"

class Rover {
private:
    MotorDriver motorDriver;
    Cortadora cortadora;
    Alarma alarma;

public:
    Rover(int pinDerechaA, int pinDerechaB, int pinDerechaPWM, 
          int pinIzquierdaA, int pinIzquierdaB, int pinIzquierdaPWM,
          int pinMedioA, int pinMedioB, int pinAlarma);

    void inicializar();
    void avanzar(int velocidad);
    void retroceder(int velocidad);
    void girarALaDerecha(int velocidad);
    void girarALaIzquierda(int velocidad);
    void parar();
    void girarCortadora();
    void configurarAlarma();
    void encenderAlarma();
    void apagarAlarma();
};

#endif