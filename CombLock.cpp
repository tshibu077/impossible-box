#include <Arduino.h>
#include "CombLock.h"
#include "7SegCharCodes.h"

/*Source file for CombLock library.
 *  Reads rotary encoder to dial numbers up/down on the 7=segment display,
 *  creating a digital combination lock.    
 */

#define common_cathode 0
#define common_anode 1

int _digPins[4] = {0,0,0,0};
int _segPins[8] = {0,0,0,0,0,0,0,0};
bool _digOn;
bool _segOn;
bool _mode;


/*Constructor*/
CombLock::CombLock(int a, int b, int c, int d, int e, int f, int g, int dp, int d1, int d2, int d3, int d4, int swPin, int clkPin, int dtPin) 
{
  /*4x7 Segment Display pins*/
  _segPins[0] = a;
  _segPins[1] = b;
  _segPins[2] = c;
  _segPins[3] = d;
  _segPins[4] = e;
  _segPins[5] = f;
  _segPins[6] = g;
  _segPins[7] = dp;
  
  _digPins[0] = d1;
  _digPins[1] = d2;
  _digPins[2] = d3;
  _digPins[3] = d4;

  /*Rotary encoder pins*/
  _swPin = swPin;
  _clkPin = clkPin;
  _dtPin = dtPin;
}

void CombLock::initRotary() {

  /*Set pins as inputs*/
  pinMode(_swPin, INPUT_PULLUP);     //enable input with passive pullup
  pinMode(_clkPin, INPUT);           //enable input
  pinMode(_dtPin, INPUT);            //enable input

  /*Initialize state variables*/
  _switchState = HIGH;
  _clockState = LOW;               
  _clockStateLast = _clockState; 

  /*Variables for working with combination dial*/
  _CW = false;                      //Direction of rotation. First turn must be CW and will toggle this. 
  _CCW = false;                     //Second digit must be CCW, will toggle this to true. 
  _pos = 0;                         //Postition counter for rotation
  digitCounter = 0;
}

void CombLock::init7seg(bool mode) {

  /*Set mode*/
  setMode(mode);

  /*Set pins as outputs*/
  for(int i=0; i<8; i++){
    pinMode(_segPins[i], OUTPUT); 
  }
  for(byte i=0; i<4; i++){
    pinMode(_digPins[i], OUTPUT);  
  }

  /*Reset 7 segment*/
  blankOut();

  /*Initialize the display-control variables*/
  digitCounter = 0;
  _currentNumIndex = IDX_BLANK;     //character code for ' '
  _lastNumIndex = _currentNumIndex;
 
}

void CombLock::blankOut() {

  /*Turns off segments; blanks out without using character codes*/
  for(int i=0; i<8; i++){
    digitalWrite(_segPins[i], !_segOn);    //turn off segments
  }
  for(int i=0; i<4; i++){
    digitalWrite(_digPins[i], !_digOn);    //turn off digits
  }
}

void CombLock::setMode(bool mode) {

  /*Common cathode type, all cathode ends are grounded. For common anode, all anode ends are connected to Vcc.
   * Global var common_cathode = 0; so setting segment pin to 1 and digit pin to 0 means ON. 
   * Opposite for common anode. 
   */
   
  switch (mode) 
  {
    case common_cathode: 
      _segOn = HIGH;
      _digOn = LOW;
      break;    
    case common_anode:
      _segOn = LOW;
      _digOn = HIGH;
      break;
  }

  _mode = mode;
}

void CombLock::setKey(int key1, int key2, int key3, int key4 )
{
  _myKey[0] = key1;
  _myKey[1] = key2;
  _myKey[3] = key3;
  _myKey[4] = key4;

}

void CombLock::initLock(bool mode) {

  init7seg(mode);
  initRotary();

  /*Display '----' to indicate ready*/
  displayNum(IDX_DASH, 1);
  displayNum(IDX_DASH, 2);
  displayNum(IDX_DASH, 3);
  displayNum(IDX_DASH, 4);

  TASK1_DONE = false;

}

/*Handler for rotary encoder. 
 * ISR detects direction of rotation. Goes through 'switch' cases 0-5.
 *  0. Has not started writing to digits display. 
 *  1. First CW turn initiates first digit. 
 *  2. Switch direction (to CCW) to move to second digit. 
 *  3. Switch again (to CW) for third digit. 
 *  4. Switch again (to CCW) for fourth digit. 
 *  5. Press button to submit code (only possible after 1-4 occurs)
 *
 *  Note: The interrupt service routine for the rotary encoder ('updateLock') depends
 *         on a change in pinB rather than pinA. pinB is connected to the MEGA's int pin (pin3).
 *         This means the directions detected by the ISR would be opposite to if pinA was used. 
 * 
 *          Order of output changes for CW rotation: 
 *            #     Position   Bit1   Bit2   
 *          ------------------------------------
 *           1       Step1     0      0      LL
 *           2        1/4      1      0      LH
 *           3        1/2      1      1      HH
 *           4        3/4      0      1      HL
 *           5       Step2     0      0      LL
 *        
 *          For CCW rotation, just read the table bottom to up.            
 */

