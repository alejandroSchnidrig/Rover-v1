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

TaskHandle_t TaskSensores;
ConexionWifi wifi(ssid, password);
Rover rover(DERECHA_A, DERECHA_B, DERECHA_PWM, IZQUIERDA_A, IZQUIERDA_B, IZQUIERDA_PWM);
ControladorWeb controladorWeb;
RoverControl roverControl(80, &rover, controladorWeb);

void loopSensores(void *parameter){

    bool obstaculoDetectado = false;

    for (;;){
       

        unsigned int distancia1 = sensor1.ping_cm();
        unsigned int distancia2 = sensor2.ping_cm();

        Serial.print("Sensor 1 : ");
        Serial.println(distancia1);
        Serial.print("Sensor 2 : ");
        Serial.println(distancia2);
        Serial.println(" ");

        if(distancia1 > 5 && distancia1 <= DISTANCIA_OBSTACULO){
            distancia1 = sensor1.ping_cm();
        }

        if(distancia2 > 5 && distancia1 <= DISTANCIA_OBSTACULO){
            distancia2 = sensor2.ping_cm();
        }
        
        if ((distancia1 > 5 && distancia1 <= DISTANCIA_OBSTACULO) || 
            (distancia2 > 5 && distancia2 <= DISTANCIA_OBSTACULO)) {
            rover.parar();
            rover.retroceder(255);
            vTaskDelay(300/ portTICK_PERIOD_MS);
            rover.girarALaDerecha(200);
            vTaskDelay(300 / portTICK_PERIOD_MS);
            rover.parar();
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

void setup(){

    xTaskCreatePinnedToCore(loopSensores, "TaskSensores", 10000, NULL, 1, &TaskSensores, 0);
    
    Serial.begin(115200);

    pinMode(BUZZER, OUTPUT);

    wifi.crearRed();

    rover.inicializar();
   
    roverControl.startServer();

}

void loop(){
   roverControl.handleClient();
}
