# Led Light  Virtual Machine

Led Light Virtual Machine (tongue in cheek, LLVM for short)
is a minimal virtual machine for writing animations for led strips.


## Machines
```
typedef f32le < a little endian IEEE 32 bit float>
stack : List f32le
opcode : u8
```

## Instruction set

### BRK
* opcode : `00`
* args : `none`
* behaviour:  stops execution

### LDC
* opcode : `01`
* args: `c : f32le`
* behaviour:
  ```
  ldc c stack = c : stack
  ```

### LDS
* opcode: `02`
* args: `offset : ptrdiff_t`
* behaviour:
  ```
  lds offset stack = (stack ! offset) : stack
  ```
### POP
* opcode: `02`
* args: `none`
* behaviour:
  ```
  pop (_:stack) = stack
  ```
### ADD
* opcode: `02`
* args: `none`
* behaviour:
  ```
  add (x:y:stack) = (x+y):stack
  ```
### SUB
* opcode: `02`
* args: `none`
* behaviour:
  ```
  sub (x:y:stack) = (x-y):stack
  ```
### MUL
* opcode: `02`
* args: `none`
* behaviour:
  ```
  sub (x:y:stack) = (x*y):stack
  ```
### DIV
### SIN
### MIN
### HSB
* opcode: `00`
* args: `none`
* behaviour:
  ```
  hsb (r:g:b:stack) = let (h,s,b) = rgb2hsb(r,g,b) in h:s:v:stack
  ```
### HSL
* opcode: `00`
* args: `none`
* behaviour:
  ```
  hsb (r:g:b:stack) = let (h,s,b) = rgb2hsl(r,g,b) in h:s:v:stack
  ```
### RGB
* opcode: `00`
* args: `none`
* behaviour:
  ```
  rgb stack = stack
  ```
