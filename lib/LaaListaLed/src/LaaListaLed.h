#ifndef LAALISTALED_H
#define LAALISTALED_H

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <vector>

class LaaListaLed {
  public:
    LaaListaLed(int pin);
    void laaColorDisponibilitaParcheggio(String wsKey, String wsValue);

  private:
    Adafruit_NeoPixel thisLista;
    const int         COLOR_RED;
    const int         COLOR_GREEN;
};

#endif // LAALISTALED_H