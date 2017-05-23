#include <llvm.h>
#include <stddef.h>
#include <NeoPixelBus.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "sensitive.h"

const uint16_t PixelCount = 151;
const size_t ProgramSize = 256;
const size_t StackSize = 256;
const uint16_t port = 4210;

WiFiUDP udp;
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount);
uint8_t program[ProgramSize];
float program_stack[StackSize];
NeoGamma<NeoGammaEquationMethod> colorGamma;
uint8_t *cursor = program;

bool connected = false;

HsbColor run_program(uint8_t *begin, uint8_t *end, float **stack_pointer) {
  llvm_run(begin, end, stack_pointer);

  float b = *((*stack_pointer) - 1);
  float s = *((*stack_pointer) - 2);
  float h = *((*stack_pointer) - 3);

  return HsbColor(h, s, b);
}




void trippy(uint8_t **cursor) {
  llvm_code_op(cursor, LDC); llvm_code_float(cursor, 0.05f);
  llvm_code_op(cursor, MUL);
  llvm_code_op(cursor, MUL);
  llvm_code_op(cursor, SIN);
  llvm_code_op(cursor, LDC); llvm_code_float(cursor, 0.5f);
  llvm_code_op(cursor, MUL);
  llvm_code_op(cursor, LDC); llvm_code_float(cursor, 0.5f);
  llvm_code_op(cursor, ADD);
  llvm_code_op(cursor, LDC); llvm_code_float(cursor, 1.0f);
  llvm_code_op(cursor, LDC); llvm_code_float(cursor, 0.5f);
}

void off(uint8_t **cursor) {
  llvm_code_op(cursor, LDC); llvm_code_float(cursor, 0.0f);
  llvm_code_op(cursor, LDC); llvm_code_float(cursor, 0.0f);
  llvm_code_op(cursor, LDC); llvm_code_float(cursor, 0.0f);
}
void cycle(uint8_t **cursor) {
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

void setup() {
  Serial.begin(115200);
  Serial.println("STARTED");
  WiFi.begin(SSID, PSK);
  strip.Begin();
  trippy(&cursor);
  for (uint8_t *c = program; c != cursor; c++) {
    Serial.printf("\\x%02x", *c);
  }
  Serial.printf("\n");

}

void loop() {
  if (WiFi.status() == WL_CONNECTED)  {
    if (!connected) {
      udp.begin(port);
      Serial.println(WiFi.localIP());
      connected = true;
    }
    int numread = udp.parsePacket();
    // if a packet is received, we change the program
    if (numread > 0 && numread < ProgramSize) { 
      memset(program, 0, ProgramSize);
      udp.read(program, ProgramSize);
      cursor = program + numread;
    }
  }

  float time_seconds = millis() / 1000.0f;
  for (uint16_t i = 0; i < PixelCount; i++) {
    program_stack[0] = time_seconds;
    program_stack[1] = i;
    float *stack_pointer = program_stack + 2;
    HsbColor color = run_program(program, cursor, &stack_pointer);
    RgbColor rgb = RgbColor(color);
    strip.SetPixelColor(i, colorGamma.Correct(rgb));
  }
  strip.Show();
}
