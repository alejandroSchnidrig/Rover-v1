#ifndef ALARMA_H
#define ALARMA_H

class Alarma {
private:
    int pinA;

public:
    Alarma(int pinA);
    void configurar();
    void encenderAlarma();
    void apagarAlarma();
}; 

#endif