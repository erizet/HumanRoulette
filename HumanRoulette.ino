
/*
  HumanRoulette
*/

#include "Arduino.h"
#include <RCSwitch.h>
#include "Roulette_Step.h"
#include <Button.h>
#include "tx433_proove.h"

#define TRANSMIT_PIN 4
#define PULSE_LENGTH 170
#define REPEAT_TRANSMIT 2

#define START_BUTTON_PIN 11
#define FUNCTION_BUTTON_PIN 10
#define START_BUTTON_LIGHT 7
#define FUNCTION_BUTTON_LIGHT 6

Button startButton = Button(START_BUTTON_PIN, BUTTON_PULLUP, false, 0);
Button functionButton = Button(FUNCTION_BUTTON_PIN, BUTTON_PULLUP, false, 0);

RCSwitch mySwitch;

// The transmitter unique address (you will need to chage this)
char *transmitter = "1010100101101001010101100101011001010101010101010110";
// The transmitter channel (might need to change this)
char *channel="0101";
// Create an instance of the Proove class
Tx433_Proove Proove(4, transmitter, channel);

   
char sendStrings[4][13] = {
  "1FFFFFFF0rgb",
  "F1FFFFFF0rgb",
  "FF1FFFFF0rgb",
  "FFF1FFFF0rgb"  
};

boolean startButtonLightOn = false;
unsigned long lastTime = 0;
Roulette_Step currentStep = Start;
int timesToSendRed = 0;
int timesToSendGreen = 0;
int timesToSendBlue = 0;
int winningHat = 0;

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
  Serial.println(START_BUTTON_PIN);
  Serial.print("Function button pin: ");
  Serial.println(FUNCTION_BUTTON_PIN);  
  Serial.print("Start button light pin: ");
  Serial.println(START_BUTTON_LIGHT);
  Serial.print("Function button light pin: ");
  Serial.println(FUNCTION_BUTTON_LIGHT);

  pinMode(START_BUTTON_PIN,INPUT);
  pinMode(FUNCTION_BUTTON_PIN,INPUT);
  pinMode(START_BUTTON_LIGHT,OUTPUT);
  pinMode(FUNCTION_BUTTON_LIGHT,OUTPUT);
  
  

}

void loop() {
/*  startButton.process();
  if(startButton.isPressed()){
    Serial.println("pressed");
    rouletteStarted = !rouletteStarted;
    digitalWrite(START_BUTTON_LIGHT, HIGH);
  }  
  else
  {
        digitalWrite(START_BUTTON_LIGHT, LOW);
  }
  */
  //if(rouletteStarted)
  {  
    NextStep();
  }
  
  //delay(200);

}


void NextStep()
{
  unsigned long newTime = millis();
  unsigned long elapsedTime = newTime - lastTime;
  
  switch(currentStep)
  {
    case Start:
      Serial.println("Start....");
      currentStep = WaitingForButton;
      lastTime = newTime;
      break;
    case WaitingForButton:
      startButton.process();
      functionButton.process();

      if(startButton.isPressed()){
        currentStep = InitializeSending;
        lastTime = newTime;
        digitalWrite(START_BUTTON_LIGHT, LOW);
        digitalWrite(FUNCTION_BUTTON_LIGHT, LOW);
      } 
      else if(functionButton.isPressed()){
        currentStep = SendNexa;
        lastTime = newTime;
        digitalWrite(START_BUTTON_LIGHT, LOW);
        digitalWrite(FUNCTION_BUTTON_LIGHT, HIGH);
      }
      else if(elapsedTime > 400)
      {
        lastTime = newTime;
        startButtonLightOn = !startButtonLightOn;
        digitalWrite(START_BUTTON_LIGHT, startButtonLightOn);
        digitalWrite(FUNCTION_BUTTON_LIGHT, !startButtonLightOn);
      }

      break;
    case SendNexa:
      Serial.println("SendNexa....");
  
      for(int i= 0; i<3; i++)
      {
        Proove.Device_On(1);
        delay(1500);
        Proove.Device_Off(1);
        delay(1500);
      }

      currentStep = Start;
      break;
    case InitializeSending:
      // reset all hats
      for(int i=0; i<4; i++)
        SetColor(i, false, false, false);
      Send(-1);

      // randomize the number of laps around
      winningHat = random(0,3);
      timesToSendRed = random(1,3);
      timesToSendGreen = random(1,3);
      timesToSendBlue = random(1,3);
      Serial.println("Initialize sending");
      Serial.print("Times to send red: ");
      Serial.println(timesToSendRed);
      Serial.print("Times to send green: ");
      Serial.println(timesToSendGreen);
      Serial.print("Times to send blue: ");
      Serial.println(timesToSendBlue);

      currentStep = Waiting;
      break;
    case Waiting:
      //Serial.print("Waiting......elapsed: ");
      //Serial.println(elapsedTime);
      if(elapsedTime > 500)
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
          timesToSendRed--; 
          if(timesToSendRed<0)
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
          timesToSendGreen--; 
          if(timesToSendGreen<0)
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
          timesToSendBlue--; 
          if(timesToSendBlue<0)
            currentStep = ShowResult;
        }
        lastTime = newTime;
      }
      break;
    case ShowResult:
      Serial.print("ShowResult...elapsed: ");
      Serial.println(elapsedTime);
      if(elapsedTime > 1000)
      {
        if(winningHat>=0)
        {
           Step_Sending(true, true, true);
           winningHat--;
        }
        else
        {
           currentStep = Finished;
        }
        lastTime = newTime;
      }
      break;
    case Finished:
      //Serial.print("Finished....elapsed: ");
      //Serial.println(elapsedTime);
      if(elapsedTime > 5000)
      {
        lastTime = newTime;
        currentStep = Start;
      }
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
  
  Send(hat);
  
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
      sendStrings[hatNo][11] = red ? '1' : '0';
      sendStrings[hatNo][9] = green ? '1' : '0';
      sendStrings[hatNo][10] = blue ? '1' : '0';
      break;
    case 3:
      sendStrings[hatNo][9] = red ? '1' : '0';
      sendStrings[hatNo][11] = green ? '1' : '0';
      sendStrings[hatNo][10] = blue ? '1' : '0';      
      break;
  }
}


void Send(int hatWithColor)
{
  for(int i=0; i<4; i++)
  {
    if(i!=hatWithColor)
    {
      Serial.print("Sending: ");
      Serial.println(sendStrings[i]);
      
      mySwitch.sendTriState(sendStrings[i]);
      delay(10);
    }
  }

  // always sends hat with color last
  mySwitch.sendTriState(sendStrings[hatWithColor]);
}
