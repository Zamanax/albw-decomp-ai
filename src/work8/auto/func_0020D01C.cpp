extern "C" void func_0020D020();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0020D01C() { func_0020D020(); }
