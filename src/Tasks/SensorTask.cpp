#include <Arduino.h>
#include <NewPing.h>
#include "./Sensores/Sensor.h"
#include "SensorTask.h"

// sensor pines
#define TRIG_PIN_IZQUIERDO 5
#define ECHO_PIN_IZQUIERDO 34

#define TRIG_PIN_DERECHO 18
#define ECHO_PIN_DERECHO 39

// En centimetros
#define MAX_DISTANCIA_SENSOR 60
#define DISTANCIA_OBSTACULO 30

#define TIEMPO_DELAY 40

void SensorTask(void *pvParameters) {
    QueueHandle_t sensorDataQueue = (QueueHandle_t)pvParameters;

    Sensor sensorDerecho(TRIG_PIN_DERECHO, ECHO_PIN_DERECHO, MAX_DISTANCIA_SENSOR, DISTANCIA_OBSTACULO);
    Sensor sensorIzquierdo(TRIG_PIN_IZQUIERDO, ECHO_PIN_IZQUIERDO, MAX_DISTANCIA_SENSOR, DISTANCIA_OBSTACULO);

    bool obstaculoDetectado = false;

    for (;;){

        //Verificar si hubo un cambio de estado en cualquiera de los sensores
        if (sensorIzquierdo.actualizarEstado() || sensorDerecho.actualizarEstado()) {
            //Actualizar el valor de obstaculoDetectado según el estado de los sensores
            obstaculoDetectado = sensorIzquierdo.detectarObstaculo() || sensorDerecho.detectarObstaculo();

            //Enviar el nuevo estado a la cola
            if (xQueueSend(sensorDataQueue, &obstaculoDetectado, portMAX_DELAY) != pdPASS) {
                Serial.println("Failed to send to queue.");
            }
        }

        //delay para no sobrecargar los sensores
        vTaskDelay(TIEMPO_DELAY / portTICK_PERIOD_MS);
    }
}
