
#include "CPU.h"
#include "SinclairScientific.h"
#include "Disassembler.h"

//These are the 320 instructions that performed all the tasks on the Sinclair Scientific.
//the rest of this program is to execute and interface these instructions to todays hardware

const unsigned int objectCode[] PROGMEM = {
  1408, 1392, 1792, 1824, 1860, 1808, 1360, 1376,
  518, 1319, 1360, 1376, 9, 1360, 1908, 1072,
  1083, 1075, 1121, 1129, 1073, 1069, 1051, 1840,
  1955, 1840, 516, 1425, 552, 1430, 33, 1792,
  1398, 1631, 1920, 1683, 34, 2003, 1540, 4,
  1399, 1858, 1872, 1538, 4, 1329, 1335, 4,
  1349, 1347, 4, 1443, 676, 1431, 57, 1559,
  4, 1553, 59, 1443, 677, 1839, 1632, 2018,
  65, 2023, 1719, 72, 1730, 71, 1840, 1666,
  1751, 587, 1840, 1754, 78, 1840, 1718, 594,
  1924, 78, 2017, 1713, 89, 1540, 130, 1844,
  1841, 1652, 597, 130, 1730, 95, 1849, 1650,
  114, 1443, 675, 1355, 1345, 130, 1409, 1559,
  105, 1443, 750, 1839, 1632, 1844, 2023, 1719,
  92, 1538, 1537, 116, 1451, 1796, 791, 1908,
  1781, 637, 1722, 1540, 120, 1940, 1786, 119,
  1445, 820, 1754, 512, 1747, 145, 1860, 1751,
  142, 1686, 141, 1799, 1798, 1686, 1558, 132,
  132, 1908, 1751, 662, 1686, 1686, 1558, 152,
  1441, 614, 1392, 1334, 1408, 1750, 161, 1559,
  159, 1568, 4, 1351, 1355, 1686, 681, 1908,
  165, 1801, 1689, 1824, 1445, 180, 1447, 179,
  1568, 1819, 185, 1565, 1820, 1924, 2011, 1693,
  738, 1888, 1888, 1888, 2012, 1696, 1936, 1936,
  1936, 1872, 1872, 1872, 2012, 1584, 1724, 1920,
  1920, 1920, 1445, 183, 1561, 1447, 210, 1779,
  697, 220, 1451, 727, 1732, 185, 220, 1754,
  1844, 1764, 1844, 185, 1904, 1904, 1904, 1904,
  1904, 130, 1447, 233, 1616, 1600, 1808, 1411,
  100, 1451, 236, 1632, 1840, 130, 1445, 251,
  1750, 760, 1751, 759, 1908, 1686, 240, 1860,
  1794, 1864, 1864, 1824, 2003, 1636, 1924, 1924,
  1700, 1431, 823, 2009, 1787, 253, 1993, 2036,
  1723, 1920, 1920, 1920, 1920, 1588, 1844, 1445,
  814, 1600, 1479, 1447, 765, 1572, 1796, 1806,
  1764, 797, 1700, 1562, 280, 1571, 803, 1860,
  1631, 1892, 280, 1807, 1443, 808, 130, 10,
  1572, 1796, 1904, 1904, 1794, 61, 1572, 1796,
  1803, 1652, 1844, 117, 1908, 1335, 251, 1693,
  253, 1565, 1860, 1563, 2036, 1844, 1411, 790
};

const char masks [][MASK_LENGTH] PROGMEM = {
  {"00000000000"}, // M0
  {"5          "}, // M1
  {"  00       "}, // M2
  {"    1      "}, // M3
  {"    0000000"}, // M4
  {"          1"}, // M5
  {"  01       "}, // M6
  {" 5         "}, // M7
  {"000000     "}, // M8
  {"0001       "}, // M9
  {"    0000001"}, // M10
  {"     1     "}, // M11
  {"    00005  "}, // M12
  {"    00001  "}, // M13
  {"    4      "}, // M14
  {"    0      "}, // M15
};

// OPS WITH K: 1:AAKA 2:AAKC 5:ACKA 6:ACKB 9: 11:
//const unsigned long LISTOPSWITHK = 000111100000001111010101001100110b;
const unsigned long LISTOPSWITHK = 1007135334;

boolean opsWithK(byte opcode)
{
  return (LISTOPSWITHK & (1UL << opcode));
}

unsigned int getInstruction(unsigned int PC)
{
  return pgm_read_word_near(objectCode + PC);
}

