#include <Arduino.h>
#include "MyRGB.h"

#define blinkRate 150

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
  pinMode(switchPin, INPUT);
  
  _redPin = redPin;
  _greenPin = greenPin;
  _bluePin = bluePin;
  sw = switchPin;
}

/*Functions to make setting a color simple in main program*/
void MyRGB::redRGB() {
  analogWrite(_redPin, 255);
  analogWrite(_greenPin, 0);
  analogWrite(_bluePin, 0);
}

void MyRGB::greenRGB() {
  analogWrite(_redPin, 0);
  analogWrite(_greenPin, 255);
  analogWrite(_bluePin, 0);
}

void MyRGB::blueRGB() {
  analogWrite(_redPin, 0);
  analogWrite(_greenPin, 0);
  analogWrite(_bluePin, 255);
}

void MyRGB::whiteRGB() {
  analogWrite(_redPin, 255);
  analogWrite(_greenPin, 255);
  analogWrite(_bluePin, 255);
}

void MyRGB::offRGB() {
  analogWrite(_redPin, 0);
  analogWrite(_greenPin, 0);
  analogWrite(_bluePin, 0);
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
