#include "RoverControl.h"

RoverControl::RoverControl(int port, Rover* rover, ControladorWeb& controladorWeb) : server(port), rover(rover), controladorWeb(controladorWeb) {}

void RoverControl::startServer(){
   
    server.on("/", [this]() {
        server.send(200, "text/html", controladorWeb.getWebApp());
    });

    server.on("/AVANZAR", [this]() {
        rover->avanzar(255);
    });

    server.on("/RETROCEDER", [this]() {
        rover->retroceder(190);
    });

    server.on("/GIRO_IZQUIERDA", [this]() {
        rover->girarALaIzquierda(200);
    });

    server.on("/GIRO_DERECHA", [this]() {
        rover->girarALaDerecha(200);
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
