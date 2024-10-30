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
#include "ConexionWifi.h"
#include "ControladorWeb.h"
#include "RoverControl.h"
#include <NewPing.h>

#define DERECHA_A 12
#define DERECHA_B 14
#define DERECHA_PWM 13
#define IZQUIERDA_A 26
#define IZQUIERDA_B 27
#define IZQUIERDA_PWM 25

// sensor
#define TRIG_PIN_1 5
#define ECHO_PIN_1 34

#define TRIG_PIN_2 18
#define ECHO_PIN_2 39

#define BUZZER 4

#define MAX_DISTANCIA_SENSOR 60 //(60 cm)
#define DISTANCIA_OBSTACULO 35  //(35cm)

NewPing sensor1(TRIG_PIN_1, ECHO_PIN_1, MAX_DISTANCIA_SENSOR);
NewPing sensor2(TRIG_PIN_2, ECHO_PIN_2, MAX_DISTANCIA_SENSOR);

// credenciales a la re wifi
const char* ssid = "WIFI_ROVER";
const char* password = "123456789";

TaskHandle_t TaskSensores, TaskControl;
QueueHandle_t colaDeSensor;

ConexionWifi wifi(ssid, password);
Rover rover(DERECHA_A, DERECHA_B, DERECHA_PWM, IZQUIERDA_A, IZQUIERDA_B, IZQUIERDA_PWM);
ControladorWeb controladorWeb;
RoverControl roverControl(80, &rover, controladorWeb);

void loopSensores(void *parameter){

    int obstaculoDetectado = 0;

    for (;;){
        unsigned int distancia1 = sensor1.ping_cm();
        unsigned int distancia2 = sensor2.ping_cm();
        obstaculoDetectado = (distancia1 <= DISTANCIA_OBSTACULO || distancia2 <= DISTANCIA_OBSTACULO) ? 1 : 0;

        xQueueSend(colaDeSensor, &obstaculoDetectado, portMAX_DELAY);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void loopControl(void *parameter){
    int obstaculoDetectado;

    for (;;){
        if (xQueueReceive(colaDeSensor, &obstaculoDetectado, portMAX_DELAY)){
            if (obstaculoDetectado){
                rover.parar();
                rover.retroceder(255);
                vTaskDelay(300 / portTICK_PERIOD_MS);
                rover.girarALaDerecha(200);
                vTaskDelay(300 / portTICK_PERIOD_MS);
                rover.parar();
            } else {
                roverControl.handleClient();
            }
        }
    }
}

void setup(){
    Serial.begin(115200);
    pinMode(BUZZER, OUTPUT);
    wifi.crearRed();
    rover.inicializar();
    roverControl.startServer();

    colaDeSensor = xQueueCreate(5, sizeof(int));

    if (colaDeSensor == NULL) {
        Serial.println("Fallo en la creación de la cola");
        while (1);
    }

    xTaskCreatePinnedToCore(loopSensores, "TaskSensores", 10000, NULL, 1, &TaskSensores, 0);
    xTaskCreatePinnedToCore(loopControl, "TaskControl", 4096, NULL, 1, &TaskControl, 1);
}

void loop(){
   //roverControl.handleClient();
}
