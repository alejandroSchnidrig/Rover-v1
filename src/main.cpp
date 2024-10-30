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
#include "Tasks/control_handler.h"
#include "Tasks/sensor_task.h"

QueueHandle_t colaDeSensor;

void setup() {
    Serial.begin(115200);

    colaDeSensor = xQueueCreate(5, sizeof(bool));

    if (colaDeSensor == NULL) {
        Serial.println("Fallo en la creacion de la cola");
        while (1); 
    }

    xTaskCreatePinnedToCore(sensorTask, "Sensor Task", 2048, (void *)colaDeSensor, 1, NULL, 0);
    xTaskCreatePinnedToCore(controlTask, "Motor Task", 4096, (void *)colaDeSensor, 1, NULL, 1);
}

void loop() {
    // FreeRTOS
}

