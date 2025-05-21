#ifndef LAALISTALED_H
#define LAALISTALED_H

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <vector>
#include "LaaWifiWsBoiderplate.h"

class LaaListaLed {
  private:
    Adafruit_NeoPixel thisLista;
    const int         COLOR_RED = thisLista.Color(255,0,0);
    const int         COLOR_GREEN = thisLista.Color(0,255,0);
  public:
    LaaListaLed(int pin);
    void laaColorDisponibilitaParcheggio(String wsKey, String wsValue);
};

#endif // LAALISTALED_H