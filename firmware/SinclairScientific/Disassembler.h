
#pragma once

#include <Arduino.h>

void displayArray(signed char src1[]);

//to ENABLE instruction viaualization in step()
//comment #define NoDisassembly in main file
void displayInstruction(byte instructionid);
