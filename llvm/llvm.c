#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "llvm.h"


# define DO_UNARY(fn, stack) do { float a = *(--(*stack)); *((*stack)++) = fn(a); } while (0)
# define DO_BINARY(op, stack) do { float b = *(--(*stack)); float a = *(--(*stack)); *((*stack)++) = a op b; } while (0)


void run(uint8_t *begin, uint8_t *end, float *stack) {
  float *top = stack;

  uint8_t *pc = begin;
  while (pc != end) {
    printf("pc: %li\n", pc - begin);
    opcode op = (opcode) *(pc++);
    printf("opcode: %02x \n", op);

    switch (op) {
      case Dup: {
        float a = *(top - 1);
        *(top++) = a;
        break;
      }
      case Push: {
        union { float f; uint8_t b[sizeof(float)]; } dest;
        for (size_t i = 0; i < sizeof(float); i++) dest.b[i] = *(pc++);
        *(top++) = dest.f;
        break;
      }
      case Add: DO_BINARY(+, &top); break;
      case Mul: DO_BINARY(*, &top); break;
      case Sub: DO_BINARY(-, &top); break;
      case Div: DO_BINARY(/, &top); break;
      case Sin: DO_UNARY(sin, &top); break;
      default: assert("impossible" && 0);
    }

    printf("stacklen: %li\n", top - stack);
    printf("stack:\n");
    for (float *c = stack ; c != top; c++) {
      printf("%f\n", *c);
    }
  }
}
