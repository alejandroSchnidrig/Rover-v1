#include "MotorDriver.h"

    MotorDriver::MotorDriver(int pinDerechaA, int pinDerechaB, int pinDerechaPWM, 
        int pinIzquierdaA, int pinIzquierdaB, int pinIzquierdaPWM) :
            ruedasDerecha(pinDerechaA, pinDerechaB, pinDerechaPWM),
                ruedasIzquierda(pinIzquierdaA,pinIzquierdaB, pinIzquierdaPWM){}

    void MotorDriver::inicializar(){
        ruedasDerecha.inicializar();
        ruedasIzquierda.inicializar();
    }

    void MotorDriver::avanzar(int velocidad){
        ruedasDerecha.moverAdelante(velocidad);
        ruedasIzquierda.moverAdelante(velocidad);
    }

    void MotorDriver::retroceder(int velocidad){
        ruedasDerecha.moverAtras(velocidad);
        ruedasIzquierda.moverAtras(velocidad);
    }

    void MotorDriver::girarALaDerecha(int velocidad){
        ruedasDerecha.girarALaDerecha(velocidad);
        ruedasIzquierda.girarALaIzquierda(velocidad);
    }

    void MotorDriver::girarALaIzquierda(int velocidad){
        ruedasDerecha.girarALaIzquierda(velocidad);
        ruedasIzquierda.girarALaDerecha(velocidad);
    }

    void MotorDriver::parar(){
        ruedasDerecha.detener();
        ruedasIzquierda.detener();
    }