byte getMaskNum()
{
  return getInstruction(SinclairData.address) & 0x0f;
}

//char *getMask()
signed char *getMask()
{
  unsigned int instruction = getInstruction(SinclairData.address);
  byte classBits = instruction >> 9;
  byte opcode = (instruction >> 4) & 0x1f;

  if (classBits == 3 || (classBits == 2 && opcode > 18 && opcode != 21 && opcode != 22))
  {
    byte maskno = getMaskNum();

    for (byte i = 0; i <= 10; i++)
    {
      char maskdigit = pgm_read_byte_near(masks[maskno] + i);

      if (maskdigit == ' ')
      {
        SinclairData.mask[i] = maskdigit;
      }
      else if (classBits == 3 && opsWithK(opcode))
      {
        // Register instruction
        SinclairData.mask[i] = maskdigit - '0';;
      }
      else
      {
        SinclairData.mask[i] = '*';
      }
    }
  }
  else
  {
    SinclairData.mask[0] = 0;
  }

  return SinclairData.mask;
}

void add(signed char src1[], signed char src2[], signed char dst[], bool hex)
{
  byte carry = 0;
  getMask();
  for (signed char i = 10; i >= 0; i--)
  {
    if (SinclairData.mask[i] == ' ')
    {
      // masked out
      // continue;
    }
    else
    {
      signed char result = src1[i] + src2[i] + carry;
      if (!hex && result >= 10)
      {
        result -= 10;
        carry = 1;
      }
      else if (hex && result >= 16)
      {
        result -= 16;
        carry = 1;
      }
      else
      {
        carry = 0;
      }
      dst[i] = result;
    }
  }
  if (carry)
  {
    SinclairData.cc = carry;
    //SinclairData.ccMeaning = carry ? 'overflow' : 'no overflow';
  }
}

void sub(signed char src1[], signed char src2[], signed char dst[], bool hex)
{
  byte borrow = 0;
  getMask();
  for (signed char i = 10; i >= 0; i--)
  {
    if (SinclairData.mask[i] == ' ')
    {
      // masked out
      // continue;
    }
    else
    {
      signed char result = src1[i] - src2[i] - borrow;
      if (result < 0)
      {
        result += hex ? 16 : 10;
        borrow = 1;
      }
      else
      {
        borrow = 0;
      }
      dst[i] = result;
    }
  }
  if (borrow)
  {
    SinclairData.cc = borrow;
    //SinclairData.ccMeaning = borrow ? 'borrow' : 'no borrow';
  }
}

