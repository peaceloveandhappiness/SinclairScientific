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
// To test the up/down buttons press:
// C up X up / up + up - 5.4105-01
// C dn X dn / dn + dn - 4.4200-01
//
// Sinclair Scientific Glitches implemented:
// dot stays on when display turns off, dot gets brighter
// pressing 0 makes dot brighter, other keys not so much
// pressing a key glitches the number displayed,
// pressing 7 glitches more numbers than pressing 1
// pressing C dims the display
// 1 is brighter than 0
// - in mantissa is brighter
//
// Glitches not implemented:
// ???
//
// Other Features:
// press 0 when powering up to display short display self test.
// press 8 when short display self test is showing for longer self test, press C to exit.
// press 1 when powering up for slower than normal speed, display stays lit while computing a result.
// press 2 when powering up for normal speed with display on.
// press 3 when powering up for faster speed with display on.
// press 9 when powering up to toggle showing Sinclair logo at bootup
//
// to enter KITT mode ???
//
// Notes:
// Adjusted refresh delay in updateDisplay() so execution time of ArcCos 0.0001 matches real hardware.
// loop() function get called every 340uS for an effective clock speed of 2.9kHz
//
//

#include "SinclairScientific.h"
#include "DisplayAndKeys.h"

#include <Arduino.h>
//#include <EEPROM.h>

#define _steptime 341

//modern LED PCB v5 is Common Anode
//bubble LED PCB v7 is Common Cathode
//recessed modern LED PCB v8 is Common Anode
#define CommonAnode
//#define CommonCathode
//#define BoardV8

//Alignment for SINCLAIR logo
#define AlignRight
//#define AlignLeft

#if defined(CommonAnode)
// The EnableDissassembly option has not been tested with the Common Chathode Display
// and could damage it by taking too long to execute the step function, keeping the display on for too long
//#define EnableDisassembly
#endif

extern void step();

extern void SinclairLogo();
extern void displaySelfTest(bool longtest = false);
extern void displayRigTest();


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
//#define DK 1


SinclairData_t SinclairData;

const byte DisplayOrder[9] = {1, 7, 8, 9, 2, 3, 4, 5, 6};

void updateDisplay()
{
  byte displayon = SinclairData.display + SinclairData.showwork;

  bool dp = false; // needed for logic below, keep initialized to false

  byte showdigit;
  byte digitoff = 99;
  byte digiton = 99;
  byte digitpos = 0;

  digitpos = DisplayOrder[SinclairData.dActive - 1];

  switch (digitpos)
  {
    case 1:
      digiton = (SinclairData.a[0] == 0) ? 99 : 10;
      break;

    case 2:
      digiton = SinclairData.a[4];
      break;

    case 3:
      digiton = SinclairData.a[5];
      break;

    case 4:
      digiton = SinclairData.a[6];
      break;

    case 5:
      digiton = SinclairData.a[7];
      break;

    case 6:
      digiton = SinclairData.a[8];
      break;

    case 7:
      digiton = (SinclairData.a[1] == 0) ? 99 : 10;
      break;

    case 8:
      digiton = SinclairData.a[2];
      break;

    case 9:
      digiton = SinclairData.a[3];
      break;
  }

  // SINCLAIR behavior: turn decimal point on automatically at fixed position
  // dot stays on whether the rest of the display is on or off
  // this logic attempts to make optimizer do variable copy on dp1 = dp2 and dp1 = dp below.
  if (digitpos == 2) {
    dp = true;
  }
  else
  {
    dp = false;
  }

  // attempt to have this block take same time to run whether a digit or blank is displayed
  if (displayon) {
    showdigit = digiton;
  }
  else {
    showdigit = digitoff;

    // SINCLAIR behavior: dot goes brighter when display is off.
    // only needed in common anode hardware
#if defined(CommonAnode)
    //(control brightness of dot, 2=brighter .. 8=dimmer)
    if (digitpos > 5) // set to greater than 2 to allow column 1 to be read for C and column 2 to display dot
    {
      digitpos = 2;
      dp = true;
    }
#endif

  }

  SinclairData.segmentslit = outputDigit(showdigit, dp);
  selectDigit(digitpos);

  // adjust case 1 for the following:
  // Tan 8 takes 11.6 seconds
  // Sin 1 takes about 7.3 seconds.
  // Arccos .2 takes about 13.6 seconds
  // Arctan 1 takes about 6.6 seconds
  // Arccos of a very small value (e.g. 0.0001) goes into an almost-infinite loop and takes 1 minute, 38 seconds to complete

}

