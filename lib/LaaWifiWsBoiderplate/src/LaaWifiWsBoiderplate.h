#ifndef LAA_WIFI_WS_BOIDERPLATE_H
#define LAA_WIFI_WS_BOIDERPLATE_H

#include <Arduino.h>
#include <WebSocketsClient.h>
#include <WiFi.h>

class LaaWifiWs {
  public:
    LaaWifiWs(String wsServerUrl, String wifiNome = "nomeWifi",
              String wifiPassword = "passwordWifi");
    void laaOnReceiveMessage(void (*myCallback)(String wsKey, String wsValue));
    // void laaSetup();
    void laaLoop();

  private:
    WebSocketsClient wsClient;

    // String _wifiNome;
    // String _wifiPassword;

    void laaConnectToWifi(String wifiNome, String wifiPassword);
    void laaConnectToWs(String wsServerUrl);
};

#endif