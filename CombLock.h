/*
  CombLock.h - Library for digital combination lock.
*/

#ifndef COMBLOCK_H
#define COMBLOCK_H

#include <Arduino.h>

/* Global constants */
#define common_cathode 0
#define common_anode 1


class CombLock {

  public: 

    CombLock( int a, int b, int c, int d, int e, int f, int g, int dp, int d1, int d2, int d3, int d4, int swPin, int clkPin, int dtPin );   /*Constructor*/
    
    /*Setup Functions*/
    void setMode(bool mode);
    void setKey(int key1, int key2, int key3, int key4);  
    void blankOut(); 
    void init7seg(bool mode);
    void initRotary();
    void initLock(bool mode); /*initialize 7 segment display (setMode) and rotary encoder, fill myCode array */

    /*Dial turning functions*/
    void turnDial();
    void displayNum(byte num, byte dig);
    bool verifyCode();      

    /*Public Variables*/
    bool TASK1_DONE;
    int digitCounter;

  private:

    /*Combination lock*/
    int _myKey[4] = {0};
    int _myAttempt[4] = {0};
    
    /*Rotary encoder pins*/
    int _swPin;
    int _dtPin;
    int _clkPin;

    int _switchState;
    int _clockState;
    int _clockStateLast;
    
    bool _CW;
    bool _CCW;
    float _pos;
    byte _currentNumIndex;
    byte _lastNumIndex;

};

#endif
