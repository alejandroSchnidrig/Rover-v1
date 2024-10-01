#include "Rover.h"

    Rover::Rover(int pinDerechaA, int pinDerechaB, int pinDerechaPWM, 
        int pinIzquierdaA, int pinIzquierdaB, int pinIzquierdaPWM)
            : motor(pinDerechaA, pinDerechaB, pinDerechaPWM, 
                pinIzquierdaA, pinIzquierdaB, pinIzquierdaPWM){}

    void Rover::inicializar(){
         motor.inicializar();
    }

    void Rover::avanzar(int velocidad){
        motor.avanzar(velocidad);
    }

    void Rover::retroceder(int velocidad){
        motor.retroceder(velocidad);
    }

    void Rover::parar(){
        motor.parar();
    }


