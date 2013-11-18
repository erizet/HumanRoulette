/*
  HumanRoulette
*/

#include "Arduino.h"
#include "Roulette.h"
#include "Hat.h"
#include <RCSwitch.h>

#define START_BUTTON 10
#define FUNCTION_BUTTON 11
#define START_BUTTON_LIGHT 5
#define FUNCTION_BUTTON_LIGHT 6

Roulette roulette;

void setup() {

  Serial.begin(9600);
  
  // while the serial stream is not open, do nothing:
  while (!Serial) 
    ;
  


  // Optional set number of transmission repetitions.
  //mySwitch.setRepeatTransmit(REPEAT_TRANSMIT);
  
  Serial.print("Start button pin: ");
  Serial.println(START_BUTTON);
  Serial.print("Function button pin: ");
  Serial.println(FUNCTION_BUTTON);  
  Serial.print("Start button light pin: ");
  Serial.println(START_BUTTON_LIGHT);
  Serial.print("Function button light pin: ");
  Serial.println(FUNCTION_BUTTON_LIGHT);

/*  pinMode(START_BUTTON,INPUT);
  pinMode(FUNCTION_BUTTON,INPUT);
  pinMode(START_BUTTON_LIGHT,OUTPUT);
  pinMode(FUNCTION_BUTTON_LIGHT,OUTPUT);
  */
  
  roulette.Init();
}

void loop() {

  //for(int i=140; i<180; i+=2)
  {
  //Serial.println("Sending...");
  //Serial.println(i);
    //mySwitch.setPulseLength(i);
      //mySwitch.setPulseLength(PULSE_LENGTH);

    /* Same switch as above, but tri-state code */ 
 //   mySwitch.sendTriState("FFFFFFFF0000");
 //   delay(500);   
 //    mySwitch.sendTriState("FFFFFFFF1111");
 //   delay(500);
  }

  roulette.NextStep();
}
