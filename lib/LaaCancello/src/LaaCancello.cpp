#include "LaaCancello.h"

#include <ESP32Servo.h>
#include <Ticker.h>

Ticker        myDelay;
static Servo *servoToDetach = nullptr;

LaaCancello::LaaCancello(int pinEntrata, int pinUscita) {
  cancelloEntrata = {pinEntrata, Servo(), true};
  cancelloUscita  = {pinUscita, Servo(), true};
};

void LaaCancello::laaMoveCancello(Cancello &cancello, int angolo, String wsKey) {
  cancello.motore.attach(cancello.pin);
  cancello.motore.write(angolo);
  servoToDetach = &cancello.motore;
  myDelay.once_ms(250, &LaaCancello::laaSpegniMotore);
  myDelay.once_ms(5000, &LaaCancello::laaChiudiCancello(cancello, wsKey));
}

void LaaCancello::laaConnectToAppTelecomando(String wsKey, String wsValue) {
  if (wsKey == "ingresso") {
    int angolo = wsValue == "0" ? 90 : cancelloEntrata.canClose ? 0 : 90;
    laaMoveCancello(cancelloEntrata, angolo, wsKey);
  }

  if (wsKey == "uscita" && cancelloUscita.canClose) {
    int angolo = wsValue == "1" ? 180 : cancelloUscita.canClose ? 90 : 180;
    laaMoveCancello(cancelloUscita, angolo, wsKey);
  }
}

void LaaCancello::laaChiudiCancello(Cancello &cancello, String wsKey) {
  cancello.motore.attach(cancello.pin);
  cancello.motore.write(wsKey == "ingresso" ? 0 : 90);
  myDelay.once_ms(250, &LaaCancello::laaSpegniMotore);
}

void LaaCancello::laaSpegniMotore() {
  if (!servoToDetach) { return; }
  servoToDetach->detach();
  servoToDetach = nullptr;
};