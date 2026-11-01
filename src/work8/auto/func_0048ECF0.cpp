extern "C" void func_0048ECF4();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0048ECF0() { func_0048ECF4(); }
