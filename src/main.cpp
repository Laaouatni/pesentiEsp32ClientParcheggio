#include "LaaCancello.h"
#include "LaaWifiWsBoiderplate.h"

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <vector>

LaaWifiWs         laaWifi;
LaaCancello       laaCancelli(15, 2);
Adafruit_NeoPixel thisLista(60, 4);

const int COLOR_RED                  = thisLista.Color(255, 0, 0);
const int COLOR_GREEN                = thisLista.Color(0, 255, 0);
const int NUM_PARCHEGGI              = 9;
const int LED_INDEXES[NUM_PARCHEGGI] = {50,47,43,30,26,23,10,6,3};

void wsCallbackReceive(String wsKey, String wsValue) {
  // if (wsKey == "cancelloCameraInput") {
  //   const char canOpenEntrataChar        = wsValue.charAt(0 * 2);
  //   const char canOpenUscitaChar         = wsValue.charAt(1 * 2);
  //   laaCancelli.cancelloEntrata.canClose = canOpenEntrataChar == '0';
  //   laaCancelli.cancelloUscita.canClose  = canOpenUscitaChar == '0';
  //   if (laaCancelli.cancelloEntrata.canClose) {
  //     laaCancelli.laaMoveCancello(laaCancelli.cancelloEntrata, 90, "ingresso");
  //   }
  //   if (laaCancelli.cancelloUscita.canClose) {
  //     laaCancelli.laaMoveCancello(laaCancelli.cancelloUscita, 180, "uscita");
  //   }
  //   return;
  // };
  // if (wsKey == "slotsCameraInput") {
  //   for (int ledIndex = 0; ledIndex < NUM_PARCHEGGI; ledIndex++) {
  //     const int  charIndex = ledIndex * 2;
  //     const char thisValue = String(wsValue).charAt(charIndex);
  //     thisLista.setPixelColor(LED_INDEXES[ledIndex], thisValue == '0' ? COLOR_GREEN : COLOR_RED);
  //   }
  //   thisLista.show();
  //   return;
  // };
  laaCancelli.laaConnectToAppTelecomando(wsKey, wsValue);
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