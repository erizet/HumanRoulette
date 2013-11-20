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
  "1FFFFFFF0rgb",
  "F1FFFFFF0rgb",
  "FF1FFFFF0rgb"  
};

int winningHat;
unsigned long lastTime = 0;
Roulette_Step currentStep = Start;

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
//  Serial.println("test...");
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
  delay(200);

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
      Serial.print("Waiting......elapsed: ");
      Serial.println(elapsedTime);
      if(elapsedTime > 5000)
      {
        lastTime = newTime;
        currentStep = SendingRed;
      }
      break;

    case SendingRed:
      Serial.print("Red......elapsed: ");
      Serial.println(elapsedTime);
      if(elapsedTime > 1000)
      {
        if(Step_Sending(true, false, false))
        {
          currentStep = SendingGreen;
        }
        lastTime = newTime;
      }
      break;
    case SendingGreen:
      Serial.print("Green......elapsed: ");
      Serial.println(elapsedTime);
      if(elapsedTime > 1000)
      {
        if(Step_Sending(false, true, false))
        {
          currentStep = SendingBlue;
        }
      lastTime = newTime;
      }
      break;
    case SendingBlue:
      Serial.print("Blue......elapsed: ");
      Serial.println(elapsedTime);
      if(elapsedTime > 1000)
      {
        if(Step_Sending(false, false, true))
        {
          currentStep = ShowResult;
          winningHat = random(0,3);
        }
        lastTime = newTime;
      }
      break;
    case ShowResult:
      Serial.println("Finished");
      lastTime = newTime;
      currentStep = Start;
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
  
  Send();
  
  hat++;
  Serial.print("Hat: ");
  Serial.println(hat);
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
      sendStrings[hatNo][9] = red ? '1' : '0';
      sendStrings[hatNo][10] = green ? '1' : '0';
      sendStrings[hatNo][11] = blue ? '1' : '0';
      break;
    case 3:
      sendStrings[hatNo][9] = red ? '1' : '0';
      sendStrings[hatNo][10] = green ? '1' : '0';
      sendStrings[hatNo][11] = blue ? '1' : '0';      
      break;
  }
}


void Send()
{
  for(int i=0; i<4; i++)
  {
    Serial.print("Sending: ");
    Serial.println(sendStrings[i]);
    
    mySwitch.sendTriState(sendStrings[i]);
    delay(100);
  }
  
}
