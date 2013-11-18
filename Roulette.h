#ifndef ROULETTE_H
#define ROULETTE_H


#include "Arduino.h"
#include "Hat.h"
#include <RCSwitch.h>
#include "Roulette_Step.h";

#define TRANSMIT_PIN 4
#define PULSE_LENGTH 170
#define REPEAT_TRANSMIT 2

#define NO_OF_HATS 4



class Roulette
{
  private:
    Hat _hatA;
    Hat _hatB;
    Hat _hatC;
    Hat _hatD;
    Hat* _hats[NO_OF_HATS];
    Roulette_Step _currentStep;
    unsigned long _lastTime;
    RCSwitch mySwitch;
    void Send();
  public:
    Roulette();
    void Init();
    void NextStep();
};

#endif
