#include "Motor.h"

class Rover {
private:
    Motor motor;

public:
    Rover(int pinDerechaA, int pinDerechaB, int pinDerechaPWM, 
          int pinIzquierdaA, int pinIzquierdaB, int pinIzquierdaPWM);

    void inicializar();
    void avanzar(int velocidad);
    void retroceder(int velocidad);
    void parar();
};