
#pragma once

#include <Arduino.h>

#define NUMBER_OF_MASKS 16
#define MASK_LENGTH 12

bool opsWithK(byte opcode);

unsigned int getInstruction(unsigned int PC);

byte getMaskNum();

//char *getMask();
signed char *getMask();

void add(signed char src1[], signed char src2[], signed char dst[], bool hex = false);

void sub(signed char src1[], signed char src2[], signed char dst[], bool hex = false);

void compare(signed char src1[], signed char src2[]);

void copy(signed char src[], signed char dst[]);

void sll(signed char src[]);

void srl(signed char src[]);

void writeFlag(signed char dest[], signed char val);

void compareFlags(signed char src1[], signed char src2[]);

void exchange(signed char src1[], signed char src2[]);

void testFlag(signed char src[]);

void updateD();

void step();

