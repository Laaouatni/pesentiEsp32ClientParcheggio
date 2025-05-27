#include "LaaCancello.h"
#include "LaaWifiWsBoiderplate.h"
// #include "LaaListaLed.h"

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <vector>

LaaWifiWs         laaWifi;
LaaCancello       laaCancelli(15, 2);
Adafruit_NeoPixel thisLista(60, 4);

const int COLOR_RED     = thisLista.Color(255, 0, 0);
const int COLOR_GREEN   = thisLista.Color(0, 255, 0);
const int NUM_PARCHEGGI = 9;

void wsCallbackReceive(String wsKey, String wsValue) {
  laaCancelli.laaConnectToAppTelecomando(wsKey, wsValue);
  if (wsKey == "cameraInput") {
    for (int ledIndex = 0; ledIndex < NUM_PARCHEGGI; ledIndex++) {
      const int    charIndex = ledIndex*2;
      const char thisValue = wsValue.charAt(charIndex);
      thisLista.setPixelColor(ledIndex, thisValue == "0" ? COLOR_GREEN : COLOR_RED);
    }
    thisLista.show();
  };
};

void setup() {
  thisLista.begin();
  thisLista.setBrightness(10);
  thisLista.fill(0);
  thisLista.show();
  laaWifi.laaSetup(String("pesentiws-43f6274c0f11.herokuapp.com"), String("nomeWifi"),
                   String("passwordWifi"));
  laaWifi.laaOnReceiveMessage(&wsCallbackReceive);
};

void loop() {
  laaWifi.laaLoop();
}