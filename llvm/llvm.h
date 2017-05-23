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
  BRK,
  LDC,  // load constant value onto stack
  LDS,  // load a value from an off
  POP,  // pops off a value from the stack
  ADD,
  SUB,
  MUL,
  DIV,
  SIN,
  MIN,
} llvm_opcode;


// program builder helpers
void llvm_code_op(uint8_t **code, llvm_opcode opcode);
void llvm_code_float(uint8_t **code, float val);
void llvm_code_uint8_t(uint8_t **code, uint8_t val);

void llvm_run(uint8_t *begin, uint8_t *end, float **top);

};
