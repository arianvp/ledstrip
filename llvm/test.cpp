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
  llvm_code_op(&cursor, SUB);

  float *stack_pointer = stack;
  llvm_run(code, cursor, &stack_pointer);
  float result = *(stack_pointer - 1);

  assert(result == (15.0f - 3.33f));
}

void cycle1(uint8_t **cursor) {
  // h = sin (0.5*t - 0.05*i);
  // s = 1.0f;
  // b = 1.0f;

  // [t,i]
  llvm_code_op(cursor, LDC); llvm_code_float(cursor, 0.5f);
  // [t, i, 0.5f]
  llvm_code_op(cursor, LDS); llvm_code_uint8_t(cursor, 2);
  // [t, i, 0.5f, t]
  llvm_code_op(cursor, MUL);
  // [t, i, 0.5f*t]
  llvm_code_op(cursor, LDC); llvm_code_float(cursor, 0.05f);
  // [t, i, 0.5f*t, 0.05f]
  llvm_code_op(cursor, LDS); llvm_code_uint8_t(cursor, 2);
  // [t, i, 0.5f*t, 0.05f, i]
  llvm_code_op(cursor, MUL);
  // [t, i, 0.5f*t, 0.05f*i]
  llvm_code_op(cursor, SUB);
  // [t, i, 0.5f*t-0.05f*i]
  llvm_code_op(cursor, SIN);
  // [t, i, sin(0.5f*t-0.05f*i)]
  llvm_code_op(cursor, LDC); llvm_code_float(cursor, 1.0f);
  // [t, i, sin(0.5f*t-0.05f*i), 1.0f]
  llvm_code_op(cursor, LDS); llvm_code_uint8_t(cursor, 0);
  // [t, i, sin(0.5f*t-0.05f*i), 1.0f, 1.0f]
}

int main() {
  float stack[20];

  uint8_t code[128];

  uint8_t *cursor = code;
  cycle1(&cursor);
  

  printf("len = %li\n", cursor - code);

  for (uint8_t *c = code; c != cursor; c++) {
    printf("\\x%02x", *c);
  }
  printf("\n");

  float *stack_pointer = stack;
  llvm_run(code, cursor, &stack_pointer);

  float h = *(stack_pointer - 1);
  printf("h: %f\n", h);
  float s = *(stack_pointer - 2);
  printf("s: %f\n", s);
  float v = *(stack_pointer - 3);
  printf("v: %f\n", v);
  printf("stack size: %li", stack_pointer - stack);
      
}
