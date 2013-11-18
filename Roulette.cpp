
#include "Arduino.h"
#include "Roulette.h"




Roulette::Roulette() : mySwitch(), _hatA(), _hatB(), _hatC(), _hatD()
{
  _hats[0] = &_hatA;  
  _hats[1] = &_hatB;  
  _hats[2] = &_hatC;  
  _hats[3] = &_hatD;
}

void Roulette::Init()
{
 
  Serial.println("----- Setup -----");
  Serial.print("Transmit pin: ");
  Serial.println(TRANSMIT_PIN);  
  Serial.print("Pulse length: ");
  Serial.println(PULSE_LENGTH);  
  Serial.print("Repeat transmit: ");
  Serial.println(REPEAT_TRANSMIT);

  mySwitch.enableTransmit(TRANSMIT_PIN);
  mySwitch.setPulseLength(PULSE_LENGTH);
  
  _currentStep = Waiting;
}


void Roulette::NextStep()
{
  unsigned long newTime = millis();
  unsigned long elapsedTime = newTime - _lastTime;
  
  
  
}


void Roulette::Send()
{
  for(int i=0; i<NO_OF_HATS; i++)
  {
    //mySwitch.sendTriState("FFFFFFFF0000");
    mySwitch.sendTriState(_hats[i]->sendString);
    Serial.println(_hats[i]->sendString);
  }
}
