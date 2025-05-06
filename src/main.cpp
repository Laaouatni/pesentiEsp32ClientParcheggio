#include <Arduino.h>
#include <ESP32Servo.h>

Servo motoreEntrata;
const int pinMotoreEntrata = 15;
Servo motoreUscita;
const int pinMotoreUscita = 2;

void setup() {
  Serial.begin(115200);
}

void loop() { wsClient.loop(); }
