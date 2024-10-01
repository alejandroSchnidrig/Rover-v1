#include "Motor.h"

    Motor::Motor(int pinDerechaA, int pinDerechaB, int pinDerechaPWM, 
        int pinIzquierdaA, int pinIzquierdaB, int pinIzquierdaPWM) :
            ruedasDerecha(pinDerechaA, pinDerechaB, pinDerechaPWM),
                ruedasIzquierda(pinIzquierdaA,pinIzquierdaB, pinIzquierdaPWM){}

    void Motor::inicializar(){
        ruedasDerecha.inicializar();
        ruedasIzquierda.inicializar();
    }

    void Motor::avanzar(int velocidad){
        ruedasDerecha.moverAdelante(velocidad);
        ruedasIzquierda.moverAdelante(velocidad);
    }

    void Motor::retroceder(int velocidad){
        ruedasDerecha.moverAtras(velocidad);
        ruedasIzquierda.moverAtras(velocidad);
    }

    void Motor::parar(){
        ruedasDerecha.detener();
        ruedasIzquierda.detener();
    }
