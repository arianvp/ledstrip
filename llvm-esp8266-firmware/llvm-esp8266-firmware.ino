#include <llvm.h>
#include <stddef.h>
#include <NeoPixelBus.h>

const uint16_t PixelCount = 100;
const size_t ProgramSize = 256;
const size_t StackSize = 256;


NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount);
uint8_t program[ProgramSize];
float program_stack[StackSize];


HsbColor run_program(uint8_t *begin, uint8_t *end, float **stack_pointer) {
  llvm_run(begin, end, stack_pointer);

  float b = *((*stack_pointer) - 1);
  float s = *((*stack_pointer) - 2);
  float h = *((*stack_pointer) - 3);

  return HsbColor(h, s, b);
}


void setup() {
  // put your setup code here, to run once:
  strip.Begin();

}

void loop() {
  uint8_t *cursor = program;
  llvm_code_op(&cursor, MUL);
  llvm_code_op(&cursor, SIN);
  llvm_code_op(&cursor, LDC); llvm_code_float(&cursor, 0.5f);
  llvm_code_op(&cursor, MUL);
  llvm_code_op(&cursor, LDC); llvm_code_float(&cursor, 0.5f);
  llvm_code_op(&cursor, ADD);
  llvm_code_op(&cursor, LDC); llvm_code_float(&cursor, 1.0f);
  llvm_code_op(&cursor, LDC); llvm_code_float(&cursor, 0.5f);


  float time_seconds = millis() / 1000.0f;
  for (uint16_t i = 0; i < PixelCount; i++) {
    program_stack[0] = time_seconds;
    program_stack[1] = i * 0.05f;

    float *stack_pointer = program_stack + 2;

    HsbColor color = run_program(program, cursor, &stack_pointer);

    strip.SetPixelColor(i, color);
  }
  strip.Show();
}
