#include "LaaCancello.h"
#include "LaaWifiWsBoiderplate.h"

#include <Arduino.h>

LaaWifiWs laaWifi;
LaaCancello laaCancelli(15, 2);
// LaaListaLed laaListaLed(4);

void wsCallbackReceive(String wsKey, String wsValue) {
  laaCancelli.laaConnectToAppTelecomando(wsKey, wsValue);
  // laaListaLed.laaColorDisponibilitaParcheggio(wsKey, wsValue);
};

void setup() {
  laaWifi.laaSetup(String("pesentiws-43f6274c0f11.herokuapp.com"), String("nomeWifi"),
                   String("passwordWifi"));
  laaWifi.laaOnReceiveMessage(&wsCallbackReceive);
};

void loop() {
  laaWifi.laaLoop();
}