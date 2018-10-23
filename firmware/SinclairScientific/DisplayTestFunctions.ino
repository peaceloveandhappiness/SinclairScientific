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
// The following functions are display related and only meant to appear before the calculator code starts executing
// disable for authenticity
//

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

  SegmentA.output();
  SegmentB.output();
  SegmentC.output();
  SegmentD.output();
  SegmentE.output();
  SegmentF.output();
  SegmentG.output();
  SegmentDP.output();

  Digit1.output();
  Digit2.output();
  Digit3.output();
  Digit4.output();
  Digit5.output();
  Digit6.output();
  Digit7.output();
  Digit8.output();
  Digit9.output();

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

        SegmentA.SegmentOff();
        SegmentB.SegmentOff();
        SegmentC.SegmentOff();
        SegmentD.SegmentOff();
        SegmentE.SegmentOff();
        SegmentF.SegmentOff();
        SegmentG.SegmentOff();
        SegmentDP.SegmentOff();

        switch (d)
        {
          case 0:
            SegmentA.SegmentOn();
            break;
          case 1:
            SegmentB.SegmentOn();
            break;
          case 2:
            SegmentC.SegmentOn();
            break;
          case 3:
            SegmentD.SegmentOn();
            break;
          case 4:
            SegmentE.SegmentOn();
            break;
          case 5:
            SegmentF.SegmentOn();
            break;
        }

        Digit1.DigitOff();
        Digit2.DigitOff();
        Digit3.DigitOff();
        Digit4.DigitOff();
        Digit5.DigitOff();
        Digit6.DigitOff();
        Digit7.DigitOff();
        Digit8.DigitOff();
        Digit9.DigitOff();

        switch (k)
        {
          case 0:
            //Digit1.DigitOn();
            break;
          case 1:
            Digit2.DigitOn();
            break;
          case 2:
            Digit3.DigitOn();
            break;
          case 3:
            Digit4.DigitOn();
            break;
          case 4:
            Digit5.DigitOn();
            break;
          case 5:
            Digit6.DigitOn();
            break;
          case 6:
            Digit7.DigitOn();
            break;
          case 7:
            Digit8.DigitOn();
            break;
          case 8:
            Digit9.DigitOn();
            break;
        }
        delayMicroseconds(320);

        if (analogRead(6) IsKeyPushed)
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

  SegmentA.SegmentOff();
  SegmentB.SegmentOff();
  SegmentC.SegmentOff();
  SegmentD.SegmentOff();
  SegmentE.SegmentOff();
  SegmentF.SegmentOff();
  SegmentG.SegmentOff();
  SegmentDP.SegmentOff();

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
            SegmentA.SegmentOn();
            SegmentB.SegmentOff();
            SegmentC.SegmentOff();
            SegmentD.SegmentOn();
            SegmentE.SegmentOn();
            SegmentF.SegmentOn();
            SegmentG.SegmentOff();
            LetterS.DigitOn();
            LetterS.output();
            if (t > 0) {
              delayMicroseconds(showtime);
            }
            LetterS.DigitOff();
            LetterS.input();
            break;
          case 1:           // A
            SegmentA.SegmentOn();
            SegmentB.SegmentOn();
            SegmentC.SegmentOn();
            SegmentD.SegmentOff();
            SegmentE.SegmentOn();
            SegmentF.SegmentOn();
            SegmentG.SegmentOn();
            LetterI.DigitOn();
            LetterI.output();
            if (t > 0) {
              delayMicroseconds(showtime);
            }
            LetterI.DigitOff();
            LetterI.input();
            break;
          case 2:           // S
            SegmentA.SegmentOn();
            SegmentB.SegmentOff();
            SegmentC.SegmentOn();
            SegmentD.SegmentOn();
            SegmentE.SegmentOff();
            SegmentF.SegmentOn();
            SegmentG.SegmentOn();
            LetterN.DigitOn();
            LetterN.output();
            if (t > 0) {
              delayMicroseconds(showtime);
            }
            LetterN.DigitOff();
            LetterN.input();
            break;
          case 3:           // I
            SegmentA.SegmentOff();
            SegmentB.SegmentOn();
            SegmentC.SegmentOn();
            SegmentD.SegmentOff();
            SegmentE.SegmentOff();
            SegmentF.SegmentOff();
            SegmentG.SegmentOff();
            LetterC.DigitOn();
            LetterC.output();
            if (t > 0) {
              delayMicroseconds(showtime);
            }
            LetterC.DigitOff();
            LetterC.input();
            break;
          case 4:           // O
            SegmentA.SegmentOn();
            SegmentB.SegmentOn();
            SegmentC.SegmentOn();
            SegmentD.SegmentOn();
            SegmentE.SegmentOn();
            SegmentF.SegmentOn();
            SegmentG.SegmentOff();
            LetterL.DigitOn();
            LetterL.output();
            if (t > 0) {
              delayMicroseconds(showtime);
            }
            LetterL.DigitOff();
            LetterL.input();
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
            SegmentA.SegmentOff();
            SegmentB.SegmentOff();
            //SegmentC.SegmentOn();
            SegmentD.SegmentOff();
            SegmentE.SegmentOff();
            //SegmentF.SegmentOff();
            SegmentG.SegmentOff();
            LetterI.DigitOn();
            LetterI.output();
            if (t > 0) {
              delayMicroseconds(showtime);
            }
            LetterI.DigitOff();
            LetterI.input();
            break;
          case 1:           // i
            //SegmentA.SegmentOff();
            //SegmentB.SegmentOff();
            //SegmentC.SegmentOn();
            //SegmentD.SegmentOff();
            //SegmentE.SegmentOff();
            //SegmentF.SegmentOff();
            //SegmentG.SegmentOff();
            LetterII.DigitOn();
            LetterII.output();
            if (t > 0) {
              delayMicroseconds(showtime);
            }
            LetterII.DigitOff();
            LetterII.input();
            break;
          case 2:           // l
            //SegmentA.SegmentOff();
            SegmentB.SegmentOn();
            //SegmentC.SegmentOn();
            //SegmentD.SegmentOff();
            //SegmentE.SegmentOff();
            //SegmentF.SegmentOff();
            //SegmentG.SegmentOff();
            LetterL.DigitOn();
            LetterL.output();
            if (t > 0) {
              delayMicroseconds(showtime);
            }
            LetterL.DigitOff();
            LetterL.input();
            break;
          case 3:           // n
            SegmentA.SegmentOn();
            //SegmentB.SegmentOn();
            //SegmentC.SegmentOn();
            //SegmentD.SegmentOff();
            SegmentE.SegmentOn();
            SegmentF.SegmentOn();
            //SegmentG.SegmentOff();
            LetterN.DigitOn();
            LetterN.output();
            if (t > 0) {
              delayMicroseconds(showtime);
            }
            LetterN.DigitOff();
            LetterN.input();
            break;
          case 4:           // r
            //SegmentA.SegmentOn();
            SegmentB.SegmentOff();
            SegmentC.SegmentOff();
            //SegmentD.SegmentOff();
            //SegmentE.SegmentOn();
            //SegmentF.SegmentOn();
            //SegmentG.SegmentOff();
            LetterR.DigitOn();
            LetterR.output();
            if (t > 0) {
              delayMicroseconds(showtime);
            }
            LetterR.DigitOff();
            LetterR.input();
            break;
          case 5:           // c
            //SegmentA.SegmentOn();
            //SegmentB.SegmentOff();
            //SegmentC.SegmentOff();
            SegmentD.SegmentOn();
            //SegmentE.SegmentOn();
            //SegmentF.SegmentOn();
            //SegmentG.SegmentOff();
            LetterC.DigitOn();
            LetterC.output();
            if (t > 0) {
              delayMicroseconds(showtime);
            }
            LetterC.DigitOff();
            LetterC.input();
            break;
          case 6:            // S
            //SegmentA.SegmentOn();  //low is on
            //SegmentB.SegmentOff();
            SegmentC.SegmentOn();
            //SegmentD.SegmentOn();
            SegmentE.SegmentOff();
            //SegmentF.SegmentOn();
            SegmentG.SegmentOn();
            LetterS.DigitOn();
            LetterS.output();
            if (t > 0) {
              delayMicroseconds(showtime);
            }
            LetterS.DigitOff();
            LetterS.input();
            break;
          case 7:           // a
            //SegmentA.SegmentOn();
            SegmentB.SegmentOn();
            //SegmentC.SegmentOn();
            //SegmentD.SegmentOn();
            SegmentE.SegmentOn();
            SegmentF.SegmentOff();
            //SegmentG.SegmentOn();
            LetterA.DigitOn();
            LetterA.output();
            if (t > 0) {
              delayMicroseconds(showtime);
            }
            LetterA.DigitOff();
            LetterA.input();
            break;
        }
      }
    }
  }

exitsinclair:
  allSegmentOff();
  allDigitOff();

}


void displaySelfTest(bool longtest = false) {

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
