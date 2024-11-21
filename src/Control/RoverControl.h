#include <WebServer.h>
#include "./Rover/Rover.h"
#include "ControladorWeb.h"

class RoverControl {
  private:
    WebServer server;
    Rover* rover;
    ControladorWeb& controladorWeb;

  public:
    RoverControl(int port, Rover* rover, ControladorWeb& controladorWeb);

    void startServer();
    void handleClient();
};