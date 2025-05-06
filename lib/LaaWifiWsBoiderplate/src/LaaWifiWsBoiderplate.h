#include <Arduino.h>

class LaaWifiWs {
  public:
    LaaWifiWs(String wsServerUrl, String wifiNome = "nomeWifi", String wifiPassword = "passwordWifi");

  private:
    void laaConnectToWifi(String wifiNome, String wifiPassword);
};