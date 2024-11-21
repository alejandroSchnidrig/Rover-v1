#include "ConexionWifi.h"

ConexionWifi::ConexionWifi(const char *ssid, const char *password){
      this->ssid = ssid;
      this->password = password;
 }

void ConexionWifi::crearRed(){
    // Optional: Set a custom IP address
    IPAddress local_IP(192, 168, 4, 1);
    IPAddress gateway(192, 168, 4, 1);
    IPAddress subnet(255, 255, 255, 0);

    // Configure the Soft AP IP address before starting the AP
    if (!WiFi.softAPConfig(local_IP, gateway, subnet)) {
        Serial.println("AP Config failed.");
        return;
    }

    // Start the Wi-Fi network
    if (WiFi.softAP(this->ssid, this->password)) {
        Serial.println("Soft AP started successfully.");
    } else {
        Serial.println("Soft AP start failed.");
        return;
    }

    // Get and print the IP address
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
}
