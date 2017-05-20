#include "llvm.h"
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <assert.h>

int main() {
  float stack[4];

  uint8_t code[128];

  uint8_t *cursor = code;

  llvm_code_op(&cursor, Push);
  llvm_code_float(&cursor, 1.0f);
  llvm_code_op(&cursor, Push);
  llvm_code_float(&cursor, 2.0f);
  llvm_code_op(&cursor, Add);

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
  assert(result == 3.0f);
      
}
