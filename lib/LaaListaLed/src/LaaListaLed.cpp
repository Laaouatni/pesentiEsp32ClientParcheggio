#include <Adafruit_NeoPixel.h>

class LaaListaLed {
  public:
    LaaListaLed(int pin) {
      thisLista = Adafruit_NeoPixel(60, pin);
      thisLista.begin();
      thisLista.setBrightness(50);
    };

    void laaColorDisponibilitaParcheggio(String wsKey, String wsValue) {
      bool canRun = wsKey == "cameraInput";
      if (!canRun) { return; }
      std::vector wsValueArray = LaaWifiWs::splitStringIntoVectorStringArray(wsValue);
      for (int i = 0; i < wsValueArray.size(); i++) {
        thisLista.setPixelColor(i, wsValueArray[i] == "0" ? COLOR_GREEN : COLOR_RED);
      }
      thisLista.show();
    }

  private:
    Adafruit_NeoPixel thisLista;
    const int         COLOR_RED   = thisLista.Color(255, 0, 0);
    const int         COLOR_GREEN = thisLista.Color(0, 255, 0);
};