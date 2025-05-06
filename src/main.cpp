#include "LaaWifiWsBoiderplate.h"

#include <Arduino.h>
#include <ESP32Servo.h>

LaaWifiWs laaWifi = LaaWifiWs("pesentiws-43f6274c0f11.herokuapp.com");

struct Cancello {
    int pin;
    Servo motore;
};

Cancello entrata 
Servo motoreEntrata;

const int pinMotoreEntrata = 15;

Servo motoreUscita;

const int pinMotoreUscita = 2;

void setup() {
  Serial.begin(115200);
  laaWifi.laaOnReceiveMessage()
}

void loop() {
  laaWifi.laaLoop();
}

void wsCallbackReceive(String wsKey, String wsValue) {

};
