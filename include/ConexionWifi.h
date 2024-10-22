#include <WiFi.h>

class ConexionWifi {
  private:
    const char* ssid;
    const char* password;

  public:
    ConexionWifi(const char* ssid, const char* password);
    void crearRed();
};