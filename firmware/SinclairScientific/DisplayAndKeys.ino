// Arduino Port of
//
// TI calculator simulator
// Ken Shirriff, http://righto.com/ti
// Based on patent US3934233
//
// The goal of this project is to run the following simulator: http://righto.com/sinclair
// on an arduino nano powered custom pcb resembling the original Sinclair Scientific Calculator
// @arduinoenigma 2018
//
// tedious but fast, most lines compile to 1 instruction.
// this whole file compiles to less than 1KB of code
//

//
// A0 = D14
// A1 = D15
// A2 = D16
// A3 = D17
// A4 = D18
// A5 = D19
// A6 = D20
// A7 = D21
//

#if defined(CommonCathode)
GPIO<BOARD::D6>  SegmentA;
GPIO<BOARD::D10> SegmentB;
GPIO<BOARD::D19> SegmentC;
GPIO<BOARD::D8>  SegmentD;
GPIO<BOARD::D5>  SegmentE;
GPIO<BOARD::D11> SegmentF;
GPIO<BOARD::D9>  SegmentG;
GPIO<BOARD::D18> SegmentDP;

GPIO<BOARD::D2>  Digit1;
GPIO<BOARD::D3>  Digit2;
GPIO<BOARD::D4>  Digit3;
GPIO<BOARD::D17> Digit4;
GPIO<BOARD::D16> Digit5;
GPIO<BOARD::D7>  Digit6;
GPIO<BOARD::D15> Digit7;
GPIO<BOARD::D14> Digit8;
GPIO<BOARD::D12> Digit9;

#define SegmentOn high
#define SegmentOff low
#define DigitOn low
#define DigitOff high
#define IsKeyPushed < 800
#endif

#if defined(CommonAnode)
GPIO<BOARD::D5>  SegmentA;
GPIO<BOARD::D8>  SegmentB;
GPIO<BOARD::D10> SegmentC;
GPIO<BOARD::D19> SegmentD;
GPIO<BOARD::D9>  SegmentE;
GPIO<BOARD::D6>  SegmentF;
GPIO<BOARD::D14> SegmentG;
GPIO<BOARD::D18> SegmentDP;

GPIO<BOARD::D2>  Digit1;
GPIO<BOARD::D3>  Digit2;
GPIO<BOARD::D4>  Digit3;
GPIO<BOARD::D17> Digit4;
GPIO<BOARD::D16> Digit5;
GPIO<BOARD::D7>  Digit6;
GPIO<BOARD::D15> Digit7;
GPIO<BOARD::D11> Digit8;
GPIO<BOARD::D12> Digit9;

#define SegmentOn low
#define SegmentOff high
#define DigitOn high
#define DigitOff low
#define IsKeyPushed > 100
#endif

#if defined(BoardV8)
GPIO<BOARD::D6>  SegmentA;
GPIO<BOARD::D10> SegmentB;
GPIO<BOARD::D19> SegmentC;
GPIO<BOARD::D8>  SegmentD;
GPIO<BOARD::D5>  SegmentE;
GPIO<BOARD::D11> SegmentF;
GPIO<BOARD::D9>  SegmentG;
GPIO<BOARD::D18> SegmentDP;

GPIO<BOARD::D2>  Digit1;
GPIO<BOARD::D3>  Digit2;
GPIO<BOARD::D4>  Digit3;
GPIO<BOARD::D17> Digit4;
GPIO<BOARD::D16> Digit5;
GPIO<BOARD::D7>  Digit6;
GPIO<BOARD::D15> Digit7;
GPIO<BOARD::D14> Digit8;
GPIO<BOARD::D12> Digit9;

#define SegmentOn low
#define SegmentOff high
#define DigitOn high
#define DigitOff low
#define IsKeyPushed > 100
#endif

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
  sbi(ADCSRA, ADPS2) ;
  cbi(ADCSRA, ADPS1) ;
  cbi(ADCSRA, ADPS0) ;
}

void allSegmentOutput() {
  SegmentA.output();
  SegmentB.output();
  SegmentC.output();
  SegmentD.output();
  SegmentE.output();
  SegmentF.output();
  SegmentG.output();
  SegmentDP.output();
}

void allSegmentInput() {
  SegmentA.input();
  SegmentB.input();
  SegmentC.input();
  SegmentD.input();
  SegmentE.input();
  SegmentF.input();
  SegmentG.input();
  SegmentDP.input();
}

void allDigitOutput() {
  Digit1.output();
  Digit2.output();
  Digit3.output();
  Digit4.output();
  Digit5.output();
  Digit6.output();
  Digit7.output();
  Digit8.output();
  Digit9.output();
}

void allDigitInput() {
  Digit1.input();
  Digit2.input();
  Digit3.input();
  Digit4.input();
  Digit5.input();
  Digit6.input();
  Digit7.input();
  Digit8.input();
  Digit9.input();
}

void allSegmentOff() {
  SegmentA.SegmentOff();
  SegmentB.SegmentOff();
  SegmentC.SegmentOff();
  SegmentD.SegmentOff();
  SegmentE.SegmentOff();
  SegmentF.SegmentOff();
  SegmentG.SegmentOff();
  SegmentDP.SegmentOff();
}

