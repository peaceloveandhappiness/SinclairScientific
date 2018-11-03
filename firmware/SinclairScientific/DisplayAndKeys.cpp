
#include "DisplayAndKeys.h"
#include "SinclairScientific.h"

// http://forum.arduino.cc/index.php?topic=6549.msg51570#msg51570
// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

void setupFastADC()
{
  // http://forum.arduino.cc/index.php?topic=6549.msg51570#msg51570
  // set prescale to 16
//  sbi(ADCSRA, ADPS2) ;
//  cbi(ADCSRA, ADPS1) ;
//  cbi(ADCSRA, ADPS0) ;
}

void allSegmentOutput()
{
  pinMode(SegmentA, OUTPUT);
  pinMode(SegmentB, OUTPUT);
  pinMode(SegmentC, OUTPUT);
  pinMode(SegmentD, OUTPUT);
  pinMode(SegmentE, OUTPUT);
  pinMode(SegmentF, OUTPUT);
  pinMode(SegmentG, OUTPUT);
  pinMode(SegmentDP, OUTPUT);
}

void allSegmentInput()
{
  pinMode(SegmentA, INPUT);
  pinMode(SegmentB, INPUT);
  pinMode(SegmentC, INPUT);
  pinMode(SegmentD, INPUT);
  pinMode(SegmentE, INPUT);
  pinMode(SegmentF, INPUT);
  pinMode(SegmentG, INPUT);
  pinMode(SegmentDP, INPUT);
}

void allDigitOutput()
{
  pinMode(Digit1, OUTPUT);
  pinMode(Digit2, OUTPUT);
  pinMode(Digit3, OUTPUT);
  pinMode(Digit4, OUTPUT);
  pinMode(Digit5, OUTPUT);
  pinMode(Digit6, OUTPUT);
  pinMode(Digit7, OUTPUT);
  pinMode(Digit8, OUTPUT);
  pinMode(Digit9, OUTPUT);
}

void allDigitInput()
{
  pinMode(Digit1, INPUT);
  pinMode(Digit2, INPUT);
  pinMode(Digit3, INPUT);
  pinMode(Digit4, INPUT);
  pinMode(Digit5, INPUT);
  pinMode(Digit6, INPUT);
  pinMode(Digit7, INPUT);
  pinMode(Digit8, INPUT);
  pinMode(Digit9, INPUT);
}

void allSegmentOff()
{
  digitalWrite(SegmentA, SegmentOff);
  digitalWrite(SegmentB, SegmentOff);
  digitalWrite(SegmentC, SegmentOff);
  digitalWrite(SegmentD, SegmentOff);
  digitalWrite(SegmentE, SegmentOff);
  digitalWrite(SegmentF, SegmentOff);
  digitalWrite(SegmentG, SegmentOff);
  digitalWrite(SegmentDP, SegmentOff);
}

void allDigitOff()
{
  digitalWrite(Digit1, DigitOff);
  digitalWrite(Digit2, DigitOff);
  digitalWrite(Digit3, DigitOff);
  digitalWrite(Digit4, DigitOff);
  digitalWrite(Digit5, DigitOff);
  digitalWrite(Digit6, DigitOff);
  digitalWrite(Digit7, DigitOff);
  digitalWrite(Digit8, DigitOff);
  digitalWrite(Digit9, DigitOff);
}

