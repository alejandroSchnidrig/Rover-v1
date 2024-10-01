class Ruedas {
private:
    int pinA;
    int pinB;
    int pinPWM;

public:
    Ruedas(int pinA, int pinB, int pinPWM);
    
    void inicializar();
    void moverAdelante(int velocidad);
    void moverAtras(int velocidad);
    void girarALaDerecha(int velocidad);
    void girarALaIzquierda(int velocidad);
    void detener();
};