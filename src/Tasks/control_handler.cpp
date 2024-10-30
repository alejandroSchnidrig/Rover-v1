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
    QueueHandle_t controlDataQueue = (QueueHandle_t)pvParameters; //Declaracion de la cola de datos

    //Creo la red wifi AP y configuro tanto el Rover como su controlador para ser usados
    wifi.crearRed();
    rover.inicializar();
    roverControl.startServer();

    //Configuracion del pin de Buzzer
    pinMode(BUZZER, OUTPUT);

    bool controlAutomatico = false; //Booleano que monitorea el modo de control
    unsigned long tiempoDeInicio; //Monitoreo del tiempo

    for (;;) {

        //Recibo una señal booleana de los sensores, true si detecta un obstaculo 
        //Se guarda en la variable controlAutomatico, porque de ser detectado
        //Un obstaculo, quiero que el control pase de ser manual a automatico
        if(xQueueReceive(controlDataQueue, &(controlAutomatico),(TickType_t) 10) == pdPASS ){
            //Cuando detecto cualquier señal que proviene de los sensores, paro el rover para
            //manejar la situacion
            rover.parar();

            //indicacion sonora de un cambio de estado
            digitalWrite(BUZZER, HIGH);
            vTaskDelay(50 / portTICK_PERIOD_MS);
            digitalWrite(BUZZER, LOW);
            vTaskDelay(50 / portTICK_PERIOD_MS);

            //Si se detecta que se cambia a un controlAutomatico, empiezo a monitorear el tiempo
            if(controlAutomatico) tiempoDeInicio = millis();
        }

        if(controlAutomatico){
            //retrocedo para evadir el obstaculo y espero un poco para tener un margen de maniobra
            rover.retroceder(150);
            vTaskDelay(15 / portTICK_PERIOD_MS);

            if((millis() - tiempoDeInicio) > 3000) {
                //Si estoy en modo automatico por mas de 3 segundos asumo que algo está mal y aborto
                //El control automatico con una doble señal sonora
                digitalWrite(BUZZER, HIGH);
                vTaskDelay(50 / portTICK_PERIOD_MS);
                digitalWrite(BUZZER, LOW);
                vTaskDelay(50 / portTICK_PERIOD_MS);

                digitalWrite(BUZZER, HIGH);
                vTaskDelay(50 / portTICK_PERIOD_MS);
                digitalWrite(BUZZER, LOW);

                rover.parar();
                controlAutomatico = false;
            }
        }else{
            //Si el control es manual entonces manejo las peticiones de la aplicacion web
            roverControl.handleClient();
        }
    }
}
