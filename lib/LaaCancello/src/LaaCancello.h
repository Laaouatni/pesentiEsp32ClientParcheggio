#ifndef LAA_CANCELLO_H
#define LAA_CANCELLO_H

#include <Ticker.h>
#include <ESP32Servo.h>

extern Ticker myDelay;


struct Cancello {
  int   pin;
  Servo motore;
};

struct laaChiudiCancelloArgs {
    Cancello* cancello;
    String*   wsKey;
};

class LaaCancello {
  public:
    Cancello cancelloEntrata;
    Cancello cancelloUscita;
    LaaCancello(int pinEntrata, int pinUscita);
    void laaConnectToAppTelecomando(String wsKey, String wsValue);
    void     laaMoveCancello(Cancello &cancello, int angolo, String wsKey);

  private:
    static void     laaSpegniMotore();
    static void     laaChiudiCancello(laaChiudiCancelloArgs *args);
};

#endif