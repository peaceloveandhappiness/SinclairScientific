#pragma once

#include "CPU.h"
#include <Arduino.h>

#define _steptime 341

#define CommonAnode


#define AlignRight
//#define AlignLeft

//#define EnableDisassembly

//signed char digits[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
//
//// keysKN and keysKO must match PrintableKeys on DisplayAndKeys.ino
////const char PrintableKeys[19] = "12+E0v-378X654/9^C";
//
//const char keysKN[10] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 0};
//const char keysKO[10] = {'C', 'v', '+', '-', '/', 'X', '^', 'E', '0', 0};
////const char keysKP[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//
//// to use with keyPressed
#define DK 1

// ORIGINAL SINCLAIR DATA
typedef struct 
{
  boolean sinclair = true;

  // Important: Array order matches display order, not bit order.
  // I.e. a[0] is high-order digit S10, a[10] is low-order digit S0.
  signed char  a[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};    // Register A
  signed char  b[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};    // Register B
  signed char  c[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};    // Register C
  signed char af[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};    // Flags A
  signed char bf[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};    // Flags A

  signed char  d[11] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

  byte dActive = 1;          // Currently active D value 1-11. d[dActive-1] == 0
  signed char cc = 0;
  byte keyPressed = 0;

  byte keyStrobeKN = 0;      //
  byte keyStrobeKO = 0;      // '
  byte keyStrobeKP = 0;      // '

  unsigned int address = 0;  // PROGRAM COUNTER
  byte display = 1;          // Flag for display on
  //char mask[MASK_LENGTH];
  signed char mask[MASK_LENGTH];

  byte showwork = 0;         // when 0, display flag controls LED, when 1, LED always on
  byte speed = 1;            // 0 - slow 1 - normal 2 - fast
  int steptime = _steptime;  // the step() function will take this many microseconds to execute, uses a delay to eat remaining time if it finishes faster.
  int steptime1 = _steptime; // backup

  bool resetinprogress = false;
  byte segmentslit = 0;

  byte lastSelectDigit = 0;

  bool timeinit = false;
  unsigned long nextentrytime = 0;

} SinclairData_t;

extern SinclairData_t SinclairData;



