#include "LaaCancello.h"
#include <Ticker.h>
#include <ESP32Servo.h>

Ticker myDelay;
static Servo *servoToDetach = nullptr;

LaaCancello::LaaCancello(int pinEntrata, int pinUscita) {
  cancelloEntrata = {pinEntrata, Servo()};
  cancelloUscita = {pinUscita, Servo()};
};


void LaaCancello::laaMoveCancello(Cancello &cancello, int angolo) {
  cancello.motore.attach(cancello.pin);
  cancello.motore.write(angolo);
  servoToDetach = &cancello.motore;
  myDelay.once_ms(250, &LaaCancello::laaSpegniMotore);
}

void LaaCancello::laaConnectToAppTelecomando(String wsKey, String wsValue) {
  if (wsKey == "ingresso") {
    int angolo = wsValue == "0" ? 90 : 0;
    laaMoveCancello(cancelloEntrata, angolo);
  }
  
  if (wsKey == "uscita") {
    int angolo = wsValue == "1" ? 180 : 90;
    laaMoveCancello(cancelloUscita, angolo);
  }
}


void LaaCancello::laaSpegniMotore() {
  if (!servoToDetach) return;
  servoToDetach->detach();
  servoToDetach = nullptr;
};