void allDigitOff() {
  Digit1.DigitOff();
  Digit2.DigitOff();
  Digit3.DigitOff();
  Digit4.DigitOff();
  Digit5.DigitOff();
  Digit6.DigitOff();
  Digit7.DigitOff();
  Digit8.DigitOff();
  Digit9.DigitOff();
}

byte outputDigit(signed char digit, bool decimalpoint = false) {

  byte segmentslit = 0;

  allDigitOff();

  if (decimalpoint)
  {
    //segmentslit++;
    SegmentDP.SegmentOn();
  }
  else
  {
    SegmentDP.SegmentOff();
  }

  switch (digit) {
    case 0:
      SegmentA.SegmentOn();
      SegmentB.SegmentOn();
      SegmentC.SegmentOn();
      SegmentD.SegmentOn();
      SegmentE.SegmentOn();
      SegmentF.SegmentOn();
      SegmentG.SegmentOff();
      segmentslit += 6;
      break;
    case 1:
      SegmentA.SegmentOff();
      SegmentB.SegmentOn();
      SegmentC.SegmentOn();
      SegmentD.SegmentOff();
      SegmentE.SegmentOff();
      SegmentF.SegmentOff();
      SegmentG.SegmentOff();
      segmentslit += 2;
      break;
    case 2:
      SegmentA.SegmentOn();
      SegmentB.SegmentOn();
      SegmentC.SegmentOff();
      SegmentD.SegmentOn();
      SegmentE.SegmentOn();
      SegmentF.SegmentOff();
      SegmentG.SegmentOn();
      segmentslit += 5;
      break;
    case 3:
      SegmentA.SegmentOn();
      SegmentB.SegmentOn();
      SegmentC.SegmentOn();
      SegmentD.SegmentOn();
      SegmentE.SegmentOff();
      SegmentF.SegmentOff();
      SegmentG.SegmentOn();
      segmentslit += 5;
      break;
    case 4:
      SegmentA.SegmentOff();
      SegmentB.SegmentOn();
      SegmentC.SegmentOn();
      SegmentD.SegmentOff();
      SegmentE.SegmentOff();
      SegmentF.SegmentOn();
      SegmentG.SegmentOn();
      segmentslit += 4;
      break;
    case 5:
      SegmentA.SegmentOn();
      SegmentB.SegmentOff();
      SegmentC.SegmentOn();
      SegmentD.SegmentOn();
      SegmentE.SegmentOff();
      SegmentF.SegmentOn();
      SegmentG.SegmentOn();
      segmentslit += 5;
      break;
    case 6:
      SegmentA.SegmentOn();
      SegmentB.SegmentOff();
      SegmentC.SegmentOn();
      SegmentD.SegmentOn();
      SegmentE.SegmentOn();
      SegmentF.SegmentOn();
      SegmentG.SegmentOn();
      segmentslit += 6;
      break;
    case 7:
      SegmentA.SegmentOn();
      SegmentB.SegmentOn();
      SegmentC.SegmentOn();
      SegmentD.SegmentOff();
      SegmentE.SegmentOff();
      SegmentF.SegmentOff();
      SegmentG.SegmentOff();
      segmentslit += 3;
      break;
    case 8:
      SegmentA.SegmentOn();
      SegmentB.SegmentOn();
      SegmentC.SegmentOn();
      SegmentD.SegmentOn();
      SegmentE.SegmentOn();
      SegmentF.SegmentOn();
      SegmentG.SegmentOn();
      segmentslit += 7;
      break;
    case 9:
      SegmentA.SegmentOn();
      SegmentB.SegmentOn();
      SegmentC.SegmentOn();
      SegmentD.SegmentOff();
      SegmentE.SegmentOff();
      SegmentF.SegmentOn();
      SegmentG.SegmentOn();
      segmentslit += 5;
      break;
    case 10:
      SegmentA.SegmentOff();
      SegmentB.SegmentOff();
      SegmentC.SegmentOff();
      SegmentD.SegmentOff();
      SegmentE.SegmentOff();
      SegmentF.SegmentOff();
      SegmentG.SegmentOn();
      segmentslit += 1;
      break;
    case 99:
      SegmentA.SegmentOff();
      SegmentB.SegmentOff();
      SegmentC.SegmentOff();
      SegmentD.SegmentOff();
      SegmentE.SegmentOff();
      SegmentF.SegmentOff();
      SegmentG.SegmentOff();
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
      Digit1.DigitOn();
      Digit1.output();
      break;
    case 2:
      Digit2.DigitOn();
      Digit2.output();
      break;
    case 3:
      Digit3.DigitOn();
      Digit3.output();
      break;
    case 4:
      Digit4.DigitOn();
      Digit4.output();
      break;
    case 5:
      Digit5.DigitOn();
      Digit5.output();
      break;
    case 6:
      Digit6.DigitOn();
      Digit6.output();
      break;
    case 7:
      Digit7.DigitOn();
      Digit7.output();
      break;
    case 8:
      Digit8.DigitOn();
      Digit8.output();
      break;
    case 9:
      Digit9.DigitOn();
      Digit9.output();
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

  if (analogRead(7) IsKeyPushed)
  {
    SinclairData.keyStrobeKN = 1;
    key = KeysKN[SinclairData.lastSelectDigit - 1];
  }
  else
  {
    SinclairData.keyStrobeKN = 0;
  }

  if (analogRead(6) IsKeyPushed)
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
