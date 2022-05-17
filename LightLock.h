/*
  LightLock.h - Library for task involving setting LED colours with switches, to match a given RGB pattern. 
*/

#ifndef LIGHTLOCK_H
#define LIGHTLOCK_H

#include <Arduino.h>
#include <Bounce2.h>
#include "MyRGB.h"

/*
 * Includes: 
 * 1. 3x SPDT Switch: 
 *    - Pins: sw1, sw2, sw3 are to turn on/off each rgb led, initalized in the MyRGB objects, 
 *            sw4 is the control switch for the lock that sets color
 *    - Outputs: MyRGB color (led1,led2,led3)     
 *    
 * 2. RGB LED with switch
 *    - Pins: redPin, bluePin, greenPin (sets value for each between 0-255)
 *            switchPin (turn on/off when flipped up/down)
 *    - Uses MyRGB library
 */

class LightLock {

  MyRGB led1;
  MyRGB led2;
  MyRGB led3;

  public: 
    
    LightLock (int sw1, int sw2, int sw3, int sw4, int r1, int g1, int b1, int r2, int g2, int b2, int r3, int g3, int b3);
    
    void nextColor();   
    void turnOff(MyRGB);
    void setColorOn(MyRGB);
    void updateLightLock();
 
  private:

    int _sw4;
    byte _color;

    bool _swState1;
    bool _swStateLast1;
    
    bool _swState2;
    bool _swStateLast2;
    
    bool _swState3;
    bool _swStateLast3;

    bool _swState4;
    bool _swStateLast4;
    
};


#endif
