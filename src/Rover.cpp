#include "Rover.h"

    Rover::Rover(int pinDerechaA, int pinDerechaB, int pinDerechaPWM, 
        int pinIzquierdaA, int pinIzquierdaB, int pinIzquierdaPWM, 
        int pinMedioA, int pinMedioB, int pinMedioPWM, int pinAlarma)
            : motorDriver(pinDerechaA, pinDerechaB, pinDerechaPWM, 
                pinIzquierdaA, pinIzquierdaB, pinIzquierdaPWM),
              cortadora(pinMedioA, pinMedioB, pinMedioPWM),
              alarma(pinAlarma){}

    void Rover::inicializar(){
         motorDriver.inicializar();
         cortadora.inicializar();
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
        cortadora.parar();
    }

    void Rover::girarCortadora(){
        cortadora.cortar();
    }

    void Rover::configurarAlarma(){
        alarma.configurar();
    }

    void Rover::encenderAlarma(){
        alarma.encenderAlarma();
    }

    void Rover::apagarAlarma(){
        alarma.apagarAlarma();
    }
