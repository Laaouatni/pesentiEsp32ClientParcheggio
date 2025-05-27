#include "LaaCancello.h"
#include <Ticker.h>
#include <ESP32Servo.h>

Ticker myDelay;
static Servo *servoToDetach = nullptr;
static Servo *servoToChiudere = nullptr;

LaaCancello::LaaCancello(int pinEntrata, int pinUscita) {
  cancelloEntrata = {pinEntrata, Servo()};
  cancelloUscita = {pinUscita, Servo()};
};

void LaaCancello::laaMoveCancello(Cancello &cancello, int angolo) {
  cancello.motore.attach(cancello.pin);
  cancello.motore.write(angolo);
  servoToDetach = &cancello.motore;
  myDelay.once_ms(250, &LaaCancello::laaSpegniMotore);
  servoToChiudere = &cancello.motore;
  myDelay.once_ms(5000, &LaaCancello::chiudiCancello);
}

void LaaCancello::laaConnectToAppTelecomando(String wsKey, String wsValue) {
  if (wsKey == "ingresso") {
    int angolo = wsValue == "0" ? 90 : cancelloEntrata.canClose ? 0 : 90;
    laaMoveCancello(cancelloEntrata, angolo);
  }
  
  if (wsKey == "uscita" && cancelloUscita.canClose) {
    int angolo = wsValue == "1" ? 180 : cancelloUscita.canClose ? 90 : 180;
    laaMoveCancello(cancelloUscita, angolo);
  }
}

void LaaCancello::chiudiCancello() {
  if (!servoToChiudere) return;
  cancello.motore.attach(cancello.pin);
  cancello.motore.write(wsKey == "ingresso" ? 0 : 90);
  myDelay.once_ms(250, &LaaCancello::laaSpegniMotore);
  servoToChiudere = nullptr;
}

void LaaCancello::laaSpegniMotore() {
  if (!servoToDetach) return;
  servoToDetach->detach();
  servoToDetach = nullptr;
};