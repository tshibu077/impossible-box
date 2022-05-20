#include <Servo.h>
#include "ServoBox.h"

#define OPEN_POS = 180;
#define CLOSE_POS = 0;
#define DEBOUNCE_DELAY = 50;

ServoBox::ServoBox (int servoPin, int buttonPin) 
{
  _servoPin = servoPin;
  _buttonPin = buttonPin;
  
  myServo.attach(_servoPin);
  pinMode(_buttonPin, INPUT);    /*HIGH when switch is open (button pushed), LOW when closed*/

  _buttonStateLast = LOW;
  _buttonState = LOW;
  _lastPush = 0;        

  _pos = CLOSE_POS;

  
}

void ServoBox::openBox() 
{
  myServo.write(OPEN_POS);  
}

void ServoBox::closeBox() 
{
  myServo.write(CLOSE_POS);
}

void ServoBox::checkBoxButton() 
{
  int val = digitalRead(_buttonPin);

  /*Check if the input went from LOW to HIGH, i.e. button pushed.
    Check if enough time has passed to debounce.*/

  if (val != _buttonStateLast)
  {
    _lastPush = millis();
  }

  if ((millis() - _lastPush) > DEBOUNCE_DELAY) 
  {
    if (val != _buttonState) {
      _buttonState = val;

      if (_buttonState == HIGH) {
        openBox();
      }
    }
  }

  _buttonStateLast = val;
}