void setup()
{
  // put your setup code here, to run once:

  Serial.begin(2000000);

  // makes it easier to see if an arduino is programmed or not
  Serial.print(F("SINCLAIR v7 092318"));
#if defined(CommonAnode)
  Serial.print(F(" -Common Anode"));
#endif
#if defined(CommonCathode)
  Serial.print(F(" -Common Cathode"));
#endif
#if defined(BoardV8)
  Serial.print(F(" -Common Anode V8"));
#endif
#if defined(AlignRight)
  Serial.print(F(" -Aligned Right"));
#endif
#if defined(AlignLeft)
  Serial.print(F(" -Aligned Left"));
#endif
  Serial.println(F(""));

  setupFastADC();

  allSegmentOff();
  allSegmentOutput();

  allDigitOff();
  allDigitOutput();

  int actual;
  boolean failure = false;

  byte showlogo = true; //EEPROM.read(1);
  if (showlogo != 0) {
    showlogo = 255;
    SinclairLogo();
    //CasioLogo();
  }
  showlogo ^= 255;

  char key = readKeys();
  SinclairData.showwork = 1;  //takes effect only on 1,2,3

  switch (key)
  {
    case '0':
      displaySelfTest();
      SinclairData.speed = 1;
      SinclairData.showwork = 0; //normal speed, display off during calculations
      break;
    case '1':
      SinclairData.speed = 0;  //slow, display on
      SinclairData.steptime1 = 400;
      SinclairData.steptime = 400;
      break;
    case '2':
      SinclairData.speed = 1;  //normal, display on
      break;
    case '3':
      SinclairData.speed = 2;  //fast, display on
      SinclairData.steptime1 = 200;
      SinclairData.steptime = 200;
      break;
    case '9':
      //EEPROM.write(1, showlogo); // break has been omitted on purpose so speed and showwork are the normal values
      if (showlogo != 0) {
        SinclairLogo();
      }
    default:
      SinclairData.speed = 1;
      SinclairData.showwork = 0; //normal speed, display off during calculations
      break;
  }

  pinMode(13, OUTPUT);
}

// timing the loop function using the micros() function, finds it executes every 340uS, for a 2.9kHz clock speed
int loop_count = 0;
bool HB = false;
void loop()
{
  loop_count++;
  if (loop_count % 1024 == 0)
  {
    HB = !HB;
    digitalWrite(13, HB);
  }

  
  // put your main code here, to run repeatedly:
  char key;

  if (!SinclairData.timeinit)
  {
    SinclairData.nextentrytime = micros() + SinclairData.steptime;
    SinclairData.timeinit = true;
  }
  else
  {
    do
    {

    } while (micros() < SinclairData.nextentrytime);
    SinclairData.nextentrytime += SinclairData.steptime;
  }

  step();

  updateDisplay();

  key = readKey();

  if (SinclairData.resetinprogress)
  {
    // SINCLAIR behavior: makes the display dim when C is pressed, SinclairData.steptime must be reduced below 148 for this delay to take effect.
    delayMicroseconds(120); // sets brightness when C is pressed. smaller=dimmer

    allSegmentOff();
    if (SinclairData.address > 8) {
      SinclairData.resetinprogress = false;
      SinclairData.timeinit = false;
      SinclairData.steptime = SinclairData.steptime1;
    }
  }

  if (key == 'C') {
    if (SinclairData.resetinprogress == false) {
      SinclairData.address = 0;
      SinclairData.keyStrobeKN = 0;
      SinclairData.keyStrobeKO = 0;
      SinclairData.keyStrobeKP = 0;
      SinclairData.dActive = 1;
      SinclairData.steptime = 5; // speed up step() function so digit brightness can be controlled via smaller delayMicroseconds()
      SinclairData.resetinprogress = true;
    }
  }

  //detect numbers with 4 segments or less lit and turn them off sooner
  //this reduces the visible difference between a 1 and an 8 (without this 1 is normally brighter)
  //only affects commonCathode display
#if defined(CommonCathode)
  if (SinclairData.segmentslit < 4)
  {
    // 1 7
    delayMicroseconds(140);
    allDigitOff();
  }
  else if (SinclairData.segmentslit < 5)
  {
    // 4
    delayMicroseconds(180);
    allDigitOff();
  }
#endif

}
