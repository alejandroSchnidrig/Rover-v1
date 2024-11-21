#include "RoverControl.h"

#define HTTP_STATUS_OK 200
#define VELOCIDAD_AVANZAR 255
#define VELOCIDAD_RETROCEDER 190
#define VELOCIDAD_GIRO 200

RoverControl::RoverControl(int port, Rover* rover, ControladorWeb& controladorWeb) : server(port), rover(rover), controladorWeb(controladorWeb) {}

void RoverControl::startServer(){
   
    server.on("/", [this]() {
        server.send(HTTP_STATUS_OK, "text/html", controladorWeb.getWebApp());
    });

    server.on("/AVANZAR", [this]() {
        rover->avanzar(VELOCIDAD_AVANZAR);
    });

    server.on("/RETROCEDER", [this]() {
        rover->retroceder(VELOCIDAD_RETROCEDER);
    });

    server.on("/GIRO_IZQUIERDA", [this]() {
        rover->girarALaIzquierda(VELOCIDAD_GIRO);
    });

    server.on("/GIRO_DERECHA", [this]() {
        rover->girarALaDerecha(VELOCIDAD_GIRO);
    });

    server.on("/PARAR", [this]() {
        rover->parar();
    });

    server.on("/CORTADORA", [this]() {
        rover->girarCortadora();
    });

    server.begin();
}

void RoverControl::handleClient(){
    server.handleClient();
}
