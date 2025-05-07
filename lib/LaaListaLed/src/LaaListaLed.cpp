#include <Adafruit_NeoPixel.h>

class LaaListaLed {
  public:
    LaaListaLed(int pin) { _pin = pin; };
    void laaColorDisponibilitaParcheggio(String wsKey, String wsValue) {
      bool canRun = wsKey == "cameraInput";
      if (!canRun) return;
      

    }

  private:
    int _pin;
};