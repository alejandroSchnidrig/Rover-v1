/**
 * UnTref 2024
 * Diseño y Arquitectura de Sistemas de Computación
 *
 * Proyecto: Rover
 * Integrantes:
 *  -Balmelli Pérez Mateo 
 *  -Di Leo, Tomás
 *  -Schnidrig Alejandro
 *
 * Docentes:
 *  -Fossati, Jorge
 *  -Moreno Fernández, Joaquín
 */

#include <Arduino.h>
#include "Rover.h"

#define DERECHA_A 12
#define DERECHA_B 14
#define DERECHA_PWM 13
#define IZQUIERDA_A 26
#define IZQUIERDA_B 27
#define IZQUIERDA_PWM 25

// Crear instancia del Rover
Rover rover(DERECHA_A, DERECHA_B, DERECHA_PWM, IZQUIERDA_A, IZQUIERDA_B, IZQUIERDA_PWM);

void setup()
{
    Serial.begin(115200);

    rover.inicializar();
    delay(3000);  // Espera de 3 segundos
    
    //criterio de aceptacion 1
    rover.avanzar(200);
    delay(5000);
    rover.parar();

    delay(5000);

    //criterio de aceptacion 2
    rover.retroceder(200);
    delay(5000);
    rover.parar();

    delay(5000);

    //criterio de aceptacion 3
    rover.avanzar(200);
    delay(5000);
    rover.parar();
    delay(500);
    rover.retroceder(200);
    delay(5000);
    rover.parar();

    delay(5000);

    //criterio de aceptacion 4
    rover.retroceder(200);
    delay(5000);
    rover.parar();
    delay(500);
    rover.avanzar(200);
    delay(5000);
    rover.parar();

    //requerimiento N°2
    //criterio de aceptacion 1
    rover.girarALaDerecha(255);
    delay(2000);
    rover.avanzar(200);
    delay(3000);
    rover.parar();

    //criterio de aceptacion 2
    rover.girarALaIzquierda(255);
    delay(2000);
    rover.avanzar(200);
    delay(3000);
    rover.parar();
}

void loop()
{
   Serial.println("Rover en funcionamiento");
}
