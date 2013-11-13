/*
  HumanRoulette
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {

  Serial.begin(9600);
  
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(4);

  // Optional set pulse length.
  // mySwitch.setPulseLength(320);
  
  // Optional set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);
  
  // Optional set number of transmission repetitions.
  // mySwitch.setRepeatTransmit(15);
  
}

void loop() {

  //for(int i=140; i<180; i+=2)
  {
//    Serial.println(i);
    mySwitch.setPulseLength(170);
    /* Same switch as above, but tri-state code */ 
    mySwitch.sendTriState("FFFFFFFF0000");
    delay(500);  
    mySwitch.sendTriState("FFFFFFFF1111");
    delay(500);
  }

}
