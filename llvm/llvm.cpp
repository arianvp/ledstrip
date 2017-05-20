#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include "llvm.h"


# define DO_UNARY(fn, stack) do { float a = *(--(*stack)); *((*stack)++) = fn(a); } while (0)
# define DO_BINARY(op, stack) do { float b = *(--(*stack)); float a = *(--(*stack)); *((*stack)++) = a op b; } while (0)

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
void llvm_code_reg(uint8_t **code, uint8_t val) {
  *((*code)++) = val;
}

void llvm_run(uint8_t *begin, uint8_t *end, float **stack_pointer) {
  float registers[32];
  uint8_t *pc = begin;
  while (pc != end) {
    llvm_opcode op = (llvm_opcode) *(pc++);
    switch (op) {
      case LDC: {
        union { float f; uint8_t b[sizeof(float)]; } dest;
        for (size_t i = 0; i < sizeof(float); i++) dest.b[i] = *(pc++);
        *((*stack_pointer)++) = dest.f;
        break;
      }
      case LDR: {
        llvm_register reg = (llvm_register) *(pc++);
        float val = registers[reg];
        *((*stack_pointer)++) = val;
        break;
      }
      case DUP: {
        float a = *((*stack_pointer) - 1);
        *((*stack_pointer)++) = a;
        break;
      }
      case SDR: {
        llvm_register reg = (llvm_register) *(pc++);
        float val = *(--(*stack_pointer));
        registers[reg] = val;
        break;
      }
      case ADD: DO_BINARY(+, stack_pointer); break;
      case MUL: DO_BINARY(*, stack_pointer); break;
      case SUB: DO_BINARY(-, stack_pointer); break;
      case DIV: DO_BINARY(/, stack_pointer); break;
      case SIN: DO_UNARY(sin, stack_pointer); break;
      default: break;
    }
  }
}
