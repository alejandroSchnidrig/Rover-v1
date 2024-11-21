#ifndef CORTADORA_H
#define CORTADORA_H

class Cortadora {
private:
    int pinA;
    int pinB;
    int pinPWM;
    int valorPWM;

public:
    Cortadora(int pinA, int pinB, int pinPWM);
    void inicializar();
    void cortar();
    void parar();
}; 

#endif