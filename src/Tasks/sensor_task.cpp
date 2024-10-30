#include <Arduino.h>
#include <NewPing.h>
#include "sensor_task.h"

// sensor
#define TRIG_PIN_IZQUIERDO 5
#define ECHO_PIN_IZQUIERDO 34

#define TRIG_PIN_DERECHO 18
#define ECHO_PIN_DERECHO 39

// En centimetros
#define MAX_DISTANCIA_SENSOR 60 
#define DISTANCIA_OBSTACULO 20  

void sensorTask(void *pvParameters) {
    QueueHandle_t sensorDataQueue = (QueueHandle_t)pvParameters;

    NewPing sensorIzquierdo(TRIG_PIN_IZQUIERDO, ECHO_PIN_IZQUIERDO, MAX_DISTANCIA_SENSOR);
    NewPing sensorDerecho(TRIG_PIN_DERECHO, ECHO_PIN_DERECHO, MAX_DISTANCIA_SENSOR);

    bool obstaculoDetectado = false;

    for (;;){

        unsigned int tiempoIzquierda = sensorIzquierdo.ping_median(3);
        unsigned int tiempoDerecha = sensorDerecho.ping_median(3);

        unsigned int distanciaIzquierda = tiempoIzquierda/58;
        unsigned int distanciaDerecha = tiempoDerecha/58;
        
        if ((distanciaIzquierda > 5 && distanciaIzquierda <= DISTANCIA_OBSTACULO) || 
            (distanciaDerecha > 5 && distanciaDerecha <= DISTANCIA_OBSTACULO)) {
            if(!obstaculoDetectado){
                obstaculoDetectado = true;
                if (xQueueSend(sensorDataQueue, &obstaculoDetectado, portMAX_DELAY) != pdPASS) {
                    Serial.println("Failed to send to queue.");
                }
            }

        }else{
            if(obstaculoDetectado){
                obstaculoDetectado = false;
                if (xQueueSend(sensorDataQueue, &obstaculoDetectado, portMAX_DELAY) != pdPASS) {
                    Serial.println("Failed to send to queue.");
                }
            }
        }

        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}
