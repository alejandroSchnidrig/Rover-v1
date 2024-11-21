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
#include "Tasks/ControlTask.h"
#include "Tasks/SensorTask.h"

#define TAMANO_PILA_TAREA_SENSOR 2048
#define NUCLEO_CPU_TAREA_SENSOR 0
#define TAMANO_PILA_TAREA_CONTROL 4096
#define NUCLEO_CPU_TAREA_CONTROL 1
#define PRIORIDAD_TAREA 1

QueueHandle_t colaDeSensor;

void setup() {

    Serial.begin(115200);

    colaDeSensor = xQueueCreate(5, sizeof(bool));

    if (colaDeSensor == NULL) {
        Serial.println("Fallo en la creacion de la cola");
        while (1); 
    }

    xTaskCreatePinnedToCore(SensorTask, "Sensor Task", TAMANO_PILA_TAREA_SENSOR, (void *)colaDeSensor, PRIORIDAD_TAREA, NULL, NUCLEO_CPU_TAREA_SENSOR);
    xTaskCreatePinnedToCore(ControlTask, "Control Task", TAMANO_PILA_TAREA_CONTROL, (void *)colaDeSensor, PRIORIDAD_TAREA, NULL, NUCLEO_CPU_TAREA_CONTROL);
}

void loop() {
    // FreeRTOS
}

