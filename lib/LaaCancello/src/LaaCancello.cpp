#include "LaaCancello.h"

#include <ESP32Servo.h>
#include <Ticker.h>

Ticker myDelay;

LaaCancello::LaaCancello(int pinEntrata, int pinUscita) {
  cancelloEntrata = {pinEntrata, Servo()};
  cancelloUscita  = {pinUscita, Servo()};
};

void LaaCancello::laaMoveCancello(Cancello &cancello, int angolo) {
  cancello.motore.attach(cancello.pin);
  cancello.motore.write(angolo);
  if (isStillDetaching) return;
  myDelay.once_ms(250, &LaaCancello::laaSpegniMotore, cancello);
  isStillDetaching = true;
}

void LaaCancello::handleCancelloCommand(Cancello &cancello, int angoloOpen, int angoloClose,
                                        String wsValue) {
  bool canOpen = wsValue == "1";
  int  angolo  = canOpen ? angoloOpen : angoloClose;
  laaMoveCancello(cancello, angolo);
}

void LaaCancello::laaConnectToAppTelecomando(String wsKey, String wsValue) {
  if (wsKey == "ingresso") {
    const int ANGOLO_OPEN  = 90;
    const int ANGOLO_CLOSE = 180;
    handleCancelloCommand(cancelloEntrata, ANGOLO_OPEN, ANGOLO_CLOSE, wsValue);
  } else if (wsKey == "uscita") {
    const int ANGOLO_OPEN  = 90;
    const int ANGOLO_CLOSE = 0;
    handleCancelloCommand(cancelloUscita, ANGOLO_OPEN, ANGOLO_CLOSE, wsValue);
  }
}

void LaaCancello::laaSpegniMotore(Cancello &cancello) {
  cancello.motore.detach();
  isStillDetaching = false;
};