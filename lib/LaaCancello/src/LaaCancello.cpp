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
    void laaLogicCancello(String wsKey, String wsValue);

  private:
    Cancello cancelloEntrata = {.pin = 15, .motore = Servo()};
    Cancello cancelloUscita  = {.pin = 2, .motore = Servo()};
    void     laaMoveCancello(Cancello &cancello, int angolo);
}

void LaaCancello::laaMoveCancello(Cancello &cancello, int angolo) {
  cancello.motore.attach(cancello.pin);
  cancello.motore.write(angolo);

  myDelay.once_ms(250, [&cancello]() { cancello.motore.detach(); })
}

void LaaCancello::laaLogicCancello(String wsKey, String wsValue) {
  if (wsKey == "ingresso") {
    int angolo = wsValue == "0" ? 90 : 0;
    laaMoveCancello(cancelloEntrata, angolo);
  }

  if (wsKey == "uscita") {
    int angolo = wsValue == "1" ? 180 : 90;
    laaMoveCancello(cancelloUscita, angolo);
  }
}