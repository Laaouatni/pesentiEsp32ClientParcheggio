#ifndef LAA_WIFI_WS_BOIDERPLATE_H
#define LAA_WIFI_WS_BOIDERPLATE_H

#include <Arduino.h>
#include <WebSocketsClient.h>
#include <WiFi.h>
#include <vector>

class LaaWifiWs {
  public:
    LaaWifiWs();
    void laaOnReceiveMessage(void (*myCallback)(String wsKey, String wsValue));
    void laaSetup(String wsServerUrl, String wifiNome, String wifiPassword);
    void laaLoop();

  private:
    WebSocketsClient wsClient;
    void laaConnectToWifi(String wifiNome, String wifiPassword);
    void laaConnectToWs(String wsServerUrl);
};

#endif