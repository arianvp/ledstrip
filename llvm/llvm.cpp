#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include "llvm.h"


# define DO_UNARY(fn, stack) do { float a = *(--(*stack)); *((*stack)++) = fn(a); } while (0)
# define DO_BINARY(op, stack) do { float b = *(--(*stack)); float a = *(--(*stack)); *((*stack)++) = a op b; } while (0)
# define DO_BINARYF(op, stack) do { float b = *(--(*stack)); float a = *(--(*stack)); *((*stack)++) = op(a,b); } while (0)

extern "C" {
void llvm_code_op(uint8_t **code, llvm_opcode opcode) {
  *((*code)++) = (uint8_t) opcode;
}

void llvm_code_float(uint8_t **code, float val) {
  union { float f; uint8_t b[sizeof(float)]; } src;
  src.f = val;
  for (size_t i = 0; i < sizeof(float); i++) {
    *((*code)++) = src.b[i];
  }
}
void llvm_code_uint8_t(uint8_t **code, uint8_t val) {
  *((*code)++) = val;
}

void llvm_run(uint8_t *begin, uint8_t *end, float **stack_pointer) {
  uint8_t *pc = begin;
  bool running = true;
  while (pc != end && running) {
    llvm_opcode op = (llvm_opcode) *(pc++);
    switch (op) {
      case BRK:
        running = false;
        break;
      case LDC: {
        union { float f; uint8_t b[sizeof(float)]; } dest;
        for (size_t i = 0; i < sizeof(float); i++) dest.b[i] = *(pc++);
        *((*stack_pointer)++) = dest.f;
        break;
      }
      case LDS: {
        uint8_t offset = *(pc++); 
        float val = *((*stack_pointer) - offset - 1);
        *((*stack_pointer)++) = val;
        break;
      }
      case ADD: DO_BINARY(+, stack_pointer); break;
      case MUL: DO_BINARY(*, stack_pointer); break;
      case SUB: DO_BINARY(-, stack_pointer); break;
      case DIV: DO_BINARY(/, stack_pointer); break;
      case SIN: DO_UNARY(sin, stack_pointer); break;
      case MIN: DO_BINARYF(fmin, stack_pointer); break;
      default: break;
    }
  }
}
}
