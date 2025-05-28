#include "LaaCancello.h"

#include <ESP32Servo.h>
#include <Ticker.h>

Ticker        myDelay;

LaaCancello::LaaCancello(int pinEntrata, int pinUscita) {
  cancelloEntrata = {pinEntrata, Servo()};
  cancelloUscita  = {pinUscita, Servo()};
};

void LaaCancello::laaMoveCancello(Cancello &cancello, int angolo) {
  cancello.motore.attach(cancello.pin);
  cancello.motore.write(angolo);
  myDelay.once_ms(250, &LaaCancello::laaSpegniMotore, &cancello);
}

void LaaCancello::laaConnectToAppTelecomando(String wsKey, String wsValue) {
  if (wsKey == "ingresso") {
    const int ANGOLO_OPEN = 90;
    const int ANGOLO_CLOSE = 180;
    bool canOpenEntrata = wsValue == "1";
    int  angolo         = canOpenEntrata ? ANGOLO_OPEN : ANGOLO_CLOSE;
    laaMoveCancello(cancelloEntrata, angolo);
  }

  if (wsKey == "uscita") {
    const int ANGOLO_OPEN = 90;
    const int ANGOLO_CLOSE = 0;
    bool canOpenUscita = wsValue == "1";
    int  angolo        = canOpenUscita ? ANGOLO_OPEN : ANGOLO_CLOSE;
    laaMoveCancello(cancelloUscita, angolo);
  }
}

void LaaCancello::laaChiudiCancello() {
  // args->cancello->motore.attach(args->cancello->pin);
  // args->cancello->motore.write(*(args->wsKey) == "ingresso" ? 0 : 90);
  // servoToDetach = &args->cancello->motore;
  // myDelay.once_ms(250, &LaaCancello::laaSpegniMotore);
  // delete args->wsKey;
  // delete args;
}

void LaaCancello::laaSpegniMotore(Cancello &cancello) {
  cancello.motore.detach();
};