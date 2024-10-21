#include "ConexionWifi.h"

ConexionWifi::ConexionWifi(const char *ssid, const char *password){
    this->ssid = ssid;
    this->password = password;
}

void ConexionWifi::conectar(){
    WiFi.begin(ssid, password);

    Serial.print("Conectando a WiFi...");
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);  
        Serial.print(".");
    }

    Serial.println("\nConectado a la red WiFi.");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());
}

bool ConexionWifi::estaConectado(){
    return WiFi.status() == WL_CONNECTED;
}

void ConexionWifi::desconectar(){
    WiFi.disconnect();
    Serial.println("Desconectado del WiFi.");
}
