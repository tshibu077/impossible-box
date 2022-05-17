#include <Arduino.h>
#include "MyRGB.h"

/*Constructor*/
MyRGB::MyRGB(int redPin, int greenPin, int bluePin) {
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  
  _redPin = redPin;
  _greenPin = greenPin;
  _bluePin = bluePin;
}

void MyRGB::greenRGB() {
  analogWrite(_redPin, 0);
  analogWrite(_greenPin, 255);
  analogWrite(_bluePin, 0);
}

void MyRGB::redRGB() {
  analogWrite(_redPin, 255);
  analogWrite(_greenPin, 0);
  analogWrite(_bluePin, 0);
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

void MyRGB::blinkRGB(int blinkRate) { 
  digitalWrite(_bluePin, HIGH);
  digitalWrite(_redPin, HIGH);
  digitalWrite(_greenPin, HIGH);
  delay(blinkRate); 
  digitalWrite(_bluePin, LOW);
  digitalWrite(_redPin, LOW);
  digitalWrite(_greenPin, LOW);  
  delay(blinkRate);
}