void compare(signed char src1[], signed char src2[])
{
  signed char tmp[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  sub(src1, src2, tmp);
  // Compare sets condition if not borrow
  //SinclairData.ccMeaning = SinclairData.cc ? "less than" : "not less than";
}

void copy(signed char src[], signed char dst[])
{
  getMask();
  for (signed char i = 10; i >= 0; i--)
  {
    if (SinclairData.mask[i] == ' ')
    {
      // masked out
      // continue;
    }
    else
    {
      dst[i] = src[i];
    }
  }
}

void sll(signed char src[])
{
  getMask();
  signed char digit = 0;
  for (signed char i = 10; i >= 0; i--)
  {
    if (SinclairData.mask[i] == ' ')
    {
      // masked out
      // continue;
    }
    else
    {
      signed char newdigit = src[i];
      src[i] = digit;
      digit = newdigit;
    }
  }
}

void srl(signed char src[])
{
  getMask();
  signed char digit = 0;
  for (signed char i = 0; i <= 10; i++)
  {
    if (SinclairData.mask[i] == ' ')
    {
      // masked out
      // continue;
    }
    else
    {
      signed char newdigit = src[i];
      src[i] = digit;
      digit = newdigit;
    }
  }
}

void writeFlag(signed char dest[], signed char val)
{
  getMask();
  for (signed char i = 10; i >= 0; i--)
  {
    if (SinclairData.mask[i] == ' ')
    {
      // masked out
      // continue;
    }
    else
    {
      // Flip dst if val == -1, otherwise set to val
      dest[i] = (val < 0) ? (1 - dest[i]) : val;
    }
  }
}

void compareFlags(signed char src1[], signed char src2[])
{
  signed char cc = 0;
  getMask();
  for (signed char i = 10; i >= 0; i--)
  {
    if (SinclairData.mask[i] == ' ')
    {
      // masked out
      // continue;
    }
    else
    {
      if (src1[i] != src2[i])
      {
        cc = 1;
      }
    }
  }
  if (cc)
  {
    SinclairData.cc = 1;
    //SinclairData.ccMeaning = 'flags not equal';
  }
}

void exchange(signed char src1[], signed char src2[])
{
  getMask();
  for (signed char i = 10; i >= 0; i--)
  {
    if (SinclairData.mask[i] == ' ')
    {
      // masked out
      // continue;
    }
    else
    {
      signed char t = src1[i];
      src1[i] = src2[i];
      src2[i] = t;
    }
  }
}

void testFlag(signed char src[])
{
  signed char cc = 0;
  getMask();
  for (signed char i = 10; i >= 0; i--)
  {
    if (SinclairData.mask[i] == ' ')
    {
      // masked out
      // continue;
    }
    else
    {
      if (src[i])
      {
        cc = 1;
      }
    }
  }
  /* Only update cc if bit set */
  if (cc)
  {
    SinclairData.cc = cc;
    //SinclairData.ccMeaning = 'flag set';
  }
}

void updateD()
{
  for (signed char i = 10; i >= 0; i--)
  {
    SinclairData.d[i] = 1;
  }

  SinclairData.dActive += 1;
  if (SinclairData.dActive > 10)
  {
    SinclairData.dActive = 1;
  }
  SinclairData.d[SinclairData.dActive - 1] = 0;
}

void step()
{
#if defined(EnableDisassembly)
  Serial.print(F("addr:"));
  Serial.print(SinclairData.address);
#endif

  unsigned int instruction = getInstruction(SinclairData.address);
  byte classBits = instruction >> 9;
  byte opcode = (instruction >> 4) & 0x1f;
  unsigned int nextAddress = SinclairData.address + 1;

  //Serial.print(F(" data:"));
  //Serial.print(opcode);
  //Serial.print(F(" classbits:"));
  //Serial.print(classBits);

  if (classBits == 3)
  {
    // Register instruction
    byte maskBits = instruction & 0xf;
    switch (opcode)
    {
      case 0: // AABA: A+B -> A
        displayInstruction(1);
        add(SinclairData.a, SinclairData.b, SinclairData.a);
        break;
      case 1: // AAKA: A+K -> A
        displayInstruction(2);
        add(SinclairData.a, getMask(), SinclairData.a);
        break;
      case 2: // AAKC: A+K -> C
        displayInstruction(3);
        add(SinclairData.a, getMask(), SinclairData.c);
        break;
      case 3:
        if (SinclairData.sinclair)
        { // ACBB C+B -> B
          displayInstruction(4);
          add(SinclairData.c, SinclairData.b, SinclairData.b);
        }
        else
        { // ABOA: B -> A
          displayInstruction(5);
          copy(SinclairData.b, SinclairData.a);
        }
        break;
      case 4: // ABOC: B -> C
        displayInstruction(6);
        copy(SinclairData.b, SinclairData.c);
        break;
      case 5: // ACKA: C+K -> A
        displayInstruction(7);
        add(SinclairData.c, getMask(), SinclairData.a);
        break;
      case 6: // AKCB: C+K -> B
        displayInstruction(8);
        add(SinclairData.c, getMask(), SinclairData.b);
        break;
      case 7: // SABA: A-B -> A
        displayInstruction(9);
        sub(SinclairData.a, SinclairData.b, SinclairData.a);
        break;
      case 8: // SABC: A-B -> C
        displayInstruction(10);
        sub(SinclairData.a, SinclairData.b, SinclairData.c);
        break;
      case 9: // SAKA: A-K -> A
        displayInstruction(11);
        sub(SinclairData.a, getMask(), SinclairData.a);
        break;
      case 10: // SCBC: C-B -> C
        displayInstruction(12);
        sub(SinclairData.c, SinclairData.b, SinclairData.c);
        break;
      case 11: // SCKC: C-K -> C
        displayInstruction(13);
        sub(SinclairData.c, getMask(), SinclairData.c);
        break;
      case 12: // CAB: compare A-B
        displayInstruction(14);
        compare(SinclairData.a, SinclairData.b);
        break;
      case 13: // CAK: compare A-K
        displayInstruction(15);
        compare(SinclairData.a, getMask());
        break;
      case 14: // CCB: compare C-B
        displayInstruction(16);
        compare(SinclairData.c, SinclairData.b);
        break;
      case 15: // CCK: compare C-K
        displayInstruction(17);
        compare(SinclairData.c, getMask());
        break;
      case 16: // AKA: K -> A
        displayInstruction(18);
        copy(getMask(), SinclairData.a);
        break;
      case 17: // AKB: K -> B
        displayInstruction(19);
        copy(getMask(), SinclairData.b);
        break;
      case 18: // AKC: K -> C
        displayInstruction(20);
        copy(getMask(), SinclairData.c);
        break;
      case 19: // EXAB: exchange A and B
        displayInstruction(21);
        exchange(SinclairData.a, SinclairData.b);
        break;
      case 20: // SLLA: shift A left
        displayInstruction(22);
        sll(SinclairData.a);
        break;
      case 21: // SLLB: shift B left
        displayInstruction(23);
        sll(SinclairData.b);
        break;
      case 22: // SLLC: shift C left
        displayInstruction(24);
        sll(SinclairData.c);
        break;
      case 23: // SRLA: shift A right
        displayInstruction(25);
        srl(SinclairData.a);
        break;
      case 24: // SRLB: shift B right
        displayInstruction(26);
        srl(SinclairData.b);
        break;
      case 25: // SRLC: shift C right
        displayInstruction(66);
        srl(SinclairData.c);
        break;
      case 26: // AKCN: A+K -> A until key down on N or D11 [sic]
        // Patent says sets condition if key down, but real behavior
        // is to set condition if addition overflows (i.e. no key down)
        //SinclairData.display = 0; //comment this line to glitch the display when a number key is pressed (SINCLAIR behavior: actual hardware behavior)
        add(SinclairData.a, getMask(), SinclairData.a);
        if (SinclairData.keyStrobeKN)
        {
          displayInstruction(27);
          // Advance to next instruction
        }
        else if (SinclairData.dActive != 10)
        {
          displayInstruction(28);
          // Hold at current instruction and continue scan
          nextAddress = SinclairData.address;
        }
        else
        {
          displayInstruction(29);
          // For state d10, fall through
        }
        break;
      case 27:
        if (SinclairData.sinclair)
        { // SCBA C-B -> A
          displayInstruction(30);
          sub(SinclairData.c, SinclairData.b, SinclairData.a);
        }
        else
        { // AAKAH A+K -> A hex
          displayInstruction(31);
          add(SinclairData.a, getMask(), SinclairData.a, 1 /* hex */ );
          SinclairData.cc = 0;
          //SinclairData.ccMeaning = '';
        }
        break;
      case 28:
        if (SinclairData.sinclair)
        { // SCKB C-K -> B
          displayInstruction(32);
          sub(SinclairData.c, getMask(), SinclairData.b);
        }
        else
        { // SAKAH A-K -> A hex
          displayInstruction(33);
          sub(SinclairData.a, getMask(), SinclairData.a, 1 /* hex */ );
          SinclairData.cc = 0;
          //SinclairData.ccMeaning = '';
        }
        break;
      case 29: // ACKC: C+K -> C
        displayInstruction(34);
        add(SinclairData.c, getMask(), SinclairData.c);
        break;
      case 30:
        if (SinclairData.sinclair)
        { // AABC A+B -> C
          displayInstruction(35);
          add(SinclairData.a, SinclairData.b, SinclairData.c);
          break;
        }
      case 31:
        if (SinclairData.sinclair)
        { // ACBC C+B -> C
          displayInstruction(36);
          add(SinclairData.c, SinclairData.b, SinclairData.c);
          break;
        }
      default:
        //bad instruction
        //alert('Bad instruction ' + instruction);
        displayInstruction(37);
        break;
    }
  }
  else if ((instruction >> 8) == 5)
  {
    // Flag instruction
    byte maskBits = instruction & 0xf;
    switch (opcode)
    {
      case 16: // NOP
        displayInstruction(38);
        break;
      case 17: // WAITDK: wait for display key
        SinclairData.display = 0;
        if (SinclairData.keyPressed == DK)
        {
          // Jump
          displayInstruction(39);
          nextAddress = instruction & 0x1ff;
        }
        else
        {
          // Hold address until DK pressed
          displayInstruction(40);
          nextAddress = SinclairData.address;
        }
        break;
      case 18: // WAITNO: wait for key or address register overflow
        if (SinclairData.keyStrobeKO || SinclairData.keyStrobeKN || SinclairData.keyStrobeKP)
        {
          // Jump
          displayInstruction(41);
          nextAddress = instruction & 0x1ff;
        }
        else
        {
          // Hold address until key pressed or address overflow (TODO)
          displayInstruction(42);
          nextAddress = SinclairData.address;
        }
        break;
      case 19: // SFB: set flag B
        displayInstruction(43);
        writeFlag(SinclairData.bf, 1);
        break;
      case 20: // SFA: set flag A
        displayInstruction(44);
        writeFlag(SinclairData.af, 1);
        break;
      case 21: // SYNC (SYNCH): hold address until end of D10
        displayInstruction(45);
        if (SinclairData.dActive != 10)
        {
          nextAddress = SinclairData.address;
        }
        SinclairData.cc = 0;
        //SinclairData.ccMeaning = '';
        break;
      case 22: // SCAN (SCANNO): wait for key
        SinclairData.display = 1; // Reset display power off latch
        if (SinclairData.keyStrobeKO || SinclairData.keyStrobeKN || SinclairData.keyStrobeKP)
        {
          displayInstruction(46);
          SinclairData.cc = 1;
          //SinclairData.ccMeaning = 'key';
        }
        else
        {
          displayInstruction(47);
          SinclairData.cc = 0;
          //SinclairData.ccMeaning = 'no key';
          if (SinclairData.dActive != 10)
          {
            // Hold address until end of D10
            nextAddress = SinclairData.address;
          }
        }
        break;
      case 23: // ZFB: zero flag B
        displayInstruction(48);
        writeFlag(SinclairData.bf, 0);
        break;
      case 24: // ZFA: zero flag A
        displayInstruction(49);
        writeFlag(SinclairData.af, 0);
        break;
      case 25: // TFB: test flag B
        displayInstruction(50);
        testFlag(SinclairData.bf);
        break;
      case 26: // TFA: test flag A
        displayInstruction(51);
        testFlag(SinclairData.af);
        break;
      case 27: // FFB: flip flag B
        displayInstruction(52);
        writeFlag(SinclairData.bf, -1 /* flip */ );
        break;
      case 28: // FFA: flip flag A
        displayInstruction(67);
        writeFlag(SinclairData.af, -1 /* flip */ );
        break;
      case 29: // CF: compare flags
        displayInstruction(53);
        compareFlags(SinclairData.af, SinclairData.bf);
        break;
      case 30: // NOP
        displayInstruction(54);
        break;
      case 31: // EXF: exchange flags
        displayInstruction(55);
        exchange(SinclairData.af, SinclairData.bf);
        break;
      default:
        //bad instruction
        //alert('Bad instruction ' + instruction);
        displayInstruction(56);
        break;
    }
  }
  else if (classBits == 0)
  {
    // jump if reset: BIU, BIZ, BIGE, BINC, BIE, BET
    displayInstruction(57);
    if (SinclairData.cc == 0)
    {
      displayInstruction(58);
      nextAddress = instruction & 0x1ff;
    }
    SinclairData.cc = 0; // Clear after jump
    //SinclairData.ccMeaning = '';
  }
  else if (classBits == 1)
  {
    // jump if set: BID, BIO, BILT, BIC, BINE
    displayInstruction(59);
    if (SinclairData.cc == 1)
    {
      displayInstruction(60);
      nextAddress = instruction & 0x1ff;
    }
    SinclairData.cc = 0; // Clear after jump
    //SinclairData.ccMeaning = '';
  }
  else if ((instruction >> 7) == 8)
  {
    // Jump if key down on KO (BKO)
    displayInstruction(61);
    if (SinclairData.keyStrobeKO)
    {
      SinclairData.display = 0;
      displayInstruction(62);
      nextAddress = instruction & 0x1ff;
    }
    SinclairData.cc = 0; // Clear after jump
    //SinclairData.ccMeaning = '';
  }
  else if ((instruction >> 7) == 9)
  {
    // Jump if key down on KP (BKP)
    displayInstruction(63);
    if (SinclairData.keyStrobeKP)
    {
      SinclairData.display = 0;
      displayInstruction(64);
      nextAddress = instruction & 0x1ff;
    }
    SinclairData.cc = 0; // Clear after jump
    //SinclairData.ccMeaning = '';
  }
  else
  {
    displayInstruction(65);
    //bad instruction
    //alert('Bad instruction code ' + instruction);
  }
  SinclairData.address = nextAddress;
  // Put the mask for the next instruction in the model for display
  //SinclairData.mask = getMask();
  getMask();
  // Update D state
  updateD();

  displayInstruction(68); // if printing is enabled, do a println after executing a line of code
}
