#include "LaaCancello.h"
#include <Ticker.h>
#include <ESP32Servo.h>

Ticker myDelay;

struct Cancello {
    int   pin;
    Servo motore;
};

class LaaCancello {
  public:
    void logicCancello(String wsKey, String wsValue);

  private:
    Cancello cancelloEntrata = {.pin = 15, .motore = Servo()};
    Cancello cancelloUscita  = {.pin = 2, .motore = Servo()};
    void     moveCancello(Cancello &cancello, int angolo);
}

void LaaCancello::moveCancello(Cancello &cancello, int angolo) {
  cancello.motore.attach(cancello.pin);
  cancello.motore.write(angolo);

  myDelay.once_ms(250, [&cancello]() { cancello.motore.detach(); })
}

void LaaCancello::logicCancello(String wsKey, String wsValue) {
  if (wsKey == "ingresso") {
    int angolo = wsValue == "0" ? 90 : 0;
    moveCancello(cancelloEntrata, angolo);
  }

  if (wsKey == "uscita") {
    int angolo = wsValue == "1" ? 180 : 90;
    moveCancello(cancelloUscita, angolo);
  }
}