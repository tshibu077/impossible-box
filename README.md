# EENG 348: Final Project
# (Evil) Puzzle Box
### Tanya Shibu



### Overview of the final project: 
  
  The goal of the project is to build a "evil" (as in, tricky to open) box. The aim was to create something fun and visual.
  The Puzzle Box is a game, and the goal for a player is to "unlock" it. 
  The box can only be opened electronically: a servo rotates a piece of the top face of the box to open a hole, and rotates back to close it. 
  
  The completion of three puzzle-like interactive tasks result in this servo-controlled opening. 
  The tasks can be worked on concurrently. Each task has a simple success condition. 
  When all 3 success conditions are met, the main program will open the box. 
  The I2C Display will be used to display the instruction/clue needed to solve each task.
 

Below is a more detailed description of each task (Name, Hardware components, Setup, Instructions, Success condition). 
At the bottom of the README file is a table of contents. 


####  1. Name: LightLock
     
     Hardware components: 3x RGB LEDs, 4x SPDT switches
     
     Setup: There are three pairs of LEDs/Switches. Within each pair, the switch is used to toggle the LED on or off. 
            The fourth switch is a colour-control switch that affects all the LEDs. 
            Toggling this switch changes what colour an LED will appear, if it is turned from OFF to ON. Note that 
            this means a LED never changes colour while ON; it must be turned OFF then ON again to change its colour. 
            There are three possible colours and two states for the SPDT switch, so each toggle cycles between red-green-blue.
            
            Example: 
            Let LEDs be labelled A-C. Switch D sets colour. 
              1. Switch D is set to red. LED A, LED B, LED C are OFF.  
              2. LED A is turned ON. Now A is red, B is OFF, C is OFF.
              3. Switch D is toggled once, now set to green. 
              4. LED B is turned ON. Now A is red, B is green, C is OFF. 
              5. Switch D is toggled once, now set to blue. 
              6. LED B is turned OFF then ON. LED C is turned ON. Now A is red, B is blue, C is blue. 
              and so on. 
              
     Instructions: A random code is generated that represents the colours the 3 LEDs need to be set to. 
     This code is displayed on the I2C OLED-display. For example, red-blue-blue will be displayed as "R B B". 
     The player needs to use the switches to set the colours to this correct code. 
     
     Success condition: When the LED colours satisfy the code, the task is complete. 


 #### 2. Name: CombLock    
     
     Hardware components: Rotary encoder, 4 Digit x 7 Segment LED Display. 
     
     Setup: A digital combination lock. The rotary encoder is the 'dial' being rotated, the 4x7-segment 
     LED displays the numbers that the dial is currently pointing to. 
     The 4-digit password is randomly generated every game and displayed on the I2C. 
     
     Instructions: Just like in a real combination lock, the player must reverse the direction of turning the dial
     to set each successive digit. Turning the dial CW to sets the 1st digit; then CCW to set the 2nd digit; then CW
     to set the 3rd digit; then CCW to set the 4th digit; then CW to submit the 4 digits to be checked by the main program.
     
     Success condition: If the final four digits being displayed match the password displayed on the I2C, task is complete. 
     Otherwise, lock is reset and the player can try again.


  #### 3. Name: PCLock
     
     Hardware components: 8x Photocells
     
     Setup: There are 8 photocells (PCs) embedded in the face of the box. Two PCs are randomly selected to be 
     the "active target" PCs. The other 6 PCs will create the smokescreen. 
     If the player covers a PC with their finger, the PC (being a light-dependent resistor) will detect it as dark.
     
     Instructions:  The aim is to cover both of the "active target" PCs simultaneously. 
     However, the player has no way of knowing which two are active, because there are 6 inactive red herrings. 
     The challenge is to figure out which two are the right combination. 
     
     Success condition: The two active PCs must detect "dark" simultaneously. 
     If more than 2 PCs are "dark", no success. So, a player cannot cheat by covering all the PCs. This also means
     there must be sufficient ambient light while playing for this task to work, so all the inactive PCs can detect "light". 
     
     
     
### Contents of this repository: 

1. A library and class was made for each task. Each library has a source code (.cpp) and header file (.h). 
    These files are named LightLock, PCLock, and CombLock. 
    The classes contain functions to init the hardware components, init the passwords/codes, respond to player's inputs, 
    and verify success at the end. 

2. A library for the servo-controlled lid. Contains function to init the servo, open the box, close the box. 

3. A library for defining class for RGB LEDs. Contains functions for setting red/green/blue colour. 

In the "Demos, Schematics, PDFs" folder:

4. PDF "Box - Laser-cut Layout" showing the laser-cut cardboard pieces of the box. 

5. PDF: "Circuit schematics" for the 3 lock tasks

6. Video demos: 
    
    "LightLock Demo.mov" : 
    
    Player William Starch is given a puzzle code ("BGR") and demonstrates control of the switches to solve to puzzle.
    Arduino main program run for this video uses function updateLightLock() from LightLock.cpp

