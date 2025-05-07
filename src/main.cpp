#include "LaaWifiWsBoiderplate.h"
#include "LaaCancello.h"
#include <Arduino.h>

LaaWifiWs   laaWifi;
LaaCancello laaCancelli(15,2);

void wsCallbackReceive(String wsKey, String wsValue) {
  laaCancelli.laaConnectToAppTelecomando(wsKey, wsValue);
};

void setup() {
  Serial.begin(115200);
  laaWifi = LaaWifiWs(String("pesentiws-43f6274c0f11.herokuapp.com"));
  laaWifi.laaOnReceiveMessage(&wsCallbackReceive);
}

void loop() {
  laaWifi.laaLoop();
}