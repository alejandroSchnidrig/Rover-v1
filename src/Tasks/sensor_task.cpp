#include <Arduino.h>
#include <NewPing.h>
#include "sensor_task.h"

// sensor
#define TRIG_PIN_1 5
#define ECHO_PIN_1 34

#define TRIG_PIN_2 18
#define ECHO_PIN_2 39

#define BUZZER 4

#define MAX_DISTANCIA_SENSOR 60 //(80 cm)
#define DISTANCIA_OBSTACULO 35  //(30cm)

void sensorTask(void *pvParameters) {
    QueueHandle_t sensorDataQueue = (QueueHandle_t)pvParameters;

    NewPing sensor1(TRIG_PIN_1, ECHO_PIN_1, MAX_DISTANCIA_SENSOR);
    NewPing sensor2(TRIG_PIN_2, ECHO_PIN_2, MAX_DISTANCIA_SENSOR);

    int sensorValue = 0;

    bool obstaculoDetectado = false;

    for (;;){
        unsigned int distancia1 = sensor1.ping_cm();
        unsigned int distancia2 = sensor2.ping_cm();

        if(distancia1 > 5 && distancia1 <= DISTANCIA_OBSTACULO){
            distancia1 = sensor1.ping_cm();
        }

        if(distancia2 > 5 && distancia1 <= DISTANCIA_OBSTACULO){
            distancia2 = sensor2.ping_cm();
        }
        
        if ((distancia1 > 5 && distancia1 <= DISTANCIA_OBSTACULO) || 
            (distancia2 > 5 && distancia2 <= DISTANCIA_OBSTACULO)) {

            sensorValue = distancia1;
            if (xQueueSend(sensorDataQueue, &sensorValue, portMAX_DELAY) != pdPASS) {
                Serial.println("Failed to send to queue.");
            }

            if(obstaculoDetectado == false){
                obstaculoDetectado = true;
                for(int i = 0; i < 3; i++){
                    digitalWrite(BUZZER, HIGH);
                    delay(50);
                    digitalWrite(BUZZER, LOW);
                    delay(50);
                }
            }
        }else{
            obstaculoDetectado = false;
        }

        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}
