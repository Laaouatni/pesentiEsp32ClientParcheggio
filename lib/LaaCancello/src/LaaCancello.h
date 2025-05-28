#ifndef LAA_CANCELLO_H
#define LAA_CANCELLO_H

#include <ESP32Servo.h>
#include <Ticker.h>

extern Ticker myDelay;

struct Cancello {
    int   pin;
    Servo motore;
};

class LaaCancello {
  public:
    Cancello cancelloEntrata;
    Cancello cancelloUscita;
    LaaCancello(int pinEntrata, int pinUscita);
    void laaConnectToAppTelecomando(String wsKey, String wsValue);

  private:
    static bool isStillDetaching = false;
    static void laaSpegniMotore(Cancello *cancello);
    void handleCancelloCommand(Cancello &cancello, int angoloOpen, int angoloClose, String wsValue);
    void laaMoveCancello(Cancello &cancello, int angolo);
};

#endif