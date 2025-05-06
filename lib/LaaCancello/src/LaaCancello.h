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
    void laaLogicCancello(String wsKey, String wsValue);

  private:
    Cancello cancelloEntrata;
    Cancello cancelloUscita;
    void     laaMoveCancello(Cancello &cancello, int angolo);
    void     laaSpegniMotore();
};

#endif