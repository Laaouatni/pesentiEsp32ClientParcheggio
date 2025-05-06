#include <Arduino.h>
#include <WebSocketsClient.h>
#include <WiFi.h>

#include <vector>

class LaaWifi {
 public:
  LaaWifi(String wsServerUrl, String wifiNome = "nomeWifi",
          String wifiPassword = "passwordWifi") {
    laaConnectToWifi();
  }

 private:
  void laaConnectToWifi();
};

// laaConnectToWifi function definition
void LaaWifi::laaConnectToWifi() {
  const String NOME_WIFI = ;
  const String PASSWORD_WIFI = "passwordWifi";

  Serial.println("Connecting to WiFi...");

  WiFi.begin(NOME_WIFI, PASSWORD_WIFI);
  while (WiFi.status() != WL_CONNECTED);
  Serial.println("WiFi connected! IP Address: " + WiFi.localIP().toString());
}