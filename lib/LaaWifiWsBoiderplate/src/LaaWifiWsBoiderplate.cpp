#include "LaaWifiWsBoiderplate.h"

#include <Arduino.h>
#include <WebSocketsClient.h>
#include <WiFi.h>

#include <vector>

class LaaWifiWs {
 public:
  LaaWifiWs(String wsServerUrl, 
            String wifiNome = "nomeWifi",
            String wifiPassword = "passwordWifi") {
    laaConnectToWifi(wifiNome, wifiPassword);
  }

 private:
  void laaConnectToWifi(String wifiNome, String wifiPassword);
};

// laaConnectToWifi function definition
void LaaWifiWs::laaConnectToWifi(String wifiNome, String wifiPassword) {
  Serial.println("Connecting to WiFi...");

  WiFi.begin(wifiNome, wifiPassword);
  while (WiFi.status() != WL_CONNECTED);
  Serial.println("WiFi connected! IP Address: " + WiFi.localIP().toString());
}
