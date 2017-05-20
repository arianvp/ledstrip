#include "llvm.h"
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <assert.h>


void push_op(uint8_t **code, opcode opcode) {
  *((*code)++) = (uint8_t) opcode;
}

void push_float(uint8_t **code, float val) {
  union { float f; uint8_t b[sizeof(float)]; } src;
  src.f = val;

  for (size_t i = 0; i < sizeof(float); i++) {
    *((*code)++) = src.b[i];
  }

}

int main() {
  float stack[4];

  uint8_t code[128];

  uint8_t *cursor = code;

  push_op(&cursor, Push);
  push_float(&cursor, 1.0f);
  push_op(&cursor, Push);
  push_float(&cursor, 2.0f);
  push_op(&cursor, Add);

  printf("len = %li\n", cursor - code);

  for (uint8_t *c = code; c != cursor; c++) {
    printf("%02x ", *c);
  }
  printf("\n");

  run(code, cursor, stack);

  printf("result: %f\n", stack[0]);
  assert(stack[0] == 3.0f);
      
}
