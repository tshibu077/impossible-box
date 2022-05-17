#include <Arduino.h>
#include "PCLock.h"

/*Photocell reading from 0-1023 represents dark to light*/

#define numToCover 2

PCLock::PCLock(int pc0, int pc1, int pc2, int pc3, int pc4, int pc5, int pc6, int pc7, int pc8, int pc9) 
{
  _pc0 = pc0;
  _pc1 = pc1;
  _pc2 = pc2;
  _pc3 = pc3;
  _pc4 = pc4;
  _pc5 = pc5;
  _pc6 = pc6;
  _pc7 = pc7;
  _pc8 = pc8;
  _pc9 = pc9;

  _pcArray[] = {_pc0, _pc1, _pc2, _pc3, _pc4, _pc5, _pc6, _pc7, _pc8, _pc9};
}

void PCLock::activatePCs()
{
  task1 = random(0,totalPcs-1);
  task2 = random(0,totalPcs-1);

  while (_task2 == _task1)
  {
    _task2 = random(0,totalPcs-1);
  }

  pinMode(_pcArray[_task1], INPUT);
  pinMode(_pcArray[_task2], INPUT);
}

bool PCLock::checkPCs()
{
  _task1_val = analogRead(_pcArray[_task1]);
  _task2_val = analogRead(_pcArray[_task2]);

  if (_task1_val < DARK_VAL && _task2_val < DARK_VAL) 
  {
    return true;
  }
  
  return false;
}
