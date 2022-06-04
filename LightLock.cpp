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

void LightLock::updateLightLock() 
{
  swState4 = digitalRead(_sw4);

  if (swState4 != swLast4)
  {
    Serial.print("Switch 4 flipped: Color is ");
    if (color == "red") 
    {
      color = "green";
    }
    else if (color == "green")
    {
      color = "blue";
    }   
    else if (color == "blue")
    {
      color = "red";
    }
    Serial.println(color);
    swLast4 = swState4;
    delay(50);
  } 

  swState1 = led1.updateSwitch();
  swState2 = led2.updateSwitch();
  swState3 = led3.updateSwitch();

  led1.updateLed(color, swState1);
  led2.updateLed(color, swState2);
  led3.updateLed(color, swState3);
  
  delay(DELAY_SPDT);

}
