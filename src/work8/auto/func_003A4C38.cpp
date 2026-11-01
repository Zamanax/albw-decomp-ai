extern "C" void func_003A4C3C();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_003A4C38() { func_003A4C3C(); }
