#pragma once

#include <stdint.h>

typedef enum llvm_opcode {
  Push = 0,
  Dup,
  Add,
  Sub,
  Mul,
  Div,
  Sin,
} llvm_opcode;


// program builder helpers
void llvm_code_op(uint8_t **code, llvm_opcode opcode);
void llvm_code_float(uint8_t **code, float val);

void llvm_run(uint8_t *begin, uint8_t *end, float **top);
