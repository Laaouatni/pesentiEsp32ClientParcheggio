#include "LaaCancello.h"
#include <Ticker.h>
#include <ESP32Servo.h>

Ticker myDelay;

void LaaCancello::laaSpegniMotore() {
  cancello.motore.detach();
};

void LaaCancello::laaMoveCancello(Cancello &cancello, int angolo) {
  cancello.motore.attach(cancello.pin);
  cancello.motore.write(angolo);

  myDelay.once_ms(250, LaaCancello::laaSpegniMotore);
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