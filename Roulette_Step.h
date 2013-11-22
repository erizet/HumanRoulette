#ifndef ROULETTE_STEP_H
#define ROULETTE_STEP_H

enum Roulette_Step
{
  Start,
  WaitingForButton,
  SendNexa,
  Waiting,
  InitializeSending,
  SendingRed,
  SendingGreen,
  SendingBlue,
  ShowResult,
  Finished
};

#endif
