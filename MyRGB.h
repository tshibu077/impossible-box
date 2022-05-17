#ifndef MyRGB_H
#define MyRGB_H

#include <Arduino.h>

class MyRGB {
  public: 
    MyRGB(int redPin, int greenPin, int bluePin);
    MyRGB(int redPin, int greenPin, int bluePin, int switchPin); /*rgb with switch control, for lightlock*/
    
    void greenRGB();
    void redRGB();
    void blueRGB();
    void whiteRGB();
    void blinkThrice(int blinkRate);
    void offRGB();

    int sw;

  private:
    int _redPin;
    int _bluePin;
    int _greenPin;   

};

#endif
