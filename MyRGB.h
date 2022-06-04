#ifndef MyRGB_H
#define MyRGB_H

#include "Arduino.h"

//RGB LED digital output pins

class MyRGB {
  public: 
    MyRGB(int redPin, int greenPin, int bluePin);
    MyRGB(int redPin, int greenPin, int bluePin, int switchPin); /*rgb with switch control, for lightlock*/
    
    void greenRGB();
    void redRGB();
    void blueRGB();
    void whiteRGB();
    void blinkThrice();
    void offRGB();
    int updateSwitch();
    void updateLed(String color, int on);

    int sw;
    
  private:
    int _redPin;
    int _bluePin;
    int _greenPin;   
    int swState;
    int swStateLast;

};

#endif
