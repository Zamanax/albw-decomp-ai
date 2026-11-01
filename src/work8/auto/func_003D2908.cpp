extern "C" void func_003D290C();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_003D2908() { func_003D290C(); }
