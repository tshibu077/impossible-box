#include "Arduino.h"
#include "MyRGB.h"

#define blinkRate 150
#define DELAY_SPDT 50

/*Constructor without switch*/
MyRGB::MyRGB(int redPin, int greenPin, int bluePin) {
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  
  _redPin = redPin;
  _greenPin = greenPin;
  _bluePin = bluePin;
}

/*Constructor with switch*/
MyRGB::MyRGB(int redPin, int greenPin, int bluePin, int switchPin) {
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  
  _redPin = redPin;
  _greenPin = greenPin;
  _bluePin = bluePin;
  sw = switchPin;
}

/*Functions to make setting a color simple in main program*/
void MyRGB::redRGB() {
  digitalWrite(_redPin, HIGH);
  digitalWrite(_greenPin, LOW);
  digitalWrite(_bluePin, LOW);
}

void MyRGB::greenRGB() {
  digitalWrite(_redPin, LOW);
  digitalWrite(_greenPin, HIGH);
  digitalWrite(_bluePin, LOW);
}

void MyRGB::blueRGB() {
  digitalWrite(_redPin, LOW);
  digitalWrite(_greenPin, LOW);
  digitalWrite(_bluePin, HIGH);
}

void MyRGB::whiteRGB() {
  digitalWrite(_redPin, HIGH);
  digitalWrite(_greenPin, HIGH);
  digitalWrite(_bluePin, HIGH);
}

void MyRGB::offRGB() {
  digitalWrite(_redPin, LOW);
  digitalWrite(_greenPin, LOW);
  digitalWrite(_bluePin, LOW);
}

/*Function that blinks the LED three times*/
void MyRGB::blinkThrice() { 
  for (int i=0; i<3; i++) 
  {
    digitalWrite(_bluePin, HIGH);
    digitalWrite(_redPin, HIGH);
    digitalWrite(_greenPin, HIGH);
    delay(blinkRate); 
    digitalWrite(_bluePin, LOW);
    digitalWrite(_redPin, LOW);
    digitalWrite(_greenPin, LOW);  
    delay(blinkRate);
  }
}

int MyRGB::updateSwitch() {
  swState = digitalRead(sw);
  
  if (swState != swStateLast) 
  {
    return swState;
    swStateLast = swState;
  }
  else {
    return swStateLast;
  }
  delay(50);
}

void MyRGB::updateLed(String color, int on) 
{
  if (on == 0)
  {
    offRGB();
  }
  else
  {
    int red = digitalRead(_redPin);
    int blue = digitalRead(_bluePin);
    int green = digitalRead(_greenPin);

    if (red == HIGH || blue == HIGH || green == HIGH)
    {
      return;
    }
    
    else
    {
      if (color == "red")
      {
        redRGB();
      }
      else if (color == "green")
      {
        greenRGB();
      }
      else if (color == "blue")
      {
        blueRGB();
      }
    }
  }
}

