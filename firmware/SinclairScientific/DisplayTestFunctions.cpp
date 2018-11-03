
#include "DisplayTestFunctions.h"
#include "DisplayAndKeys.h"
#include "SinclairScientific.h"

#if defined(AlignRight)
#define LetterS Digit2
#define LetterI Digit3
#define LetterN Digit4
#define LetterC Digit5
#define LetterL Digit6
#define LetterA Digit7
#define LetterII Digit8
#define LetterR Digit9
#endif

#if defined(AlignLeft)
#define LetterS Digit1
#define LetterI Digit2
#define LetterN Digit3
#define LetterC Digit4
#define LetterL Digit5
#define LetterA Digit6
#define LetterII Digit7
#define LetterR Digit8
#endif

void Spinners() {

  byte A[9];
  byte d = 0;

  pinMode(SegmentA, OUTPUT);
  pinMode(SegmentB, OUTPUT);
  pinMode(SegmentC, OUTPUT);
  pinMode(SegmentD, OUTPUT);
  pinMode(SegmentE, OUTPUT);
  pinMode(SegmentF, OUTPUT);
  pinMode(SegmentG, OUTPUT);
  pinMode(SegmentDP, OUTPUT);

  pinMode(Digit1, OUTPUT);
  pinMode(Digit2, OUTPUT);
  pinMode(Digit3, OUTPUT);
  pinMode(Digit4, OUTPUT);
  pinMode(Digit5, OUTPUT);
  pinMode(Digit6, OUTPUT);
  pinMode(Digit7, OUTPUT);
  pinMode(Digit8, OUTPUT);
  pinMode(Digit9, OUTPUT);

  for (byte i = 0; i < 9; i++)
  {
    A[i] = d++;
    if (d == 6)
    {
      d = 0;
    }
  }

  for (byte i = 0; i < 250; i++)
  {
    for (byte j = 0; j < 22; j++)
    {
      for (byte k = 0; k < 9; k++)
      {
        byte d = A[k];

        digitalWrite(SegmentA, SegmentOff);
        digitalWrite(SegmentB, SegmentOff);
        digitalWrite(SegmentC, SegmentOff);
        digitalWrite(SegmentD, SegmentOff);
        digitalWrite(SegmentE, SegmentOff);
        digitalWrite(SegmentF, SegmentOff);
        digitalWrite(SegmentG, SegmentOff);
        digitalWrite(SegmentDP, SegmentOff);

        switch (d)
        {
          case 0:
            digitalWrite(SegmentA, SegmentOn);
            break;
          case 1:
            digitalWrite(SegmentB, SegmentOn);
            break;
          case 2:
            digitalWrite(SegmentC, SegmentOn);
            break;
          case 3:
            digitalWrite(SegmentD, SegmentOn);
            break;
          case 4:
            digitalWrite(SegmentE, SegmentOn);
            break;
          case 5:
            digitalWrite(SegmentF, SegmentOn);
            break;
        }

        digitalWrite(Digit1, DigitOff);
        digitalWrite(Digit2, DigitOff);
        digitalWrite(Digit3, DigitOff);
        digitalWrite(Digit4, DigitOff);
        digitalWrite(Digit5, DigitOff);
        digitalWrite(Digit6, DigitOff);
        digitalWrite(Digit7, DigitOff);
        digitalWrite(Digit8, DigitOff);
        digitalWrite(Digit9, DigitOff);

        switch (k)
        {
          case 0:
            //digitalWrite(Digit1, DigitOn);
            break;
          case 1:
            digitalWrite(Digit2, DigitOn);
            break;
          case 2:
            digitalWrite(Digit3, DigitOn);
            break;
          case 3:
            digitalWrite(Digit4, DigitOn);
            break;
          case 4:
            digitalWrite(Digit5, DigitOn);
            break;
          case 5:
            digitalWrite(Digit6, DigitOn);
            break;
          case 6:
            digitalWrite(Digit7, DigitOn);
            break;
          case 7:
            digitalWrite(Digit8, DigitOn);
            break;
          case 8:
            digitalWrite(Digit9, DigitOn);
            break;
        }
        delayMicroseconds(320);

        //if (analogRead(6) IsKeyPushed)
        if (digitalRead(8))
        {
          if (k == 0)
          {
            goto exit;
          }
        }
      }
    }

    for (byte k = 0; k < 9; k++)
    {
      byte d = A[k];
      d++;
      if (d == 6)
      {
        d = 0;
      }
      A[k] = d;
    }
  }

exit:

  digitalWrite(SegmentA, SegmentOff);
  digitalWrite(SegmentB, SegmentOff);
  digitalWrite(SegmentC, SegmentOff);
  digitalWrite(SegmentD, SegmentOff);
  digitalWrite(SegmentE, SegmentOff);
  digitalWrite(SegmentF, SegmentOff);
  digitalWrite(SegmentG, SegmentOff);
  digitalWrite(SegmentDP, SegmentOff);

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

void CasioLogo() {

  //uncomment to disable
  //return;

  int showtime = 1;

  for (byte t = 0; t < 14; t++) {
    if (t > 2)
    {
      showtime++;
    }
    if (t > 4)
    {
      showtime++;
    }
    for (int s = 0; s < 400; s++) {
      delayMicroseconds(120); // this delay is more important than the hyperoptimized logic below. must have off time.
      for (byte digit = 0; digit < 9; digit++) {
        switch (digit) {
          case 0:           // C  (comment out pins that do not change, low is on, high is off)
            digitalWrite(SegmentA, SegmentOn);
            digitalWrite(SegmentB, SegmentOff);
            digitalWrite(SegmentC, SegmentOff);
            digitalWrite(SegmentD, SegmentOn);
            digitalWrite(SegmentE, SegmentOn);
            digitalWrite(SegmentF, SegmentOn);
            digitalWrite(SegmentG, SegmentOff);
            digitalWrite(LetterS, DigitOn);
            pinMode(LetterS, OUTPUT);
            if (t > 0) {
              delayMicroseconds(showtime);
            }
            digitalWrite(LetterS, DigitOff);
            pinMode(LetterS, INPUT);
            break;
          case 1:           // A
            digitalWrite(SegmentA, SegmentOn);
            digitalWrite(SegmentB, SegmentOn);
            digitalWrite(SegmentC, SegmentOn);
            digitalWrite(SegmentD, SegmentOff);
            digitalWrite(SegmentE, SegmentOn);
            digitalWrite(SegmentF, SegmentOn);
            digitalWrite(SegmentG, SegmentOn);
            digitalWrite(LetterI, DigitOn);
            pinMode(LetterI, OUTPUT);
            if (t > 0) {
              delayMicroseconds(showtime);
            }
            digitalWrite(LetterI, DigitOff);
            pinMode(LetterI, INPUT);
            break;
          case 2:           // S
            digitalWrite(SegmentA, SegmentOn);
            digitalWrite(SegmentB, SegmentOff);
            digitalWrite(SegmentC, SegmentOn);
            digitalWrite(SegmentD, SegmentOn);
            digitalWrite(SegmentE, SegmentOff);
            digitalWrite(SegmentF, SegmentOn);
            digitalWrite(SegmentG, SegmentOn);
            digitalWrite(LetterN, DigitOn);
            pinMode(LetterN, OUTPUT);
            if (t > 0) {
              delayMicroseconds(showtime);
            }
            digitalWrite(LetterN, DigitOff);
            pinMode(LetterN, INPUT);
            break;
          case 3:           // I
            digitalWrite(SegmentA, SegmentOff);
            digitalWrite(SegmentB, SegmentOn);
            digitalWrite(SegmentC, SegmentOn);
            digitalWrite(SegmentD, SegmentOff);
            digitalWrite(SegmentE, SegmentOff);
            digitalWrite(SegmentF, SegmentOff);
            digitalWrite(SegmentG, SegmentOff);
            digitalWrite(LetterC, DigitOn);
            pinMode(LetterC, OUTPUT);
            if (t > 0) {
              delayMicroseconds(showtime);
            }
            digitalWrite(LetterC, DigitOff);
            pinMode(LetterC, INPUT);
            break;
          case 4:           // O
            digitalWrite(SegmentA, SegmentOn);
            digitalWrite(SegmentB, SegmentOn);
            digitalWrite(SegmentC, SegmentOn);
            digitalWrite(SegmentD, SegmentOn);
            digitalWrite(SegmentE, SegmentOn);
            digitalWrite(SegmentF, SegmentOn);
            digitalWrite(SegmentG, SegmentOff);
            digitalWrite(LetterL, DigitOn);
            pinMode(LetterL, OUTPUT);
            if (t > 0) {
              delayMicroseconds(showtime);
            }
            digitalWrite(LetterL, DigitOff);
            pinMode(LetterL, INPUT);
            break;
        }
      }
    }
  }

exitsinclair:
  allSegmentOff();
  allDigitOff();

}

void SinclairLogo() {

  //uncomment to disable
  //return;

  int showtime = 1;

  for (byte t = 0; t < 14; t++) {
    if (t > 2)
    {
      showtime++;
    }
    if (t > 4)
    {
      showtime++;
    }
    for (int s = 0; s < 400; s++) {
      delayMicroseconds(120); // this delay is more important than the hyperoptimized logic below. must have off time.
      for (byte digit = 0; digit < 9; digit++) {
        switch (digit) {
          case 0:           // i  (comment out pins that do not change, low is on, high is off)
            digitalWrite(SegmentA, SegmentOff);
            digitalWrite(SegmentB, SegmentOff);
            //digitalWrite(SegmentC, SegmentOn);
            digitalWrite(SegmentD, SegmentOff);
            digitalWrite(SegmentE, SegmentOff);
            //digitalWrite(SegmentF, SegmentOff);
            digitalWrite(SegmentG, SegmentOff);
            digitalWrite(LetterI, DigitOn);
            pinMode(LetterI, OUTPUT);
            if (t > 0) {
              delayMicroseconds(showtime);
            }
            digitalWrite(LetterI, DigitOff);
            pinMode(LetterI, INPUT);
            break;
          case 1:           // i
            //digitalWrite(SegmentA, SegmentOff);
            //digitalWrite(SegmentB, SegmentOff);
            //digitalWrite(SegmentC, SegmentOn);
            //digitalWrite(SegmentD, SegmentOff);
            //digitalWrite(SegmentE, SegmentOff);
            //digitalWrite(SegmentF, SegmentOff);
            //digitalWrite(SegmentG, SegmentOff);
            digitalWrite(LetterII, DigitOn);
            pinMode(LetterII, OUTPUT);
            if (t > 0) {
              delayMicroseconds(showtime);
            }
            digitalWrite(LetterII, DigitOff);
            pinMode(LetterII, INPUT);
            break;
          case 2:           // l
            //digitalWrite(SegmentA, SegmentOff);
            digitalWrite(SegmentB, SegmentOn);
            //digitalWrite(SegmentC, SegmentOn);
            //digitalWrite(SegmentD, SegmentOff);
            //digitalWrite(SegmentE, SegmentOff);
            //digitalWrite(SegmentF, SegmentOff);
            //digitalWrite(SegmentG, SegmentOff);
            digitalWrite(LetterL, DigitOn);
            pinMode(LetterL, OUTPUT);
            if (t > 0) {
              delayMicroseconds(showtime);
            }
            digitalWrite(LetterL, DigitOff);
            pinMode(LetterL, INPUT);
            break;
          case 3:           // n
            digitalWrite(SegmentA, SegmentOn);
            //digitalWrite(SegmentB, SegmentOn);
            //digitalWrite(SegmentC, SegmentOn);
            //digitalWrite(SegmentD, SegmentOff);
            digitalWrite(SegmentE, SegmentOn);
            digitalWrite(SegmentF, SegmentOn);
            //digitalWrite(SegmentG, SegmentOff);
            digitalWrite(LetterN, DigitOn);
            pinMode(LetterN, OUTPUT);
            if (t > 0) {
              delayMicroseconds(showtime);
            }
            digitalWrite(LetterN, DigitOff);
            pinMode(LetterN, INPUT);
            break;
          case 4:           // r
            //digitalWrite(SegmentA, SegmentOn);
            digitalWrite(SegmentB, SegmentOff);
            digitalWrite(SegmentC, SegmentOff);
            //digitalWrite(SegmentD, SegmentOff);
            //digitalWrite(SegmentE, SegmentOn);
            //digitalWrite(SegmentF, SegmentOn);
            //digitalWrite(SegmentG, SegmentOff);
            digitalWrite(LetterR, DigitOn);
            pinMode(LetterR, OUTPUT);
            if (t > 0) {
              delayMicroseconds(showtime);
            }
            digitalWrite(LetterR, DigitOff);
            pinMode(LetterR, INPUT);
            break;
          case 5:           // c
            //digitalWrite(SegmentA, SegmentOn);
            //digitalWrite(SegmentB, SegmentOff);
            //digitalWrite(SegmentC, SegmentOff);
            digitalWrite(SegmentD, SegmentOn);
            //digitalWrite(SegmentE, SegmentOn);
            //digitalWrite(SegmentF, SegmentOn);
            //digitalWrite(SegmentG, SegmentOff);
            digitalWrite(LetterC, DigitOn);
            pinMode(LetterC, OUTPUT);
            if (t > 0) {
              delayMicroseconds(showtime);
            }
            digitalWrite(LetterC, DigitOff);
            pinMode(LetterC, INPUT);
            break;
          case 6:            // S
            //digitalWrite(SegmentA, SegmentOn);  //low is on
            //digitalWrite(SegmentB, SegmentOff);
            digitalWrite(SegmentC, SegmentOn);
            //digitalWrite(SegmentD, SegmentOn);
            digitalWrite(SegmentE, SegmentOff);
            //digitalWrite(SegmentF, SegmentOn);
            digitalWrite(SegmentG, SegmentOn);
            digitalWrite(LetterS, DigitOn);
            pinMode(LetterS, OUTPUT);
            if (t > 0) {
              delayMicroseconds(showtime);
            }
            digitalWrite(LetterS, DigitOff);
            pinMode(LetterS, INPUT);
            break;
          case 7:           // a
            //digitalWrite(SegmentA, SegmentOn);
            digitalWrite(SegmentB, SegmentOn);
            //digitalWrite(SegmentC, SegmentOn);
            //digitalWrite(SegmentD, SegmentOn);
            digitalWrite(SegmentE, SegmentOn);
            digitalWrite(SegmentF, SegmentOff);
            //digitalWrite(SegmentG, SegmentOn);
            digitalWrite(LetterA, DigitOn);
            pinMode(LetterA, OUTPUT);
            if (t > 0) {
              delayMicroseconds(showtime);
            }
            digitalWrite(LetterA, DigitOff);
            pinMode(LetterA, INPUT);
            break;
        }
      }
    }
  }

exitsinclair:
  allSegmentOff();
  allDigitOff();

}


void displaySelfTest(bool longtest) {

  //uncomment to disable
  //return;

  char c = 0;

  //kitt stuff
  byte pos = 0;
  byte p1 = 0;
  byte p2 = 0;
  char sign = 0;

  bool kitt = false;
  bool spinner = false;

  // show 8.8.8.8.8.8.8.8.8.
  for (int t = 0; t < 400; t++) {
    for (byte j = 0; j < 9; j++) {
      outputDigit(8, true);
      selectDigit(j + 1);
      delayMicroseconds(350);
      allSegmentOff();
      c = readKey();
      if (c == '8') {
        longtest = true;
      }
      if ((longtest == true ) && (c == '2')) {
        kitt = true;
      }
      if ((longtest == true ) && (c == '3')) {
        spinner = true;
      }
      if (c == 'C') {
        goto exitfn;
      }
      //delay(2);
    }
  }

  if (kitt && !spinner) {
    goto kitt;
  }

  if (!kitt && spinner) {
    Spinners();
    goto exitfn;
  }


  if (!longtest) {
    goto exitfn;
  }

  // cycle through 0..9 - on all digits at the same time
  for (byte i = 0; i < 12; i++) {
    for (int t = 0; t < 300; t++) {
      for (byte j = 0; j < 9; j++) {
        outputDigit((i != 11) ? i : 99, (i == 11));
        selectDigit(j + 1);
        delayMicroseconds(350);
        allSegmentOff();
        if (readKey() == 'C') {
          goto exitfn;
        }
        //delay(2);
      }
    }
  }

  // show 12345678
  for (int t = 0; t < 300; t++) {
    for (byte j = 0; j < 9; j++) {
      outputDigit(j, false);
      selectDigit(j + 1);
      delayMicroseconds(350);
      allSegmentOff();
      if (readKey() == 'C') {
        goto exitfn;
      }
      //delay(2);
    }
  }

  // move the dot from left to right on 12345678
  for (byte i = 0; i < 9; i++) {
    for (int t = 0; t < 300; t++) {
      for (byte j = 0; j < 9; j++) {
        outputDigit(j, i == j);
        selectDigit(j + 1);
        delayMicroseconds(350);
        allSegmentOff();
        if (readKey() == 'C') {
          goto exitfn;
        }
        //delay(2);
      }
    }
  }

  // move dot from right to left on blank display
  for (byte j = 9; j > 0; j--) {
    for (int t = 0; t < 300; t++) {
      for (byte i = 0; i < 9; i++) {
        outputDigit(99, i == (j - 1));
        selectDigit(i + 1);
        delayMicroseconds(350);
        allSegmentOff();
        if (readKey() == 'C') {
          goto exitfn;
        }
        //delay(2);
      }
    }
  }

  // cycle through 0..9 - on each digit individually
  for (byte j = 0; j < 9; j++) {
    for (byte i = 0; i < 12; i++) {
      for (byte t = 0; t < 125; t++) {
        for (byte k = 0; k < 9; k++) {
          outputDigit( ((k == j) && (i != 11)) ? i : 99, ((k == j) && (i == 11)));
          selectDigit(k + 1);
          delayMicroseconds(350);
          allSegmentOff();
          if (readKey() == 'C') {
            goto exitfn;
          }
          //delay(2);
        }
      }
    }
  }

  goto exitfn;

kitt:

  for (byte i = 0; i < 249; i++)
  {
    p2 = p1;
    p1 = pos;
    pos += sign;

    if (pos == 0) {
      sign = 1;
    }

    if (pos == 8) {
      sign = -1;
    }

    for (byte t = 0; t < 25; t++) {
      for (byte j = 0; j < 9; j++) {
        c = readKey();
        if (c == 'C') {
          goto exitfn;
        }
        outputDigit(10, false);
        selectDigit(j + 1);
        if (j == pos)
        {
          delayMicroseconds(350);
        } else if (j == p1)
        {
          delayMicroseconds(200);
        } else if (j == p2)
        {
          delayMicroseconds(100);
        } else
        {
          delayMicroseconds(10);
        }
        allSegmentOff();
        delayMicroseconds(150);
      }
    }
  }

exitfn:
  allSegmentOff();
  allDigitOff();

}