byte outputDigit(signed char digit, bool decimalpoint) {

  byte segmentslit = 0;

  allDigitOff();

  if (decimalpoint)
  {
    //segmentslit++;
    digitalWrite(SegmentDP, SegmentOn);
  }
  else
  {
    digitalWrite(SegmentDP, SegmentOff);
  }

  switch (digit) {
    case 0:
      digitalWrite(SegmentA, SegmentOn);
      digitalWrite(SegmentB, SegmentOn);
      digitalWrite(SegmentC, SegmentOn);
      digitalWrite(SegmentD, SegmentOn);
      digitalWrite(SegmentE, SegmentOn);
      digitalWrite(SegmentF, SegmentOn);
      digitalWrite(SegmentG, SegmentOff);
      segmentslit += 6;
      break;
    case 1:
      digitalWrite(SegmentA, SegmentOff);
      digitalWrite(SegmentB, SegmentOn);
      digitalWrite(SegmentC, SegmentOn);
      digitalWrite(SegmentD, SegmentOff);
      digitalWrite(SegmentE, SegmentOff);
      digitalWrite(SegmentF, SegmentOff);
      digitalWrite(SegmentG, SegmentOff);
      segmentslit += 2;
      break;
    case 2:
      digitalWrite(SegmentA, SegmentOn);
      digitalWrite(SegmentB, SegmentOn);
      digitalWrite(SegmentC, SegmentOff);
      digitalWrite(SegmentD, SegmentOn);
      digitalWrite(SegmentE, SegmentOn);
      digitalWrite(SegmentF, SegmentOff);
      digitalWrite(SegmentG, SegmentOn);
      segmentslit += 5;
      break;
    case 3:
      digitalWrite(SegmentA, SegmentOn);
      digitalWrite(SegmentB, SegmentOn);
      digitalWrite(SegmentC, SegmentOn);
      digitalWrite(SegmentD, SegmentOn);
      digitalWrite(SegmentE, SegmentOff);
      digitalWrite(SegmentF, SegmentOff);
      digitalWrite(SegmentG, SegmentOn);
      segmentslit += 5;
      break;
    case 4:
      digitalWrite(SegmentA, SegmentOff);
      digitalWrite(SegmentB, SegmentOn);
      digitalWrite(SegmentC, SegmentOn);
      digitalWrite(SegmentD, SegmentOff);
      digitalWrite(SegmentE, SegmentOff);
      digitalWrite(SegmentF, SegmentOn);
      digitalWrite(SegmentG, SegmentOn);
      segmentslit += 4;
      break;
    case 5:
      digitalWrite(SegmentA, SegmentOn);
      digitalWrite(SegmentB, SegmentOff);
      digitalWrite(SegmentC, SegmentOn);
      digitalWrite(SegmentD, SegmentOn);
      digitalWrite(SegmentE, SegmentOff);
      digitalWrite(SegmentF, SegmentOn);
      digitalWrite(SegmentG, SegmentOn);
      segmentslit += 5;
      break;
    case 6:
      digitalWrite(SegmentA, SegmentOn);
      digitalWrite(SegmentB, SegmentOff);
      digitalWrite(SegmentC, SegmentOn);
      digitalWrite(SegmentD, SegmentOn);
      digitalWrite(SegmentE, SegmentOn);
      digitalWrite(SegmentF, SegmentOn);
      digitalWrite(SegmentG, SegmentOn);
      segmentslit += 6;
      break;
    case 7:
      digitalWrite(SegmentA, SegmentOn);
      digitalWrite(SegmentB, SegmentOn);
      digitalWrite(SegmentC, SegmentOn);
      digitalWrite(SegmentD, SegmentOff);
      digitalWrite(SegmentE, SegmentOff);
      digitalWrite(SegmentF, SegmentOff);
      digitalWrite(SegmentG, SegmentOff);
      segmentslit += 3;
      break;
    case 8:
      digitalWrite(SegmentA, SegmentOn);
      digitalWrite(SegmentB, SegmentOn);
      digitalWrite(SegmentC, SegmentOn);
      digitalWrite(SegmentD, SegmentOn);
      digitalWrite(SegmentE, SegmentOn);
      digitalWrite(SegmentF, SegmentOn);
      digitalWrite(SegmentG, SegmentOn);
      segmentslit += 7;
      break;
    case 9:
      digitalWrite(SegmentA, SegmentOn);
      digitalWrite(SegmentB, SegmentOn);
      digitalWrite(SegmentC, SegmentOn);
      digitalWrite(SegmentD, SegmentOff);
      digitalWrite(SegmentE, SegmentOff);
      digitalWrite(SegmentF, SegmentOn);
      digitalWrite(SegmentG, SegmentOn);
      segmentslit += 5;
      break;
    case 10:
      digitalWrite(SegmentA, SegmentOff);
      digitalWrite(SegmentB, SegmentOff);
      digitalWrite(SegmentC, SegmentOff);
      digitalWrite(SegmentD, SegmentOff);
      digitalWrite(SegmentE, SegmentOff);
      digitalWrite(SegmentF, SegmentOff);
      digitalWrite(SegmentG, SegmentOn);
      segmentslit += 1;
      break;
    case 99:
      digitalWrite(SegmentA, SegmentOff);
      digitalWrite(SegmentB, SegmentOff);
      digitalWrite(SegmentC, SegmentOff);
      digitalWrite(SegmentD, SegmentOff);
      digitalWrite(SegmentE, SegmentOff);
      digitalWrite(SegmentF, SegmentOff);
      digitalWrite(SegmentG, SegmentOff);
      break;
    default:
      allSegmentOff();
      break;
  }

  return segmentslit;
}


