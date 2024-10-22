#include "ConexionWifi.h"

ConexionWifi::ConexionWifi(const char *ssid, const char *password){
      this->ssid = ssid;
      this->password = password;
 }

void ConexionWifi::crearRed(){
    WiFi.softAP(ssid, password);
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
}
