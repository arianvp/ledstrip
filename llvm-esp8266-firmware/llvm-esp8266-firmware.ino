#include <llvm.h>
#include <stddef.h>
#include <NeoPixelBus.h>

const uint16_t PixelCount = 50;
const size_t ProgramSize = 256;
const size_t StackSize = 256;


NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount);
uint8_t program[ProgramSize];
float program_stack[StackSize];


RgbColor run_program(uint8_t *begin, uint8_t *end, float **stack_pointer) {
  llvm_run(begin, end, stack_pointer);

  uint8_t b = *((*stack_pointer) - 1);
  uint8_t g = *((*stack_pointer) - 2);
  uint8_t r = *((*stack_pointer) - 3);

  return RgbColor(r, g, b);
}


void setup() {
  // put your setup code here, to run once:
  strip.Begin();

}

void loop() {
  uint8_t *cursor = program;
  llvm_code_op(&cursor, Push); llvm_code_float(&cursor, 255.0f);
  llvm_code_op(&cursor, Push); llvm_code_float(&cursor, 0.0f);
  llvm_code_op(&cursor, Push); llvm_code_float(&cursor, 255.0f);

  float time_seconds = millis() / 1000.0f;
  for (uint16_t i = 0; i < PixelCount; i++) {
    program_stack[0] = i * 1.0f;
    program_stack[1] = time_seconds;

    float *stack_pointer = program_stack + 2;

    HslColor color = run_program(program, cursor, &stack_pointer);

    strip.SetPixelColor(i, color);
  }
  strip.Show();
}
