#include "LaaListaLed.h"

#include "LaaWifiWsBoiderplate.h"

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <vector>

LaaListaLed::LaaListaLed(int pin) {
  thisLista   = Adafruit_NeoPixel(60, pin);
  thisLista.begin();
  thisLista.setBrightness(10);
  thisLista.fill(0);
  thisLista.show();
}

void LaaListaLed::laaColorDisponibilitaParcheggio(String wsKey, String wsValue) {
  const int COLOR_RED   = thisLista.Color(255, 0, 0);
  const int COLOR_GREEN = thisLista.Color(0, 255, 0);
  bool canRun = wsKey == "cameraInput";
  if (!canRun) { return; }
  LaaWifiWs                  thisWifiClass = LaaWifiWs();
  std::vector<String> wsValueArray = thisWifiClass.splitStringIntoVectorStringArray(wsValue);
  for (int i = 0; i < wsValueArray.size(); i++) {
    Serial.println(String(i) + "\t" + wsValueArray[i] + "\t");
    thisLista.setPixelColor(i, wsValueArray[i] == "0" ? COLOR_GREEN : COLOR_RED);
  }
  thisLista.show();
}