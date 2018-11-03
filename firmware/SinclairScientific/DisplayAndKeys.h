#pragma once

#include <Arduino.h>

#define SegmentA 5
#define SegmentB 0
#define SegmentC 10
#define SegmentD 19
#define SegmentE 1
#define SegmentF 6
#define SegmentG 14
#define SegmentDP 18

#define Digit1 2
#define Digit2 3
#define Digit3 4
#define Digit4 17
#define Digit5 16
#define Digit6 7
#define Digit7 15
#define Digit8 11
#define Digit9 12

#define SegmentOn HIGH
#define SegmentOff LOW
#define DigitOn HIGH
#define DigitOff LOW
//#define IsKeyPushed > 100


void setupFastADC();

void allSegmentOutput();

void allSegmentInput();

void allDigitOutput();

void allDigitInput();

void allSegmentOff();

void allDigitOff();

byte outputDigit(signed char digit, bool decimalpoint = false);

void selectDigit(byte digit);

byte readKey();

//since reakKey only reads the active column, this function sweeps through all columns and calls readKey
byte readKeys();

