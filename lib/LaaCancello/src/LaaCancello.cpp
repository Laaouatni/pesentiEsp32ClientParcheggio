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
  myDelay.once_ms(250, &LaaCancello::laaSpegniMotore, &cancello);
}

void LaaCancello::handleCancelloCommand(Cancello &cancello, int angoloOpen, int angoloClose,
                                        String wsValue) {
  bool canOpen = wsValue == "1";
  int  angolo  = canOpen ? angoloOpen : angoloClose;
  laaMoveCancello(cancello, angolo);
}

void LaaCancello::laaConnectToAppTelecomando(String wsKey, String wsValue) {
  if (wsKey == "ingresso") {
    handleCancelloCommand(cancelloEntrata, 90, 180, wsValue);
  } else if (wsKey == "uscita") {
    handleCancelloCommand(cancelloUscita, 90, 0, wsValue);
  }
}

void LaaCancello::laaSpegniMotore(Cancello &cancello) {
  cancello.motore.detach();
};