#ifndef LAA_CANCELLO_H
#define LAA_CANCELLO_H

#include <Ticker.h>
#include <ESP32Servo.h>

extern Ticker myDelay;

struct Cancello {
    int   pin;
    Servo motore;
};

class LaaCancello {
  public:
    LaaCancello(int pinEntrata, int pinUscita);
    void laaConnectToAppTelecomando(String wsKey, String wsValue);

  private:
    Cancello cancelloEntrata;
    Cancello cancelloUscita;
    void     laaMoveCancello(Cancello &cancello, int angolo);
    static void     laaSpegniMotore();
};

#endif