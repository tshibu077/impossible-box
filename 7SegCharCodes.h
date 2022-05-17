/*Character codes for 7-segment display*/

#include <Arduino.h>

static const byte numOfChars = 13;     /*how many characters are included in this file*/
static const byte IDX_DASH = 11;    /*indices*/
static const byte IDX_DOT = 12; 
static const byte IDX_BLANK = 13;

/*Segment naming convention: 
            A 
            --
         F |  | B  
            -- G 
         E |  | C 
            --  
            D
Array of 8-bit character codes:*/
static const byte segCodes[numOfChars] 
{
    0b00111111, // 0   
    0b00000110, // 1   
    0b01011011, // 2   
    0b01001111, // 3   
    0b01100110, // 4  
    0b01101101, // 5   
    0b01111101, // 6 
    0b00000111, // 7   
    0b01111111, // 8   
    0b01101111, // 9   
    0b01000000, // '-'  dash. error output
    0b10000000, // '.'  point. 
    0b00000000, // ' '  blank.
};
