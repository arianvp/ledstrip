// very much inspired Bij Dijkstra's Simple Stack Machine
// but simplified a bit , and only added arthmatic useful for light

// effects.
// http://www.staff.science.uu.nl/~dijks106/SSM/instructions.html
#pragma once

#include <stdint.h>

// some utility registers. Upto 32.  In the future, we could perhaps expose
// the Stack Pointer and whatnot but for now that seems totally overkill
typedef enum llvm_register {
  R = 0,
  G = 1,
  B = 2,
  H = 0,
  S = 1,
  V = 2,
  L = 2,
} llvm_register;

typedef enum llvm_opcode {
  LDC = 0,  // load constant value onto stack
  LDR = 1,  // load value from register onto stack
  SDR = 2,  // pop the top of the stack into a register
  DUP = 3,  // convenience: duplicates the top of the stack
  ADD = 4,
  SUB = 5,
  MUL = 6,
  DIV = 7,
  SIN = 8,
} llvm_opcode;


// program builder helpers
void llvm_code_op(uint8_t **code, llvm_opcode opcode);
void llvm_code_float(uint8_t **code, float val);
void llvm_code_reg(uint8_t **code, uint8_t val);

void llvm_run(uint8_t *begin, uint8_t *end, float **top);
