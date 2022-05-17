#include <Arduino.h>
#include "LightLock.h"
#include "MyRGB.h"

#define DELAY_SPDT 50

LightLock::LightLock (int sw1, int sw2, int sw3, int sw4, int r1, int g1, int b1, int r2, int g2, int b2, int r3, int g3, int b3): led1(r1,g1,b1,sw1), led2(r1,g2,b2,sw2), led3(r1,g3,b3,sw3) 
{
  _sw4 = sw4;
  pinMode(_sw4, INPUT); /*control switch set as input*/


  /*Rest of arguments are initialized in MyRGB Constructor for led1, led2, led3*/
  
}

void LightLock::setColorOn(MyRGB thisled) 
{
  if (_color == 2) {
    thisled.redRGB();
  }
  else if (_color == 3) {
    thisled.greenRGB();
  }
  else if (_color == 4) {
    thisled.blueRGB();
  }
  else
  {
    thisled.blinkThrice();
    thisled.offRGB();
  }
}

void LightLock::turnOff(MyRGB thisled) 
{
  thisled.offRGB();
}

/*Cycles between red (2), green (3), blue (4)*/
void LightLock::nextColor() 
{
  if (_color == 4) 
  {
    _color = 2;
  }
  else 
  {
    _color += 1;
  }
}

void LightLock::updateLightLock() 
{
  _swState1 = digitalRead(led1.sw);
  _swState2 = digitalRead(led2.sw);
  _swState3 = digitalRead(led3.sw);
  _swState4 = digitalRead(_sw4);

  /*First light switch*/
  if (_swState1 != _swStateLast1) {
    if (_swState1 == HIGH) {
      setColorOn(led1);
    }
    else if (_swState1 == LOW) {
      turnOff(led1);
    }
    _swStateLast1 = _swState1;
  }


  /*Second light switch*/
  if (_swState2 != _swStateLast2) {
    if (_swState2 == HIGH) {
      setColorOn(led2);
    }
    else if (_swState2 == LOW) {
      turnOff(led2);
    }
    _swStateLast2 = _swState2;
  }


  /*Third light switch*/
  if (_swState3 != _swStateLast3) {
    if (_swState3 == HIGH) {
      setColorOn(led3);
    }
    else if (_swState3 == LOW) {
      turnOff(led3);
    }
    _swStateLast3 = _swState3;
  }

  
  /*Fourth (control) light switch*/
  if (_swState4 != _swStateLast4) {
    nextColor();
    _swStateLast4 = _swState4;
  }
  
  delay(DELAY_SPDT);

}
