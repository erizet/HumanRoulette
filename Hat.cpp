#include "Arduino.h"
#include "Hat.h"

HatA::HatA()
{
  sendString[0] = 'F';
  sendString[1] = 'F';
  sendString[2] = 'F';
  sendString[3] = 'F';
  sendString[4] = 'F';
  sendString[5] = 'F';
  sendString[6] = 'F';
  sendString[7] = 'F';
  sendString[8] = '0';
  sendString[9] = 'r';
  sendString[10] = 'g';
  sendString[11] = 'b';
}

void HatA::SetColor(boolean R, boolean G, boolean B)
{
  sendString[10] = R ? '1' : '0';
  sendString[11] = G ? '1' : '0';
  sendString[12] = B ? '1' : '0';
}

HatB::HatB()
{
  sendString[0] = 'F';
  sendString[1] = 'F';
  sendString[2] = 'F';
  sendString[3] = 'F';
  sendString[4] = 'F';
  sendString[5] = 'F';
  sendString[6] = 'F';
  sendString[7] = 'F';
  sendString[8] = '0';
  sendString[9] = 'r';
  sendString[10] = 'g';
  sendString[11] = 'b';
}
void HatB::SetColor(boolean R, boolean G, boolean B)
{
  sendString[10] = R ? '1' : '0';
  sendString[11] = G ? '1' : '0';
  sendString[12] = B ? '1' : '0';
}

HatC::HatC()
{
  sendString[0] = 'F';
  sendString[1] = 'F';
  sendString[2] = 'F';
  sendString[3] = 'F';
  sendString[4] = 'F';
  sendString[5] = 'F';
  sendString[6] = 'F';
  sendString[7] = 'F';
  sendString[8] = '0';
  sendString[9] = 'r';
  sendString[10] = 'g';
  sendString[11] = 'b';
}
void HatC::SetColor(boolean R, boolean G, boolean B)
{
  sendString[10] = R ? '1' : '0';
  sendString[11] = G ? '1' : '0';
  sendString[12] = B ? '1' : '0';  
}

HatD::HatD()
{
  sendString[0] = 'F';
  sendString[1] = 'F';
  sendString[2] = 'F';
  sendString[3] = 'F';
  sendString[4] = 'F';
  sendString[5] = 'F';
  sendString[6] = 'F';
  sendString[7] = 'F';
  sendString[8] = '0';
  sendString[9] = 'r';
  sendString[10] = 'g';
  sendString[11] = 'b';
}

void HatD::SetColor(boolean R, boolean G, boolean B)
{
  sendString[10] = R ? '1' : '0';
  sendString[11] = G ? '1' : '0';
  sendString[12] = B ? '1' : '0';
}
