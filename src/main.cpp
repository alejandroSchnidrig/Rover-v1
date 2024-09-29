/**
 * UnTref 2024
 * Diseño y Arquitectura de Sistemas de Computación
 *
 * Proyecto: FarmBot
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
#include "Motor.h"

Motor motor;

void setup()
{
    Serial.begin(115200);

    motor.inicializar();
    delay(3000);  // Espera de 3 segundos
    
    //criterio de aceptacion 1
    motor.avanzar();
    delay(5000);
    motor.parar();

    delay(5000);

    //criterio de aceptacion 2
    motor.retroceder();
    delay(5000);
    motor.parar();

    delay(5000);

    //criterio de aceptacion 3
    motor.avanzar();
    delay(5000);
    motor.parar();
    delay(500);
    motor.retroceder();
    delay(5000);
    motor.parar();

    delay(5000);

    //criterio de aceptacion 4
    motor.retroceder();
    delay(5000);
    motor.parar();
    delay(500);
    motor.avanzar();
    delay(5000);
    motor.parar();
}

void loop()
{
   Serial.println("Rover en funcionamiento");
}
