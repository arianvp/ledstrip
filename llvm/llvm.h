#pragma once

#include <stdint.h>

typedef enum opcode {
  Push = 0,
  Dup,
  Add,
  Sub,
  Mul,
  Div,
  Sin,
} opcode;

void run(uint8_t *begin, uint8_t *end, float *stack);
