/* 
 * -------------------------------------------------------------------------
 * Arduino Button Box
 * -------------------------------------------------------------------------
 * Copyright Kevin Peat 2014
 * kevin@kevinpeat.com
 * This sketch is licensed public domain
 * -------------------------------------------------------------------------
 * Original code provided by Dan Nixon on his blog
 * Multiplexing Switches on Arduino without additional ICs
 * http://www.dan-nixon.com/2012/04/multiplexing-switches-on-arduino.html
 * -------------------------------------------------------------------------
 * Requires an Arduino Leonardo or other similar device that is able to 
 * emulate a USB HID Keyboard
 * -------------------------------------------------------------------------
 * Hardware to be used with iRacing and other racing sims. The simple 
 * hardware design means that only one button can be pressed at a time 
 * which is not a problem for this type of hardware. Also there is no need 
 * for key modifiers so only simple key presses can be sent.
 * -------------------------------------------------------------------------
 * Mike: Changes
 *    1) Added include of Keyboard.h (note capitalization)
 *    2) Remove hex-codes - use literals from "Keyboard.h"
 *    3) Added the keyboard modifier codes
 *    4) Added the code to press, then release the keyboard modifier if not set
 *    5) Tarted up the debug text output
 *    6) Tarted up the key matrix arrays
 *    7) Support key modifiers without keypresses (keypress of 0)
 *    8) Added a short delay between each key scan-row to mitigate capacitive coupling
 * Mike : 28/7/2025
 *    Updated to include auto button repeat.
 * Mike : 30/7/2025
 *    Removed all spurious delays
 * Mike : 17/8/2025
 *    Complete rewrite - key scan and USB keycode insertion logic. Re-org whole sw
 */

#include "myKeyboard.h"
//#include "Keyboard.h"
#include "settings.h"
#include "debug.h"

void setup()
{
  //Start Serial
  Serial.begin(9600);
  delay(1000);
  SERIAL_PRINTLN("");
  SERIAL_PRINTLN("");
  Serial.print("Version: "); Serial.print(VERSION); Serial.print("\n");

  for (int cPin = 0; cPin < cPinsNo; cPin++)
  {
    pinMode(cPins[cPin], OUTPUT);
    digitalWrite(cPins[cPin], HIGH);
  }

  //Set the Row Pin Mode

  for (int rPin = 0; rPin < rPinsNo; rPin++)
  {
    pinMode(rPins[rPin], INPUT_PULLUP);
    digitalWrite(rPins[rPin], HIGH);
  }
}
int logno = 0;

void loop()
{

  typedef struct KeyScan_t
  {
    uint8_t Col;                  // Key matrix column - for the 'active' (pressed or just released key)
    uint8_t Row;                  // Key matrix row
    bool    Active;               // Whether that matrix key is active or not
    bool    KeyPressed;           // Current Key State
    bool    PreviousKeyPressed;   // Current Key State on the previous cycle
  };

  static KeyScan_t keyScan = {0,0,false};


  if (keyScan.Active == false)
  {
    // Loop through the columns
    for (int cPin = 0; cPin < cPinsNo; cPin++)
    {
      digitalWrite(cPins[cPin], LOW);

      // Loop through the rows
      for (int rPin = 0; rPin < rPinsNo; rPin++)
      {
        //Check if each switch is pressed
        if (digitalRead(rPins[rPin]) == LOW)
        {
          if (keyScan.Active == false)    
          {
            keyScan = {cPin,rPin,true,true,false};
          }
        }
      }
      digitalWrite(cPins[cPin], HIGH);
    }
  }


  if (keyScan.Active)
  {
    // Evaluate the state of the current active key
    digitalWrite(cPins[keyScan.Col], LOW);
    if (digitalRead(rPins[keyScan.Row]) == LOW)
      keyScan.KeyPressed = true;
    else
      keyScan.KeyPressed = false;
    digitalWrite(cPins[keyScan.Col], HIGH);  


    switch (keyScan.KeyPressed)
    {
      //
      // Key has just been released
      //
      case false:
        if (Codes[keyScan.Col][keyScan.Row].hold)
        {
          myKeyboard.releaseAll();
        }

        // Release the active key
        keyScan = { 0, 0, false, false, false };
        break;

      //
      // Key is pressed 
      //
      case true:
        if (keyScan.PreviousKeyPressed == false)
        {
          // Key has only just been pressed

          keyScan.PreviousKeyPressed = true;

          if (Codes[keyScan.Col][keyScan.Row].hold)
          {
            // An auto-repeat key is selected
            myKeyboard.pressWithoutSending(Codes[keyScan.Col][keyScan.Row].modifierCode);
            myKeyboard.press(Codes[keyScan.Col][keyScan.Row].keyCode);
          }
          else
          {
            // A non-repeat key is selected
            myKeyboard.pressWithoutSending(Codes[keyScan.Col][keyScan.Row].modifierCode);
            myKeyboard.press(Codes[keyScan.Col][keyScan.Row].keyCode);
            delay(10);
            myKeyboard.releaseAll();
          }
        }
        break;
    }
  }
}

