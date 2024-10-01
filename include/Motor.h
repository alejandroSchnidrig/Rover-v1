#include "Ruedas.h" 

class Motor {
private:
    Ruedas ruedasDerecha;
    Ruedas ruedasIzquierda;

public:
    Motor(int pinDerechaA, int pinDerechaB, int pinDerechaPWM, 
          int pinIzquierdaA, int pinIzquierdaB, int pinIzquierdaPWM);

    void inicializar();
    void avanzar(int velocidad);
    void retroceder(int velocidad);
    void girarALaDerecha(int velocidad);
    void girarALaIzquierda(int velocidad);
    void parar();
};