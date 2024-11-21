#include <Arduino.h>
#include "ControlTask.h"
#include "./Rover/Rover.h"
#include "./Control/RoverControl.h"
#include "./WiFi/ConexionWifi.h"
#include "./Control/ControladorWeb.h"
#include "./Sensores/SensorCorriente.h"

#define DERECHA_A 12
#define DERECHA_B 14
#define DERECHA_PWM 13
#define IZQUIERDA_A 26
#define IZQUIERDA_B 27
#define IZQUIERDA_PWM 25
#define MEDIO_A 32
#define MEDIO_B 33
#define MEDIO_PWM 23
#define BUZZER 4
#define SENSOR 36

#define PUERTO 80
#define DEFAULT_DELAY 50
#define ALARMA_DELAY 100
#define TIEMPO_TICK 10
#define TIEMPO_ESPERA 3000
#define TIEMPO_DELAY 15
#define VELOCIDAD_RETROCEDER 150

const char* ssid = "WIFI_ROVER";
const char* password = "123456789";

ConexionWifi wifi(ssid, password);
Rover rover(DERECHA_A, DERECHA_B, DERECHA_PWM, IZQUIERDA_A, IZQUIERDA_B, IZQUIERDA_PWM, MEDIO_A, MEDIO_B, MEDIO_PWM, BUZZER);
ControladorWeb controladorWeb;
RoverControl roverControl(PUERTO, &rover, controladorWeb);
SensorCorriente sensorCorriente(SENSOR);

void alarmaSonora(Rover& rover, int delay = DEFAULT_DELAY) {
    rover.encenderAlarma();
    vTaskDelay(delay / portTICK_PERIOD_MS);
    rover.apagarAlarma();
    vTaskDelay(delay / portTICK_PERIOD_MS);
}

void ControlTask(void *pvParameters) {
    QueueHandle_t controlDataQueue = (QueueHandle_t)pvParameters; //Declaracion de la cola de datos

    //Creo la red wifi AP y configuro tanto el Rover como su controlador para ser usados
    wifi.crearRed();
    rover.inicializar();
    rover.configurarAlarma();
    roverControl.startServer();

    bool controlAutomatico = false; //Booleano que monitorea el modo de control
    unsigned long tiempoDeInicio; //Monitoreo del tiempo

    for (;;) {

        //Recibo una señal booleana de los sensores, true si detecta un obstaculo 
        //Se guarda en la variable controlAutomatico, porque de ser detectado
        //Un obstaculo, quiero que el control pase de ser manual a automatico
        if(xQueueReceive(controlDataQueue, &(controlAutomatico),(TickType_t) TIEMPO_TICK) == pdPASS ){
            //Cuando detecto cualquier señal que proviene de los sensores, paro el rover para
            //manejar la situacion
            rover.parar();

            //indicacion sonora de un cambio de estado
            alarmaSonora(rover);

            //Si se detecta que se cambia a un controlAutomatico, empiezo a monitorear el tiempo
            if(controlAutomatico) tiempoDeInicio = millis();
        }

        if(controlAutomatico){
            //retrocedo para evadir el obstaculo y espero un poco para tener un margen de maniobra
            rover.retroceder(VELOCIDAD_RETROCEDER);
            vTaskDelay(TIEMPO_DELAY / portTICK_PERIOD_MS);

            if((millis() - tiempoDeInicio) > TIEMPO_ESPERA) {
                //Si estoy en modo automatico por mas de 3 segundos asumo que algo está mal y aborto
                //El control automatico con una doble señal sonora
                alarmaSonora(rover);
                alarmaSonora(rover);
                rover.parar();
                controlAutomatico = false;
            }
        }else{
            //Si el control es manual entonces manejo las peticiones de la aplicacion web
            roverControl.handleClient();

            float corriente = sensorCorriente.sensarCorriente();

            if(corriente > 3.2){
                rover.parar();
                alarmaSonora(rover, ALARMA_DELAY);
                alarmaSonora(rover, ALARMA_DELAY);
                alarmaSonora(rover, ALARMA_DELAY);
                alarmaSonora(rover, ALARMA_DELAY);
            }
        }
    }
}


