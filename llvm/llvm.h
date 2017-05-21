// very much inspired Bij Dijkstra's Simple Stack Machine
// but simplified a bit , and only added arthmatic useful for light

// effects.
// http://www.staff.science.uu.nl/~dijks106/SSM/instructions.html
#pragma once

#include <stdint.h>

extern "C" {

/*
// some utility registers. Upto 32.  In the future, we could perhaps expose
// the Stack Pointer and whatnot but for now that seems totally overkill
typedef enum llvm_register {
  A = 0,
  B = 1,
  C = 2,

} llvm_register;*/

typedef enum llvm_opcode {
  BRK = 0,
  LDC = 1,  // load constant value onto stack
  LDR = 2,  // load value from register onto stack
  SDR = 3,  // pop the top of the stack into a register
  DUP = 4,  // convenience: duplicates the top of the stack
  ADD = 5,
  SUB = 6,
  MUL = 7,
  DIV = 8,
  SIN = 9,
  SWP = 10, // swaps the two latest values on the stack
} llvm_opcode;


// program builder helpers
void llvm_code_op(uint8_t **code, llvm_opcode opcode);
void llvm_code_float(uint8_t **code, float val);
void llvm_code_reg(uint8_t **code, uint8_t val);

void llvm_run(uint8_t *begin, uint8_t *end, float **top);

};