void selectDigit(byte digit) {

  SinclairData.lastSelectDigit = digit;

  allDigitOff();
  allDigitInput();

  switch (digit) {
    case 1:
      digitalWrite(Digit1, DigitOn);
      pinMode(Digit1, OUTPUT);
      break;
    case 2:
      digitalWrite(Digit2, DigitOn);
      pinMode(Digit2, OUTPUT);
      break;
    case 3:
      digitalWrite(Digit3, DigitOn);
      pinMode(Digit3, OUTPUT);
      break;
    case 4:
      digitalWrite(Digit4, DigitOn);
      pinMode(Digit4, OUTPUT);
      break;
    case 5:
      digitalWrite(Digit5, DigitOn);
      pinMode(Digit5, OUTPUT);
      break;
    case 6:
      digitalWrite(Digit6, DigitOn);
      pinMode(Digit6, OUTPUT);
      break;
    case 7:
      digitalWrite(Digit7, DigitOn);
      pinMode(Digit7, OUTPUT);
      break;
    case 8:
      digitalWrite(Digit8, DigitOn);
      pinMode(Digit8, OUTPUT);
      break;
    case 9:
      digitalWrite(Digit9, DigitOn);
      pinMode(Digit9, OUTPUT);
      break;
  }
}

const char KeysKN[10] = "156789234";
const char KeysKO[10] = "C/*^E0v+-";

byte readKey() {

  byte key = 0;

  //if CommonCathode
  //#define IsKeyPushed < 400
  //if CommonAnode
  //#define IsKeyPushed > 100

  //if (analogRead(7) IsKeyPushed)
  if (digitalRead(9))
  {
    SinclairData.keyStrobeKN = 1;
    key = KeysKN[SinclairData.lastSelectDigit - 1];
  }
  else
  {
    SinclairData.keyStrobeKN = 0;
  }

  //if (analogRead(6) IsKeyPushed)
  if (digitalRead(8))
  {
    SinclairData.keyStrobeKO = 1;
    key = KeysKO[SinclairData.lastSelectDigit - 1];
  }
  else
  {
    SinclairData.keyStrobeKO = 0;
  }

  // ensure C has priority
  if ((SinclairData.lastSelectDigit == 1) && (SinclairData.keyStrobeKO))
  {
    key = 'C';
  }

  /*
    Serial.print(lastSelectDigit);
    Serial.print(SinclairData.dActive);
    Serial.print(SinclairData.keyStrobeKN);
    Serial.print(SinclairData.keyStrobeKO);
    Serial.print(key);
    Serial.println("");
  */

  return key;
}

//since reakKey only reads the active column, this function sweeps through all columns and calls readKey
byte readKeys()
{
  byte k;
  byte key = 0;

  outputDigit(99);
  for (byte i = 1; i < 10; i++)
  {
    selectDigit(i);
    k = readKey();

    if (k)
    {
      key = k;
    }

  }

  return key;
}
