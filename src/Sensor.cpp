#include "Sensor.h"

#define TIEMPO_MEDIA 3
#define TIEMPO_APROXIMADO 58
#define DISTANCIA_MAXIMA 5

Sensor::Sensor(int triggerPin, int echoPin, int maxDistance, 
    unsigned int distanciaObstaculo)
        : sensor(triggerPin, echoPin, maxDistance), 
        distanciaObstaculo(distanciaObstaculo) {}

//calculo una mediana de 3 valores para tener una medicion
//mas precisa y evitar saltos en las mediciones
unsigned int Sensor::getDistancia(){
    unsigned int tiempo = sensor.ping_median(TIEMPO_MEDIA);
    return tiempo / TIEMPO_APROXIMADO;
}

bool Sensor::detectarObstaculo(){
    unsigned int distancia = getDistancia();
    return (distancia > DISTANCIA_MAXIMA && distancia <= distanciaObstaculo);
}

bool Sensor::actualizarEstado(){
    bool estadoActual = detectarObstaculo();
    if (estadoActual != obstaculoDetectado) {
        obstaculoDetectado = estadoActual;  
        return true;
    }
    return false;
}
