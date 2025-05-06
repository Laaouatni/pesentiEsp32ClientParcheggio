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
  cancelloUscita.motore.attach(cancelloUscita.pin);
  
  if (wsKey == "ingresso") { 
    cancelloEntrata.motore.attach(cancelloEntrata.pin);
    cancelloEntrata.motore.write(wsValue == "0" ? 90 : 0);
    delay(250);
    cancelloEntrata.motore.detach();
  }
  if (wsKey == "uscita") { 
    cancelloUscita.motore.attach(cancelloUscita.pin);
    cancelloUscita.motore.write(wsValue == "1" ? 180 : 90);
    delay(250);
    cancelloUscita.motore.detach();
   }
}
