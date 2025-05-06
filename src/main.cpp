#include "LaaWifiWsBoiderplate.h"

#include <Arduino.h>
#include <ESP32Servo.h>

LaaWifiWs laaWifi = LaaWifiWs("pesentiws-43f6274c0f11.herokuapp.com");

struct Cancello {
    int   pin;
    Servo motore;
};

Cancello cancelloEntrata = {.pin = 15, .motore = Servo()};
Cancello cancelloUscita  = {.pin = 2, .motore = Servo()};

void setup() {
  Serial.begin(115200);
  laaWifi.laaOnReceiveMessage(&wsCallbackReceive)
}

void loop() {
  laaWifi.laaLoop();
}

void wsCallbackReceive(String wsKey, String wsValue) {
  logicCancello(wsKey, wsValue);
};

void logicCancello(String wsKey, String wsValue) {
  if (wsKey == "ingresso") {
    int angolo = wsValue == "0" ? 90 : 0;
    moveCancello(cancelloEntrata, angolo);
  } 

  if (wsKey == "uscita") {
    int angolo = wsValue == "1" ? 180 : 90;
    moveCancello(cancelloUscita, angolo);
  }
}

void moveCancello(Cancello &cancello, int angolo) {
  cancello.motore.attach(cancello.pin);
  cancello.motore.attach_ms()
  cancello.motore.write(angolo);
  delay(250);
  cancello.motore.detach();
}
