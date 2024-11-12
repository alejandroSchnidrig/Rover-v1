#ifndef CORTADORA_H
#define CORTADORA_H

class Cortadora {
private:
    int pinA;
    int pinB;

public:
    Cortadora(int pinA, int pinB);
    void cortar();
}; 

#endif