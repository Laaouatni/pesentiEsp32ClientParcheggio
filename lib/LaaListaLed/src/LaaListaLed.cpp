#include <Adafruit_NeoPixel.h>
#include <vector>
#include "LaaWifiWsBoiderplate.h"
#include "LaaListaLed.h"
#include <Arduino.h>





LaaListaLed::LaaListaLed(int pin) {
  thisLista = Adafruit_NeoPixel(60, pin);
  thisLista.begin();
  thisLista.setBrightness(50);
}

void LaaListaLed::laaColorDisponibilitaParcheggio(String wsKey, String wsValue) {
  bool canRun = wsKey == "cameraInput";
  if (!canRun) { return; }
  LaaWifiWs           thisWifiClass = LaaWifiWs();
  static std::vector<String> wsValueArray = thisWifiClass.splitStringIntoVectorStringArray(wsValue);
  for (int i = 0; i < wsValueArray.size(); i++) {
    thisLista.setPixelColor(i, wsValueArray[i] == "0" ? COLOR_GREEN : COLOR_RED);
  }
  thisLista.show();
}