void CombLock::turnDial() {

  _clockState = digitalRead(_clkPin);
  
  if ((_clockStateLast == LOW) && (_clockState == HIGH)) 
  {
    delay (3);                                          //short delay helps debounce
    
    if (digitalRead(_dtPin) == HIGH) 
    {                  
      _CW = true;                                       //if pinB high, CW direction
      _CCW = false;
    }
    
    else if (digitalRead(_dtPin) == LOW) 
    {             
       _CCW = true;                                     //if pinB low, CCW direction
       _CW = false;
    } 
    _clockStateLast = _clockState;
  }
  
  switch (digitCounter)
  {
    case 0:
      if (_CW = false) {
        break;
      } 
      else if (_CW == true && _CCW == false) 
      {        
        digitCounter = 1;
        _currentNumIndex = 0;
        _lastNumIndex = _currentNumIndex;
        _pos = 0;
      }
      break;
      
    case 1:
      if ( _CW == true ) 
      {
        if (_pos < 10.0) 
        {
          _pos += 0.25;
        } else if (_pos > 9.75) {
          _pos = 0;
        }
        _currentNumIndex = _pos;
        
        if (_currentNumIndex != _lastNumIndex)
        {
          displayNum(_currentNumIndex, 1);
          _lastNumIndex = _currentNumIndex;       
        }
      }
       
      else if ( _CCW == true) 
      {
        _myAttempt[0] = _lastNumIndex;
        
        digitCounter = 2;
        _currentNumIndex = 0;
        _lastNumIndex = _currentNumIndex;
        _pos = 0;
      }
      
      break;

    case 2:
      if (_CCW == true)
      {
        if (_pos < 10.0) 
        {
          _pos += 0.25;
        } else if (_pos > 9.75) {
          _pos = 0;
        }
        _currentNumIndex = _pos;
        
        if (_currentNumIndex != _lastNumIndex)
        {
          displayNum(_currentNumIndex, 2);
          _lastNumIndex = _currentNumIndex;       
        }
      }

      else if ( _CW == true )
      {
        _myAttempt[1] = _lastNumIndex;
        
        digitCounter = 3;
        _currentNumIndex = 0;
        _lastNumIndex = _currentNumIndex;
        _pos = 0;
      }

      break;

    case 3:
      if (_CW == true)
      {
        if (_pos < 10.0) 
        {
          _pos += 0.25;
        } else if (_pos > 9.75) {
          _pos = 0;
        }
        _currentNumIndex = _pos;
        
        if (_currentNumIndex != _lastNumIndex)
        {
          displayNum(_currentNumIndex, 2);
          _lastNumIndex = _currentNumIndex;       
        }
      }

      else if ( _CCW == true )
      {
        _myAttempt[2] = _lastNumIndex;
        
        digitCounter = 4;
        _currentNumIndex = 0;
        _lastNumIndex = _currentNumIndex;
        _pos = 0;
      }

      break;

    case 4:
      if (_CCW == true)
      {
        if (_pos < 10.0) 
        {
          _pos += 0.25;
        } else if (_pos > 9.75) {
          _pos = 0;
        }
        _currentNumIndex = _pos;
        
        if (_currentNumIndex != _lastNumIndex)
        {
          displayNum(_currentNumIndex, 2);
          _lastNumIndex = _currentNumIndex;       
        }
      }

      else if ( _CW == true )
      {
        _myAttempt[3] = _lastNumIndex;
        
        digitCounter = 5;
        _currentNumIndex = 0;
        _lastNumIndex = _currentNumIndex;
        _pos = 0;
      }
      break;

    case 5:     
      if (TASK1_DONE == false) 
      {
        displayNum(_myAttempt[0], 1);
        displayNum(_myAttempt[1], 2);
        displayNum(_myAttempt[2], 3);
        displayNum(_myAttempt[3], 4);
      }
      /* Main program will call verifyCode function; if correct,
       * will set TASK1_DONE to true then detach the interrupt for CombLock.*/   
      break;
  }
}

bool CombLock::verifyCode() 
{
  for (int i=0; i<4; i++) 
  {
    if (_myKey[i] != _myAttempt[i])
    {
      return TASK1_DONE;
    }
  }
  TASK1_DONE = false;
  return TASK1_DONE;
}

void displayNum(byte num, int digit) 
{  
  /*Set digit port on, other digits off*/
  for (int i=0; i<4; i++) 
  {
    if (i == digit) 
    {
      digitalWrite(_digPins[i], _digOn);
    } 
    else {
      digitalWrite(_digPins[i], !_digOn);
    }
  }

  /*Use character codes in 7SegCharCodes.h to set segments on or off. */
  /* segCodes[] index is given by input 'num' */                               

  for (int j=0; j<8; j++) 
  {
    /*Use bitwise AND with bit-shifting to get individual bits*/   
    byte b = (segCodes[num] & (1 << j));
    
    if (_mode == common_cathode) 
    {
      digitalWrite(_segPins[j], b);
    }
    else if (_mode == common_anode) 
    {
      digitalWrite(_segPins[j], !b);
    }
  }
}
