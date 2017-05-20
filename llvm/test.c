#include "llvm.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <assert.h>

int main() {
  float stack[20];

  uint8_t code[128];

  uint8_t *cursor = code;

  llvm_code_op(&cursor, LDC); llvm_code_float(&cursor, 3.33f);
  llvm_code_op(&cursor, LDC); llvm_code_float(&cursor, 15.0f);
  llvm_code_op(&cursor, MUL);
  llvm_code_op(&cursor, SIN);
  llvm_code_op(&cursor, LDC); llvm_code_float(&cursor, 255.0f / 2.0f);
  llvm_code_op(&cursor, MUL);
  llvm_code_op(&cursor, LDC); llvm_code_float(&cursor, 255.0f / 2.0f);
  llvm_code_op(&cursor, ADD);

  printf("len = %li\n", cursor - code);

  for (uint8_t *c = code; c != cursor; c++) {
    printf("%02x ", *c);
  }
  printf("\n");

  float *stack_pointer = stack;
  llvm_run(code, cursor, &stack_pointer);

  float result = *(stack_pointer - 1);
  printf("stack size: %li", stack_pointer - stack);
  printf("result: %f\n", result);
  assert(result == sin(3.33f) * (255.0f / 2.0f) + (255.0f / 2.0f) );
      
}
