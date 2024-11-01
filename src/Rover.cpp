#include "Rover.h"

    Rover::Rover(int pinDerechaA, int pinDerechaB, int pinDerechaPWM, 
        int pinIzquierdaA, int pinIzquierdaB, int pinIzquierdaPWM)
            : motorDriver(pinDerechaA, pinDerechaB, pinDerechaPWM, 
                pinIzquierdaA, pinIzquierdaB, pinIzquierdaPWM){}

    void Rover::inicializar(){
         motorDriver.inicializar();
    }

    void Rover::avanzar(int velocidad){
        motorDriver.avanzar(velocidad);
    }

    void Rover::retroceder(int velocidad){
        motorDriver.retroceder(velocidad);
    }

    void Rover::girarALaDerecha(int velocidad){
        motorDriver.girarALaDerecha(velocidad);
    }

    void Rover::girarALaIzquierda(int velocidad){
        motorDriver.girarALaIzquierda(velocidad);
    }

    void Rover::parar(){
        motorDriver.parar();
    }


