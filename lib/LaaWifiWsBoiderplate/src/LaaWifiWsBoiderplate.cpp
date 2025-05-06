#include <Arduino.h>
#include <WebSocketsClient.h>
#include <WiFi.h>

#include <vector>

class LaaWifi {
 public:
  LaaWifi(String wsServerUrl) { laaConnectToWifi(); }

 private:
  void laaConnectToWifi() {
    const String NOME_WIFI = "nomeWifi";
    const String PASSWORD_WIFI = "passwordWifi";

    Serial.println("Connecting to WiFi...");
    
    WiFi.begin(NOME_WIFI, PASSWORD_WIFI);
    while (WiFi.status() != WL_CONNECTED);
    Serial.println("WiFi connected! IP Address: " + WiFi.localIP().toString());
  }
}