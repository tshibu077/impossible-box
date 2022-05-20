#ifndef ServoBox_H
#define ServoBox_H

#include <Arduino.h>
#include <Servo.h>

class ServoBox {

  public: 

    ServoBox(int servoPin, int buttonPin);

    Servo myServo;

    void openBox();
    void closeBox();
    void checkBoxButton();

  private:

    int _pos;
    int _servoPin;
    int _buttonPin;

    bool _buttonState;
    bool _buttonStateLast;
    int _lastPush;             /*last time the button was pushed*/
      
}

#endif
