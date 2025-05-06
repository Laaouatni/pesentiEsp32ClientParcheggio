#include "LaaWifiWsBoiderplate.h"
#include "LaaCancello.h"
#include <Arduino.h>

LaaWifiWs laaWifi = LaaWifiWs("pesentiws-43f6274c0f11.herokuapp.com");
LaaCancello laaCancelli;

void setup() {
  Serial.begin(115200);
  laaWifi.laaOnReceiveMessage(&wsCallbackReceive)
}

void loop() {
  laaWifi.laaLoop();
}

void wsCallbackReceive(String wsKey, String wsValue) {
  laaCancelli.
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
  cancello.motore.write(angolo);

  myDelay.once_ms(250, [&cancello]() { cancello.motore.detach(); })
}
