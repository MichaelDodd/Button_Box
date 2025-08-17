#define VERSION "0.1"

/*
 * Holds settings / constants away from the main code units. Anything that
 * should be configurable by the user should be included in this file.
 *
 * Vers   Date         Comment
 *  1     03/08/2025   First release
 *
 */

#ifndef SETTINGS_H
#define SETTINGS_H
/*
 * -------------------------------------------------------------------------
 * Arduino Leonardo key codes
 * -------------------------------------------------------------------------
      0 = 0x30
      1 = 0x31
      2 = 0x32
      3 = 0x33
      4 = 0x34
      5 = 0x35
      6 = 0x36
      7 = 0x37
      8 = 0x38
      9 = 0x39
      a = 0x61
      b = 0x62
      c = 0x63
      d = 0x64
      e = 0x65
      f = 0x66
      g = 0x67
      h = 0x68
      i = 0x69
      j = 0x6A
      k = 0x6B
      l = 0x6C
      m = 0x6D
      n = 0x6E
      o = 0x6F
      p = 0x70
      q = 0x71
      r = 0x72
      s = 0x73
      t = 0x74
      u = 0x75
      v = 0x76
      v = 0x76
      w = 0x77
      x = 0x78
      y = 0x79
      z = 0x7A
      ' = 0x27
      , = 0x2C
      - = 0x2D
      . = 0x2E
      / = 0x2F 
      ; = 0x3B
      = = 0x3D
      [ = 0x5B
      ] = 0x5D
      #~ = 0x7E
      # = 0xE0
      F1 = 0xC2
      F2 = 0xC3
      F3 = 0xC4
      F4 = 0xC5
      F5 = 0xC6
      F6 = 0xC7
      F7 = 0xC8
      F8 = 0xC9
      F9 = 0xCA
      F10 = 0xCB
      F11 = 0xCC
      F12 = 0xCD
      BACKSPACE = 0xB2
      DELETE = 0xD4
      ESC = 0xB1
      HOME = 0xD2
      INSERT = 0xD1
      RETURN = 0xB0
      SPACE = 0x20
      TAB = 0xB3
      LEFT_ARROW = 0xD8
      RIGHT_ARROW = 0xD7
      UP_ARROW = 0xDA
      DOWN_ARROW = 0xD9
 * -------------------------------------------------------------------------
 */
// Number of pins in the column array
int const cPinsNo = 5;

// Number of pins in the row array
int const rPinsNo = 4;

// number of milliseconds delay between each keyboard column strobe, to minimise capacitive coupling noise
int const decoupleDelay = 1;

// Array of pins for the columns
int cPins[cPinsNo] = { 2, 3, 4, 5, 6 };

// Array of pins for the rows
int rPins[rPinsNo] = { 7, 8, 9, 10 };

// Array for the last known switch states [cPinsNo][rPinsNo]
//int colPrev[cPinsNo][rPinsNo] = { 0 };

/*
class Repeat_c
{
  typedef uint8_t Repeat_t;

  Repeat_t const AUTO_REPEAT = 0;
  Repeat_t const NO_REPEAT = 1;
};
*/

// buttons
//
// Buttons have 3 attributes:
// keyCode      : physical key-code value
// modifierCode : Keyboard modifier key to be pressed before the keyCode (can be 0) 
// hold         : boolean - if true, then the keycode press is held pressed
//
typedef struct
{
  uint8_t keyCode;
  uint8_t modifierCode;
  bool    hold;
} buttons;

#define NO_MODIFIER 0
#define AUTO_REPEAT 1
#define NO_REPEAT   0


buttons const Codes[cPinsNo][rPinsNo] = 
{
  { {KEY_LEFT_ARROW, NO_MODIFIER,AUTO_REPEAT}, {KEY_RIGHT_ARROW, NO_MODIFIER, AUTO_REPEAT},  {KEY_UP_ARROW, NO_MODIFIER, NO_REPEAT}, {KEY_DOWN_ARROW, NO_MODIFIER, NO_REPEAT} },
  { {'e', NO_MODIFIER,    NO_REPEAT}          , {'f', NO_MODIFIER, NO_REPEAT},                {'g', KEY_LEFT_ALT, NO_REPEAT},         {'h', NO_MODIFIER, NO_REPEAT} },
  { {'i', KEY_LEFT_SHIFT, NO_REPEAT}          , {'j', NO_MODIFIER, NO_REPEAT},                {'k', KEY_LEFT_ALT, NO_REPEAT},         {'l', NO_MODIFIER, NO_REPEAT} },
  { {'m', KEY_LEFT_SHIFT, NO_REPEAT}          , {'n', NO_MODIFIER, NO_REPEAT},                {'o', KEY_LEFT_ALT, NO_REPEAT},         {'p', NO_MODIFIER, NO_REPEAT} },
  { {'q', KEY_LEFT_SHIFT, NO_REPEAT}          , {'r', NO_MODIFIER, NO_REPEAT},                {'s', KEY_LEFT_ALT, NO_REPEAT},         {'t', NO_MODIFIER, NO_REPEAT} }
};

#endif
