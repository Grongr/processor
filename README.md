### Processor

This project is using `stack` https://github.com/Grongr/protected_stack from  repository and `textio` library from https://github.com/Grongr/oneginsort.

It has assembler, disassembler and compiler. To write program on my language use commands from the list below.

* Input-output commands:
  * `in` - It gets one number from standard stream and writes it in stack of values.
  * `out` - it puts top value of stack in standard output.
* Stack commands:
  * `push <a>` - puts `<a>` in stack. `<a>` could be constant value, register name or combination of it. If you wanna use RAM you can simply use `[<a>]` expression.
  * `pop <a = NULL>` - gets from stack it's top element and deletes it from stack. If it has no parameters only deletes. Otherwise writes top element in register which name could be in `<a>` option.
* Mathematical options:
  * `sum` - sums two top values from stack.
  * `mul` - multiplies two top values from stack.
  * `div` - divides two top values from stack.
* End of program command:
  * `ippon` - means end of program, all the next commands will be ignored.

To simply compile all the stuff use `cmake` and `make` commands with `CMakeLists.txt` file from repository.

For example: 

```bash
mkdir cmake-build
cd cmake-build
cmake ..
make
```

And after that you can run programs you need to run with commands:

```bash
./ass filename.sht
./dis filename.asm
./cml filename.asm
```

Or with only one script `run.sh filename.sht`.

And now, lets code!

![](./img/cat_coding.jpeg)
