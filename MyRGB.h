#ifndef MyRGB_H
#define MyRGB_H

#include <Arduino.h>

//RGB LED digital output pins

class MyRGB {
  public: 
    MyRGB(int redPin, int greenPin, int bluePin);
    void greenRGB();
    void redRGB();
    void whiteRGB();
    void offRGB();
    void blinkRGB(int blinkRate);  //whichever colour

  private:
    int _redPin;
    int _bluePin;
    int _greenPin;   
};

#endif
