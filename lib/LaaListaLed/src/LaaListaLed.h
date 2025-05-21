#ifndef LAALISTALED_H
#define LAALISTALED_H

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <vector>
#include "LaaWifiWsBoiderplate.h"

class LaaListaLed {
  private:
    Adafruit_NeoPixel thisLista;
    int               COLOR_RED;
    int               COLOR_GREEN;

  public:
    LaaListaLed(int pin);
    void laaColorDisponibilitaParcheggio(String wsKey, String wsValue);
};

#endif // LAALISTALED_H