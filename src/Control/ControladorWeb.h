#ifndef CONTROLADORWEB_H
#define CONTROLADORWEB_H

#include <WiFi.h>

class ControladorWeb {
    public:
        ControladorWeb();
        String getWebApp();
};

#endif