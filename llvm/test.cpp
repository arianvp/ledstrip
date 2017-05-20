#include "llvm.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <assert.h>

void test_swap() {
  float stack[20];
  uint8_t code[128];
  uint8_t *cursor = code;

  llvm_code_op(&cursor, LDC); llvm_code_float(&cursor, 3.33f);
  llvm_code_op(&cursor, LDC); llvm_code_float(&cursor, 15.0f);
  llvm_code_op(&cursor, SWP);
  llvm_code_op(&cursor, SUB);

  float *stack_pointer = stack;
  llvm_run(code, cursor, &stack_pointer);
  float result = *(stack_pointer - 1);

  assert(result == (15.0f - 3.33f));
}
int main() {
  test_swap();
  float stack[20];

  uint8_t code[128];

  uint8_t *cursor = code;

  llvm_code_op(&cursor, LDC); llvm_code_float(&cursor, 3.33f);
  llvm_code_op(&cursor, LDC); llvm_code_float(&cursor, 15.0f);
  llvm_code_op(&cursor, LDC); llvm_code_float(&cursor, 3.33f);
  llvm_code_op(&cursor, LDC); llvm_code_float(&cursor, 15.0f);
  llvm_code_op(&cursor, SDR); llvm_code_reg(&cursor, B);
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
  assert(result == 3.33f + 15.0f);
      
}
