#include <Arduino.h>
#include <ESP32Servo.h>
#include "LaaWifiWsBoiderplate.h"

LaaWifiWs laaWifi = LaaWifiWs("pesentiws-43f6274c0f11.herokuapp.com");

Servo motoreEntrata;
const int pinMotoreEntrata = 15;
Servo motoreUscita;
const int pinMotoreUscita = 2;

void setup() {
  Serial.begin(115200);

}

void loop() {
  laaWifi.laaLoop();
 }
