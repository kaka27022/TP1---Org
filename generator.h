#ifndef GENERATOR_H
#define GENERATOR_H

#include "cpu.h"

Instruction* generateMultiInstructions(int, int);
Instruction* generateDiviInstructions(int, int);
Instruction* generateRandomInstructions(int);
Instruction* generateMultiplicationInstructions(int, int);
Instruction* readInstructions(char*, int*);
Instruction* menu();
void attInstructions(Machine *machine, Instruction *inst);

#endif // !GENERATOR_H