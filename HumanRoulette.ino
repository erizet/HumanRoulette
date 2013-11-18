/*
  HumanRoulette
*/

#include "Arduino.h"
#include <RCSwitch.h>
#include "Roulette_Step.h"

#define TRANSMIT_PIN 4
#define PULSE_LENGTH 170
#define REPEAT_TRANSMIT 2

#define START_BUTTON 10
#define FUNCTION_BUTTON 11
#define START_BUTTON_LIGHT 5
#define FUNCTION_BUTTON_LIGHT 6

RCSwitch mySwitch;
   
char sendStrings[4][13] = {
  "FFFFFFFF0rgb",
  "FFFFFFFF0rgb",
  "FFFFFFFF0rgb",
  "FFFFFFFF0rgb"  
};

unsigned long lastTime = 0;
Roulette_Step currentStep = Waiting;

void setup() {

  Serial.begin(9600);
  
  // while the serial stream is not open, do nothing:
  while (!Serial) 
    ;
  
  Serial.println("----- Setup -----");
  Serial.print("Transmit pin: ");
  Serial.println(TRANSMIT_PIN);  
  Serial.print("Pulse length: ");
  Serial.println(PULSE_LENGTH);  
  Serial.print("Repeat transmit: ");
  Serial.println(REPEAT_TRANSMIT);

  mySwitch.enableTransmit(TRANSMIT_PIN);
  mySwitch.setPulseLength(PULSE_LENGTH);

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
  
  NextStep();
  

}


void NextStep()
{
  unsigned long newTime = millis();
  unsigned long elapsedTime = newTime - lastTime;
  
  switch(currentStep)
  {
    case Start:
      for(int i=0; i<4; i++)
        SetColor(i, false, false, false);
      Send();
      currentStep = Waiting;
      lastTime = newTime;
      break;
    case Waiting:
      if(elapsedTime > 15000)
      {
        lastTime = newTime;
        currentStep = SendingRed;
      }
      break;

    case SendingRed:
      if(elapsedTime > 1000)
      {
        if(Step_Sending(true, false, false))
        {
          lastTime = newTime;
          currentStep = SendingGreen;
        }
      }
      break;
    case SendingGreen:
      if(elapsedTime > 1000)
      {
        if(Step_Sending(false, true, false))
        {
          lastTime = newTime;
          currentStep = SendingBlue;
        }
      }
      break;
    case SendingBlue:
      if(elapsedTime > 1000)
      {
        if(Step_Sending(false, false, true))
        {
          lastTime = newTime;
          currentStep = ShowResult;
        }
      }
      break;
    case ShowResult:
      break;
  }
}


boolean Step_Sending(boolean red, boolean green, boolean blue)
{
  static int hat = 0;
  
  for(int i=0; i<4; i++)
  {
    if(hat==i)
      SetColor(i, red, green, blue);
    else  
      SetColor(i, false, false, false);
  }
  
  hat++;
  
  if(hat>3)
  {
    hat = 0;
    return true;
  }
  
  return false;
}

void SetColor(int hatNo, boolean red, boolean green, boolean blue)
{
  switch(hatNo)
  {
    case 0:    
    case 1:    
    case 2:
      sendStrings[hatNo][10] = red ? '1' : '0';
      sendStrings[hatNo][11] = green ? '1' : '0';
      sendStrings[hatNo][12] = blue ? '1' : '0';
      break;
    case 3:
      sendStrings[hatNo][10] = red ? '1' : '0';
      sendStrings[hatNo][11] = green ? '1' : '0';
      sendStrings[hatNo][12] = blue ? '1' : '0';      
      break;
  }
}


void Send()
{
  for(int i=0; i<4; i++)
  {
    Serial.print("Sending: ");
    Serial.println(sendStrings[i]);
    
//    mySwitch.sendTriState("FFFFFFFF1111");
  }
  
}
