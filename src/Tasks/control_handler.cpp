#include <Arduino.h>
#include "control_handler.h"
#include "./Rover.h"
#include "./RoverControl.h"
#include "./ConexionWifi.h"
#include "./ControladorWeb.h"

#define DERECHA_A 12
#define DERECHA_B 14
#define DERECHA_PWM 13
#define IZQUIERDA_A 26
#define IZQUIERDA_B 27
#define IZQUIERDA_PWM 25

#define BUZZER 4

const char* ssid = "WIFI_ROVER";
const char* password = "123456789";

ConexionWifi wifi(ssid, password);
Rover rover(DERECHA_A, DERECHA_B, DERECHA_PWM, IZQUIERDA_A, IZQUIERDA_B, IZQUIERDA_PWM);
ControladorWeb controladorWeb;
RoverControl roverControl(80, &rover, controladorWeb);

void controlTask(void *pvParameters) {
    QueueHandle_t sensorDataQueue = (QueueHandle_t)pvParameters;

    wifi.crearRed();
    rover.inicializar();
    roverControl.startServer();

    pinMode(BUZZER, OUTPUT);

    int receivedValue = 0;
    for (;;) {
        if (xQueueReceive(sensorDataQueue, &receivedValue, portMAX_DELAY) == pdPASS) {
            rover.parar();
            vTaskDelay(50 / portTICK_PERIOD_MS);
            rover.retroceder(150);
            vTaskDelay(50 / portTICK_PERIOD_MS);
            rover.parar();
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }else{
            roverControl.handleClient();
        }
    }
}
