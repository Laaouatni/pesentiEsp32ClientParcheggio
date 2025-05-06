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
    void logicCancello(String wsKey, String wsValue);

  private:
    Cancello cancelloEntrata;
    Cancello cancelloUscita;
    void     moveCancello(Cancello &cancello, int angolo);
};

#endif